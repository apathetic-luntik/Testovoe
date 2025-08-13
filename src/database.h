#ifndef DATABASE_H
#define DATABASE_H

#include <QDate>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

// class Database {
// public:
//  static Database &instance();
//  bool init();

//  // Методы для работы с метриками
//  bool addMetric(const QString &name, int value, const QDate &date);
//  bool updateMetric(int id, int value);
//  bool deleteMetric(int id);
//  QList<QVariantMap> getMetricsForDate(const QDate &date);
//  QList<QVariantMap> getAllMetrics();

//  // Методы для работы с заметками
//  bool addNote(const QString &text, const QDate &date);
//  bool updateNote(int id, const QString &text);
//  bool deleteNote(int id);
//  QList<QVariantMap> getNotesForDate(const QDate &date);

// private:
//  Database() = default;
//  ~Database() = default;
//  Database(const Database &) = delete;
//  Database &operator=(const Database &) = delete;

//  QSqlDatabase m_db;
//};

#endif // DATABASE_H
