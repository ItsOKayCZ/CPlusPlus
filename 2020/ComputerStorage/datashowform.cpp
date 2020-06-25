#include "datashowform.h"
#include "ui_datashowform.h"

DataShowForm::DataShowForm(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::MSWindowsFixedSizeDialogHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::DataShowForm)
  , properties()
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(terminateLoop()));
}

void DataShowForm::setupSettings(Settings *_settings){
    settings = _settings;

    properties.setupSettings(settings);
}

/*
 * Setup the form for the user from the settings->labels
 */
void DataShowForm::setupLabels(){

    for(int i = 0; i < settings->labels.size(); i++){
        ui->labelsLayout->addWidget(new QLabel(settings->labels[i] + ":"));

        QLineEdit *line = new QLineEdit();
        fields.append(line);
        if(settings->labels[i] == settings->nameLabel){

            QHBoxLayout *layout = new QHBoxLayout;

            QToolButton *button = new QToolButton();
            button->setText("More");
            connect(button, SIGNAL(clicked()), this, SLOT(showOwned()));

            layout->addWidget(line);
            layout->addWidget(button);

            ui->inputLayout->addLayout(layout);
        } else {
            ui->inputLayout->addWidget(line);
        }
    }
}

DataShowForm::~DataShowForm()
{
    delete ui;
}

/*
 * Displays the the form with filled information form the table
 * Returns the values from the form
 */
QStringList DataShowForm::display(QString categoryName, QStringList data, int col, int row){
    // TODO: Refactor -> Use function settings->findData
    updateFields(categoryName, data);

    fields[col]->setFocus();
    fields[col]->setSelection(0, data[col].size());
    this->activateWindow();

    this->show();

    QStringList changed;
    while(true){
        int code = loop.exec();
        if(code == 1){
            return data;
        }

        bool error = false;
        for(int i = 0; i < fields.size(); i++){

            if(checkEmptyString(fields[i]->text().simplified())){
                QMessageBox::warning(this,
                                     "Empty field",
                                     "All fields are required. Please make sure you filled all fields.");
                error = true;
                break;
            } else {
                changed.append(fields[i]->text());
            }

        }

        if(!error){
            break;
        }
    }

    this->close();
    settings->editData(categoryName, row, settings->parseData(changed));
    return changed;
}

/*
 * TODO
 */
void DataShowForm::updateFields(QString categoryName, QStringList data){

    this->data = data;
    this->data.append(categoryName);

    int categoryIndex = settings->findIndexByCategory(categoryName);
    int dataIndex = settings->findIndexByData(categoryIndex, settings->parseData(data));

    if(categoryIndex == -1 || dataIndex == -1){
        return;
    }

    QList<Settings::Data> save = settings->getSave();
    for(int i = 0; i < settings->labels.size(); i++){
        fields[i]->setText(save[categoryIndex].data[dataIndex][settings->labels[i]]);
    }

}

/*
 * Checks if the parameter is an empty string
 * Returns true if empty, otherwise false
 */
bool DataShowForm::checkEmptyString(QString str){
    QString temp = str.simplified();
    if(temp.replace(" ", "") == ""){
        return true;
    }
    return false;
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void DataShowForm::closeEvent(QCloseEvent *){
    this->loop.exit(1);
    this->close();
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void DataShowForm::terminateLoop(){
    this->loop.exit(1);
    this->close();
}

/*
 * Opens a dialog and show all the properties owned by a name
 */
void DataShowForm::showOwned(){
    properties.display(fields[settings->nameIndex]->text());
    QStringList temp = data;
    QString categoryName = temp.last();
    temp.pop_back();
    temp[settings->nameIndex] = "Spare";
    updateFields(categoryName, temp);
}
