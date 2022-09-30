#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::ErrorMessage(){
    switch(user->get_error()){
        case NOTFOUND : {
            QMessageBox::critical(this,"Error","File Not Found.");
            break;
        }
        case NOTTEXT : {
            QMessageBox::critical(this,"Error","Not A Text File.");
        }
        case NOTDIR :{
            QMessageBox::critical(this,"Error","Not A Dir.");
        }
        case PERMISSION :{
            QMessageBox::critical(this,"Error","Permission Denied.");
        }
        default : {

        }
    }
    user->set_error(NO);
}

void MainWindow::Clear(){
    listWidget->disconnect();
    listWidget->clear();
}

void MainWindow::PrintItems(){
    Clear();
    for(auto item : user->get_current_dir()->get_contents()){
        QListWidgetItem* listitem = nullptr;
        switch(item.second->get_filetype()){
            case DIR : {
                listitem = new QListWidgetItem(QIcon(":/res/dir.png"),item.first.c_str());
                break;
            }
            case BINARY : {
                listitem = new QListWidgetItem(QIcon(":/res/binary.png"),item.first.c_str());
                break;
            }
            case TEXT : {
                listitem = new QListWidgetItem(QIcon(":/res/txt.png"),item.first.c_str());
                break;
            }
            case UNKNOWN : {
                listitem = new QListWidgetItem(QIcon(":/res/unknown.png"),item.first.c_str());
                break;
            }
            case LINK : {
                listitem = new QListWidgetItem(QIcon(":/res/link.png"),item.first.c_str());
                break;
            }
            default : {
                listitem = new QListWidgetItem(QIcon(":/res/unknown.png"),item.first.c_str());
                break;
            }
        }

        if(listitem != nullptr){
            listWidget->MAP[listitem] = item.second;
            listWidget->addItem(listitem);
        }
    }
    connect(listWidget,&FileSystemListWidget::itemDoubleClicked,[=](QListWidgetItem* item,filesystem_c* filesystem){
        qDebug() << filesystem->get_name().c_str();
        vector<string> v;
        v.push_back(filesystem->get_name());
        switch(filesystem->get_filetype()){
            case DIR : {
                user->cd(v);
                ErrorMessage();
                break;
            }
            case BINARY : {

                break;
            }
            case TEXT : {
                user->vim(v);
                ErrorMessage();
                break;
            }
            case UNKNOWN : {

                break;
            }
            case LINK : {
                switch(dynamic_cast<link_c*>(filesystem)->get_real()->get_filetype())
                {
                    case DIR : {
                        v.clear();
                        v.push_back(dynamic_cast<link_c*>(filesystem)->get_real()->get_name());
                        user->cd(v);
                        ErrorMessage();
                        break;
                    }
                    case BINARY : {

                        break;
                    }
                    case TEXT : {

                        break;
                    }
                    case UNKNOWN : {

                        break;
                    }
                    default : {
                        break;
                    }
                }
                break;
            }
            default : {
                break;
            }
        }
        PrintItems();
    });
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/Icon.png"));
    listWidget = ui->listWidget;
    dir_c* D = new dir_c(user,"123",dynamic_cast<filesystem_c*>(root));
    file_c* F1 = new file_c(user,"文件1.txt",dynamic_cast<filesystem_c*>(root));
    link_c* L = new link_c(user,"链接1",dynamic_cast<filesystem_c*>(root));
    file_c* F2 = new file_c(user,"文件2",dynamic_cast<filesystem_c*>(root));
    L->set_real(D);
    user->set_current_dir(root);
    PrintItems();
    connect(ui->toolBar,&QToolBar::actionTriggered,[=](QAction* action){
        vector<string> v;
        if(action->text() == "new"){
            Dialog dialog(this);
            dialog.exec();
            dialog.setAttribute(Qt::WA_DeleteOnClose);
        }else if(action->text() == "save"){

        }else if(action->text() == "back"){
            v.push_back("..");
            user->cd(v);
            PrintItems();
            v.clear();
        }else if(action->text() == "delete"){
            if(listWidget->currentItem() != NULL){
                v.push_back(listWidget->MAP[listWidget->currentItem()]->get_name());
                user->rm(v);
                PrintItems();
                v.clear();
            }
        }else if(action->text() == "copy"){
            if(listWidget->currentItem() != NULL){

            }
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

