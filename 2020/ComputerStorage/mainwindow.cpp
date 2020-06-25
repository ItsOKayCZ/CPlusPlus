#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new Settings();

    // EVENTS
    connect(ui->actionAdd_category, SIGNAL(triggered()), this, SLOT(addCategory()));
    connect(ui->actionRemove_category, SIGNAL(triggered()), this, SLOT(removeCategory()));
    connect(ui->actionSave_file, SIGNAL(triggered()), this, SLOT(showSettings()));
    connect(ui->addDataButton, SIGNAL(clicked()), this, SLOT(addDataToTable()));
    connect(ui->removeDataButton, SIGNAL(clicked()), this, SLOT(removeDataFromTable()));

    // Setup
    categoryAdd.setupSettings(settings);
    categoryRemove.setupSettings(settings);
    dataAdd.setupSettings(settings);
    dataRemove.setupSettings(settings);
    dataShow.setupSettings(settings);

    dataAdd.setupLabels();
    dataShow.setupLabels();

    // Loading data into table if saved
    loadDataIntoTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Adds a category to the QTabWidget
 * with a name entered by the user
 */
void MainWindow::addCategory(){

    this->setEnabled(false);
    QString categoryName = categoryAdd.getName();
    this->setEnabled(true);

    if(categoryName == ""){
        return;
    }

    setupTab(categoryName);
}

/*
 * Inserts a tab into the QTabWidget with a name from the parameter
 * and the QTableWidget as the child
 */
void MainWindow::setupTab(QString categoryName){

    // Setting up columns
    QTableWidget *table = new QTableWidget();
    for(int i = 0; i < settings->labels.size(); i++){
        table->insertColumn(i);
    }

    table->setHorizontalHeaderLabels(settings->labels);
    table->setObjectName(categoryName);
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(showDataFromTable(int, int)));

    // Setting layout
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(table, 1);
    tab->setLayout(layout);

    table->horizontalHeader();

    ui->tabWidget->addTab(tab, categoryName);
}

/*
 * Removes a tab from QTabWidget chosen by user
 */
void MainWindow::removeCategory(){
    this->setEnabled(false);
    QString category = categoryRemove.getName(ui->tabWidget);
    this->setEnabled(true);

    for(int i = 0; i < ui->tabWidget->count(); i++){
        if(ui->tabWidget->tabText(i) == category){
            ui->tabWidget->removeTab(i);
            break;
        }
    }

}

/*
 * Adds data to there corresponding labels into the QTableWidget
 * of the selected QTabWidget
 */
void MainWindow::addDataToTable(){
    this->setEnabled(false);
    QStringList list = dataAdd.getData(ui->tabWidget);
    this->setEnabled(true);

    if(list.size() == 0){
        return;
    }

    addItemToTable(list);
}

/*
 * Adds a row and adds data to it from list
 */
void MainWindow::addItemToTable(QStringList list){

    QTableWidget *table = ui->tabWidget->findChildren<QTableWidget*>(list[0])[0];
    table->insertRow(table->rowCount());

    for(int i = 1; i < list.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(list[i]);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        table->setItem(table->rowCount() - 1, i - 1, item);
    }
}

/*
 * Removes a row where a cell is selected
 */
void MainWindow::removeDataFromTable(){
    QTableWidget *tab = getSelectedTab();

    this->setEnabled(false);
    dataRemove.remove(tab);
    this->setEnabled(true);
}

/*
 * Show a dialog with the labels and data
 * and if users changes the data it will update the
 * table
 */
void MainWindow::showDataFromTable(int row, int col){
    QStringList data;

    QTableWidget *table = getSelectedTab();
    for(int i = 0; i < table->columnCount(); i++){
        data.append(table->item(row, i)->text());
    }

    this->setEnabled(false);
    data = dataShow.display(table->objectName(), data, col, row);
    this->setEnabled(true);

    for(int i = 0; i < data.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(data[i]);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        table->setItem(row, i, item);
    }

}

/*
 * Returns the selected tab
 */
QTableWidget *MainWindow::getSelectedTab(){
    QList<QTableWidget*> tables = ui->tabWidget->findChildren<QTableWidget*>();
    return tables[tables.size() - 1];
}

/*
 * Shows the settings of the config
 */
void MainWindow::showSettings(){
    this->setEnabled(false);
    settings->display();
    this->setEnabled(true);
}

/*
 * Loads the data file and updates the tabs and tables
 * loaded from the file
 */
void MainWindow::loadDataIntoTables(){
    QList<Settings::Data> data = settings->getSave();

    QStringList list;
    for(int i = 0; i < data.size(); i++){
        setupTab(data[i].name);

        for(int j = 0; j < data[i].data.size(); j++){

            list.append(data[i].name);
            for(int x = 0; x < settings->labels.size(); x++){
                list.append(data[i].data[j][settings->labels[x]]);
            }

            addItemToTable(list);
            list.clear();
        }
    }

}

/*
 * Save the data when user closes the window
 */
void MainWindow::closeEvent(QCloseEvent*){
    settings->saveDataFile();
    QApplication::exit();
}
