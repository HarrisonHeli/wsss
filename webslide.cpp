#include "webslide.h"

webslide::webslide(QObject *parent) :
    QObject(parent)
{
}

void webslide::setUrl(const QString& new_url)
{
    string_url = new_url;
}

QString webslide::getUrl()
{
    return string_url;
}



void webslide::setShowTime(unsigned int new_show_time)
{
    show_time = new_show_time;
}

unsigned int webslide::getShowTime()
{
    return show_time;
}

void webslide::setZoomRatio(double new_zoom_ratio)
{
    zoom_ratio = new_zoom_ratio;

}

double webslide::getZoomRatio()
{
    return zoom_ratio;
}
