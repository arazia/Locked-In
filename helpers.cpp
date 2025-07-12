#include <helpers.h>
#include <QStandardPaths>
#include <QDir>

QString getSaveDirectory() {
    QString baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString saveDir = baseDir + "/locked_in/saves";
    QDir().mkpath(saveDir);
    return saveDir;
}
