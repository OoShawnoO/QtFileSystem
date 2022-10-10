#ifndef FILESYSTEMLISTWIDGET_H
#define FILESYSTEMLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QApplication>
#include "filesystemitem.h"

class FileSystemListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit FileSystemListWidget(QWidget *parent = nullptr);

    QListWidgetItem* m_item;
    QPoint m_startPos;
    map<QListWidgetItem*,filesystem_c*> MAP;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
Q_SIGNALS:
    void itemDoubleClicked(QListWidgetItem*,filesystem_c*);
};

#endif // FILESYSTEMLISTWIDGET_H
