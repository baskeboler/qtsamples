#ifndef SOUNDSAMPLETABLEMODEL_H
#define SOUNDSAMPLETABLEMODEL_H

#include <QtCore/qglobal.h>

#include "soundsample.h"
#include <QAbstractTableModel>
#include <QVector>

class SoundSampleTableModel : public QAbstractTableModel {
  Q_OBJECT
public:
  SoundSampleTableModel(QObject *parent = nullptr);

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent) const override;
  virtual int columnCount(const QModelIndex &parent) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role) const override;

  virtual void sort(int column, Qt::SortOrder order) override;

public slots:
  void filterSamples(const QString &str) {

    beginResetModel();

    filteredSamples = samples;
    if (!str.trimmed().isEmpty()) {

      filteredSamples.erase(
          std::remove_if(filteredSamples.begin(), filteredSamples.end(),
                         [str](SoundSamplePtr s) {
                           return !s->getPhrase().contains(str);
                         }),
          filteredSamples.end());
    }
    endResetModel();
  }

private:
  QString filterString;
  QVector<SoundSamplePtr> samples;

  QVector<SoundSamplePtr> filteredSamples;
};

#endif // SOUNDSAMPLETABLEMODEL_H
