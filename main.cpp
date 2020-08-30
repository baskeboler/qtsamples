#include "mainwindow.h"

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <QtGui/QApplication>
#endif

#include "samplemanager.h"
#include <QDebug>

int main(int argc, char *argv[]) {

  auto sMgr = SampleManager::getInstance();
  sMgr->setSampleBasePath(
      "/home/victor/Downloads/musicradar-female-vocal-samples");
  sMgr->init();

  qInfo() << "available phrases: ";
  for (auto p : sMgr->getAvailablePhrases()) {
    qInfo() << p << ", samples: " << sMgr->getSamplesByPhrase(p).size();
  }

  qInfo() << "total phrases: " << sMgr->getAvailablePhrases().size();

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
