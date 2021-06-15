#include <iostream>
#include "operation_tab.hpp"
#include "ui_operation_tab.h"
#include "result_signal_dialog.hpp"
#include "custom_signal.hpp"


OperationTab::OperationTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::OperationTab) {
    ui->setupUi(this);
    std::vector<QString> possibleOperations = {
            "+",
            "-",
            ":",
            "*",
            "conv",
            "corr"
    };
    for (const auto& operation : possibleOperations)
    {
        ui->comboBox->addItem(operation);
    }
}

OperationTab::~OperationTab() {
    delete ui;
}

void OperationTab::on_operateButton_clicked()
{
    const auto signalLeft = ui->leftSignal->signal();
    const auto signalRight = ui->rightSignal->signal();
    QString operation = ui->comboBox->currentText();
    std::shared_ptr<cps::CustomSignal> resultSignal;
    if (operation == "+")
    {
        resultSignal = *signalLeft + *signalRight;
    }
    else if (operation == "-")
    {
        resultSignal = *signalLeft - *signalRight;
    }
    else if (operation == "*")
    {
        resultSignal = *signalLeft * *signalRight;
    }
    else if (operation == ":")
    {
        resultSignal = *signalLeft / *signalRight;
    }
    else if (operation == "conv")
    {
        resultSignal = (*signalLeft).convolute(*signalRight);
    }
    else if (operation == "corr")
    {
        resultSignal = (*signalLeft).correlate(*signalRight);
    }
    ResultSignalDialog dialog;
    dialog.setSignal(resultSignal);
    dialog.setModal(true);
    dialog.exec();
}

