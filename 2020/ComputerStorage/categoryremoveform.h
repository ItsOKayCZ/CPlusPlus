#ifndef CATEGORYREMOVEFORM_H
#define CATEGORYREMOVEFORM_H

#include <QDialog>

#include <QTabWidget>
#include <QMessageBox>
#include <QEventLoop>

#include "settings.h"

#include <QtDebug>

namespace Ui {
class CategoryRemoveForm;
}

class CategoryRemoveForm : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryRemoveForm(QWidget *parent = nullptr);
    ~CategoryRemoveForm();

    void setupSettings(Settings*);

    QString getName(QTabWidget*);

private:
    Ui::CategoryRemoveForm *ui;

    Settings *settings;

    QEventLoop loop;

    void closeEvent(QCloseEvent *);

private slots:
    void terminateLoop();
};

#endif // CATEGORYREMOVEFORM_H
