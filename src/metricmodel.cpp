#include "metricmodel.h"
#include "database.h"

MetricModel::MetricModel(QObject *parent) : QAbstractListModel(parent) {}

int MetricModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_metrics.size();
}

QVariant MetricModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_metrics.size())
    return QVariant();

  const QVariantMap &metric = m_metrics.at(index.row());

  switch (role) {
  case IdRole:
    return metric["id"];
  case NameRole:
    return metric["name"];
  case ValueRole:
    return metric["value"];
  case DateRole:
    return metric["date"];
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> MetricModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[NameRole] = "name";
  roles[ValueRole] = "value";
  roles[DateRole] = "date";
  return roles;
}

void MetricModel::addMetric(const QString &name, int value, const QDate &date) {
     // if (Database::instance().addMetric(name, value, date)) {
     //     loadMetricsForDate(date);
     // }
}

void MetricModel::updateMetric(int id, int value) {
     // if (Database::instance().updateMetric(id, value)) {
     //     loadMetricsForDate(m_currentDate);
     // }
}

void MetricModel::deleteMetric(int id) {
     // if (Database::instance().deleteMetric(id)) {
     //     loadMetricsForDate(m_currentDate);
     // }
}

void MetricModel::loadMetricsForDate(const QDate &date) {
  beginResetModel();
  m_currentDate = date;
  // m_metrics = Database::instance().getMetricsForDate(date);
  endResetModel();
}

void MetricModel::addCustomMetric(const QString &name) {
  // Заглушка для добавления пользовательских метрик
  Q_UNUSED(name)
}
