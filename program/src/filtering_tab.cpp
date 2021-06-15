#include "filtering_tab.hpp"
#include "ui_filtering_tab.h"


FilteringTab::FilteringTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::FilteringTab) {
    ui->setupUi(this);
}

FilteringTab::~FilteringTab() {
    delete ui;
}

