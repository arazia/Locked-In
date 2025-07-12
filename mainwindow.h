#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QDir>
#include <QSettings>
#include <QProcess>
#include <QStringList>
#include <QApplication>
#include <QKeyEvent>
#include <QListWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QHostInfo>
#include <windows.h>
#include <TlHelp32.h>
#include <gamestate.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameState gameState = GameState();

    void showMessage(const QString &title, const QString &msg, bool isError=false);
    void setUIControls(bool enabled);

    // slots
    void handleBrowseButton();

    void handleAddAppButton();
    void handleAdddnsButton();

    void handleDnsAddButton();
    void handleBlockAllButton();
    void handleUnblockAllButton();
    void handleBackupButton();
    void handleRestoreButton();

    void handleSave();
    void handleLoad();

    // file helpers
    QString getHostsPath();
    bool backupHosts(const QString &outPath);
    bool applyHostsBlock(const QStringList &hostnames);
    bool restoreHosts(const QString &inPath);

    // save states
    void saveBlocklistState(const QString& filePath);
    void loadBlocklistState(const QString& filePath);


};
#endif // MAINWINDOW_H
