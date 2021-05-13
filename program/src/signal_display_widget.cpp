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
//    ui->periodTextEdit->hide();
//    ui->samplingFrequencyTextEdit->hide();
//    ui->probabilityTextEdit->hide();
//    ui->kwTextEdit->hide();
//    ui->impulseSampleNumberTextEdit->hide();
//    ui->stepTimeTextEdit->hide();
    const double amplitude = ui->amplitudeTextEdit->toPlainText().toDouble();
    const double initialTime = ui->initialTimeTextEdit->toPlainText().toDouble();
    const double duration = ui->durationTextEdit->toPlainText().toDouble();
    if (text == "gaussian noise")
    {
        cps::GaussianNoise signal(amplitude, initialTime, duration);
        plotSignal(signal, text);
    }
    else if (text == "half rectified sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        cps::HalfRectifiedSinusoidalSignal signal(amplitude, initialTime, duration, period);
        plotSignal(signal, text);
    }
    else if (text == "impulse noise")
    {
        const int samplingFrequency = ui->samplingFrequencyTextEdit->toPlainText().toInt();
        const double probability = ui->probabilityTextEdit->toPlainText().toDouble();
        cps::ImpulseNoise signal(amplitude, initialTime, duration, samplingFrequency, probability);
        plotSignal(signal, text);
    }
    else if (text == "rectangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        cps::RectangularSignal signal(amplitude, initialTime, duration, period, kw);
        plotSignal(signal, text);
    }
    else if (text == "rectified sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        cps::RectifiedSinusoidalSignal signal(amplitude, initialTime, duration, period);
        plotSignal(signal, text);
    }
    else if (text == "sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        cps::SinusoidalSignal signal(amplitude, initialTime, duration, period);
        plotSignal(signal, text);
    }
    else if (text == "symmetrical rectangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        cps::SymmetricalRectangularSignal signal(amplitude, initialTime, duration, period, kw);
        plotSignal(signal, text);
    }
    else if (text == "triangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        cps::TriangularSignal signal(amplitude, initialTime, duration, period, kw);
        plotSignal(signal, text);
    }
    else if (text == "uniform distribution noise")
    {
        cps::UniformDistributionNoise signal(amplitude, initialTime, duration);
        plotSignal(signal, text);
    }
    else if (text == "unit impulse")
    {
        const int samplingFrequency = ui->samplingFrequencyTextEdit->toPlainText().toInt();
        const int impulseSampleNumber = ui->impulseSampleNumberTextEdit->toPlainText().toInt();
        cps::UnitImpulseSignal signal(initialTime, duration, impulseSampleNumber, samplingFrequency);
        plotSignal(signal, text);
    }
    else if (text == "unit step")
    {
        const int stepTimeSec = ui->stepTimeTextEdit->toPlainText().toInt();
        cps::UnitStepSignal signal(amplitude, initialTime, duration, stepTimeSec);
        plotSignal(signal, text);
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

