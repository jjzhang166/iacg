#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *root_ctx = engine.rootContext();
    root_ctx->setContextProperty("argcode",QVariant(argv[1]));
    root_ctx->setContextProperty("argdes",QVariant(argv[2]));

    engine.load(QUrl(QStringLiteral("qrc:/UI/bug_report.qml")));
    return app.exec();
}
