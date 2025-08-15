#ifndef CALENDARMODEL_H
#define CALENDARMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <QDate>

class CalendarModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum CalendarRoles {
    DateRole = Qt::UserRole + 1,
    DayNumberRole,
    IsCurrentMonthRole,
    IsTodayRole,
    AverageScoreRole,
    ColorRole
  };

  explicit CalendarModel(QObject *parent = nullptr);

  // Переопределение методов QAbstractListModel
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  // Методы для работы с календарем
  Q_INVOKABLE void setDate(const QDate &date);
  Q_INVOKABLE QDate getDate() const;
  Q_INVOKABLE void previousMonth();
  Q_INVOKABLE void nextMonth();
  Q_INVOKABLE void previousYear();
  Q_INVOKABLE void nextYear();

signals:
  void currentDateChanged();

private:
  QDate m_currentDate;
  QDate m_selectedDate;
  void updateCalendar();
  QColor getColorForScore(double score) const;
};

#endif // CALENDARMODEL_H
