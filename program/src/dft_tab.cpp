#include "dft_tab.hpp"
#include "ui_dft_tab.h"


DftTab::DftTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::DftTab) {
    ui->setupUi(this);
}

DftTab::~DftTab() {
    delete ui;
}

