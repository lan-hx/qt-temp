#include "mainwindow.h"

#include <QMessageBox>
#include <iostream>

#include "./ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_exit_clicked() {
  cout << "exit!" << endl;
  exit(0);
}

void MainWindow::on_Find_clicked() {
  auto search = ui->lineEdit->text();
  QMessageBox::warning(this, "Warning", search);
  ui->textEdit->find(search, QTextDocument::FindWholeWords);
  while(1) {}
}
