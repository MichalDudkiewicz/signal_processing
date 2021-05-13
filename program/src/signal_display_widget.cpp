#include "signal_display_widget.hpp"
#include "ui_signal_display_widget.h"
#include <QString>
#include <vector>
#include "gaussian_noise.hpp"


SignalDisplayWidget::SignalDisplayWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::SignalDisplayWidget) {
    ui->setupUi(this);
    std::vector<QString> possibleSignals = {
            "custom",
            "gaussian noise",
            "half rectified sinusoidal",
            "impulse noise",
            "rectangular",
            "rectified sinusoidal",
            "sinusoidal",
            "symmetrical rectangular",
            "triangular",
            "uniform distribution noise",
            "unit impulse",
            "unit step"
    };
    for (const auto& signal : possibleSignals)
    {
        ui->comboBox->addItem(signal);
    }
}

SignalDisplayWidget::~SignalDisplayWidget() {
    delete ui;
}

void SignalDisplayWidget::on_comboBox_currentTextChanged(const QString& text)
{
    std::string currentSignalName = text.toStdString();

    if (currentSignalName == "gaussian noise")
    {
        const double amplitude = ui->amplitudeTextEdit->toPlainText().toDouble();
        const double initialTime = ui->initialTimeTextEdit->toPlainText().toDouble();
        const double duration = ui->durationTextEdit->toPlainText().toDouble();
        cps::GaussianNoise gaussianNoise(amplitude, initialTime, duration);
        std::string properties = gaussianNoise.stringProperties();
        ui->propertiesText->setText(QString::fromStdString(properties));
    }
}

