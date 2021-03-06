#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    prompt(),
    settings()
{
    ui->setupUi(this);


    // Opening the info file to get the cookie and the url
    QFile infoFile(QDir::currentPath() + "/info");
    infoFile.open(QIODevice::ReadOnly);
    QList<QByteArray> contents = infoFile.readAll().split(0x0a);

    // If the settings are correct
    if(contents.size() == 2 && (contents[0] != "" || contents[1] != "")){
        url = contents[urlIndex];
        cookie = contents[cookieIndex];
    } else {
        on_settings_triggered(true);
    }

    if(url.endsWith("/") == false){
        url += "/";
    }
    if(url.startsWith("http") == false){
        url.push_front("http://");
    }

    // Setting the cookie
    request.setRawHeader("Cookie", "auth=" + cookie.toUtf8());

    // When right clicked an item
    connect(ui->directoryList, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(display_menu_on_click(const QPoint &)));
    connect(ui->directoryContents, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(display_menu_on_click(const QPoint &)));

    // Clearing the selections
    connect(ui->directoryList, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(clear_selection(QListWidgetItem *)));
    connect(ui->directoryContents, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(clear_selection(QListWidgetItem *)));

    manager = new QNetworkAccessManager();

    // Getting data from the API
    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        ui->directoryList->clear();
        ui->directoryContents->clear();
        ui->directoryLabel->setText("Directory:");

        if(reply->error()){
            qDebug() << reply->errorString();
            ui->directoryContents->addItem(reply->errorString());
            return;
        }

        QString response = reply->readAll();
        if(response == "Unauthorized"){
            ui->directoryContents->addItem(response);
            return;
        }

        // Setting the folderStructure
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

        QListWidgetItem *firstItem = ui->directoryList->itemAt(QPoint(0, 0));
        firstItem->setFlags(firstItem->flags() & Qt::ItemIsEnabled);
    });

    request.setUrl(QUrl(url + "getFolders"));
    manager->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

// Adding files to the currently selected directory
// If no directory selected, it is added to the root
void MainWindow::on_addFiles_triggered()
{
    QStringList filePath = QFileDialog::getOpenFileNames(this, "Select a file", QDir::currentPath(), "All files (*)");

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

            request.setUrl(QUrl(url + "uploadFile?path=" + path));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            manager->post(request, "file=" + file.readAll().toBase64());
        }

    }

}

// Changing the directoryContents widget to display
// all the contents of the folder selected
void MainWindow::on_directoryList_itemPressed(QListWidgetItem *item)
{
    itemPath = item->text();
    if(itemPath == "Main"){
        itemPath = "";
    }

    this->updateDirectoryContents(itemPath);
}

// Displays the contents of a directory
void MainWindow::updateDirectoryContents(QString directory){

    ui->directoryContents->clear();

    QStringList path = directory.split("/");

    QStringList list;

    // Getting content for the root directory
    if(path[0] == ""){

        QJsonArray arr = folderStructure.array();

        foreach(QJsonValue val, arr){
            if(val["type"] != "folder"){
                list.append(val["name"].toString() + "\t(" + val["description"].toString().split("\n")[0] + ")");
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
                                list.append(val["name"].toString() + "\t(Directory)");
                            } else {
                                list.append(val["name"].toString() + "\t(" + val["description"].toString().split("\n")[0] + ")");
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

    QListWidgetItem *firstItem = ui->directoryContents->itemAt(QPoint(0, 0));
    firstItem->setFlags(firstItem->flags() & Qt::ItemIsEnabled);

    ui->directoryLabel->setText("Directory: " + itemPath);
}

// Changes the directoryContents when clicked
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

// Adds a folder to the current directory
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

// When right clicked on the directoryContent widget
// the same menu is showed when clicked on the menubar
void MainWindow::display_menu_on_click(const QPoint &pos)
{
    Q_UNUSED(pos);

    QMenu menu("Options", this);

    menu.addAction("Add files", this, &MainWindow::on_addFiles_triggered);
    menu.addAction("Add folder", this, &MainWindow::on_addFolders_triggered);
    menu.addAction("Remove selection", this, &MainWindow::remove_file_or_folders);
    menu.exec(QCursor::pos());
}

// Removes a file or a folder
void MainWindow::remove_file_or_folders(){

    QList<QListWidgetItem *> directoryListSelection = ui->directoryList->selectedItems();
    QList<QListWidgetItem *> directoryContentsSelection = ui->directoryContents->selectedItems();
    QString itemName;

    if(directoryListSelection.size() == 1){
        itemName = directoryListSelection[0]->text();
    } else if(directoryContentsSelection.size() == 1){
        itemName = itemPath + "/" + directoryContentsSelection[0]->text().split("\t")[0];
    } else {
        return;
    }


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Are you sure you want to delete " + itemName, QMessageBox::Yes|QMessageBox::No);

    if(reply == QMessageBox::No){
        return;
    }

    itemName = itemName.split("\t")[0];

    request.setUrl(QUrl(url + "remove?path=" + itemName));
    manager->get(request);

}

// Removes the selection in the QListWidget
void MainWindow::clear_selection(QListWidgetItem *item){
    Q_UNUSED(item);


    QString name = sender()->objectName();

    if(name == "directoryList"){
        ui->directoryContents->clearSelection();
    } else if(name == "directoryContents"){
        ui->directoryList->clearSelection();
    }


}

// When the settings are opened
void MainWindow::on_settings_triggered(bool fromStartup = false)
{
    QStringList values = settings.getValues(fromStartup);

    QString urlValue = values[urlIndex].replace(" ", "");
    QString cookieValue = values[cookieIndex].replace(" ", "");

    if(urlValue == "" && cookieValue == "" && fromStartup){
        QMessageBox messageBox;
        messageBox.critical(nullptr, "No settings", "No settings were entered");
        exit(1);
    }

    if(urlValue == "" && cookieValue == ""){
        return;
    }

    url = urlValue;
    cookie = cookieValue;

    QFile infoFile(QDir::currentPath() + "/info");
    infoFile.open(QIODevice::WriteOnly);
    infoFile.write(url.toUtf8() + "\n" + cookie.toUtf8());

    if(fromStartup == false){
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
}
