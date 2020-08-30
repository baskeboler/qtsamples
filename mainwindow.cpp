#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "samplessummarytablemodel.h"
#include "soundsampletablemodel.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  model = new SoundSampleTableModel;
  //  ui->samplesTable->setModel(new SamplesSummaryTableModel());
  ui->samplesTable->setModel(model);
  ui->samplesTable->resizeColumnsToContents();

  connect(ui->filterInput, &QLineEdit::textChanged, model,
          &SoundSampleTableModel::filterSamples);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key::Key_Escape) {
    QApplication::quit();
  }
}
