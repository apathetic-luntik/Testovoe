#include "calendarmodel.h"
#include "database.h"
#include "metricmodel.h"
#include "notemodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Главная точка входа в приложение
// Инициализирует все компоненты и запускает главный цикл событий
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  // Инициализация базы данных - создает файл calendar_tracker.db и таблицы
  // Database::instance().init();

  // Создание моделей данных для работы с календарем, метриками и заметками
  CalendarModel calendarModel;
  MetricModel metricModel;
  NoteModel noteModel;

  // Настройка QML движка и регистрация моделей в контексте QML
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("calendarModel", &calendarModel);
  engine.rootContext()->setContextProperty("metricModel", &metricModel);
  engine.rootContext()->setContextProperty("noteModel", &noteModel);

  // Загрузка главного QML файла
  const QUrl url("qrc:/CalendarTracker/qml/main.qml");
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
