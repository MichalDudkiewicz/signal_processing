#include <result_signal_dialog.hpp>
#include "filtering_tab.hpp"
#include "window.hpp"
#include "ui_filtering_tab.h"
#include "rectangular_window.hpp"
#include "hamming_window.hpp"
#include "low_pass_filter.hpp"
#include "high_pass_filter.hpp"

using namespace cps;

FilteringTab::FilteringTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::FilteringTab) {
    ui->setupUi(this);

    std::vector<QString> windows = {
            "rectangular",
            "hamming"
    };
    for (const auto& window : windows)
    {
        ui->windowComboBox->addItem(window);
    }

    std::vector<QString> filters = {
            "low pass",
            "high pass"
    };
    for (const auto& filter : filters)
    {
        ui->filterComboBox->addItem(filter);
    }

}

FilteringTab::~FilteringTab() {
    delete ui;
}

void FilteringTab::on_filterButton_clicked()
{
    const double M = ui->mTextEdit->toPlainText().toDouble();
    const double fo = ui->foTextEdit->toPlainText().toDouble();

    std::shared_ptr<Window> window;
    const std::string activeWindow = ui->windowComboBox->currentText().toStdString();
    if (activeWindow == "rectangular")
    {
        window = std::make_shared<RectangularWindow>();
    }
    else
    {
        window = std::make_shared<HammingWindow>(M);
    }

    const std::string activeFilter = ui->filterComboBox->currentText().toStdString();
    std::unique_ptr<Filter> filter;
    if (activeFilter == "low pass")
    {
        filter = std::make_unique<LowPassFilter>(M, fo, window);
    }
    else
    {
        filter = std::make_unique<HighPassFilter>(M, fo, window);
    }

    const auto activeSignal = ui->signalWidget->signal();
    const auto filterSignal = filter->filter(activeSignal);
    const auto resultSignal = filterSignal->convolute(*activeSignal);

    ResultSignalDialog dialog;
    dialog.setSignal(resultSignal);
    dialog.setModal(true);
    dialog.exec();
}