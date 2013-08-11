#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // Look to see if a webslide settings file has been givn on the command line

    if (argc == 1)
        QString SettingsFilePath= argv[1];


    MainWindow w;

    w.show();
    
    return a.exec();
}
