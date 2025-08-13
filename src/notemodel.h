#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractListModel>
#include <QDate>

class NoteModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NoteRoles {
        IdRole = Qt::UserRole + 1,
        TextRole,
        DateRole
    };

    explicit NoteModel(QObject *parent = nullptr);

    // Переопределение методов QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Методы для работы с заметками
    Q_INVOKABLE void addNote(const QString& text, const QDate& date);
    Q_INVOKABLE void updateNote(int id, const QString& text);
    Q_INVOKABLE void deleteNote(int id);
    Q_INVOKABLE void loadNotesForDate(const QDate& date);

private:
    QList<QVariantMap> m_notes;
    QDate m_currentDate;
};

#endif // NOTEMODEL_H
