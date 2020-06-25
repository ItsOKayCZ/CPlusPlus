#include "dataremoveform.h"
#include "ui_dataremoveform.h"

DataRemoveForm::DataRemoveForm(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::MSWindowsFixedSizeDialogHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::DataRemoveForm)
{
    ui->setupUi(this);
}

void DataRemoveForm::setupSettings(Settings *_settings){
    settings = _settings;
}

DataRemoveForm::~DataRemoveForm()
{
    delete ui;
}

/*
 * Checks if a row in the table is selected and after asking the user
 * for confirmation, removes it
 */
void DataRemoveForm::remove(QTableWidget *table){
    int row = table->currentRow();

    if(row == -1){
        QMessageBox::information(this,
                                 "No row selected",
                                 "There are no selected rows in the current tab. Please select a row");
        return;
    }

    int answer = QMessageBox::question(this,
                                       "Are you sure?",
                                       "Are you sure you want to remove the selected row?",
                                       QMessageBox::Yes, QMessageBox::No);

    if(answer == QMessageBox::Yes){
        table->removeRow(row);
        settings->removeData(table->objectName(), table->currentRow());
    }

}
