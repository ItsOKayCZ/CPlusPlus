#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

#include <QFileDialog>

#include <QListWidgetItem>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

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
    void on_addFiles_triggered();

    void on_directoryList_itemPressed(QListWidgetItem *item);

    void on_directoryContents_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    QString url = "http://localhost:8080/";

    QJsonDocument folderStructure;
    QString itemPath;

    void updateDirectoryContents(QString path);
};

#endif // MAINWINDOW_H
