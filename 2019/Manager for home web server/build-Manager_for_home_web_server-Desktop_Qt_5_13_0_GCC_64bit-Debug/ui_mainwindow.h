/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *addFiles;
    QAction *addFolders;
    QAction *Remove;
    QAction *settings;
    QAction *documentation;
    QWidget *centralWidget;
    QLabel *directoryLabel;
    QListWidget *directoryContents;
    QListWidget *directoryList;
    QMenuBar *menuBar;
    QMenu *menuFiles_Folders;
    QMenu *menuUser;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(737, 647);
        MainWindow->setMinimumSize(QSize(737, 647));
        MainWindow->setMaximumSize(QSize(737, 647));
        addFiles = new QAction(MainWindow);
        addFiles->setObjectName(QString::fromUtf8("addFiles"));
        addFolders = new QAction(MainWindow);
        addFolders->setObjectName(QString::fromUtf8("addFolders"));
        Remove = new QAction(MainWindow);
        Remove->setObjectName(QString::fromUtf8("Remove"));
        settings = new QAction(MainWindow);
        settings->setObjectName(QString::fromUtf8("settings"));
        documentation = new QAction(MainWindow);
        documentation->setObjectName(QString::fromUtf8("documentation"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        directoryLabel = new QLabel(centralWidget);
        directoryLabel->setObjectName(QString::fromUtf8("directoryLabel"));
        directoryLabel->setGeometry(QRect(260, 0, 481, 21));
        directoryLabel->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"\n"
"background-color: white;"));
        directoryContents = new QListWidget(centralWidget);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(directoryContents);
        __qlistwidgetitem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        directoryContents->setObjectName(QString::fromUtf8("directoryContents"));
        directoryContents->setGeometry(QRect(260, 30, 471, 591));
        directoryContents->setContextMenuPolicy(Qt::CustomContextMenu);
        directoryList = new QListWidget(centralWidget);
        directoryList->setObjectName(QString::fromUtf8("directoryList"));
        directoryList->setGeometry(QRect(8, 0, 241, 621));
        directoryList->setContextMenuPolicy(Qt::CustomContextMenu);
        directoryList->setSelectionMode(QAbstractItemView::SingleSelection);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 737, 19));
        menuFiles_Folders = new QMenu(menuBar);
        menuFiles_Folders->setObjectName(QString::fromUtf8("menuFiles_Folders"));
        menuUser = new QMenu(menuBar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFiles_Folders->menuAction());
        menuBar->addAction(menuUser->menuAction());
        menuFiles_Folders->addAction(addFiles);
        menuFiles_Folders->addAction(addFolders);
        menuFiles_Folders->addAction(Remove);
        menuUser->addAction(settings);
        menuUser->addAction(documentation);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Manager", nullptr));
        addFiles->setText(QCoreApplication::translate("MainWindow", "Add files", nullptr));
        addFolders->setText(QCoreApplication::translate("MainWindow", "Add folders", nullptr));
        Remove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        settings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        documentation->setText(QCoreApplication::translate("MainWindow", "Documentation", nullptr));
        directoryLabel->setText(QCoreApplication::translate("MainWindow", "Directory:", nullptr));

        const bool __sortingEnabled = directoryContents->isSortingEnabled();
        directoryContents->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = directoryContents->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "Testing", nullptr));
        directoryContents->setSortingEnabled(__sortingEnabled);

        menuFiles_Folders->setTitle(QCoreApplication::translate("MainWindow", "Files/Folders", nullptr));
        menuUser->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
