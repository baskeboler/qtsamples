#include "samplessummarytablemodel.h"
#include "samplemanager.h"

SamplesSummaryTableModel::SamplesSummaryTableModel(QObject *parent)
    : QAbstractTableModel{parent} {

  samples = SampleManager::getInstance()->getAllSamplesByPhrase();
  auto phrasesList = samples.keys();
  phrases = QVector<QString>{phrasesList.begin(), phrasesList.end()};
}

int SamplesSummaryTableModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return samples.keys().size();
}

int SamplesSummaryTableModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return 3;
}

QVariant SamplesSummaryTableModel::data(const QModelIndex &index,
                                        int role) const {
  if (!index.isValid())
    return QVariant{};
  auto phrase = phrases[index.row()];
  auto s = samples[phrase];

  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return phrase;
    case 1:
      return s.size();
    }
  }
  return QVariant{};
}

QVariant SamplesSummaryTableModel::headerData(int section,
                                              Qt::Orientation orientation,
                                              int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return "phrase";
    case 1:
      return "sample #";
    }
  }
  return QVariant{};
}
