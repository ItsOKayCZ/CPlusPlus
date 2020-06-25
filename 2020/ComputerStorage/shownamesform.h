#ifndef SHOWNAMESFORM_H
#define SHOWNAMESFORM_H

#include <QDialog>

#include <QMessageBox>

#include "settings.h"

namespace Ui {
class ShowNamesForm;
}

class ShowNamesForm : public QDialog
{
    Q_OBJECT

public:
    explicit ShowNamesForm(QWidget *parent = nullptr);
    ~ShowNamesForm();

    void setupSettings(Settings *_settings);

    void display();

private:
    Ui::ShowNamesForm *ui;

    Settings *settings;

private slots:
    void addName();
    void removeName();
};

#endif // SHOWNAMESFORM_H
