#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

QStringList Settings::getValues(){
    this->show();

    QStringList config;

    // Two undefined configurations
    config.append("");
    config.append("");

    QEventLoop loop;
    QObject::connect(ui->buttons, SIGNAL(accepted()), &loop, SLOT(quit()));
    QObject::connect(ui->buttons, SIGNAL(rejected()), &loop, SLOT(quit()));
    loop.exec();

    config[0] = ui->hostnameInput->text();
    config[1] = ui->cookieInput->text();

    return config;
}
