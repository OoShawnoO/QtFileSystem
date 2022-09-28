#include "filesystemlistwidget.h"
#include <QDebug>

FileSystemListWidget::FileSystemListWidget(QWidget *parent)
    : QListWidget(parent)
{
    m_item = NULL;
}

void FileSystemListWidget::mouseDoubleClickEvent(QMouseEvent *event){
    filesystem_c* filesystem = MAP[itemAt(event->pos())];
    emit itemDoubleClicked(itemAt(event->pos()),filesystem);
}
