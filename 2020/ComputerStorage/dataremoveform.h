#ifndef DATAREMOVEFORM_H
#define DATAREMOVEFORM_H

#include <QDialog>

#include <QMessageBox>
#include <QTableWidget>

#include "settings.h"

#include <QDebug>

namespace Ui {
class DataRemoveForm;
}

class DataRemoveForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataRemoveForm(QWidget *parent = nullptr);
    ~DataRemoveForm();

    void setupSettings(Settings*);

    void remove(QTableWidget*);

private:
    Ui::DataRemoveForm *ui;
    Settings *settings;
};

#endif // DATAREMOVEFORM_H
