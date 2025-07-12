#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <helpers.h>

#include <thread>
#include "RegistryBlocker.h"  // BlockApp, UnblockApp, BackupRegistry, RestoreRegistry

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);;

    setWindowTitle("LockedIn");

    // ensures folders get created
    getSaveDirectory();

    //ui->statsTab = StatsTab(this->gameState.getSkills());
    ui->statsTab->loadSetup(this->gameState.getSkills());

    connect(ui->statsTab, &StatsTab::skillSelected, this, [this](const QString& skillName) {
        // Assuming your GameState has a method to set the active skill:
        ui->blockAllButton->setEnabled(!ui->statsTab->currentSkill().isEmpty());
        gameState.setActiveSkill(skillName);
    });


    ui->tabWidget->setTabText(0, tr("Skills"));
    ui->tabWidget->setTabText(1, tr("Apps to Block"));
    ui->tabWidget->setTabText(2, tr("Network Block"));
    ui->tabWidget->setTabText(3, tr("Controls"));

    ui->durationSpinBox->setMinimum(1);
    ui->durationSpinBox->setValue(30);

    ui->blockAllButton->setEnabled(!ui->statsTab->currentSkill().isEmpty());

    connect(ui->browseButton,    &QPushButton::clicked, this, &MainWindow::handleBrowseButton);
    connect(ui->pathLineEdit,  &QLineEdit::returnPressed, this, &MainWindow::handleAddAppButton);
    connect(ui->dnsLineEdit, &QLineEdit::returnPressed, this, &MainWindow::handleAdddnsButton);
    //connect(ui->addButton,       &QPushButton::clicked, this, &MainWindow::handleAddButton);
    //connect(ui->dnsAddButton,    &QPushButton::clicked, this, &MainWindow::handleDnsAddButton);
    connect(ui->blockAllButton,  &QPushButton::clicked, this, &MainWindow::handleBlockAllButton);
    connect(ui->unblockAllButton,&QPushButton::clicked, this, &MainWindow::handleUnblockAllButton);
    connect(ui->backupButton,    &QPushButton::clicked, this, &MainWindow::handleBackupButton);
    connect(ui->restoreButton,   &QPushButton::clicked, this, &MainWindow::handleRestoreButton);

    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::handleSave);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::handleLoad);

    connect(ui->appListWidget, &QListWidget::itemDoubleClicked, this, [=]() {
        QList<QListWidgetItem*> selected = ui->appListWidget->selectedItems();
        for (QListWidgetItem* item : selected) {
            delete ui->appListWidget->takeItem(ui->appListWidget->row(item));
        }
    });

    connect(ui->dnsListWidget, &QListWidget::itemDoubleClicked, this, [=]() {
        QList<QListWidgetItem*> selected = ui->dnsListWidget->selectedItems();
        for (QListWidgetItem* item : selected) {
            delete ui->dnsListWidget->takeItem(ui->dnsListWidget->row(item));
        }
    });
}

MainWindow::~MainWindow()
{
    this->gameState.saveToDisk();
    delete ui;
}

void MainWindow::showMessage(const QString &title, const QString &msg, bool isError) {
    QMessageBox box(this);
    box.setWindowTitle(title);
    box.setText(msg);
    box.setIcon(isError ? QMessageBox::Critical : QMessageBox::Information);
    box.exec();
}

void MainWindow::setUIControls(bool enabled) {

    // TODO block choosing stats to train if possible
    ui->statsTab->toggleButtons(enabled);

    // block only vital tabs
    ui->tabWidget->setTabEnabled(1, enabled);
    ui->tabWidget->setTabEnabled(2, enabled);

    ui->appListWidget->setEnabled(enabled);
    ui->dnsListWidget->setEnabled(enabled);
    ui->durationSpinBox->setEnabled(enabled);
    ui->backupButton->setEnabled(enabled);
    ui->restoreButton->setEnabled(enabled);
    ui->blockAllButton->setEnabled(enabled);
    ui->unblockAllButton->setEnabled(!enabled); // Allow unblock
}



/**
 * Network Functions
*/
// THIS DOESNT WORK BECAUSE WEBSITES CACHE DNS AND IDK HOW TO WORK AROUND THAT
// QString MainWindow::getHostsPath() {
//     wchar_t sysPath[MAX_PATH];
//     GetSystemDirectoryW(sysPath, MAX_PATH);
//     return QString::fromWCharArray(sysPath) + "/drivers/etc/hosts";
// }

