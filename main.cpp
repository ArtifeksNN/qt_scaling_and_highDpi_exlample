#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {

  // qt.conf
  //    [Platforms]
  //    WindowsArguments = dpiawareness=0

  //  qputenv("QT_SCALE_FACTOR", "2.0");

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
      Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
  //  Qt::Round
  //  Qt::Ceil
  //  Qt::Floor
  //  Qt::RoundPreferFloor
  //  Qt::PassThrough
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
