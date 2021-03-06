
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

   /*Link up the two main timers to the change slide and change clocks functions
   * timerWebSlide triggers when the sile should be changed
   * timerClock triggers when the time display on the menu bar should be updated
   */

   connect(&timerWebSlide, SIGNAL(timeout()), this, SLOT(changeSlide()));
   connect(&timerClock,SIGNAL(timeout()), this, SLOT(updateClocks()));



   /* Loads up all the staticly defined UI elements
    * The main window is the only item we need but we have to give it a default view
    * so we create a DefaultWebView that we will replace later on
    */
   ui->setupUi(this);
   ui->DefaultWebView->hide(); // Hide the defaul webView  show it later in the function

   //The main window goes to full screen mode by default
   this->changeFullScreenMode();

  QIcon icon;
  icon.setThemeName("gnome");

   qDebug() << "wsss/mainwindow.cpp-QIconThemePath:" << icon.themeSearchPaths();
   qDebug() << "wsss/mainwindow.cpp-QIcon:" << icon.themeName();

   /*Now create the toolbar -
   *
   * The toolbar has :  a number of navigation buttons
   *                    UTC and Local time
   *                    Progress bar showing how many second left on the current slide
   */

   ui->mainToolBar->addAction(icon.fromTheme("view-fullscreen"),"Fullscreen toggle",this,SLOT(changeFullScreenMode()));

   ui->mainToolBar->addSeparator();


   ui->mainToolBar->addAction(icon.fromTheme("go-previous"),"Back",this,SLOT(changeSlideBack()));
   ui->mainToolBar->addAction(icon.fromTheme("go-next"),"Forward",this,SLOT(changeSlideForward()));


   action_paused = ui->mainToolBar->addAction(icon.fromTheme("media-playback-start"),"Pause",this,SLOT(setPaused()));
   action_resume = ui->mainToolBar->addAction(icon.fromTheme("media-playback-stop"),"Resume",this,SLOT(setResume()));

   timeUTC = new QLabel;
   timeLMT = new QLabel;

   QFont font = timeUTC->font ();
   font.setPointSize(20);//set the font size here
   timeUTC->setFont(font);

   font = timeLMT->font ();
   font.setPointSize(20);//set the font size here
   timeLMT->setFont(font);


   ui->mainToolBar->addWidget(timeUTC);
   ui->mainToolBar->addWidget(timeLMT);

   ui->mainToolBar->addSeparator();
   timeRemainingBar = new QProgressBar;
   timeRemainingBar->setFormat("%v");


   ui->mainToolBar->addWidget(timeRemainingBar);

   //Setup the DefaultWebView
   ui->DefaultWebView->setZoomFactor(1.0);

   current_webslide_index = 0;

   updateClocks();

}

/******************************************************************************
 *
 *              MainWindow::loadSettingsFromFile()
 *
 ******************************************************************************
 */

void MainWindow::loadSettingsFromFile()
{
QString stringFileContents;
QFile file;
file.setFileName(SettingsFilePath);
qDebug() << "wsss/mainwindow.cpp-SettingsFilePath:" << SettingsFilePath;

file.open(QIODevice::ReadOnly | QIODevice::Text);
stringFileContents = file.readAll();
file.close();

//Create a json object from the file contents
//If there are any failures, this code will return.

QJsonDocument js_doc = QJsonDocument::fromJson(stringFileContents.toUtf8());

    if (js_doc.isNull()) {
                            this->loadDefaultSettings();
                            return;
                         };

QJsonObject js_webslide = js_doc.object();

    if (js_webslide.isEmpty())  {
                                this->loadDefaultSettings();
                                return;
                                };

QJsonArray js_webslide_array = js_webslide.find("webslides").value().toArray();

    if (js_webslide_array.isEmpty()) {
                                     this->loadDefaultSettings();
                                     return;
                                     };




/* If we have got this far then we have valid data from the file
 * so it is safe to wipe the webslide list and insert the new slides
 */
list_webslide.clear();


//Object to hold  the incomming settings
//Its values will be copied into a new object on the list_webslides
WebSlide webslide;


for (int index =0; index < js_webslide_array.count(); index ++)
    {
    QJsonValueRef js_webslide_data =  js_webslide_array[index];
    webslide.setName(js_webslide_data.toObject().find("name").value().toString());
    webslide.setUrl(js_webslide_data.toObject().find("url").value().toString());
    webslide.setShowTime(js_webslide_data.toObject().find("showtime").value().toDouble());
    webslide.setZoomRatio(js_webslide_data.toObject().find("zoomratio").value().toDouble());
    webslide.setRefreshTime(js_webslide_data.toObject().find("refreshtime").value().toDouble());

    list_webslide.append(webslide);
    }

 this->createWebSlideViews();
 this->changeSlide(true);
}

