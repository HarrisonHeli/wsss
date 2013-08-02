
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
   connect(&timerWebSlide, SIGNAL(timeout()), this, SLOT(changeSlide()));

   ui->setupUi(this);
   ui->webView_2->hide();
   ui->webView->hide();

   changeFullScreenMode();


   //Setup the toolbar
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Back));
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Forward));
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Reload));
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Stop));

   //Setup the webView
   ui->webView->setZoomFactor(1.0);

   current_webslide_index = 0;

   WebSlide webslide;
   webslide.setUrl("http://json.parser.online.fr/");
   webslide.setShowTime(15000);
   webslide.setZoomRatio(0.5);

   list_webslide.append(webslide);

   webslide.setUrl("http://www.bom.gov.au/products/IDR024.loop.shtml#skip/");
   webslide.setShowTime(15000);
   webslide.setZoomRatio(0.8);

   list_webslide.append(webslide);

   webslide.setUrl("file:///home/harrisonheli/bom-wx/bom-taf-ymmb-ymen.html");
   webslide.setShowTime(20000);
   webslide.setZoomRatio(0.7);

   list_webslide.append(webslide);

   webslide.setUrl("https://docs.google.com/spreadsheet/pub?key=0Ag-DRZCGuBxFdGRFTFE5SEpFbUIxZ3NDYUpjOU5lR0E&output=html");
   webslide.setShowTime(20000);
   webslide.setZoomRatio(1);

   list_webslide.append(webslide);

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

    current_webslide_index = webslide_to_show_index;


}

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
        ui->mainToolBar->hide();
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}
