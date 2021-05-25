#include "sampling_tab.hpp"
#include "ui_sampling_tab.h"
#include "custom_signal.hpp"
#include <memory>
#include "sin_card_reconstructed_signal.hpp"
#include "signal.hpp"
#include "signal_similarity_measures.hpp"

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
    ui->signalDisplay->signal()->setSamplingFrequency(newSamplingFreq);
    const auto signalData = ui->signalDisplay->signal()->data();
    std::shared_ptr<SinCardReconstructedSignal> signal = std::make_shared<SinCardReconstructedSignal>(signalData, N);
    signal->setSamplingFrequency(newSamplingFreq);
    const auto data2 = signal->data();
    const std::string displayInfo = signalComparisonInfo(data2, signalData);
    ui->signalDisplay->setSecondarySignal(signal);
    ui->signalDisplay->signal()->setSamplingFrequency(samplingFreqBuffer);
    ui->signalDisplay->setDisplayInfo(displayInfo);
}
