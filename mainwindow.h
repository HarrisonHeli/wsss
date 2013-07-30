#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit>
#include <QFile>
#include <QJsonDocument>

#include"webslide.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void loadUrl(const QUrl& url);


private:
    Ui::MainWindow *ui;
    QList<WebSlide> list_webslide;
    unsigned int next_webslide;

    void loadUrlFromFile();


private slots:
    void changeSlide();


};

#endif // MAINWINDOW_H
