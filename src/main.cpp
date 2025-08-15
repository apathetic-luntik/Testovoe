#include "calendarmodel.h"
#include "database.h"
#include "metricmodel.h"
#include "notemodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

 Database::instance().init();

  CalendarModel calendarModel;
  MetricModel metricModel;
  NoteModel noteModel;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("calendarModel", &calendarModel);
  engine.rootContext()->setContextProperty("metricModel", &metricModel);
  engine.rootContext()->setContextProperty("noteModel", &noteModel);

  const QUrl url("qrc:/qt/qml/test5/qml/main.qml");

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
