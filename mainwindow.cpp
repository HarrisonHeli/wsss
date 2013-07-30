
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   this->showMaximized();

   //Setup the toolbar
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Back));
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Forward));
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Reload));
   ui->mainToolBar->addAction(ui->webView->pageAction(QWebPage::Stop));

   //Setup the webView
   ui->webView->setZoomFactor(1.0);

   next_webslide = 0;

   WebSlide webslide;
   webslide.setUrl("http://www.bom.gov.au/vic/forecasts/melbourne.shtml");
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
   changeSlide();


}

void MainWindow::loadUrlFromFile()
{
QString settings;
QFile file;
file.setFileName("/home/harrisonheli/settings.json");
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



void MainWindow::loadUrl(const QUrl &url)
{
    //This will load the comand line given url
    ui->webView->load(url);
}


void MainWindow::changeSlide()
{
    if (next_webslide >= list_webslide.count())
        {
        next_webslide = 0;
        }

    ui->webView->hide();
    ui->webView->load(QUrl::fromUserInput(list_webslide[next_webslide].getUrl()));
    ui->webView->setZoomFactor(list_webslide[next_webslide].getZoomRatio());
    unsigned int timeout = list_webslide[next_webslide].getShowTime();


    QString name = QString("wsss - ") + list_webslide[next_webslide].getName() + QString(" - ") + list_webslide[next_webslide].getUrl();
    this->setWindowTitle(name) ;

    QTimer::singleShot(timeout, this, SLOT(changeSlide()));

    next_webslide ++;
    ui->webView->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}
