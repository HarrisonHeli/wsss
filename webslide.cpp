#include "webslide.h"

WebSlide::WebSlide()
{
}

WebSlide::WebSlide(const WebSlide& ori_webslide)
{

    this->setName(ori_webslide.string_name);
    this->setUrl(ori_webslide.string_url);
    setShowTime(ori_webslide.show_time);
    setZoomRatio(ori_webslide.zoom_ratio);
}


void WebSlide::setName(const QString& new_name)
{
    string_name = new_name;
}

QString WebSlide::getName()
{
    return string_name;
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
