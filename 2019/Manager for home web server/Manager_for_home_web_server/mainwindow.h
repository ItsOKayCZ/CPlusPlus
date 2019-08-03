#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "prompt.h"
#include "settings.h"

#include <QMainWindow>

#include <QProcess>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

#include <QFileDialog>

#include <QListWidgetItem>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookie>

#include <QMenu>

#include <QMessageBox>

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
    void on_directoryList_itemPressed(QListWidgetItem *);

    // Changes the directoryContents when clicked
    void on_directoryContents_itemClicked(QListWidgetItem *);

    // Adds a folder to the current directory
    void on_addFolders_triggered();

    // When right clicked on the directoryContent widget
    // the same menu is showed when clicked on the menubar
    void display_menu_on_click(const QPoint &);

    // Removes a file or a folder
    void remove_file_or_folders();

    // Removes the selection in the QListWidget
    void clear_selection(QListWidgetItem *);

    // When the settings are opened
    void on_settings_triggered(bool);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    QString url;
    int urlIndex = 0;

    QJsonDocument folderStructure;
    QString itemPath;

    Prompt prompt;

    Settings settings;

    QString cookie;
    int cookieIndex = 1;

    // Displays the contents of a directory
    void updateDirectoryContents(QString path);

    // Sets the request cookies
    void setCookiesForRequest();

};

#endif // MAINWINDOW_H
