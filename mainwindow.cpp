
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
   ui->webView->setZoomFactor(0.7);

}


void MainWindow::loadUrl(const QUrl &url)
{
    //This will load the comand line given url
    ui->webView->load(url);
}

MainWindow::~MainWindow()
{
    delete ui;
}
