#include <QApplication>
#include "mainwindow.h"
#include <QCommandLineParser>

#include <iostream>

// global debugging mode status
bool IS_DEBUG_MODE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCommandLineParser parser;
    parser.addHelpOption();

    // A boolean option with a single name (-d)
    QCommandLineOption debugModeOption(QStringList() << "d" << "debug", QCoreApplication::translate("main", "Enter debug mode"));
    parser.addOption(debugModeOption);

    parser.process(a);

    IS_DEBUG_MODE = parser.isSet(debugModeOption);

    // We cannot use w.showFullscreen() here because on Linux that creates the
    // window behind all other windows, so we have to set it to fullscreen after
    // it has been shown. 
    w.show();
    //w.setWindowState(w.windowState() | Qt::WindowFullScreen); // Comment out this line to have a windowed 800x600 game on startup.

    return a.exec();
}

