#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qssFile(":/styles/aqua.qss");

    if (qssFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = qssFile.readAll();
        a.setStyleSheet(style);
        qssFile.close();
    } else {
        qWarning("Could not load stylesheet");
    }

    MainWindow w;
    w.show();
    return a.exec();
}
