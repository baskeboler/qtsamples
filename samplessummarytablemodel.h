#ifndef SAMPLESSUMMARYTABLEMODEL_H
#define SAMPLESSUMMARYTABLEMODEL_H

#include <QtCore/qglobal.h>

#include "soundsample.h"
#include <QAbstractTableModel>
class SamplesSummaryTableModel : public QAbstractTableModel {
public:
  SamplesSummaryTableModel(QObject *parent = nullptr);

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent) const override;
  virtual int columnCount(const QModelIndex &parent) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role) const override;

private:
  QVector<QString> phrases;
  QMap<QString, QList<SoundSamplePtr>> samples;
};

#endif // SAMPLESSUMMARYTABLEMODEL_H