/******************************************************************************
 *
 *              MainWindow::loadDefaultSettings()
 *
 ******************************************************************************
 */

void MainWindow::loadDefaultSettings()
{
    /* If the settings file could not be loaded, these are the default
     * webslides that will be loaded instead
     */

    /* Object to hold  the incomming settings
     * Its values will be copied into a new object on the list_webslides
     */

    WebSlide webslide;

    list_webslide.clear();


    webslide.setUrl("http://json.parser.online.fr/");
    webslide.setShowTime(15000);
    webslide.setZoomRatio(0.5);
    webslide.setRefreshTime(10*60*1000);

    list_webslide.append(webslide);

    webslide.setUrl("file://readme.html");
    webslide.setShowTime(15000);
    webslide.setZoomRatio(0.8);
    webslide.setRefreshTime(10*60*1000);

    list_webslide.append(webslide);

    webslide.setUrl("http://www.bom.gov.au/products/IDR024.loop.shtml#skip/");
    webslide.setShowTime(15000);
    webslide.setZoomRatio(0.8);
    webslide.setRefreshTime(10*60*1000);

    list_webslide.append(webslide);

    webslide.setUrl("file:///home/harrisonheli/bom-wx/bom-taf-ymmb-ymen.html");
    webslide.setShowTime(20000);
    webslide.setZoomRatio(0.7);
    webslide.setRefreshTime(10*60*1000);

    list_webslide.append(webslide);


    this->createWebSlideViews();
    this->changeSlide(true);
}

/******************************************************************************
 *
 *              MainWindow::createWebSlides()
 *
 ******************************************************************************
 */
void MainWindow::createWebSlideViews()
{
    /* todo: remove existing webslideviews */

    for (int index =0; index < list_webslide.count(); index ++)
        {
        WebSlideView *new_webview = new WebSlideView();

        //So we can call the webview when we need it
        QString newObjectName = QString("webview") + QString::number(index);

        new_webview->setObjectName(newObjectName);

        // The line below seams to seg fault the app.
        // new_webview->setUrl(list_webslide[index].getUrl());

        // This does not seam to cause crashes.
        new_webview->load(list_webslide[index].getUrl());


        new_webview->setZoomFactor(list_webslide[index].getZoomRatio());

        new_webview->startTimer(list_webslide[index].getRefreshTime());

        new_webview->hide();

        ui->centralWidget->layout()->addWidget(new_webview);
        }
}


//****************************************************************
//
//      keyPressEvent
//
//****************************************************************
/*
 * This function is called when any key is pressed
 * and the main window has user focus.
 *
 */
void MainWindow::keyPressEvent( QKeyEvent* event ) {
    switch ( event->key() ) {
    case Qt::Key_Escape:    changeFullScreenMode(); break;

    case Qt::Key_F11:       changeFullScreenMode(); break;

    case Qt::Key_Right:     changeSlideForward(); break;

    case Qt::Key_Left:      changeSlideBack(); break;

    case Qt::Key_P:         setPauseOrResume(); break;

    case Qt::Key_Space:     setPauseOrResume(); break;

    case Qt::Key_F2:        zoomIn(); break;

    case Qt::Key_F3:        zoomOut(); break;

    default:
        event->ignore();
        break;
    }
}

//These are wrapper functions so the the key press actions can call them directly
// and not have to pass parameters to indicate the direction requred.

