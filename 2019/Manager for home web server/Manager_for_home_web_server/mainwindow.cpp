#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        if(reply->error()){
            qDebug() << reply->errorString();
            return;
        }

        // Setting the folderStructure
        QString response = reply->readAll();
        folderStructure = QJsonDocument::fromJson(response.toUtf8());

        // Showing the directories from the server
        QJsonArray arr = folderStructure.array();
        QStringList list;
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

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        if(reply->error()){
            qDebug() << reply->errorString();
            return;
        }

        qDebug() << reply->readAll();
    });

    QStringList contents;
    foreach(QString path, filePath){

        QFile file(path);
        if(file.open(QIODevice::ReadOnly)){
            QString fileContent = file.readAll().toBase64();
            request.setUrl(QUrl(url + "/uploadFile?path=" + itemPath + "&content=" + fileContent));
            manager->get(request);
        }

    }

}

void MainWindow::on_directoryList_itemPressed(QListWidgetItem *item)
{
    itemPath = item->text();

    this->updateDirectoryContents(itemPath);

}

void MainWindow::updateDirectoryContents(QString directory){

    ui->directoryContents->clear();

    QStringList path = directory.split("/");

    QStringList list;

    // Getting content for the root directory
    if(path[0] == "Main"){

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
        QString msg = "No files in directory";
        ui->directoryContents->addItem(msg);
    }
}

void MainWindow::on_directoryContents_itemClicked(QListWidgetItem *item)
{
    QString name = item->text();

    if(name.contains("Directory")){
        itemPath = itemPath + "/" + name.split("\t")[0];

        updateDirectoryContents(itemPath);
    }
}
