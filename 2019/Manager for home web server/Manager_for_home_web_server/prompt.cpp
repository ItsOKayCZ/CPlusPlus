#include "prompt.h"
#include "ui_prompt.h"

Prompt::Prompt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prompt)
{
    ui->setupUi(this);
}

Prompt::~Prompt()
{
    delete ui;
}

QString Prompt::display(){
    this->show();

    QEventLoop loop;
    QObject::connect(ui->buttons, SIGNAL(accepted()), &loop, SLOT(quit()));
    QObject::connect(ui->buttons, SIGNAL(rejected()), this, SLOT(close()));
    loop.exec();

    this->close();

    QString inputField = ui->inputField->text();
    ui->inputField->clear();

    return inputField;
}
