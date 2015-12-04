#include "webslideview.h"

WebSlideView::WebSlideView(QWidget *parent) :
    QWebView(parent)
{
}

 void WebSlideView::timerEvent(QTimerEvent *event)
 {

     qDebug() << "wsss/webslideview.cpp : Reloading page -> " << this->url();
     this->reload();

     /* This code is not working yet
      * I want to track the scrolled position of the web page so that
      * when the page refreshed the webslideview will scroll back to where
      * it was left off
      */

     //QPoint currentPosition;
     //currentPosition = this->page()->mainFrame()->scrollPosition();

     //this->scroll(currentPosition.rx(),currentPosition.ry);


 }
