#include "webslide.h"

WebSlide::WebSlide()
{
}

WebSlide::WebSlide(const WebSlide& ori_webslide)
{

    this->setName(ori_webslide.string_name);
    this->setUrl(ori_webslide.string_url);
    setShowTime(ori_webslide.show_time);
    setRefreshTime(ori_webslide.refresh_time);
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
    if (new_show_time <= 1000) show_time = 1000;
    else show_time = new_show_time;
}

unsigned int WebSlide::getShowTime()
{
    return show_time;
}

void WebSlide::setZoomRatio(double new_zoom_ratio)
{
    if (new_zoom_ratio == 0) zoom_ratio = 0.1;
    else zoom_ratio = new_zoom_ratio;
}

double WebSlide::getZoomRatio()
{
    return zoom_ratio;
}

void WebSlide::setRefreshTime(unsigned int new_refresh_time)
{
    if (new_refresh_time <= 60*1000) refresh_time = 5*60*1000;
    else refresh_time = new_refresh_time;
}
unsigned int WebSlide::getRefreshTime()
{
    return refresh_time;
}
