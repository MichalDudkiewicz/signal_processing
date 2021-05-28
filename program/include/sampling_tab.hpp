#ifndef SIGNAL_PROCESSING_SAMPLING_TAB_HPP
#define SIGNAL_PROCESSING_SAMPLING_TAB_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class SamplingTab; }
QT_END_NAMESPACE

class SamplingTab : public QWidget {
Q_OBJECT

public:
    explicit SamplingTab(QWidget *parent = nullptr);

    ~SamplingTab() override;

private slots:
    void on_sampleButton_clicked();
    void on_quantizeButton_clicked();
    void on_extrapolateButton_clicked();

private:
    Ui::SamplingTab *ui;
};


#endif //SIGNAL_PROCESSING_SAMPLING_TAB_HPP
