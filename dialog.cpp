#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->combo,&QComboBox::currentTextChanged,[=](const QString& str){
        if(str == "Link - 链接"){
            ui->linkobject->setEnabled(true);
            ui->linklabel->setEnabled(true);
        }else{
            ui->linklabel->setEnabled(false);
            ui->linkobject->setEnabled(false);
        }
    });
    connect(ui->finish,&QPushButton::clicked,[=](){
         int index = ui->combo->currentIndex();
         unsigned char state = 0;
         ui->read->isTristate()?state+=1:state+=0;
         ui->write->isTristate()?state+=2:state+=0;
         ui->excute->isTristate()?state+=3:state+=0;
         switch(index){
             case 0:{
                 file_c* file = new file_c(user,string(ui->filename->text().toUtf8()),
                                           dynamic_cast<filesystem_c*>(user->get_current_dir()),
                                           63u,63u,state);
                 file->set_filetype(TEXT);
             }
             case 1:{
                 file_c* file = new file_c(user,string(ui->filename->text().toUtf8()),
                                           dynamic_cast<filesystem_c*>(user->get_current_dir()),
                                           63u,63u,state);
                 file->set_filetype(BINARY);
             }
             case 2:{
                 dir_c* dir = new dir_c(user,string(ui->filename->text().toUtf8()),
                                        dynamic_cast<filesystem_c*>(user->get_current_dir()),
                                        63u,63u,state);
             }
             case 3:{
                 string str(ui->linkobject->text().toUtf8());
                 vector<string> v;
                 v.push_back(str);
                 link_c* link = new link_c(user,string(ui->filename->text().toUtf8()),
                                           dynamic_cast<filesystem_c*>(user->get_current_dir()),
                                           63u,63u,state);
                 user->TEMP(v,[&,link](user_c* user,string name){
                        filesystem_c* filesystem = user->get_current_dir()->get_contents()[name];
                        if(filesystem!=nullptr){
                           link->set_real(filesystem);
                        }else{
                            user->set_error(NOTFOUND);
                        }
                 });
             }
             this->close();
         }
    });
}

Dialog::~Dialog()
{
    delete ui;
}
