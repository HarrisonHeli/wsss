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

// Prevents a web page from being shown for too short a period
// Currently set to 1 second
    #define MIN_SHOW_TIME 1000


// Prevents a web page from being refeshed to often, eating up data and causing dns attack on a server.
// Currently set to 5 min
    #define MIN_REFESH_TIME 5*60000

// Prevents the web page from being too small or zero and crashing the program
    #define MIN_ZOOM_RATIO 0.1

public:
    WebSlide();                                // Creates a webslide with default settings
    WebSlide(const WebSlide& source_webslide); // Copies the settings from the source_webslide into this slide

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
