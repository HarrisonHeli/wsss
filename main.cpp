#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    // Look to see if a webslide settings file has been givn on the command line


    if (argc >= 2)
        {
        w.SettingsFilePath = argv[1];
        }

    w.show();
    
    return a.exec();
}
