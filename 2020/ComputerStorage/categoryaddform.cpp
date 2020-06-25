#include "categoryaddform.h"
#include "ui_categoryaddform.h"

CategoryAddForm::CategoryAddForm(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::MSWindowsFixedSizeDialogHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::CategoryAddForm)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(terminateLoop()));
}

void CategoryAddForm::setupSettings(Settings *_settings){
    settings = _settings;
}

CategoryAddForm::~CategoryAddForm()
{
    delete ui;
}

/*
 * A dialog opens where the user can chose the name of the category
 * and returns it
 */
QString CategoryAddForm::getName(){
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();

    this->show();

    QString name;
    while(true){
        int code = loop.exec();
        if(code == 1){
            return "";
        }

        name = ui->lineEdit->text();
        QString temp = name.simplified();
        if(temp.replace(" ", "") == ""){
            QMessageBox::warning(this,
                                 "Empty name",
                                 "You have entered an empty name. Please enter a name of the category");
        } else {
            break;
        }

    }

    settings->saveCategory(name);

    this->close();
    return name;
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void CategoryAddForm::closeEvent(QCloseEvent *){
    this->loop.exit(1);
    this->close();
}

/*
 * Is called when the cancel button is clicked
 * Closes the window and exists the event loop
 */
void CategoryAddForm::terminateLoop(){
    this->loop.exit(1);
    this->close();
}
