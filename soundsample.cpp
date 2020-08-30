#include "soundsample.h"
#include <QSharedPointer>

SoundSample::SoundSample() : SoundSample{"", ""} {}

SoundSample::SoundSample(const QString &path, const QString &fname)
    : QObject{}, Identity<SoundSample>{}, fullPath{path}, fileName{fname} {
  resolveTypeAndVariant();
}

QString SoundSample::getFullPath() const { return fullPath; }

void SoundSample::setFullPath(const QString &value) { fullPath = value; }

QString SoundSample::getFileName() const { return fileName; }

void SoundSample::setFileName(const QString &value) { fileName = value; }

QString SoundSample::toString() const {
  return QString("SoundSample{id=%1, fullPath=%2, fileName=%3, type=%4, "
                 "variant=%5, phrase=%6}")
      .arg(getId())
      .arg(getFullPath())
      .arg(getFileName())
      .arg(typeString(getType()))
      .arg(variantString(getVariant()))
      .arg(phrase);
}

SoundSample::SoundSampleType SoundSample::getType() const { return type; }

void SoundSample::setType(const SoundSampleType &value) { type = value; }

SoundSample::SoundSampleVariant SoundSample::getVariant() const {
  return variant;
}

void SoundSample::setVariant(const SoundSampleVariant &value) {
  variant = value;
}

QString SoundSample::getPhrase() const { return phrase; }

void SoundSample::setPhrase(const QString &value) { phrase = value; }

bool SoundSample::operator==(const SoundSample &other) {
  return fullPath == other.fullPath && fileName == other.fileName &&
         getId() == other.getId() && phrase == other.phrase &&
         type == other.type && variant == other.variant;
}

QString SoundSample::typeString(SoundSampleType t) {
  switch (t) {
  case HARD:
    return "hard";
  case MID:
    return "mid";
  case SOFT:
    return "soft";
  default:
    return "unknown";
  }
}

QString SoundSample::variantString(SoundSampleVariant v) {
  switch (v) {
  case BASE:
    return "base";
  case H1:
    return "h1";
  case H2:
    return "h2";
  default:
    return "unknown";
  }
}

void SoundSample::resolveTypeAndVariant() {
  auto types = {HARD, MID, SOFT};
  auto variants = {BASE, H1, H2};

  for (SoundSampleType t : types) {
    for (SoundSampleVariant v : variants) {
      QString postfix;
      if (v == BASE) {
        postfix = QString(" %1.wav").arg(typeString(t));

      } else {
        postfix =
            QString(" %1 %2.wav").arg(typeString(t)).arg(variantString(v));
      }
      if (fileName.endsWith(postfix)) {
        type = t;
        variant = v;
        phrase = fileName;
        phrase.chop(postfix.size());
        return;
      }
    }
  }
  type = SSTYPE_UNKNOWN;
  variant = SSVARIANT_UNKNOWN;
  phrase = fileName;
  phrase.chop(QString(".wav").size());
}
