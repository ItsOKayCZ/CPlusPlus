#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "prompt.h"

#include <QMainWindow>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

#include <QFileDialog>

#include <QListWidgetItem>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QMenu>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Adding files to the currently selected directory
    // If no directory selected, it is added to the root
    void on_addFiles_triggered();

    // Changing the directoryContents widget to display
    // all the contents of the folder selected
    void on_directoryList_itemPressed(QListWidgetItem *item);

    // Changes the directoryContents when clicked
    void on_directoryContents_itemClicked(QListWidgetItem *item);

    // Adds a folder to the current directory
    void on_addFolders_triggered();

    // When right clicked on the directoryContent widget
    // the same menu is showed when clicked on the menubar
    void display_menu_on_click(const QPoint &pos);

    // Removes a file or a folder
    void remove_file_or_folders();

    void testing();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    QString url = "http://localhost:8080/";

    QJsonDocument folderStructure;
    QString itemPath;

    Prompt prompt;

    // Displays the contents of a directory
    void updateDirectoryContents(QString path);

};

#endif // MAINWINDOW_H
