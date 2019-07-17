#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    prompt()
{
    ui->setupUi(this);



    manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        ui->directoryList->clear();
        ui->directoryContents->clear();
        ui->directoryLabel->setText("Directory:");

        if(reply->error()){
            qDebug() << reply->errorString();
            ui->directoryContents->addItem(reply->errorString());
            return;
        }

        // Setting the folderStructure
        QString response = reply->readAll();
        folderStructure = QJsonDocument::fromJson(response.toUtf8());

        // Showing the directories from the server
        QJsonArray arr = folderStructure.array();
        QStringList list;

        list.append("Main");
        foreach(QJsonValue val, arr){
            if(val["type"] == "folder"){
                list.append(val["name"].toString());
            }
        }

        ui->directoryList->addItems(list);
    });


    request.setUrl(QUrl(url + "getFolders"));
    manager->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::on_addFiles_triggered()
{
    QStringList filePath = QFileDialog::getOpenFileNames(this, "Select a file", "/home/oldrich/Desktop", "All files (*)");

    QStringList contents;
    foreach(QString path, filePath){

        QFile file(path);
        if(file.open(QIODevice::ReadOnly)){
            QString fileName = file.fileName().section("/", -1, -1);

            QString path;
            if(itemPath == ""){
                path = fileName;
            } else {
                path = itemPath + "/" + fileName;
            }

            QString fileContent = file.readAll().toBase64();
            request.setUrl(QUrl(url + "/uploadFile?path=" + path + "&content=" + fileContent));
            manager->get(request);
        }

    }

}

void MainWindow::on_directoryList_itemPressed(QListWidgetItem *item)
{
    itemPath = item->text();
    if(itemPath == "Main"){
        itemPath = "";
    }

    this->updateDirectoryContents(itemPath);

}

void MainWindow::updateDirectoryContents(QString directory){

    ui->directoryContents->clear();

    QStringList path = directory.split("/");

    QStringList list;

    // Getting content for the root directory
    if(path[0] == ""){

        QJsonArray arr = folderStructure.array();

        foreach(QJsonValue val, arr){
            if(val["type"] != "folder"){
                list.append(val["name"].toString() + "\t\t\t(" + val["description"].toString().split("\n")[0] + ")");
            }
        }

    } else {


        QJsonArray contents = folderStructure.array();

        bool done = false;

        int pathIndex = 0;

        // Finding the directory of folder
        while(done == false){

            for(int i = 0; i < contents.size(); i++){

                if(QJsonValue(contents[i])["name"] == path[pathIndex]){

                    contents = QJsonValue(contents[i])["contents"].toArray();
                    pathIndex++;


                    if(pathIndex == path.size()){

                        list.append("Go back");
                        foreach(QJsonValue val, contents){
                            if(val["type"] == "folder"){
                                list.append(val["name"].toString() + "\t\t\t(Directory)");
                            } else {
                                list.append(val["name"].toString() + "\t\t\t(" + val["description"].toString().split("\n")[0] + ")");
                            }
                        }

                        done = true;
                        break;
                    } else {
                        break;
                    }

                }

            }


        }

    }

    if(list.size() > 0){
        ui->directoryContents->addItems(list);
    } else {
        QString msg = "No files or folders in directory";
        ui->directoryContents->addItem(msg);
    }

    ui->directoryLabel->setText("Directory: " + itemPath);
}

void MainWindow::on_directoryContents_itemClicked(QListWidgetItem *item)
{
    QString name = item->text();

    if(name.contains("Directory")){
        itemPath = itemPath + "/" + name.split("\t")[0];

        updateDirectoryContents(itemPath);

    } else if(name.contains("Go back")){
        QStringList temp = itemPath.split("/");
        temp.removeLast();
        itemPath = temp.join("/");

        updateDirectoryContents(itemPath);
    }
}

void MainWindow::on_addFolders_triggered()
{
    QString folderName = prompt.display();

    if(folderName.replace(" ", "") == ""){
        return;
    }

    if(itemPath != ""){
        itemPath += "/";
    }
    itemPath += folderName;

    ui->directoryLabel->setText("Directory: " + itemPath);
    ui->directoryContents->clear();
}
