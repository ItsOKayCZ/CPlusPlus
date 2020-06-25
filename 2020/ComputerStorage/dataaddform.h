#ifndef DATAADDFORM_H
#define DATAADDFORM_H

#include <QDialog>

#include <QTabWidget>
#include <QEventLoop>
#include <QMessageBox>
#include <QLineEdit>

#include "settings.h"

namespace Ui {
class DataAddForm;
}

class DataAddForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataAddForm(QWidget *parent = nullptr, Settings *_settings = nullptr);
    ~DataAddForm();

    QStringList getData(QTabWidget*);

    void setupLabels();
    void setupSettings(Settings*);

private:
    Ui::DataAddForm *ui;

    Settings *settings;

    QEventLoop loop;
    QList<QLineEdit*> fields;

    void closeEvent(QCloseEvent *);

    bool checkEmptyString(QString);

private slots:
    void terminateLoop();
};

#endif // DATAADDFORM_H
