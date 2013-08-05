
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

   connect(&timerWebSlide, SIGNAL(timeout()), this, SLOT(changeSlide()));
   connect(&timerClock,SIGNAL(timeout()), this, SLOT(updateClocks()));

   ui->setupUi(this);
   ui->webView->hide();

   changeFullScreenMode();

   //Setup the toolbar

   ui->mainToolBar->addAction(QIcon::fromTheme("view-fullscreen"),"Fullscreen toggle",this,SLOT(changeFullScreenMode()));

   ui->mainToolBar->addSeparator();

   ui->mainToolBar->addAction(QIcon::fromTheme("go-previous"),"Back",this,SLOT(changeSlideBack()));
   ui->mainToolBar->addAction(QIcon::fromTheme("go-next"),"Forward",this,SLOT(changeSlideForward()));


   action_paused = ui->mainToolBar->addAction(QIcon::fromTheme("media-playback-start"),"Pause",this,SLOT(setPaused()));
   action_resume = ui->mainToolBar->addAction(QIcon::fromTheme("media-playback-stop"),"Resume",this,SLOT(setResume()));

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

   //Setup the webView
   ui->webView->setZoomFactor(1.0);

   current_webslide_index = 0;

   WebSlide webslide;
   webslide.setUrl("http://json.parser.online.fr/");
   webslide.setShowTime(15000);
   webslide.setZoomRatio(0.5);
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

   webslide.setUrl("https://docs.google.com/spreadsheet/pub?key=0Ag-DRZCGuBxFdGRFTFE5SEpFbUIxZ3NDYUpjOU5lR0E&output=html");
   webslide.setShowTime(20000);
   webslide.setZoomRatio(1);
   webslide.setRefreshTime(10*60*1000);

   list_webslide.append(webslide);

   updateClocks();
   setResume();

   loadUrlFromFile();
   createWebSlides();
   changeSlide(true);


}

void MainWindow::loadUrlFromFile()
{
QString settings;
QFile file;
file.setFileName("settings.json");
file.open(QIODevice::ReadOnly | QIODevice::Text);
settings = file.readAll();
file.close();

QJsonDocument js_doc = QJsonDocument::fromJson(settings.toUtf8());

    if (js_doc.isNull()) return;

QJsonObject js_webslide = js_doc.object();

    if (js_webslide.isEmpty()) return;

QJsonArray js_webslide_array = js_webslide.find("webslides").value().toArray();

    if (js_webslide_array.isEmpty()) return;

WebSlide webslide;
list_webslide.clear();

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
}

void MainWindow::createWebSlides()
{
    for (int index =0; index < list_webslide.count(); index ++)
        {
        QWebView *new_webview = new QWebView();

        //So we can call the webview when we need it
        QString newObjectName = QString("webview") + QString::number(index);

        new_webview->setObjectName(newObjectName);

        new_webview->setUrl(list_webslide[index].getUrl());
        new_webview->setZoomFactor(list_webslide[index].getZoomRatio());

        new_webview->hide();

        ui->centralWidget->layout()->addWidget(new_webview);
        }
}

void MainWindow::loadUrl(const QUrl &url)
{
    //This will load the comand line given url
    ui->webView->load(url);
}

void MainWindow::keyPressEvent( QKeyEvent* event ) {
    switch ( event->key() ) {
    case Qt::Key_Escape:    changeFullScreenMode(); break;

    case Qt::Key_F11:       changeFullScreenMode(); break;

    case Qt::Key_Right:     changeSlideForward(); break;

    case Qt::Key_Left:     changeSlideBack(); break;

    case Qt::Key_P: setPauseOrResume(); break;

    case Qt::Key_Space: setPauseOrResume(); break;

    case Qt::Key_F2: zoomIn(); break;

    case Qt::Key_F3: zoomOut(); break;

    default:
        event->ignore();
        break;
    }
}


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


    QString name = QString("wsss - ") + list_webslide[webslide_to_show_index].getName() + QString(" - ") + list_webslide[webslide_to_show_index].getUrl();
    this->setWindowTitle(name) ;

    QWebView *currentWebView;
    QWebView *nextWebView;
    QString nameWebView;


    nameWebView = QString("webview")  + QString::number(current_webslide_index);
    currentWebView = ui->centralWidget->findChild<QWebView *>(nameWebView);

    nameWebView = QString("webview") + QString::number(webslide_to_show_index);
    nextWebView = ui->centralWidget->findChild<QWebView *>(nameWebView);

    currentWebView->hide();
    currentWebView->reload();

    nextWebView->show();
    nextWebView->setFocus();

    current_webslide_index = webslide_to_show_index;
    setResume();


}

//These are wrapper functuins so the the key press actionscan call them directly
// and not have to pass parameters to indicate the direction requred.

void MainWindow::changeSlideForward(){changeSlide(true);}

void MainWindow::changeSlideBack(){changeSlide(false);}



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


void MainWindow::updateClocks()
{
timerClock.setSingleShot(true);
timerClock.start(1000);

QDateTime utc_date_time = QDateTime::currentDateTimeUtc();

QDateTime local_date_time = QDateTime::currentDateTime();



timeUTC->setText(utc_date_time.toString(" dd-hh:mm:ss") + " UTC ");

timeLMT->setText(local_date_time.toString(" dd-hh:mm:ss") + " LMT ");

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
    QWebView *currentWebView;
    QString nameWebView;

    nameWebView = QString("webview") + QString::number(current_webslide_index);
    currentWebView = ui->centralWidget->findChild<QWebView *>(nameWebView);

    currentWebView->setZoomFactor(currentWebView->zoomFactor() * 1.1);

}

void MainWindow::zoomOut()
{

    QWebView *currentWebView;
    QString nameWebView;

    nameWebView = QString("webview") + QString::number(current_webslide_index);
    currentWebView = ui->centralWidget->findChild<QWebView *>(nameWebView);

    currentWebView->setZoomFactor(currentWebView->zoomFactor() * 0.9);


}


MainWindow::~MainWindow()
{
    delete ui;
}
