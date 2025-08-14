#include "notemodel.h"
#include "database.h"

NoteModel::NoteModel(QObject *parent) : QAbstractListModel(parent) {}

int NoteModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_notes.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_notes.size())
    return QVariant();

  const QVariantMap &note = m_notes.at(index.row());

  switch (role) {
  case IdRole:
    return note["id"];
  case TextRole:
    return note["text"];
  case DateRole:
    return note["date"];
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> NoteModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "id";
  roles[TextRole] = "text";
  roles[DateRole] = "date";
  return roles;
}

void NoteModel::addNote(const QString &text, const QDate &date) {
     if (Database::instance().addNote(text, date)) {
         loadNotesForDate(date);
     }
}

void NoteModel::updateNote(int id, const QString &text) {
     if (Database::instance().updateNote(id, text)) {
         loadNotesForDate(m_currentDate);
     }
}

void NoteModel::deleteNote(int id) {
     if (Database::instance().deleteNote(id)) {
         loadNotesForDate(m_currentDate);
     }
}

void NoteModel::loadNotesForDate(const QDate &date) {
  beginResetModel();
  m_currentDate = date;
  m_notes = Database::instance().getNotesForDate(date);
  endResetModel();
}
