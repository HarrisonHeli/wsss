#include "webslide.h"

WebSlide::WebSlide(QObject *parent) :
    QObject(parent)
{
}

void WebSlide::setUrl(const QString& new_url)
{
    string_url = new_url;
}

QString WebSlide::getUrl()
{
    return string_url;
}



void WebSlide::setShowTime(unsigned int new_show_time)
{
    show_time = new_show_time;
}

unsigned int WebSlide::getShowTime()
{
    return show_time;
}

void WebSlide::setZoomRatio(double new_zoom_ratio)
{
    zoom_ratio = new_zoom_ratio;

}

double WebSlide::getZoomRatio()
{
    return zoom_ratio;
}
