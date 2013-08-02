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
    void keyPressEvent( QKeyEvent* event );

private:
    Ui::MainWindow *ui;
    QList<WebSlide> list_webslide;

    int current_webslide_index;


    QTimer timerWebSlide;

    void loadUrlFromFile();
    void createWebSlides();

    void changeFullScreenMode();

    void changeSlideForward();
    void changeSlideBack();


private slots:
    void changeSlide(bool go_forward = true);



};

#endif // MAINWINDOW_H
