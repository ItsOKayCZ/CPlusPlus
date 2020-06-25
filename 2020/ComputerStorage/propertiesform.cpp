#include "propertiesform.h"
#include "ui_propertiesform.h"

PropertiesForm::PropertiesForm(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::PropertiesForm)
{
    ui->setupUi(this);
}

void PropertiesForm::setupSettings(Settings *_settings){
    settings = _settings;
}

PropertiesForm::~PropertiesForm()
{
    delete ui;
}

/*
 * Displays a window with a table containing information about a properties
 * owned by a name
 */
void PropertiesForm::display(QString name){
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->groupBox->setTitle(name);
    ui->tableCheckBox->setRowCount(0);

    for(int i = 0; i < settings->labels.size(); i++){
        ui->tableWidget->insertColumn(i);
    }

    QStringList labels = settings->labels;
    labels.push_front("Category");
    labels.removeOne(settings->nameLabel);
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    QList<QMap<QString, QString>> data = settings->getDataByName(name);

    for(int i = 0; i < data.size(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        for(int j = 0; j < labels.size(); j++){
            QTableWidgetItem *item = new QTableWidgetItem(data[i][labels[j]]);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, j, item);
        }


        // Setting up checkboxes
        ui->tableCheckBox->insertRow(ui->tableCheckBox->rowCount());
        int rowCount = ui->tableCheckBox->rowCount();

        QCheckBox *printBox = new QCheckBox();
        printBox->setStyleSheet("margin-left: 10.75px");
        ui->tableCheckBox->setCellWidget(rowCount - 1,
                                         0,
                                         printBox);
        ui->tableCheckBox->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);


        QCheckBox *discardBox = new QCheckBox();
        discardBox->setStyleSheet("margin-left: 17.5px");
        ui->tableCheckBox->setCellWidget(rowCount - 1,
                                         1,
                                         discardBox);
        ui->tableCheckBox->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

        ui->tableCheckBox->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    connect(ui->buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(terminateLoop()));
    this->show();

    int code = loop.exec();
    if(code == 1){
        return;
    }

    manageExport();

    data.clear();
    for(int i = 0; i < ui->tableCheckBox->rowCount(); i++){
        QCheckBox *discardBox = (QCheckBox*)ui->tableCheckBox->cellWidget(i, 1);
        if(discardBox->checkState() == Qt::Checked){

            QMap<QString, QString> temp;
            for(int j = 0; j < settings->labels.size(); j++){
                if(settings->labels[j] == settings->nameLabel){
                    temp[settings->nameLabel] = ui->groupBox->title();
                }
                temp[labels[j]] = ui->tableWidget->item(i, j)->text();
            }

            data.append(temp);
        }
    }

    settings->makeSpare(data);

    this->close();
}

/*
 * Checks QCheckBox if they are checked
 * and calls a function (exportData) to format it and save it
 */
void PropertiesForm::manageExport(){

    for(int i = 0; i < ui->tableCheckBox->rowCount(); i++){
        QCheckBox *box = (QCheckBox*)ui->tableCheckBox->cellWidget(i, 0);
        Qt::CheckState printState = box->checkState();

        box = (QCheckBox*)ui->tableCheckBox->cellWidget(i, 1);
        Qt::CheckState discardState = box->checkState();

        if(printState == Qt::Checked){
            if(discardState == Qt::Checked){
                exportData(i, true);
            } else {
                exportData(i, false);
            }
        }
    }

}

/*
 * Formats data into a .rtf file to add the information
 * from the row where the QCheckBox is checked
 *
 * if discard is checked -> formats document named return
 * else -> formats document named acceptance
 */
void PropertiesForm::exportData(int row, bool discard){

    QFile file;
    if(!discard){
        file.setFileName(":/acceptance");
    } else {
        file.setFileName(":/return");
    }
    file.open(QIODevice::ReadOnly);

    QString outputPath;
    while(true){
        outputPath = QFileDialog::getSaveFileName(this,
                                                  "Select output",
                                                  QDir::currentPath(),
                                                  "Word (*.rtf)");
        if(outputPath == ""){
            QMessageBox::information(this, "No output path",
                                     "No output file or folder was chosen. Please chose a folder and input a name of the document");
        } else {
            break;
        }
    }

    QFile output(outputPath);
    output.open(QIODevice::WriteOnly);

    QTextStream stream(&file);
    QTextStream outputStream(&output);

    QString prefix;
    if(discard){
        prefix = "ASD";
    } else {
        prefix = "%";
    }
    while(!stream.atEnd()){
        QString data;
        try {
            data = stream.readAll();
        } catch (std::bad_alloc &ba) {
            QMessageBox::warning(this, "Error", "An error occurred. Please try again");
            break;
        }

        for(int i = 0; i < settings->labels.size(); i++){

            if(data.contains("%User%")){
                QString val = ui->groupBox->title();
                data.replace("%User%", val);
            }

            if(data.contains("%Category%")){
                QString val = ui->tableWidget->item(row, 0)->text();
                data.replace("%Category%", val);
            }

            if(data.contains("%" + settings->labels[i] + "%")){
                QString val = ui->tableWidget->item(row, i + 1)->text();
                data.replace("%" + settings->labels[i] + "%", val);
            }

            data.replace("%Date%", QDateTime::currentDateTime().toString("dd.MM.yyyy"));

        }

        outputStream << data;
    }


    output.close();
    file.close();
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void PropertiesForm::closeEvent(QCloseEvent *){
    loop.exit(1);
    this->close();
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void PropertiesForm::terminateLoop(){
    loop.exit(1);
    this->close();
}
