#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include <QtDebug>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    QStringList getValues(bool);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
