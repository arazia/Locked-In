/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "statstab.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    StatsTab *statsTab;
    QWidget *appTab;
    QListWidget *appListWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *browseButton;
    QLineEdit *pathLineEdit;
    QWidget *networkTab;
    QListWidget *dnsListWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *dnsLineEdit;
    QWidget *startTab;
    QSpinBox *durationSpinBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *blockAllButton;
    QGridLayout *gridLayout_2;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *unblockAllButton;
    QGridLayout *gridLayout_3;
    QPushButton *backupButton;
    QPushButton *restoreButton;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(930, 608);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 931, 591));
        statsTab = new StatsTab();
        statsTab->setObjectName("statsTab");
        tabWidget->addTab(statsTab, QString());
        appTab = new QWidget();
        appTab->setObjectName("appTab");
        appTab->setEnabled(true);
        appListWidget = new QListWidget(appTab);
        appListWidget->setObjectName("appListWidget");
        appListWidget->setGeometry(QRect(40, 140, 841, 371));
        verticalLayoutWidget = new QWidget(appTab);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(40, 20, 841, 121));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        browseButton = new QPushButton(verticalLayoutWidget);
        browseButton->setObjectName("browseButton");

        horizontalLayout->addWidget(browseButton);

        pathLineEdit = new QLineEdit(verticalLayoutWidget);
        pathLineEdit->setObjectName("pathLineEdit");

        horizontalLayout->addWidget(pathLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget->addTab(appTab, QString());
        networkTab = new QWidget();
        networkTab->setObjectName("networkTab");
        dnsListWidget = new QListWidget(networkTab);
        dnsListWidget->setObjectName("dnsListWidget");
        dnsListWidget->setGeometry(QRect(40, 140, 841, 371));
        verticalLayoutWidget_2 = new QWidget(networkTab);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(40, 60, 841, 61));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        dnsLineEdit = new QLineEdit(verticalLayoutWidget_2);
        dnsLineEdit->setObjectName("dnsLineEdit");

        verticalLayout_2->addWidget(dnsLineEdit);

        tabWidget->addTab(networkTab, QString());
        startTab = new QWidget();
        startTab->setObjectName("startTab");
        durationSpinBox = new QSpinBox(startTab);
        durationSpinBox->setObjectName("durationSpinBox");
        durationSpinBox->setGeometry(QRect(360, 150, 241, 151));
        QFont font1;
        font1.setPointSize(18);
        durationSpinBox->setFont(font1);
        durationSpinBox->setMaximum(9999);
        gridLayoutWidget = new QWidget(startTab);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 380, 881, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        blockAllButton = new QPushButton(gridLayoutWidget);
        blockAllButton->setObjectName("blockAllButton");
        QFont font2;
        font2.setPointSize(14);
        blockAllButton->setFont(font2);

        gridLayout->addWidget(blockAllButton, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        saveButton = new QPushButton(gridLayoutWidget);
        saveButton->setObjectName("saveButton");
        saveButton->setFont(font2);

        gridLayout_2->addWidget(saveButton, 0, 0, 1, 1);

        loadButton = new QPushButton(gridLayoutWidget);
        loadButton->setObjectName("loadButton");
        loadButton->setFont(font2);

        gridLayout_2->addWidget(loadButton, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 2, 1, 1);

        unblockAllButton = new QPushButton(gridLayoutWidget);
        unblockAllButton->setObjectName("unblockAllButton");
        unblockAllButton->setFont(font2);

        gridLayout->addWidget(unblockAllButton, 0, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        backupButton = new QPushButton(gridLayoutWidget);
        backupButton->setObjectName("backupButton");
        backupButton->setFont(font2);

        gridLayout_3->addWidget(backupButton, 0, 0, 1, 1);

        restoreButton = new QPushButton(gridLayoutWidget);
        restoreButton->setObjectName("restoreButton");
        restoreButton->setFont(font2);

        gridLayout_3->addWidget(restoreButton, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 3, 1, 1);

        label_3 = new QLabel(startTab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(400, 90, 201, 81));
        label_3->setFont(font);
        label_4 = new QLabel(startTab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(90, -30, 871, 131));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/locked_in.png")));
        tabWidget->addTab(startTab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 930, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(statsTab), QCoreApplication::translate("MainWindow", "Page", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input File Path:", nullptr));
        browseButton->setText(QCoreApplication::translate("MainWindow", "browse...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(appTab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Input URL:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(networkTab), QCoreApplication::translate("MainWindow", "Page", nullptr));
        blockAllButton->setText(QCoreApplication::translate("MainWindow", "Block All", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        unblockAllButton->setText(QCoreApplication::translate("MainWindow", "Unblock All", nullptr));
        backupButton->setText(QCoreApplication::translate("MainWindow", "Backup", nullptr));
        restoreButton->setText(QCoreApplication::translate("MainWindow", "Restore", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Time (Minutes)", nullptr));
        label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(startTab), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
