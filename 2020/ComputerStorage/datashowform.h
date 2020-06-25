#ifndef DATASHOWFORM_H
#define DATASHOWFORM_H

#include <QDialog>

#include <QLineEdit>
#include <QEventLoop>
#include <QMessageBox>
#include <QToolButton>
#include <QLabel>

#include "settings.h"
#include "propertiesform.h"

namespace Ui {
class DataShowForm;
}

class DataShowForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataShowForm(QWidget *parent = nullptr);
    ~DataShowForm();

    void setupLabels();
    void setupSettings(Settings*);

    QStringList display(QString categoryName, QStringList data, int col, int row);

private:
    Ui::DataShowForm *ui;

    Settings *settings;
    PropertiesForm properties;

    QStringList data;

    QList<QLineEdit*> fields;

    QEventLoop loop;

    void updateFields(QString categoryName, QStringList data);

    bool checkEmptyString(QString string);

    void closeEvent(QCloseEvent *);

private slots:
    void terminateLoop();
    void showOwned();
};

#endif // DATASHOWFORM_H
