#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QPushButton>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "settings.h"

#include "categoryaddform.h"
#include "categoryremoveform.h"

#include "dataaddform.h"
#include "dataremoveform.h"
#include "datashowform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Settings *settings;

    CategoryAddForm categoryAdd;
    CategoryRemoveForm categoryRemove;

    DataAddForm dataAdd;
    DataRemoveForm dataRemove;
    DataShowForm dataShow;

    QTableWidget *getSelectedTab();

    void loadDataIntoTables();

    void setupTab(QString);

    void addItemToTable(QStringList);

    void closeEvent(QCloseEvent *);
private slots:
    // Functions

    // Adds category to tab widget
    void addCategory();

    // Removes category from tab widget
    void removeCategory();

    // Opens the settings menu
    void showSettings();

    // Add data to table
    void addDataToTable();

    // Removes data from table
    void removeDataFromTable();

    // Displays the data on the row
    void showDataFromTable(int, int);
};
#endif // MAINWINDOW_H
