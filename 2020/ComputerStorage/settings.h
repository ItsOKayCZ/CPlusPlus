#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <QEventLoop>

#include <QDateTime>

#include <QDebug>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    // Labels
    QStringList labels;
    QString nameLabel;
    int nameIndex;

    struct Data {
        QString name;
        QList<QMap<QString, QString>> data;
    };

    void display();

    void saveCategory(QString categoryName);
    void removeCategory(QString categoryName);
    void addData(QMap<QString, QString> data);
    void editData(QString categoryName, int dataIndex, QMap<QString, QString> data);
    void removeData(QString categoryName, int dataIndex);

    QList<QMap<QString, QString>> getDataByName(QString);

    void makeSpare(QList<QMap<QString, QString>>);

    QList<Settings::Data> getSave();

    int findIndexByCategory(QString categoryName);
    int findIndexByData(int categoryIndex, QMap<QString, QString> data);

    QMap<QString, QString> parseData(QStringList data);

    void saveDataFile();

private:
    Ui::Settings *ui;

    QEventLoop loop;

    QList<Data> save;
    QString path;

    QString dataFile = "data.json";
    QString configFile = "config";
    QString backupFile = "backup%1.json";

    void saveConfigFile();
    void loadConfigFile();

    void backupDataFile();
    void loadDataFile();

    QList<Data> packStruct(QJsonDocument);
    QJsonDocument unpackStruct(QList<Data>);

    void closeEvent(QCloseEvent *);

private slots:
    void changePath();

    void terminateLoop();
};

#endif // SETTINGS_H
