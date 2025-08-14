#include "database.h"

#include <QDebug>
#include <QDir>

// Получение единственного экземпляра базы данных (Singleton pattern)
Database &Database::instance() {
 static Database instance;
 return instance;
}

////// Инициализация базы данных: создание файла и таблиц
bool Database::init() {
 m_db = QSqlDatabase::addDatabase("QSQLITE");

 // Определяем путь к базе данных в текущей директории
 QString dbPath = QDir::currentPath() + "/calendar_tracker.db";
 m_db.setDatabaseName(dbPath);

 if (!m_db.open()) {
   qDebug() << "Не удалось открыть базу данных:" << m_db.lastError().text();
   return false;
 }

 // Создание таблиц для метрик и заметок
 QSqlQuery query;

 // Таблица метрик: хранит название, значение (1-10) и дату
 query.exec("CREATE TABLE IF NOT EXISTS metrics ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "value INTEGER NOT NULL CHECK(value >= 1 AND value <= 10),"
            "date TEXT NOT NULL)");

 // Таблица заметок: хранит текст и дату
 query.exec("CREATE TABLE IF NOT EXISTS notes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "text TEXT NOT NULL,"
            "date TEXT NOT NULL)");

 return true;
}

// Добавление новой метрики в базу данных
bool Database::addMetric(const QString &name, int value, const QDate &date) {
 QSqlQuery query;
 query.prepare("INSERT INTO metrics (name, value, date) VALUES (?, ?, ?)");
 query.addBindValue(name);
 query.addBindValue(value);
 query.addBindValue(date.toString(Qt::ISODate));

 return query.exec();
}

// Обновление значения существующей метрики
bool Database::updateMetric(int id, int value) {
 QSqlQuery query;
 query.prepare("UPDATE metrics SET value = ? WHERE id = ?");
 query.addBindValue(value);
 query.addBindValue(id);

 return query.exec();
}

// Удаление метрики из базы данных
bool Database::deleteMetric(int id) {
 QSqlQuery query;
 query.prepare("DELETE FROM metrics WHERE id = ?");
 query.addBindValue(id);

 return query.exec();
}

// Получение всех метрик для конкретной даты
QList<QVariantMap> Database::getMetricsForDate(const QDate &date) {
 QList<QVariantMap> metrics;
 QSqlQuery query;
 query.prepare("SELECT id, name, value FROM metrics WHERE date = ?");
 query.addBindValue(date.toString(Qt::ISODate));

 if (query.exec()) {
   while (query.next()) {
     QVariantMap metric;
     metric["id"] = query.value("id").toInt();
     metric["name"] = query.value("name").toString();
     metric["value"] = query.value("value").toInt();
     metrics.append(metric);
   }
 }

 return metrics;
}

// Получение всех метрик из базы данных
QList<QVariantMap> Database::getAllMetrics() {
 QList<QVariantMap> metrics;
 QSqlQuery query("SELECT id, name, value, date FROM metrics");

 if (query.exec()) {
   while (query.next()) {
     QVariantMap metric;
     metric["id"] = query.value("id").toInt();
     metric["name"] = query.value("name").toString();
     metric["value"] = query.value("value").toInt();
     metric["date"] = query.value("date").toString();
     metrics.append(metric);
   }
 }

 return metrics;
}

// Добавление новой заметки в базу данных
bool Database::addNote(const QString &text, const QDate &date) {
 QSqlQuery query;
 query.prepare("INSERT INTO notes (text, date) VALUES (?, ?)");
 query.addBindValue(text);
 query.addBindValue(date.toString(Qt::ISODate));

 return query.exec();
}

// Обновление текста существующей заметки
bool Database::updateNote(int id, const QString &text) {
 QSqlQuery query;
 query.prepare("UPDATE notes SET text = ? WHERE id = ?");
 query.addBindValue(text);
 query.addBindValue(id);

 return query.exec();
}

// Удаление заметки из базы данных
bool Database::deleteNote(int id) {
 QSqlQuery query;
 query.prepare("DELETE FROM notes WHERE id = ?");
 query.addBindValue(id);

 return query.exec();
}

// Получение всех заметок для конкретной даты
QList<QVariantMap> Database::getNotesForDate(const QDate &date) {
 QList<QVariantMap> notes;
 QSqlQuery query;
 query.prepare("SELECT id, text FROM notes WHERE date = ?");
 query.addBindValue(date.toString(Qt::ISODate));

 if (query.exec()) {
   while (query.next()) {
     QVariantMap note;
     note["id"] = query.value("id").toInt();
     note["text"] = query.value("text").toString();
     notes.append(note);
   }
 }

 return notes;
}