// bool MainWindow::backupHosts(const QString &outPath) {
//     QFile src(getHostsPath());
//     if (!src.exists()) return false;
//     return QFile::copy(getHostsPath(), outPath);
// }

// bool MainWindow::applyHostsBlock(const QStringList &hostnames) {
//     QFile file(getHostsPath());
//     if (!file.open(QIODevice::Append | QIODevice::Text)) {
//         qDebug() << "Failed to open hosts file for writing:" << file.errorString();
//         return false;
//     }
//     QTextStream out(&file);
//     for (const QString &host : hostnames) {
//         out << "127.0.0.1 " << host << '\n';
//     }
//     file.close();

//     system("ipconfig /flushdns");
//     return true;
// }

// bool MainWindow::restoreHosts(const QString &inPath) {
//     QFile dest(getHostsPath());
//     if (dest.exists()) dest.remove();
//     return QFile::copy(inPath, getHostsPath());
// }

// bool MainWindow::restoreHosts(const QString &inPath) {
//     QFile dest(getHostsPath());
//     if (dest.exists()) dest.remove();
//     return QFile::copy(inPath, getHostsPath());
// }

bool isWindowsFirewallEnabled() {
    QSettings firewallReg("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile", QSettings::NativeFormat);
    QVariant enabled = firewallReg.value("EnableFirewall");
    return enabled.isValid() && enabled.toInt() != 0;
}

QStringList resolveDomainsToIPs(const QStringList& domains) {
    QStringList resolvedIPs;
    for (const QString& domain : domains) {
        QHostInfo info = QHostInfo::fromName(domain);
        for (const QHostAddress& addr : info.addresses()) {
            if (addr.protocol() == QAbstractSocket::IPv4Protocol)
                resolvedIPs << addr.toString();
        }
    }
    return resolvedIPs;
}

void addFirewallBlockRules(const QStringList& hosts) {
    QStringList ips = resolveDomainsToIPs(hosts);
    for (const QString& ip : ips) {
        QString rule = "Block_" + ip;
        QString cmd = QString("netsh advfirewall firewall add rule name=\"%1\" dir=out action=block remoteip=%2 enable=yes").arg(rule, ip);
        QProcess::execute("cmd.exe", {"/c", cmd});
    }
}

void removeFirewallBlockRules(const QStringList& hosts) {
    QStringList ips = resolveDomainsToIPs(hosts);
    for (const QString& ip : ips) {
        QString rule = "Block_" + ip;
        QString cmd = QString("netsh advfirewall firewall delete rule name=\"%1\"").arg(rule);
        QProcess::execute("cmd.exe", {"/c", cmd});
    }
}



/**
 * Helpers for Handlers
*/
void closeBrowsersAndApps(const QStringList &extraProcesses) {
    QStringList processes = {
        "chrome.exe", "msedge.exe", "opera.exe", "brave.exe"
    };
    processes.append(extraProcesses);

    for (const QString &procName : processes) {
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap == INVALID_HANDLE_VALUE) continue;

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnap, &pe)) {
            do {
                if (_wcsicmp(pe.szExeFile, (wchar_t*)procName.utf16()) == 0) {
                    HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                    if (hProc) {
                        TerminateProcess(hProc, 0);
                        CloseHandle(hProc);
                        qDebug() << "Terminated" << procName;
                    } else {
                        qDebug() << "Failed to open" << procName;
                    }
                }
            } while (Process32Next(hSnap, &pe));
        }
        CloseHandle(hSnap);
    }
}


/**
 * Handlers
*/


void MainWindow::handleBrowseButton() {
    QString file = QFileDialog::getOpenFileName(
        this,
        tr("Select Executable"),
        QString(),
        tr("Executables (*.exe);;All Files (*)")
        );
    if (!file.isEmpty()) ui->pathLineEdit->setText(file);
}


void MainWindow::handleAddAppButton() {
    QString path = ui->pathLineEdit->text();
    if (!path.isEmpty()) {
        ui->appListWidget->addItem(path);
        ui->pathLineEdit->clear();
    }
}

void MainWindow::handleAdddnsButton() {
    QString host = ui->dnsLineEdit->text().trimmed();
    if (!host.isEmpty()) {
        ui->dnsListWidget->addItem(host);
        ui->dnsLineEdit->clear();
    }
}

