#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QListView>
#include <QTextEdit>

#include <QStringListModel>

#include "Model.h"
#include "Item.h"
#include "Conn.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGridLayout mainLayout;
    QListView *listData, *connectionView;
    QList<Item*> data;
    Model *model;

    QStringListModel connection;

    QTextEdit *te;
    QWidget mainWidget;

    Conn *conn;

private slots:
    void changeConnectList(QStringList list);
};
#endif // MAINWINDOW_H