void MainWindow::changeSlideForward(){changeSlide(true);}

void MainWindow::changeSlideBack(){changeSlide(false);}

//******************************************************************************
//
//  changeSlide
//
//******************************************************************************
/*
 * Will work out what which webslide to show next and setup the timers
 *
 */
void MainWindow::changeSlide(bool go_forward)
{
    timerWebSlide.stop();

    int webslide_to_show_index;

    if(go_forward)
        {
         if (current_webslide_index >= list_webslide.count() - 1)
            { webslide_to_show_index = 0; }

         else webslide_to_show_index = current_webslide_index + 1;
        }
    else    //go back
        {
        if (current_webslide_index == 0)
            { webslide_to_show_index = list_webslide.count() -1; }
         else  webslide_to_show_index = current_webslide_index -1;
        }


    unsigned int timeout = list_webslide[webslide_to_show_index].getShowTime();
    timerWebSlide.start(timeout);

    timeRemainingBar->setValue(0);
    timeRemainingBar->setMaximum(timeout);


    QString name = QString("wsss - ") + list_webslide[webslide_to_show_index].getName() + QString(" - ") + list_webslide[webslide_to_show_index].getUrl();
    this->setWindowTitle(name) ;

    WebSlideView *currentWebSlideView;
    WebSlideView *nextWebSlideView;
    QString nameWebSlideView;


    nameWebSlideView = QString("webview")  + QString::number(current_webslide_index);
    currentWebSlideView = ui->centralWidget->findChild < WebSlideView *>(nameWebSlideView);

    nameWebSlideView = QString("webview") + QString::number(webslide_to_show_index);
    nextWebSlideView = ui->centralWidget->findChild < WebSlideView *>(nameWebSlideView);

    currentWebSlideView->hide();
    nextWebSlideView->show();
    nextWebSlideView->setFocus();

    current_webslide_index = webslide_to_show_index;
    setResume();
}


void MainWindow::changeFullScreenMode()
{
    if (this->isFullScreen())
        {
        this->showMaximized();
        ui->mainToolBar->show();
        }
    else
        {
        this->showFullScreen();
        //ui->mainToolBar->hide();
        }
}


void MainWindow::setPauseOrResume()
{
    if (!paused) setPaused();
    else setResume();
}


void MainWindow::setPaused()
{
    paused = true;
    timerWebSlide.stop();
    action_paused->setEnabled(false);
    action_paused->setVisible(false);
    action_resume->setEnabled(true);
    action_resume->setVisible(true);
}

void MainWindow::setResume()
{
    paused = false;
    timerWebSlide.start();
    action_resume->setEnabled(false);
    action_resume->setVisible(false);
    action_paused->setEnabled(true);
    action_paused->setVisible(true);
}


void MainWindow::zoomIn()
{
    WebSlideView *currentWebView;
    QString nameWebView;

    nameWebView = QString("webview") + QString::number(current_webslide_index);
    currentWebView = ui->centralWidget->findChild< WebSlideView *>(nameWebView);

    currentWebView->setZoomFactor(currentWebView->zoomFactor() * 1.1);

}

void MainWindow::zoomOut()
{

    WebSlideView *currentWebView;
    QString nameWebView;

    nameWebView = QString("webview") + QString::number(current_webslide_index);
    currentWebView = ui->centralWidget->findChild< WebSlideView *>(nameWebView);

    currentWebView->setZoomFactor(currentWebView->zoomFactor() * 0.9);


}

void MainWindow::updateClocks()
{
    timerClock.setSingleShot(true);
    timerClock.start(1000);

    QDateTime utc_date_time = QDateTime::currentDateTimeUtc();
    QDateTime local_date_time = QDateTime::currentDateTime();


    timeUTC->setText(utc_date_time.toString(" dd-hh:mm:ss") + " UTC ");
    timeLMT->setText(local_date_time.toString(" dd-hh:mm:ss") + " LMT ");

    timeRemainingBar->setValue(timeRemainingBar->value() + 1000);

}


MainWindow::~MainWindow()
{
    delete ui;
}
