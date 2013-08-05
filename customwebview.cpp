#include "customwebview.h"

CustomWebView::CustomWebView(QWidget *parent) :
    QWebView(parent)
{
}

 void CustomWebView::timerEvent(QTimerEvent *event)
 {
     //QPoint currentPosition;
     //currentPosition = this->page()->mainFrame()->scrollPosition();
     this->reload();
     //this->scroll(currentPosition.rx(),currentPosition.ry);
 }
