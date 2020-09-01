#include "samplemanager.h"
#include "soundsample.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QSharedPointer>

SampleManager::SampleManager() : Singleton<SampleManager>{} {}

QString SampleManager::sampleBasePath() const { return m_sampleBasePath; }

void SampleManager::setSampleBasePath(const QString &sampleBasePath) {
  m_sampleBasePath = sampleBasePath;
}

void SampleManager::init() {
  QElapsedTimer timer;
  timer.start();
  QDirIterator it{sampleBasePath(), QDirIterator::Subdirectories};
  while (it.hasNext()) {

    it.next();

    auto info = it.fileInfo();
    bool isFile = info.isFile();
    if (isFile) {
      auto sample =
          QSharedPointer<SoundSample>::create(it.filePath(), it.fileName());
      qInfo() << sample->toString();
      samples.push_back(sample);
      samplesById[sample->getId()] = sample;
      samplesByPhrase[sample->getPhrase()].push_back(sample);
    }
  }
  qInfo() << "Sample manager initialized in " << timer.elapsed() << " ms";
}

SoundSamplePtr SampleManager::getById(int id) const {
  return samplesById.find(id).value();
}

QList<QString> SampleManager::getAvailablePhrases() const {
  return samplesByPhrase.keys();
}

QList<SoundSamplePtr>
SampleManager::getSamplesByPhrase(const QString &p) const {
  return samplesByPhrase[p];
}

QVector<SoundSamplePtr> SampleManager::getAllSamples() const { return samples; }

QMap<QString, QList<SoundSamplePtr>>
SampleManager::getAllSamplesByPhrase() const {
  return samplesByPhrase;
}
