#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <modelinqmlcore/backend.h>
#include <modelinqmlcore/tablemodel.h>
#include <modelinqmlcore/particleviewmodel.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    BackEnd backend;

    qmlRegisterType<TableModel>("TableModel", 0, 1, "TableModel");
    qmlRegisterType<ParticleViewModel>("ParticleViewModel", 0, 1, "ParticleViewModel");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backEnd", &backend);
    engine.load("qrc:/main.qml");

    engine.addImportPath("./plugins");
    return app.exec();
}
