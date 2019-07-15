#include "prompt.h"
#include "ui_prompt.h"

Prompt::Prompt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prompt)
{
    ui->setupUi(this);


//    parent->setFolderName("Testing");
}

Prompt::~Prompt()
{
    delete ui;
}

void Prompt::on_buttonBox_clicked(QAbstractButton *button)
{
    QString type = button->text();

    qDebug() << type;
}

void Prompt::display(/*void *function*/){
    this->show();
}
