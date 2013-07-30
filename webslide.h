#ifndef WEBSLIDE_H
#define WEBSLIDE_H
#include <QString>

class WebSlide
{

    QString string_url;
    unsigned int show_time;
    double zoom_ratio;

public:
    WebSlide();
    WebSlide(const WebSlide& ori_webslide);

    void setUrl(const QString& new_url);
    QString getUrl();

    void setShowTime(unsigned int new_show_time);
    unsigned int getShowTime();

    void setZoomRatio(double new_zoom_ratio);
    double getZoomRatio();
    
    
};

#endif // WEBSLIDE_H
