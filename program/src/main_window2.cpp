#include "main_window2.hpp"
#include "ui_main_window2.h"


MainWindow2::MainWindow2(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow2::~MainWindow2() {
    delete ui;
}

