#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./FileSystem/headers/main.h"
#include <QToolBar>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include <QAction>
#include "filesystemitem.h"
#include "dialog.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void PrintItems();
    void Clear();
    void ErrorMessage();
    void InitToolBar();
    void InitGoButton();
private:
    Ui::MainWindow *ui;
    FileSystemListWidget* listWidget;
};
#endif // MAINWINDOW_H
