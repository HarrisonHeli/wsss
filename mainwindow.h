#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit>
#include <QFile>
#include <QJsonDocument>
#include <QLCDNumber>
#include <QLabel>

#include "webslide.h"
#include "customwebview.h"

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
    bool paused;
    QAction *action_paused;
    QAction *action_resume;

    QTimer timerWebSlide;
    QTimer timerClock;

    QLabel *timeUTC;
    QLabel *timeLMT;

    void loadUrlFromFile();
    void createWebSlides();

private slots:

    void changeFullScreenMode();

    void changeSlide(bool go_forward = true);

    void changeSlideForward();
    void changeSlideBack();

    void updateClocks();
    void setPauseOrResume();
    void setPaused();
    void setResume();

    void zoomIn();
    void zoomOut();

};

#endif // MAINWINDOW_H
