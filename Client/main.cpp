#include "Item.h"
#include "Model.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include<QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QList<Item*> data;

    data.append(new Item("name1", "0aafa1.10"));

    Model *model = new Model(data);

//    qInfo() << model->json();

    QQmlApplicationEngine engine;
    engine.globalObject().setProperty("myModel", engine.newQObject(model));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
