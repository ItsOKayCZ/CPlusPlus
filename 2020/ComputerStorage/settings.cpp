#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint
                    | Qt::MSWindowsFixedSizeDialogHint
                    | Qt::WindowStaysOnTopHint),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changePath()));

    // Setting up labels
    labels.append("Number FA");
    labels.append("Invoice received");
    labels.append("Date of purchase");
    labels.append("Handover date");
    labels.append("Price");
    labels.append("Model");
    labels.append("Serial number");
    nameLabel = "User";
    labels.append(nameLabel);
    nameIndex = labels.size() - 1;

    loadConfigFile();
    loadDataFile();
}

Settings::~Settings()
{
    delete ui;
}

/*
 * Displays form
 */
void Settings::display(){
    ui->path->setText(path);
    ui->path->setCursorPosition(path.length());

    this->show();

    connect(ui->buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(terminateLoop()));
    int code = loop.exec();
    if(code == 1){
        return;
    }

    QString temp = ui->path->text().simplified();
    if(temp.replace(" ", "") != ""){
        path = ui->path->text();
    }
    this->close();

    saveConfigFile();
    return;
}

/*
 * Changes path of data file
 */
void Settings::changePath(){
    QString prevPath = path;
    path = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
    if(prevPath != path && path != ""){
        saveConfigFile();
        QFile::remove(prevPath + dataFile);

        ui->path->setText(path);
        ui->path->setCursorPosition(path.length());
    } else {
        path = prevPath;
    }
    return;
}

/*
 * Tries to save config file
 */
void Settings::saveConfigFile(){
    QFile file(QDir::currentPath() + "/" + configFile);

    if(!file.open(QIODevice::WriteOnly)){
        qInfo() << "Didnt open";
        return;
    }

    QTextStream stream(&file);
    stream << path;
    file.close();
}

/*
 * Tries to load config file
 */
void Settings::loadConfigFile(){
    QFile file(QDir::currentPath() + "/" + configFile);

    if(!file.open(QIODevice::ReadOnly)){
        path = QDir::currentPath();
        qInfo() << "Config file doesnt exist";
        saveConfigFile();
        return;
    }

    QTextStream stream(&file);
    path = stream.readAll();
    file.close();
}

/*
 * Tries to load data file
 */
void Settings::loadDataFile(){
    QFile file(path + "/" + dataFile);

    if(!file.open(QIODevice::ReadOnly)){
        qInfo() << "Data file doesnt exist";
        return;
    }

    save = packStruct(QJsonDocument::fromJson(file.readAll()));

    file.close();
}

/*
 * Save tables with categories to file
 */
void Settings::saveDataFile(){
    backupDataFile();

    QFile file(path + "/" + dataFile);

    if(!file.open(QIODevice::WriteOnly)){
        qInfo() << "Data file doesnt exist";
        return;
    }

    QJsonDocument saveData = unpackStruct(save);

    file.write(saveData.toJson());
    file.close();
}

/*
 * Makes a copy of the latest data file
 */
void Settings::backupDataFile(){
    QFile saveFile(path + "/" + dataFile);

    if(!saveFile.open(QIODevice::ReadOnly)){
        qInfo() << "Cannot open data file for backup";
        return;
    }

    QJsonDocument saveData = QJsonDocument::fromJson(saveFile.readAll());
    if(saveData == unpackStruct(save)){
        qInfo() << "Not making backup. No changes";
        return;
    }

    QString fileName = backupFile.arg(QDateTime::currentDateTime().toString("yyMMddhhss"));
    QFile backup(fileName);

    if(!backup.open(QIODevice::WriteOnly)){
        qInfo() << "Cannot open backup file";
        return;
    }

    backup.write(saveData.toJson());

    backup.close();
    saveFile.close();
}

/*
 * Adds a category to JSON
 */
void Settings::saveCategory(QString name){
    Data temp;
    temp.name = name;

    save.append(temp);
}
void Settings::removeCategory(QString categoryName){
    save.removeAt(findIndexByCategory(categoryName));
}

/*
 * Adds data to the JSON file
 */
void Settings::addData(QMap<QString, QString> data){

    int index = findIndexByCategory(data["Category"]);

    QMap<QString, QString> temp;
    for(int i = 0; i < labels.size(); i++){
        temp[labels[i]] = data[labels[i]];
    }
    save[index].data.append(temp);
}

/*
 * Edits the data of a category at a certain row
 */
