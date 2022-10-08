#include "dialog.h"
#include "ui_dialog.h"

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
}

Dialog::~Dialog()
{
    delete ui;
}
