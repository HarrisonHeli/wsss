#ifndef WEBSLIDE_H
#define WEBSLIDE_H

#include <QObject>

class webslide : public QObject
{
    Q_OBJECT

    QString string_url;
    unsigned int show_time;
    double zoom_ratio;

public:
    explicit webslide(QObject *parent = 0);

    void setUrl(const QString& new_url);
    QString getUrl();

    void setShowTime(unsigned int new_show_time);
    unsigned int getShowTime();

    void setZoomRatio(double new_zoom_ratio);
    double getZoomRatio();
    
signals:
    
public slots:
    
};

#endif // WEBSLIDE_H
