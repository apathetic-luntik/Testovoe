#include "database.h"



Database &Database::instance() {
 static Database instance;
 return instance;
}

bool Database::init() {
 m_db = QSqlDatabase::addDatabase("QSQLITE");

 QString dbPath = QDir::currentPath() + "/calendar_tracker.db";
 m_db.setDatabaseName(dbPath);

 if (!m_db.open()) {
   qDebug() << "Не удалось открыть базу данных:" << m_db.lastError().text();
   return false;
 }

 QSqlQuery query;

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

bool Database::addMetric(const QString &name, int value, const QDate &date) {
 QSqlQuery query;
 query.prepare("INSERT INTO metrics (name, value, date) VALUES (?, ?, ?)");
 query.addBindValue(name);
 query.addBindValue(value);
 query.addBindValue(date.toString(Qt::ISODate));

 return query.exec();
}

bool Database::updateMetric(int id, int value) {
 QSqlQuery query;
 query.prepare("UPDATE metrics SET value = ? WHERE id = ?");
 query.addBindValue(value);
 query.addBindValue(id);

 return query.exec();
}

bool Database::deleteMetric(int id) {
 QSqlQuery query;
 query.prepare("DELETE FROM metrics WHERE id = ?");
 query.addBindValue(id);

 return query.exec();
}

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

bool Database::addNote(const QString &text, const QDate &date) {
 QSqlQuery query;
 query.prepare("INSERT INTO notes (text, date) VALUES (?, ?)");
 query.addBindValue(text);
 query.addBindValue(date.toString(Qt::ISODate));

 return query.exec();
}

bool Database::updateNote(int id, const QString &text) {
 QSqlQuery query;
 query.prepare("UPDATE notes SET text = ? WHERE id = ?");
 query.addBindValue(text);
 query.addBindValue(id);

 return query.exec();
}

bool Database::deleteNote(int id) {
 QSqlQuery query;
 query.prepare("DELETE FROM notes WHERE id = ?");
 query.addBindValue(id);

 return query.exec();
}

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

bool Database::clearAllMetrics() {
    QSqlQuery query;
    return query.exec("DELETE FROM metrics");
}

bool Database::clearAllNotes() {
    QSqlQuery query;
    return query.exec("DELETE FROM notes");
}

bool Database::clearAllData() {
    return clearAllMetrics() && clearAllNotes();
}
