#include "dataaddform.h"
#include "ui_dataaddform.h"

DataAddForm::DataAddForm(QWidget *parent, Settings *_settings) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::MSWindowsFixedSizeDialogHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::DataAddForm)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(terminateLoop()));

    settings = _settings;
}

void DataAddForm::setupSettings(Settings *_settings){
    settings = _settings;
}

/*
 * Setups the form from the labels in settings->labels
 */
void DataAddForm::setupLabels(){
        for(int i = 0; i < settings->labels.size(); i++){
            ui->labelsLayout->addWidget(new QLabel(settings->labels[i] + ":"));

            QLineEdit *line = new QLineEdit();
            ui->inputLayout->addWidget(line);
            fields.append(line);
        }
}

DataAddForm::~DataAddForm()
{
    delete ui;
}

/*
 * Displays a dialog with form in which every ros corresponds
 * to the labels in settings->labels.
 * Returns the list of string with the values from the form
 */
QStringList DataAddForm::getData(QTabWidget *categories){

    // Setting up fields of the form
    fields[0]->setFocus();
    for(int i = 0; i < fields.size(); i++){
        fields[i]->clear();
    }

    // Getting the previously selected category and setting it again
    QString previousSelected = "";
    if(ui->comboBox->count() != 0){
        previousSelected = ui->comboBox->currentText();
    }

    ui->comboBox->clear();
    for(int i = 0; i < categories->count(); i++){
        ui->comboBox->addItem(categories->tabText(i));
    }

    // Set last previously selected category
    if(previousSelected != ""){
        ui->comboBox->setCurrentText(previousSelected);
    }

    this->show();

    // Getting data from form
    QStringList data;
    while(true){
        int code = loop.exec();
        if(code == 1){
            return QStringList();
        }

        // Add all fields to list
        data.append(ui->comboBox->currentText());

        bool error = false;
        for(int i = 0; i < fields.size(); i++){
            if(!checkEmptyString(fields[i]->text())){
                data.append(fields[i]->text());
            } else {
                QMessageBox::warning(this,
                                     "Empty field",
                                     "All fields are required. Please make sure you filled all fields.");
                error = true;
                break;
            }
        }
        if(!error){
            break;
        }
    }

    this->close();
    settings->addData(settings->parseData(data));
    return data;
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void DataAddForm::closeEvent(QCloseEvent *){
    this->loop.exit(1);
    this->close();
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void DataAddForm::terminateLoop(){
    this->loop.exit(1);
    this->close();
}

/*
 * Checks if the parameter string is empty string
 * Return true if empty, otherwise false
 */
bool DataAddForm::checkEmptyString(QString str){
    QString temp = str.simplified();
    temp.replace(" ", "");
    if(temp == ""){
        return true;
    }

    return false;
}
