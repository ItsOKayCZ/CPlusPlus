#ifndef CATEGORYADDFORM_H
#define CATEGORYADDFORM_H

#include <QDialog>

#include <QMessageBox>
#include <QEventLoop>

#include <QDebug>

#include "settings.h"

namespace Ui {
class CategoryAddForm;
}

class CategoryAddForm : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryAddForm(QWidget *parent = nullptr);
    ~CategoryAddForm();

    QString getName();

    void setupSettings(Settings*);

private:
    Ui::CategoryAddForm *ui;

    QEventLoop loop;

    Settings *settings;

    void closeEvent(QCloseEvent *);

private slots:
    void terminateLoop();
};

#endif // CATEGORYADDFORM_H
