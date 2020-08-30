#include "soundsampletablemodel.h"
#include "samplemanager.h"
#include <QDebug>
#include <QMetaEnum>

SoundSampleTableModel::SoundSampleTableModel(QObject *parent)
    : QAbstractTableModel{parent},
      samples{SampleManager::getInstance()->getAllSamples()}, filteredSamples{
                                                                  samples} {}

int SoundSampleTableModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return filteredSamples.size();
}

int SoundSampleTableModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return 5;
}

QVariant SoundSampleTableModel::data(const QModelIndex &index, int role) const {

  if (!index.isValid()) {
    return QVariant{};
  }
  if (index.row() >= filteredSamples.size() || index.row() < 0) {
    return QVariant{};
  }
  if (role == Qt::DisplayRole) {
    auto sample = filteredSamples[index.row()];

    switch (index.column()) {
    case 0:
      return sample->getId();
    case 1:
      return sample->getFileName();
    case 2:
      return sample->getPhrase();
    case 3:
      return QMetaEnum::fromType<SoundSample::SoundSampleType>().valueToKey(
          sample->getType());
    case 4:
      return QMetaEnum::fromType<SoundSample::SoundSampleVariant>().valueToKey(
          sample->getVariant());
    }
  }

  return QVariant{};
}

QVariant SoundSampleTableModel::headerData(int section,
                                           Qt::Orientation orientation,
                                           int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return "ID";
    case 1:
      return "File name";
    case 2:
      return "phrase";
    case 3:
      return "type";
    case 4:
      return "variant";
    }
  }
  return QVariant{};
}

void SoundSampleTableModel::sort(int column, Qt::SortOrder order) {
  qInfo() << "sorting";
  using std::function;
  using std::string;
  function<QVariant(SoundSamplePtr)> getter = [](SoundSamplePtr s) {
    return "";
  };

  switch (column) {
  case 0:
    getter = [](SoundSamplePtr s) { return s->getId(); };
    break;
  case 1:
    getter = [](SoundSamplePtr s) { return s->getFileName(); };
    break;
  case 2:
    getter = [](SoundSamplePtr s) { return s->getPhrase(); };
    break;
  case 3:
    getter = [](SoundSamplePtr s) { return s->getType(); };
    break;
  case 4:
    getter = [](SoundSamplePtr s) { return s->getVariant(); };
    break;
  }

  auto compare = [getter, order](SoundSamplePtr s1, SoundSamplePtr s2) -> bool {
    return (order == Qt::SortOrder::AscendingOrder) ? getter(s1) < getter(s2)
                                                    : getter(s2) < getter(s1);
  };

  beginResetModel();
  std::sort(filteredSamples.begin(), filteredSamples.end(), compare);
  endResetModel();
}

void SoundSampleTableModel::filterSamples(const QString &str) {

  beginResetModel();

  filteredSamples = samples;
  if (!str.trimmed().isEmpty()) {

    filteredSamples.erase(std::remove_if(filteredSamples.begin(),
                                         filteredSamples.end(),
                                         [str](SoundSamplePtr s) {
                                           return !s->getPhrase().contains(str);
                                         }),
                          filteredSamples.end());
  }
  endResetModel();
}
