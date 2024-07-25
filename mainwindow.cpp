//
// Created by 류재형 on 2024. 7. 26..
//

#include "mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QLabel *label = new QLabel("Hello World", this);
    setCentralWidget(label);
}

MainWindow::~MainWindow() {
}