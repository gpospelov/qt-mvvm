#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <modelinqmlcore/backend.h>
#include <modelinqmlcore/tablemodel.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    BackEnd backend;

    qmlRegisterType<TableModel>("TableModel", 0, 1, "TableModel");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("BackEnd", &backend);
    engine.load("qrc:/main.qml");

    engine.addImportPath("./plugins");
    return app.exec();
}
