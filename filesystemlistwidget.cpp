#include "filesystemlistwidget.h"
#include <QDebug>

FileSystemListWidget::FileSystemListWidget(QWidget *parent)
    : QListWidget(parent)
{
    m_item = NULL;
}

void FileSystemListWidget::mouseDoubleClickEvent(QMouseEvent *event){
    QListWidgetItem* item = itemAt(event->pos());
    if(item!=NULL){
        filesystem_c* filesystem = MAP[item];
        emit itemDoubleClicked(itemAt(event->pos()),filesystem);
    }

}
