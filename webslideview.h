#ifndef WEBSLIDEVIEW_H
#define WEBSLIDEVIEW_H

#include <QWebView>

class WebSlideView : public QWebView
{
    Q_OBJECT
public:
    explicit WebSlideView(QWidget *parent = 0);
    void timerEvent(QTimerEvent *event);
    
signals:
    
public slots:
    
};

#endif // WEBSLIDEVIEW_H
