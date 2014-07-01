#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication WebSlideApplication(argc, argv);
    //All the code runs inside this object

    MainWindow WebSlideApplicationWindow;
    //all the visual stuff sits inside of this window object


    qDebug() << "wsss/main.cpp-App path: " << qApp->applicationDirPath();


   /* Loading Custom settings file
    *
    * 1) On startup we will check to see if a custom settings file has been given
    * The settings file will be in the json format
    *
    * A search on the internet will give tons of help with the josn format.
    * It is simmlar to XML format but without the complexity of parsing the data
    * I intend to change to XML in time.
    *
    * 2) If a custom file is not given on the command line, we will look for the default file
    * The default file is "settings.json"
    * and we will assume it is in the working path of the application
    *
    * 3) If no settings file is found we will create a default one and use it
    *
    * 4) If we cant create the file (read only system) used an internal set of webslides
    *
    */

    /* argc indicates how many arguments have been attached to the executable
     * ie. wsss settings.json would give us a value of 2, the executable
     * is treated as an argument
     *
     * argv[] is the list of arguments as strings and can be indexed.
     * indec 0 is the excecuitable string.
     *
     */


    if (argc >= 2) WebSlideApplicationWindow.SettingsFilePath = argv[1];
        else
            WebSlideApplicationWindow.SettingsFilePath = "";


    WebSlideApplicationWindow.loadSettingsFromFile();


    WebSlideApplicationWindow.show();
    return WebSlideApplication.exec();
}
