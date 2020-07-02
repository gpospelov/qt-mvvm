#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <modelinqmlcore/tablemodel.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<TableModel>("TableModel", 0, 1, "TableModel");

    QQmlApplicationEngine engine("qrc:/main.qml");

    engine.addImportPath("./plugins");
    return app.exec();
}