void Settings::editData(QString categoryName, int dataIndex, QMap<QString, QString> data){
    int index = findIndexByCategory(categoryName);

    for(int i = 0; i < labels.size(); i++){
        save[index].data[dataIndex][labels[i]] = data[labels[i]];
    }
}

/*
 * Removes data from JSON file
 */
void Settings::removeData(QString categoryName, int dataIndex){
    int index = findIndexByCategory(categoryName);
    save[index].data.removeAt(dataIndex);
}

/*
 * Finds the index of a category by name in JSON document
 */
int Settings::findIndexByCategory(QString categoryName){
    for(int i = 0; i < save.size(); i++){
        if(save[i].name == categoryName){
            return i;
        }
    }

    return -1;
}

/*
 * Retuns the data file
 */
QList<Settings::Data> Settings::getSave(){
    return save;
}

/*
 * Returns all data where it contains the name given in the parameter
 */
QList<QMap<QString, QString>> Settings::getDataByName(QString name){
    QList<QMap<QString, QString>> data;

    for(int i = 0; i < save.size(); i++){
        for(int j = 0; j < save[i].data.size(); j++){

            if(save[i].data[j][nameLabel] == name){
                QMap<QString, QString> temp;

                temp["Category"] = save[i].name;
                for(int x = 0; x < labels.size(); x++){
                    temp[labels[x]] = save[i].data[j][labels[x]];
                }

                data.append(temp);
            }
        }
    }

    return data;
}

/*
 * By the data passed, it will change its name value to "Spare"
 */
void Settings::makeSpare(QList<QMap<QString, QString>> data){

    for(int i = 0; i < data.size(); i++){

        int index = findIndexByCategory(data[i]["Category"]);
        int dataIndex = findIndexByData(index, data[i]);

        if(dataIndex != -1){
            continue;
        }

        save[index].data[dataIndex][nameLabel] = "Spare";
    }
}

/*
 * Finds the index of data in the given category
 */
int Settings::findIndexByData(int categoryIndex, QMap<QString, QString> data){

    for(int i = 0; i < save[categoryIndex].data.size(); i++){

        bool same = true;
        for(int x = 0; x < labels.size(); x++){
            if(save[categoryIndex].data[i][labels[x]] != data[labels[x]]){
                same = false;
                break;
            }
        }

        if(same){
            return i;
        }

    }

    return -1;
}

/*
 * From a QJsonDocument it packs it to a QList<Data>
 */
QList<Settings::Data> Settings::packStruct(QJsonDocument doc){
    QList<Data> data;

    QJsonArray categoryArr = doc.array();
    for(int i = 0; i < categoryArr.size(); i++){
        QJsonObject categoryObj = categoryArr[i].toObject();

        Data emptyStruct;
        data.append(emptyStruct);
        data[i].name = categoryObj["name"].toString();

        QJsonArray dataArr = categoryObj["data"].toArray();
        QMap<QString, QString> temp;
        for(int j = 0; j < dataArr.size(); j++){
            QJsonObject dataObj = dataArr[j].toObject();

            for(int x = 0; x < labels.size(); x++){
                temp[labels[x]] = dataObj[labels[x]].toString();
            }

            data[i].data.append(temp);
        }

    }

    return data;
}

/*
 * From a QList<Data> it unpacks it to a QJsonDocument
 */
QJsonDocument Settings::unpackStruct(QList<Data> data){
    QJsonDocument saveData;
    QJsonObject categoryObj;
    QJsonArray categoryArr;

    for(int i = 0; i < save.size(); i++){
        categoryObj["name"] = data[i].name;

        QJsonArray dataArr;
        for(int j = 0; j < data[i].data.size(); j++){
            QJsonObject dataObj;
            for(int x = 0; x < labels.size(); x++){
                dataObj[labels[x]] = data[i].data[j][labels[x]];
            }

            dataArr.append(dataObj);
        }

        categoryObj["data"] = dataArr;
        categoryArr.append(categoryObj);
    }

    saveData.setArray(categoryArr);

    return saveData;
}

/*
 * TODO
 */
QMap<QString, QString> Settings::parseData(QStringList data){
    QMap<QString, QString> parse;

    for(int i = 0; i < labels.size(); i++){
        parse[labels[i]] = data[i];
    }

    return parse;
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void Settings::terminateLoop(){
    loop.exit(1);
    this->close();
}

/*
 * Is called when the dialog is closed
 * Closes the window and exists the event loop
 */
void Settings::closeEvent(QCloseEvent *){
    loop.exit(1);
    this->close();
}
