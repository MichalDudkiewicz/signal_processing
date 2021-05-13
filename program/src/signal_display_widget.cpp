#include "signal_display_widget.hpp"
#include "ui_signal_display_widget.h"


SignalDisplayWidget::SignalDisplayWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::SignalDisplayWidget) {
    ui->setupUi(this);
}

SignalDisplayWidget::~SignalDisplayWidget() {
    delete ui;
}

