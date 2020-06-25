#ifndef PROPERTIESFORM_H
#define PROPERTIESFORM_H

#include <QDialog>

#include <QCheckBox>
#include <QPushButton>
#include <QDir>

#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

#include <QDateTime>

#include <QTextDocument>

#include <QFileDialog>
#include <QMessageBox>

#include <QEventLoop>

#include "settings.h"

namespace Ui {
class PropertiesForm;
}

class PropertiesForm : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesForm(QWidget *parent = nullptr);
    ~PropertiesForm();

    void display(QString);

    void setupSettings(Settings*);

private:
    Ui::PropertiesForm *ui;

    Settings *settings;

    QEventLoop loop;

    void manageExport();
    void exportData(int, bool);

    void closeEvent(QCloseEvent *);

private slots:
    void terminateLoop();
};

#endif // PROPERTIESFORM_H
