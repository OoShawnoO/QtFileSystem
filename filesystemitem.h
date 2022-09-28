#ifndef FILESYSTEMITEM_H
#define FILESYSTEMITEM_H

#include <QListWidgetItem>
#include "./FileSystem/headers/filesystem.h"

class FileSystemItem : public QListWidgetItem
{
public:
    explicit FileSystemItem(const QIcon &icon, const QString &text,
                            QListWidget *listview = nullptr, int type = Type);
signals:

};

#endif // FILESYSTEMITEM_H
