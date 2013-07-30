
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
   ui->setupUi(this);

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


   changeSlide();

   //loadUrl(QUrl::fromUserInput(list_webslide.first().getUrl()));

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

    loadUrl(QUrl::fromUserInput(list_webslide[next_webslide].getUrl()));
    ui->webView->setZoomFactor(list_webslide[next_webslide].getZoomRatio());
    unsigned int timeout = list_webslide[next_webslide].getShowTime();


    QTimer::singleShot(timeout, this, SLOT(changeSlide()));

    next_webslide ++;
}

MainWindow::~MainWindow()
{
    delete ui;
}
