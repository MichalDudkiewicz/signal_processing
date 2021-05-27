#include "sampling_tab.hpp"
#include "ui_sampling_tab.h"
#include "custom_signal.hpp"
#include <memory>
#include "sin_card_reconstructed_signal.hpp"
#include "signal.hpp"
#include "signal_similarity_measures.hpp"
#include "quantized_signal.hpp"
#include "extrapolator.hpp"
#include "quantizer.hpp"

using namespace cps;

SamplingTab::SamplingTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::SamplingTab) {
    ui->setupUi(this);
}

SamplingTab::~SamplingTab() {
    delete ui;
}

void SamplingTab::on_sampleButton_clicked()
{
    int N = ui->nTextEdit->toPlainText().toInt();
    const int samplingFreqBuffer = ui->signalDisplay->signal()->samplingFrequency();
    const int newSamplingFreq = ui->samplingFrequencyTextEdit->toPlainText().toInt();
    ui->signalDisplay->signal()->setSamplingFrequency(samplingFreqBuffer/10);
    const auto signalData = ui->signalDisplay->signal()->data();
    std::shared_ptr<SinCardReconstructedSignal> signal = std::make_shared<SinCardReconstructedSignal>(signalData, N);
    signal->setSamplingFrequency(newSamplingFreq);
    ui->signalDisplay->signal()->setSamplingFrequency(newSamplingFreq);
    const auto signalData2 = ui->signalDisplay->signal()->data();
    const auto data2 = signal->data();
    const std::string displayInfo = signalComparisonInfo(data2, signalData2);
    signal->setSamplingFrequency(samplingFreqBuffer);
    ui->signalDisplay->setSecondarySignal(signal);
    ui->signalDisplay->signal()->setSamplingFrequency(samplingFreqBuffer);
    ui->signalDisplay->setDisplayInfo(displayInfo);
}

void SamplingTab::on_quantizeButton_clicked()
{
    const size_t quantizationBitResolution = ui->textEdit->toPlainText().toUInt();
    const auto signal1 = ui->signalDisplay->signal();
    const auto data3 = signal1->data();
    const auto samplingFrequency = signal1->samplingFrequency();
    std::shared_ptr<QuantizedSignal> signal;
    if (quantizationBitResolution == 1)
    {
        const auto data = Quantizer::quantize<1>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 2)
    {
        const auto data = Quantizer::quantize<2>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 3)
    {
        const auto data = Quantizer::quantize<3>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 4)
    {
        const auto data = Quantizer::quantize<4>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 5)
    {
        const auto data = Quantizer::quantize<5>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 6)
    {
        const auto data = Quantizer::quantize<6>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 7)
    {
        const auto data = Quantizer::quantize<7>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 8)
    {
        const auto data = Quantizer::quantize<8>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else if (quantizationBitResolution == 9)
    {
        const auto data = Quantizer::quantize<9>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    else
    {
        const auto data = Quantizer::quantize<10>(*signal1, signal1->samplingFrequency()/10);
        const auto data2 = Extrapolator::extrapolateDiscreet(data, signal1->minValue(), signal1->maxValue());
        signal = std::make_shared<QuantizedSignal>(data2);
    }
    signal->setSamplingFrequency(samplingFrequency);
    signal1->setSamplingFrequency(samplingFrequency);
    ui->signalDisplay->setSecondarySignal(signal);
    auto data1 = signal->data();
    const std::string displayInfo = signalComparisonInfoForQuantization(data1, data3);
    ui->signalDisplay->setDisplayInfo(displayInfo);
}
