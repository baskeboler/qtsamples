#ifndef SOUNDSAMPLE_H
#define SOUNDSAMPLE_H

#include "identity.h"

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QSharedPointer>
#include <QString>

class SoundSample : public QObject, public Identity<SoundSample> {
  Q_OBJECT
public:
  SoundSample();

  SoundSample(const QString &path, const QString &fname);
  QString getFullPath() const;
  void setFullPath(const QString &value);

  QString getFileName() const;
  void setFileName(const QString &value);

  QString toString() const;

  enum SoundSampleType { HARD, MID, SOFT, SSTYPE_UNKNOWN };
  Q_ENUM(SoundSampleType)
  enum SoundSampleVariant { BASE, H1, H2, SSVARIANT_UNKNOWN };
  Q_ENUM(SoundSampleVariant)

  SoundSampleType getType() const;
  void setType(const SoundSampleType &value);

  SoundSampleVariant getVariant() const;
  void setVariant(const SoundSampleVariant &value);

  QString getPhrase() const;
  void setPhrase(const QString &value);

  bool operator==(const SoundSample &other);

private:
  QString fullPath;
  QString fileName;
  QString phrase;
  SoundSampleType type;
  SoundSampleVariant variant;
  static QString typeString(SoundSampleType t);
  static QString variantString(SoundSampleVariant v);
  void resolveTypeAndVariant();
};

typedef QSharedPointer<SoundSample> SoundSamplePtr;
#endif // SOUNDSAMPLE_H
