#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Clear(){
    listWidget->disconnect();
    listWidget->clear();
}

void MainWindow::PrintItems(){
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
            case LINK : {
                switch(dynamic_cast<link_c*>(filesystem)->get_real()->get_filetype())
                {
                    case DIR : {
                        v.pop_back();
                        v.push_back(dynamic_cast<link_c*>(filesystem)->get_real()->get_name());
                        user->cd(v);
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


        Clear();
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
        if(action->text() == "new"){
            qDebug() << " 新建 ----------->";
            if(listWidget->currentItem() != NULL){
                qDebug() << listWidget->currentItem()->text();
            }
        }else if(action->text() == "save"){
            qDebug() << " 保存 ----------->";
        }else if(action->text() == "back"){
            qDebug() << " 回退 ----------->";
        }else if(action->text() == "delete"){
            qDebug() << " 删除 ----------->";
        }else if(action->text() == "copy"){
            qDebug() << " 复制 ----------->";
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

