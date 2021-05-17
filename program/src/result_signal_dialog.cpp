#include "result_signal_dialog.hpp"
#include "ui_result_signal_dialog.h"


ResultSignalDialog::ResultSignalDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::ResultSignalDialog) {
    ui->setupUi(this);
}

ResultSignalDialog::~ResultSignalDialog() {
    delete ui;
}

void ResultSignalDialog::setSignal(std::shared_ptr<cps::CustomSignal> signal)
{
    ui->resultSignal->setSignal(signal);
}

