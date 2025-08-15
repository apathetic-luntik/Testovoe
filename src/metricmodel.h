#ifndef METRICMODEL_H
#define METRICMODEL_H

#include <QAbstractListModel>
#include <QDate>

class MetricModel : public QAbstractListModel {
  Q_OBJECT

public:
  //добавить везде
  ///
  /// \brief
  /// \param
  /// \return
  ///

  enum MetricRoles { IdRole = Qt::UserRole + 1, NameRole, ValueRole, DateRole };

  explicit MetricModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void addMetric(const QString &name, int value, const QDate &date);
  Q_INVOKABLE void updateMetric(int id, int value);
  Q_INVOKABLE void deleteMetric(int id);
  Q_INVOKABLE void loadMetricsForDate(const QDate &date);
    Q_INVOKABLE void addCustomMetric(const QString &name);
    Q_INVOKABLE void clearAllMetrics();

private:
  QList<QVariantMap> m_metrics;
  QDate m_currentDate;
};

#endif // METRICMODEL_H
