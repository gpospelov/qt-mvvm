#include "modelinqmlcore/backend.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    qRegisterMetaType<TableModel*>("TableModel*");
    qRegisterMetaType<ParticleViewModel*>("ParticleViewModel*");
    BackEnd backend;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backEnd", &backend);
    engine.load("qrc:/main.qml");

    return app.exec();
}
