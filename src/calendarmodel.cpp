#include "calendarmodel.h"
#include "database.h"
#include <QColor>
#include <QDate>
#include <QDebug>

CalendarModel::CalendarModel(QObject *parent)
    : QAbstractListModel(parent), m_currentDate(QDate::currentDate()) {
  updateCalendar();
}

int CalendarModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return 42; // 6 недель * 7 дней для корректного отображения
}

QVariant CalendarModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  int row = index.row();
  QDate firstDay = QDate(m_currentDate.year(), m_currentDate.month(), 1);
  int firstDayOfWeek = firstDay.dayOfWeek();
  if (firstDayOfWeek == 7)
    firstDayOfWeek = 0; // Неделя начинается с понедельника
  
  // Начинаем с понедельника первой недели месяца
  QDate startDate = firstDay.addDays(-firstDayOfWeek);
  QDate cellDate = startDate.addDays(row);

  switch (role) {
  case DateRole:
    return cellDate;
  case DayNumberRole:
    return cellDate.day();
  case IsCurrentMonthRole:
    return cellDate.month() == m_currentDate.month();
  case IsTodayRole:
    return cellDate == QDate::currentDate();
  case AverageScoreRole: {
    auto metrics = Database::instance().getMetricsForDate(cellDate);
    if (metrics.isEmpty()) return 0.0;

    double sum = 0;
    for (const auto& metric : metrics) {
      sum += metric["value"].toInt();
    }
    return sum / metrics.size();
  }
  case ColorRole: {
    auto metrics = Database::instance().getMetricsForDate(cellDate);
    if (metrics.isEmpty()) return QColor(Qt::transparent);

    double sum = 0;
    for (const auto& metric : metrics) {
      sum += metric["value"].toInt();
    }
    double average = sum / metrics.size();
    return getColorForScore(average);
  }
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> CalendarModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[DateRole] = "date";
  roles[DayNumberRole] = "dayNumber";
  roles[IsCurrentMonthRole] = "isCurrentMonth";
  roles[IsTodayRole] = "isToday";
  roles[AverageScoreRole] = "averageScore";
  roles[ColorRole] = "color";
  return roles;
}

void CalendarModel::setDate(const QDate &date) {
  if (m_currentDate != date) {
    m_currentDate = date;
    updateCalendar();
    emit currentDateChanged();
  }
}

QDate CalendarModel::getDate() const { return m_currentDate; }

void CalendarModel::previousMonth() {
  m_currentDate = m_currentDate.addMonths(-1);
  updateCalendar();
  emit currentDateChanged();
}

void CalendarModel::nextMonth() {
  m_currentDate = m_currentDate.addMonths(1);
  updateCalendar();
  emit currentDateChanged();
}

void CalendarModel::previousYear() {
  m_currentDate = m_currentDate.addYears(-1);
  updateCalendar();
  emit currentDateChanged();
}

void CalendarModel::nextYear() {
  m_currentDate = m_currentDate.addYears(1);
  updateCalendar();
  emit currentDateChanged();
}

void CalendarModel::updateCalendar() {
  beginResetModel();
  endResetModel();
}

QColor CalendarModel::getColorForScore(double score) const {
  if (score <= 0)
    return QColor(Qt::transparent);

  // Градиент от красного (1) к зеленому (10)
  int red = static_cast<int>(255 * (1.0 - (score - 1) / 9.0));
  int green = static_cast<int>(255 * ((score - 1) / 9.0));

  return QColor(red, green, 0);
}

void CalendarModel::selectToday() {
  QDate today = QDate::currentDate();
  setDate(today);
}