void MainWindow::handleBlockAllButton() {
    if (ui->statsTab->currentSkill().isEmpty()) {
        QMessageBox::warning(this, "Select Skill", "Please select a skill to train before blocking.");
        return;
    }

    QStringList files;
    for (int i = 0; i < ui->appListWidget->count(); ++i)
        files << ui->appListWidget->item(i)->text();

    QStringList hosts;
    for (int i = 0; i < ui->dnsListWidget->count(); ++i)
        hosts << ui->dnsListWidget->item(i)->text();
    int seconds = ui->durationSpinBox->value() * 60;
    std::wstring regOut = QDir::temp().filePath("iefo_backup.reg").toStdWString();
    BackupRegistry(regOut);

    std::thread([=]() {
        setUIControls(false);
        QStringList appNames;
        for (const QString &path : files)
            appNames << QFileInfo(path).fileName();
        closeBrowsersAndApps(appNames);

        for (const QString &f : files) {
            bool ok = BlockApp(f.toStdWString());
            qDebug() << "Blocking" << f << (ok ? "succeeded" : "failed");
        }

        if (!isWindowsFirewallEnabled()) {
            QMessageBox::warning(this,
                QObject::tr("Firewall Disabled"),
                QObject::tr("Windows Firewall is disabled. Please enable it for network blocking to function."));
            return;
        }
        addFirewallBlockRules(hosts);
        this->gameState.lockedIn();
        std::this_thread::sleep_for(std::chrono::seconds(seconds));

        for (const QString &f : files) {
            bool ok = UnblockApp(f.toStdWString());
            qDebug() << "Unblocking" << f << (ok ? "succeeded" : "failed");
        }

        removeFirewallBlockRules(hosts);

        QMetaObject::invokeMethod(QApplication::instance(), [=]() {
            setUIControls(true);

            this->gameState.lockedOut(seconds);
            ui->statsTab->loadSetup(this->gameState.getSkills());

            showMessage(tr("Info"), tr("Timed block complete."));
        }, Qt::QueuedConnection);
    }).detach();

    showMessage(tr("Info"), tr("Timed block started."));
}

void MainWindow::handleUnblockAllButton() {
    // Immediate unblock
    for (int i = 0; i < ui->appListWidget->count(); ++i)
        UnblockApp(ui->appListWidget->item(i)->text().toStdWString());
    //restoreHosts(QDir::temp().filePath("hosts_backup"));

    // TODO change this to a .txt savefile
    QStringList hosts;
    for (int i = 0; i < ui->dnsListWidget->count(); ++i)
        hosts << ui->dnsListWidget->item(i)->text();
    removeFirewallBlockRules(hosts);

    gameState.lockedOut(ui->durationSpinBox->value());
    ui->statsTab->loadSetup(this->gameState.getSkills());

    setUIControls(true);
    showMessage(tr("Info"), tr("Instant unblock complete."));
}

void MainWindow::handleBackupButton() {
    std::wstring regOut = QDir::temp().filePath("iefo_backup.reg").toStdWString();
    bool okReg = BackupRegistry(regOut);
    showMessage(tr("Backup"), tr("Registry: %1").arg(okReg ? tr("OK") : tr("Fail")));
}

void MainWindow::handleRestoreButton() {
    std::wstring regIn = QDir::temp().filePath("iefo_backup.reg").toStdWString();
    int code = RestoreRegistry(regIn);
    bool okReg = (code == 0);
    showMessage(tr("Restore"), tr("Registry: %1").arg(okReg ? tr("OK") : tr("Fail")));
}


/**
 * Helper functions for below handlers
 */

void MainWindow::saveBlocklistState(const QString& filePath) {
    QJsonObject root;
    QJsonArray apps, dns;

    for (int i = 0; i < ui->appListWidget->count(); ++i)
        apps.append(ui->appListWidget->item(i)->text());

    for (int i = 0; i < ui->dnsListWidget->count(); ++i)
        dns.append(ui->dnsListWidget->item(i)->text());

    root["apps"] = apps;
    root["dns"] = dns;

    QJsonDocument doc(root);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::loadBlocklistState(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return;
    QJsonObject root = doc.object();

    ui->appListWidget->clear();
    ui->dnsListWidget->clear();

    for (const QJsonValue& val : root["apps"].toArray())
        ui->appListWidget->addItem(val.toString());

    for (const QJsonValue& val : root["dns"].toArray())
        ui->dnsListWidget->addItem(val.toString());
}

void MainWindow::handleSave() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Blocklist"), getSaveDirectory(), tr("JSON Files (*.json)"));
    if (!fileName.isEmpty()) {
        saveBlocklistState(fileName);
    }
}

void MainWindow::handleLoad() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Blocklist"), getSaveDirectory(), tr("JSON Files (*.json)"));
    if (!fileName.isEmpty()) {
        loadBlocklistState(fileName);
    }
}

















