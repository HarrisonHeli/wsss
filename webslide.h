#ifndef WEBSLIDE_H
#define WEBSLIDE_H
#include <QString>

class WebSlide
{
    QString string_name;
    QString string_url;
    unsigned int show_time;
    unsigned int refresh_time;
    double zoom_ratio;

public:
    WebSlide();
    WebSlide(const WebSlide& ori_webslide);

    void setName(const QString& new_name);
    QString getName();

    void setUrl(const QString& new_url);
    QString getUrl();

    void setShowTime(unsigned int new_show_time);
    unsigned int getShowTime();

    void setZoomRatio(double new_zoom_ratio);
    double getZoomRatio();
    
    void setRefreshTime(unsigned int new_refresh_time);
    unsigned int getRefreshTime();

    
};

#endif // WEBSLIDE_H
