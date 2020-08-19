#include "MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      listData(new QListView),
      connectionView(new QListView),
      te(new QTextEdit),
      conn(new Conn(3322))
{
    data.append(new Item("name1", "01.10"));
    data.append(new Item("name2", "23.35"));
    data.append(new Item("name3", "13.45"));


    connection.setStringList(QStringList()<< "Нет подключений");
    connectionView->setModel(&connection);

    model = new Model(data);
    conn->setModel(model);
    connect(conn, &Conn::updateConnections,
            this, &MainWindow::changeConnectList);

    listData->setModel(model);
    connect(listData, &QListView::clicked,
            [this](const QModelIndex& index){
        te->setText(index.data(Model::JSON).toString());
    });

    qInfo() << model->rowCount();
    qInfo() << model->columnCount();

    mainLayout.addWidget(listData);
    mainLayout.addWidget(te,0,1);
    mainLayout.addWidget(connectionView,1,0,1,2);

    mainWidget.setLayout(&mainLayout);
    setCentralWidget(&mainWidget);
}

MainWindow::~MainWindow()
{
    delete listData;
    delete te;
}

void MainWindow::changeConnectList(QStringList list)
{
    connection.setStringList(list);
}

