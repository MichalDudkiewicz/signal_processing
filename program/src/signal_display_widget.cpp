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
#include "utils.hpp"

SignalDisplayWidget::SignalDisplayWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::SignalDisplayWidget) {
    ui->setupUi(this);
    std::vector<QString> possibleSignals = {
            "gaussian noise",
            "custom",
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

    if (text == "half rectified sinusoidal" || text == "rectified sinusoidal" || text == "sinusoidal")
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

void SignalDisplayWidget::plotSignal(cps::Signal& signal, const QString& signalName, bool histogram) const
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

    const unsigned int samplingFrequency = ui->samplingFreqTextEdit->toPlainText().toUInt();
    signal.setSamplingFrequency(samplingFrequency);
    const auto data = signal.data();
    for (int i = 0; i < data.x.size(); i++)
    {
        series->append(data.x[i], data.y[i]);
    }
    ui->chartView->chart()->addSeries(series);
    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTitleText("t [s]");
    ui->chartView->chart()->addAxis(axisX1, Qt::AlignBottom);
    series->attachAxis(axisX1);

    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setTitleText("A");
    ui->chartView->chart()->addAxis(axisY1, Qt::AlignLeft);
    series->attachAxis(axisY1);

    ui->chartView->chart()->setTitle(signalName);
    ui->chartView->chart()->legend()->setVisible(false);

    // histogram
    if (histogram)
    {
        const unsigned int numberOfIntervals = ui->intervalsNumberTextEdit->toPlainText().toUInt();
        const auto histogramData = signal.histogramData(numberOfIntervals);
        QBarSet *set = new QBarSet("histogram");
        unsigned int max = 0;
        for (const auto& occurence : histogramData.occurrences)
        {
            *set << occurence;
            if (occurence > max)
                max = occurence;
        }
        QBarSeries *histogramSeries = new QBarSeries();
        histogramSeries->append(set);
        const auto& chart = ui->histogramView->chart();
        chart->addSeries(histogramSeries);

        QStringList categories;
        for(const auto& interval : histogramData.intervals)
        {
            categories << QString::number(cps::roundTo2(interval.first)) + ':' + QString::number(cps::roundTo2(interval.second));
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        axisX->setTitleText("amplitude intervals");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,max);
        axisY->setMinorTickCount(max - 1);
        axisY->setTitleText("occurences");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        chart->legend()->setVisible(false);
    }
}

void SignalDisplayWidget::on_createButton_clicked()
{
    const auto& chart = ui->chartView->chart();
    const auto& axes1 = chart->axes();
    for (const auto& axis : axes1)
    {
        chart->removeAxis(axis);
    }
    chart->removeAllSeries();

    const auto& histogramChart = ui->histogramView->chart();
    const auto& axes2 = histogramChart->axes();
    for (const auto& axis : axes2)
    {
        histogramChart->removeAxis(axis);
    }
    histogramChart->removeAllSeries();

    const double amplitude = ui->amplitudeTextEdit->toPlainText().toDouble();
    const double initialTime = ui->initialTimeTextEdit->toPlainText().toDouble();
    const double duration = ui->durationTextEdit->toPlainText().toDouble();
    const auto text = ui->comboBox->currentText();
    if (text == "custom")
    {
        QDir dataDir("../../program/data");
        QString fileName = QFileDialog::getOpenFileName(
                this, "open", dataDir.absolutePath(), tr("All files (*.bin)"));

        std::fstream in;
        in.open(fileName.toStdString(), std::ios::in | std::ios::binary);
        auto customSignal = std::make_shared<cps::CustomSignal>();
        customSignal->unserialize(in);
        mSignalStored = std::move(customSignal);
        in.close();
        ui->amplitudeTextEdit->setText(QString::number(mSignalStored->amplitude()));
        ui->initialTimeTextEdit->setText(QString::number(mSignalStored->initialTime()));
        ui->durationTextEdit->setText(QString::number(mSignalStored->duration()));
        plotSignal(*mSignalStored, text);
    }
    else if (text == "gaussian noise")
    {
        mSignalStored = std::make_shared<cps::GaussianNoise>(amplitude, initialTime, duration);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "half rectified sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::HalfRectifiedSinusoidalSignal>(amplitude, initialTime, duration, period);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "impulse noise")
    {
        const int samplingFrequency = ui->samplingFrequencyTextEdit->toPlainText().toInt();
        const double probability = ui->probabilityTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::ImpulseNoise>(amplitude, initialTime, duration, samplingFrequency, probability);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "rectangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::RectangularSignal>(amplitude, initialTime, duration, period, kw);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "rectified sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::RectifiedSinusoidalSignal>(amplitude, initialTime, duration, period);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "sinusoidal")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::SinusoidalSignal>(amplitude, initialTime, duration, period);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "symmetrical rectangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::SymmetricalRectangularSignal>(amplitude, initialTime, duration, period, kw);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "triangular")
    {
        const double period = ui->periodTextEdit->toPlainText().toDouble();
        const double kw = ui->kwTextEdit->toPlainText().toDouble();
        mSignalStored = std::make_shared<cps::TriangularSignal>(amplitude, initialTime, duration, period, kw);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "uniform distribution noise")
    {
        mSignalStored = std::make_shared<cps::UniformDistributionNoise>(amplitude, initialTime, duration);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "unit impulse")
    {
        const int samplingFrequency = ui->samplingFrequencyTextEdit->toPlainText().toInt();
        const int impulseSampleNumber = ui->impulseSampleNumberTextEdit->toPlainText().toInt();
        mSignalStored = std::make_shared<cps::UnitImpulseSignal>(initialTime, duration, impulseSampleNumber, samplingFrequency);
        plotSignal(*mSignalStored, text);
    }
    else if (text == "unit step")
    {
        const int stepTimeSec = ui->stepTimeTextEdit->toPlainText().toInt();
        mSignalStored = std::make_shared<cps::UnitStepSignal>(amplitude, initialTime, duration, stepTimeSec);
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

std::shared_ptr<cps::Signal> SignalDisplayWidget::signal() const {
    return mSignalStored;
}

void SignalDisplayWidget::setSignal(const std::shared_ptr<cps::Signal> &newSignal) {
    mSignalStored = newSignal;
    ui->comboBox->setCurrentText("custom");
    ui->intervalsNumberTextEdit->setText("10");
    ui->amplitudeTextEdit->setText(QString::number(mSignalStored->amplitude()));
    ui->initialTimeTextEdit->setText(QString::number(mSignalStored->initialTime()));
    ui->durationTextEdit->setText(QString::number(mSignalStored->duration()));
    plotSignal(*mSignalStored, "custom");
}

void SignalDisplayWidget::setSecondarySignal(const std::shared_ptr<cps::Signal>& newSignal)
{
    mSignalForComparisonStored = newSignal;
    const auto& chart = ui->chartView->chart();
    const auto& axes1 = chart->axes();
    for (const auto& axis : axes1)
    {
        chart->removeAxis(axis);
    }
    plotSignal(*mSignalForComparisonStored, "custom", false);
}

void SignalDisplayWidget::setDisplayInfo(const std::string& info) const
{
    ui->propertiesText->clear();
    ui->propertiesText->setText(QString::fromStdString(info));
}
