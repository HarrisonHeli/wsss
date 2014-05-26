#include "webslide.h"

WebSlide::WebSlide()
{
}

WebSlide::WebSlide(const WebSlide& source_webslide)
{

    this->setName(source_webslide.string_name);
    this->setUrl(source_webslide.string_url);
    setShowTime(source_webslide.show_time);
    setRefreshTime(source_webslide.refresh_time);
    setZoomRatio(source_webslide.zoom_ratio);

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
    if (new_show_time <= MIN_SHOW_TIME) show_time = MIN_SHOW_TIME;
    else show_time = new_show_time;
}

unsigned int WebSlide::getShowTime()
{
    return show_time;
}

void WebSlide::setZoomRatio(double new_zoom_ratio)
{
    if (new_zoom_ratio <= MIN_ZOOM_RATIO) zoom_ratio = MIN_ZOOM_RATIO; // if zero system will crash
    else zoom_ratio = new_zoom_ratio;
}

double WebSlide::getZoomRatio()
{
    return zoom_ratio;
}

void WebSlide::setRefreshTime(unsigned int new_refresh_time)
{
    if (new_refresh_time <= MIN_REFESH_TIME) refresh_time = MIN_REFESH_TIME; // Limit the minium refresh time, defined in webslide.h
    else refresh_time = new_refresh_time;
}
unsigned int WebSlide::getRefreshTime()
{
    return refresh_time;
}
