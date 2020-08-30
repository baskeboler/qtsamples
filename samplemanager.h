#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "Singleton.h"
#include "soundsample.h"
#include <QDirIterator>
#include <QFile>
#include <QMap>
#include <QString>
#include <QVector>

class SampleManager : public Singleton<SampleManager> {
public:
  SampleManager();

  QString sampleBasePath() const;
  void setSampleBasePath(const QString &sampleBasePath);

  void init();
  SoundSamplePtr getById(int id) const;

  QList<QString> getAvailablePhrases() const;
  QList<SoundSamplePtr> getSamplesByPhrase(const QString &p) const;
  QVector<SoundSamplePtr> getAllSamples() const;
  QMap<QString, QList<SoundSamplePtr>> getAllSamplesByPhrase() const;

private:
  QString m_sampleBasePath;
  QVector<SoundSamplePtr> samples;
  QMap<int, SoundSamplePtr> samplesById;
  QMap<QString, QList<SoundSamplePtr>> samplesByPhrase;
};

#endif // SAMPLEMANAGER_H
