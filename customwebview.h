#ifndef CUSTOMWEBVIEW_H
#define CUSTOMWEBVIEW_H

#include <QWebView>

class CustomWebView : public QWebView
{
    Q_OBJECT
public:
    explicit CustomWebView(QWidget *parent = 0);
    void timerEvent(QTimerEvent *event);
    
signals:
    
public slots:
    
};

#endif // CUSTOMWEBVIEW_H
