#include "filesystemitem.h"

FileSystemItem::FileSystemItem(const QIcon &icon, const QString &text,
                               QListWidget *listview, int type)
    : QListWidgetItem(icon,text,listview,type)
{

}
