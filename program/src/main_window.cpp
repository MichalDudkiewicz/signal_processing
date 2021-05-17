#include "result_signal_dialog.hpp"
#include "main_window.hpp"
#include "ui_main_window.h"
#include "custom_signal.hpp"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    std::vector<QString> possibleOperations = {
            "+",
            "-",
            ":",
            "*"
    };
    for (const auto& operation : possibleOperations)
    {
        ui->comboBox->addItem(operation);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_operateButton_clicked()
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
    ResultSignalDialog dialog;
    dialog.setSignal(resultSignal);
    dialog.setModal(true);
    dialog.exec();
}

