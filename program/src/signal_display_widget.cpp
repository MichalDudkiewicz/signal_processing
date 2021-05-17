#include "signal_display_widget.hpp"
#include "ui_signal_display_widget.h"
#include <QString>
#include <vector>
#include "gaussian_noise.hpp"
#include "half_rectified_sinusoidal_signal.hpp"
#include "impulse_noise.hpp"
#include "rectangular_signal.hpp"
#include "sinusoidal_signal.hpp"
#include "symmetrical_rectangular_signal.hpp"
#include "triangular_signal.hpp"
#include "uniform_distribution_noise.hpp"
#include "unit_impulse_signal.hpp"
#include "unit_step_signal.hpp"
#include "rectified_sinusoidal_signal.hpp"
#include "custom_signal.hpp"
#include <fstream>

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
    ui->periodTextEdit->hide();
    ui->samplingFrequencyTextEdit->hide();
    ui->probabilityTextEdit->hide();
    ui->kwTextEdit->hide();
    ui->impulseSampleNumberTextEdit->hide();
    ui->stepTimeTextEdit->hide();
    ui->periodLabel->hide();
    ui->samplingFrequencyLabel->hide();
    ui->probabilityLabel->hide();
    ui->fullfilmentLabel->hide();
    ui->impulseSampleNumberLabel->hide();
    ui->stepTimeLabel->hide();

    if (text == "custom")
    {
        QDir dataDir("../../program/data");
        QString fileName = QFileDialog::getOpenFileName(
                this, "open", dataDir.absolutePath(), tr("All files (*.bin)"));

        std::fstream in;
        in.open(fileName.toStdString(), std::ios::in | std::ios::binary);
        auto customSignal = std::make_unique<cps::CustomSignal>();
        customSignal->unserialize(in);
        mSignalStored = std::move(customSignal);
        in.close();
        ui->amplitudeTextEdit->setText(QString::number(mSignalStored->amplitude()));
        ui->initialTimeTextEdit->setText(QString::number(mSignalStored->initialTime()));
        ui->durationTextEdit->setText(QString::number(mSignalStored->duration()));
    }
    else if (text == "half rectified sinusoidal" || text == "rectified sinusoidal" || text == "sinusoidal")
    {
        ui->periodTextEdit->show();
        ui->periodLabel->show();
    }
    else if (text == "impulse noise")
    {
        ui->samplingFrequencyTextEdit->show();
        ui->probabilityTextEdit->show();
        ui->samplingFrequencyLabel->show();
        ui->probabilityLabel->show();
    }
    else if (text == "rectangular" || text == "symmetrical rectangular" || text == "triangular")
    {
        ui->periodTextEdit->show();
        ui->kwTextEdit->show();
        ui->periodLabel->show();
        ui->fullfilmentLabel->show();
    }
    else if (text == "unit impulse")
    {
        ui->samplingFrequencyTextEdit->show();
        ui->impulseSampleNumberTextEdit->show();
        ui->samplingFrequencyLabel->show();
        ui->impulseSampleNumberLabel->show();
    }
    else if (text == "unit step")
    {
        ui->stepTimeTextEdit->show();
        ui->stepTimeLabel->show();
    }
}

void SignalDisplayWidget::plotSignal(const cps::Signal& signal, const QString& signalName) const
{
    std::string properties = signal.stringProperties();
    ui->propertiesText->setText(QString::fromStdString(properties));
    QXYSeries* series;
    if (dynamic_cast<const cps::DiscreetSignal*>(&signal))
    {
        series = new QScatterSeries();
    }
    else
    {
        series = new QLineSeries();
    }
    const auto data = signal.data();
    for (int i = 0; i < data.x.size(); i++)
    {
        series->append(data.x[i], data.y[i]);
    }
    ui->chartView->chart()->addSeries(series);
    ui->chartView->chart()->createDefaultAxes();
    ui->chartView->chart()->setTitle(signalName);
    ui->chartView->chart()->legend()->setVisible(false);
}

void SignalDisplayWidget::on_createButton_clicked()
{
    ui->chartView->chart()->removeAllSeries();
    const double amplitude = ui->amplitudeTextEdit->toPlainText().toDouble();
    const double initialTime = ui->initialTimeTextEdit->toPlainText().toDouble();
    const double duration = ui->durationTextEdit->toPlainText().toDouble();
    const auto text = ui->comboBox->currentText();
    if (text == "custom")
    {
        plotSignal(*mSignalStored, text);
    }
    else if (text == "gaussian noise")
    {
        mSignalStored = std::make_unique<cps::GaussianNoise>(amplitude, initialTime, duration);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "half rectified sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::HalfRectifiedSinusoidalSignal>(amplitude, initialTime, duration, period);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "impulse noise")
    {
        const int samplingFrequency = ui->samplingFrequencyTextEdit->toPlainText().toInt();
        const double probability = ui->probabilityTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::ImpulseNoise>(amplitude, initialTime, duration, samplingFrequency, probability);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "rectangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::RectangularSignal>(amplitude, initialTime, duration, period, kw);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "rectified sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::RectifiedSinusoidalSignal>(amplitude, initialTime, duration, period);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::SinusoidalSignal>(amplitude, initialTime, duration, period);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "symmetrical rectangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::SymmetricalRectangularSignal>(amplitude, initialTime, duration, period, kw);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "triangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_unique<cps::TriangularSignal>(amplitude, initialTime, duration, period, kw);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "uniform distribution noise")
    {
        mSignalStored = std::make_unique<cps::UniformDistributionNoise>(amplitude, initialTime, duration);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "unit impulse")
    {
        const int samplingFrequency = ui->samplingFrequencyTextEdit->toPlainText().toInt();
        const int impulseSampleNumber = ui->impulseSampleNumberTextEdit->toPlainText().toInt();
        mSignalStored = std::make_unique<cps::UnitImpulseSignal>(initialTime, duration, impulseSampleNumber, samplingFrequency);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "unit step")
    {
        const int stepTimeSec = ui->stepTimeTextEdit->toPlainText().toInt();
        mSignalStored = std::make_unique<cps::UnitStepSignal>(amplitude, initialTime, duration, stepTimeSec);
        plotSignal(*mSignalStored, text);
    }
}

void SignalDisplayWidget::on_saveButton_clicked()
{
    QDir dataDir("../../program/data");
    QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("Save signal"),
            dataDir.absolutePath() + "/newSignal.bin",
            tr("All files (*.bin)"));
    if (fileName.isEmpty())
        return;
    else
    {
        std::ofstream out;
        out.open( fileName.toStdString(),
                  std::ios::out | std::ios::trunc | std::ios::binary );

        mSignalStored->serialize(out);
        out.close();
    }
}
