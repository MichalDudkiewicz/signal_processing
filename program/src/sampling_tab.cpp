#include "sampling_tab.hpp"
#include "ui_sampling_tab.h"


SamplingTab::SamplingTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::SamplingTab) {
    ui->setupUi(this);
}

SamplingTab::~SamplingTab() {
    delete ui;
}

