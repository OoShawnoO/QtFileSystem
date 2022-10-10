#include "filesystemlistwidget.h"
#include <QPainter>
#include <QDebug>
#include <QDrag>
#include <QMimeData>

FileSystemListWidget::FileSystemListWidget(QWidget *parent)
    : QListWidget(parent)
{
    m_item = NULL;
}

void FileSystemListWidget::mousePressEvent(QMouseEvent *event){
    //确保左键拖拽.
        if (event->button() == Qt::LeftButton)
        {
            //先保存拖拽的起点.
            m_startPos = event->pos();
            //保留被拖拽的项.
            m_item = itemAt(event->pos());
        }
        //保留原QListWidget部件的鼠标点击操作.
        QListWidget::mousePressEvent(event);
}

void FileSystemListWidget::mouseMoveEvent(QMouseEvent *event){
    //确保按住左键移动.
        if (event->buttons() & Qt::LeftButton)
        {
            QPoint temp = event->pos() - m_startPos;
            //只有这个长度大于默认的距离,才会被系统认为是形成拖拽的操作.
            if (temp.manhattanLength() > QApplication::startDragDistance())
            {
                QDrag *drag = new QDrag(this);
                QMimeData *mimeData = new QMimeData;
                mimeData->setText(m_item->text());
                drag->setMimeData(mimeData);
                auto action = drag->exec(Qt::CopyAction | Qt::MoveAction);
            }
        }
        QListWidget::mouseMoveEvent(event);
}

void FileSystemListWidget::dragEnterEvent(QDragEnterEvent *event){
        //设置动作为移动动作.
        event->setDropAction(Qt::MoveAction);
        //然后接受事件.这个一定要写.
        event->accept();
}

void FileSystemListWidget::dragMoveEvent(QDragMoveEvent *event){
        event->setDropAction(Qt::MoveAction);
        event->accept();
}

void FileSystemListWidget::dropEvent(QDropEvent *event){
    QString str = event->mimeData()->text();
    if (!str.isEmpty())
    {
        //找到当前鼠标位置在部件中的项.
        auto item = this->itemAt(event->pos());
        //
        vector<string> v;
        v.push_back(MAP[m_item]->get_name());
        v.push_back("./"+MAP[item]->get_name()+"/");
        for(auto i : v) {qDebug() << i.c_str();}
        user->mv(v);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void FileSystemListWidget::mouseReleaseEvent(QMouseEvent *event){

}

void FileSystemListWidget::mouseDoubleClickEvent(QMouseEvent *event){
    QListWidgetItem* item = itemAt(event->pos());
    if(item!=NULL){
        filesystem_c* filesystem = MAP[item];
        emit itemDoubleClicked(itemAt(event->pos()),filesystem);
    }

}
