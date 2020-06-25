#include "shownamesform.h"
#include "ui_shownamesform.h"

ShowNamesForm::ShowNamesForm(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::ShowNamesForm)
{
    ui->setupUi(this);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addName()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeName()));
}

void ShowNamesForm::setupSettings(Settings *_settings){
    settings = _settings;
}

ShowNamesForm::~ShowNamesForm()
{
    delete ui;
}

/*
 * TODO
 */
void ShowNamesForm::display(){
    ui->lineEdit->clear();
    ui->listWidget->clear();
    QStringList names = settings->getNames();

    ui->listWidget->addItems(names);

    this->show();
}

/*
 * TODO
 */
void ShowNamesForm::addName(){
    QString name = ui->lineEdit->text();
    QString temp = name.simplified();
    if(temp.replace(" ", "") == ""){
        QMessageBox::warning(this, "No name entered",
                             "Please enter a name or click cancel");
        return;
    }
    settings->addName(name);
    ui->listWidget->addItem(name);
    ui->lineEdit->clear();
}

/*
 * TODO
 */
void ShowNamesForm::removeName(){
    if(ui->listWidget->selectedItems().size() == 0){
        QMessageBox::warning(this, "No name selected",
                             "Please select a name to remove");
        return;
    }

    QString name = ui->listWidget->selectedItems()[0]->text();

    int answer = QMessageBox::question(this,
                                       "Are you sure?",
                                       "Are you sure you want to delete the selected name?",
                                       QMessageBox::Yes, QMessageBox::No);

    if(answer == QMessageBox::Yes){
        settings->removeName(name);
        ui->listWidget->takeItem(ui->listWidget->currentRow());
    }
}
