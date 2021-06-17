#include <fstream>
#include "dft_tab.hpp"
#include "ui_dft_tab.h"
#include "custom_signal.hpp"
#include "discreet_fourier_transform.hpp"
#include "complex_signals_processor.hpp"

using namespace cps;

DftTab::DftTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::DftTab) {
    ui->setupUi(this);

    std::vector<QString> modes = {
            "amplitude mode",
            "complex factors mode"
    };
    for (const auto& mode : modes)
    {
        ui->displayComboBox->addItem(mode);
    }
    auto axisX = new QValueAxis();
    axisX->setTitleText("f [Hz]");
    ui->upperChart->chart()->addAxis(axisX, Qt::AlignBottom);

    auto axisY = new QValueAxis();
    axisY->setTitleText("A");
    ui->upperChart->chart()->addAxis(axisY, Qt::AlignLeft);

    auto axisX2 = new QValueAxis();
    axisX2->setTitleText("f [Hz]");
    ui->lowerChart->chart()->addAxis(axisX2, Qt::AlignBottom);

    auto axisY2 = new QValueAxis();
    axisY2->setTitleText("A");
    ui->lowerChart->chart()->addAxis(axisY2, Qt::AlignLeft);

    axisX->setMinorTickCount(7);
    axisX2->setMinorTickCount(7);
}

DftTab::~DftTab() {
    delete ui;
}

void DftTab::on_createButton_clicked()
{
    QDir dataDir("../../program/data");
    QString fileName = QFileDialog::getOpenFileName(
            this, "open", dataDir.absolutePath(), tr("All files (*.bin)"));

    std::fstream in;
    in.open(fileName.toStdString(), std::ios::in | std::ios::binary);
    auto customSignal = std::make_shared<cps::CustomSignal>();
    customSignal->unserialize(in);
    const auto data = customSignal->data().x.back();
    mSignalStored = std::move(customSignal);
    in.close();

    plotSignals();
}

void DftTab::plotSignals() const
{
    ui->upperChart->chart()->removeAllSeries();
    ui->lowerChart->chart()->removeAllSeries();

    const auto mode = ui->displayComboBox->currentText();

    QXYSeries* series = new QLineSeries();
    QXYSeries* series2 = new QLineSeries();
    const auto signalSampled = mSignalStored->data();
    const auto transformResult = DiscreetFourierTransform::transform(signalSampled);

    QString yAxisText = "";
    QString yAxis2Text = "";

    if (mode == "amplitude mode")
    {
        ComplexSignalData complexData = ComplexSignalsProcessor::processAmplitudeData(transformResult);

        for (int i = 0; i < complexData.frequency.size(); i++)
        {
            series->append(complexData.frequency[i], complexData.realValues[i]);
        }
        ui->upperChart->chart()->addSeries(series);

        for (int i = 0; i < complexData.frequency.size(); i++)
        {
            series2->append(complexData.frequency[i], complexData.imaginValues[i]);
        }
        ui->lowerChart->chart()->addSeries(series2);

        yAxisText = "realis A";
        yAxis2Text = "imaginaris A";
    }
    else
    {
        ComplexSignalData complexData = ComplexSignalsProcessor::processComplexFactorsData(transformResult);

        for (int i = 0; i < complexData.frequency.size(); i++)
        {
            series->append(complexData.frequency[i], complexData.realValues[i]);
        }
        ui->upperChart->chart()->addSeries(series);

        for (int i = 0; i < complexData.frequency.size(); i++)
        {
            series2->append(complexData.frequency[i], complexData.imaginValues[i]);
        }
        ui->lowerChart->chart()->addSeries(series2);

        yAxisText = "|z|";
        yAxis2Text = "arg z";
    }
    const auto& axisX = ui->upperChart->chart()->axisX();
    const auto& axisY = ui->upperChart->chart()->axisY();
    axisY->setTitleText(yAxisText);
    axisX->setRange(0, mSignalStored->samplingFrequency());

    double min = series->points().first().y();
    double max = series->points().first().y();
    for(const auto& point : series->points())
    {
        if (point.y() < min)
        {
            min = point.y();
        }
        if (point.y() > max)
        {
            max = point.y();
        }
    }

    axisY->setRange(min, max);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    ui->upperChart->chart()->legend()->setVisible(false);

    const auto& axisX2 = ui->lowerChart->chart()->axisX();
    const auto& axisY2 = ui->lowerChart->chart()->axisY();
    axisX2->setRange(0, mSignalStored->samplingFrequency());
    axisY2->setTitleText(yAxis2Text);

    double min2 = series2->points().first().y();
    double max2 = series2->points().first().y();
    for(const auto& point : series2->points())
    {
        if (point.y() < min2)
        {
            min2 = point.y();
        }
        if (point.y() > max2)
        {
            max2 = point.y();
        }
    }

    axisY2->setRange(min2, max2);

    series2->attachAxis(axisX2);
    series2->attachAxis(axisY2);
    ui->lowerChart->chart()->legend()->setVisible(false);
}
void DftTab::on_displayComboBox_currentTextChanged(const QString &text)
{
    if (mSignalStored)
    {
        plotSignals();
    }
}


