#include "categoryremoveform.h"
#include "ui_categoryremoveform.h"

CategoryRemoveForm::CategoryRemoveForm(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::MSWindowsFixedSizeDialogHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::CategoryRemoveForm)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(terminateLoop()));
}

void CategoryRemoveForm::setupSettings(Settings *_settings){
    settings = _settings;
}

CategoryRemoveForm::~CategoryRemoveForm()
{
    delete ui;
}

/*
 * User can chose from a combo box, which category he can remove.
 * Chosen category is then returned
 */
QString CategoryRemoveForm::getName(QTabWidget *tabs){

    ui->comboBox->clear();
    for(int i = 0; i < tabs->count(); i++){
        ui->comboBox->addItem(tabs->tabText(i));
    }

    this->show();

    while(true){
        int code = loop.exec();
        if(code == 1){
            return "";
        }

        int answer = QMessageBox::question(this,
                                       "Are you sure?",
                                       "Are you sure you want to delete this category?",
                                       QMessageBox::Yes, QMessageBox::No);

        if(answer != QMessageBox::No){
            break;
        }
    }

    this->close();

    QString text = ui->comboBox->currentText();
    settings->removeCategory(text);
    return text;

}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void CategoryRemoveForm::closeEvent(QCloseEvent *){
    this->loop.exit(1);
    this->close();
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void CategoryRemoveForm::terminateLoop(){
    this->loop.exit(1);
    this->close();
}
