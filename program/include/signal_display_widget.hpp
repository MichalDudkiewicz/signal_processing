#ifndef SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP
#define SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP

#include <QWidget>
#include "signal.hpp"
#include <QString>
#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui { class SignalDisplayWidget; }
QT_END_NAMESPACE

class SignalDisplayWidget : public QWidget {
Q_OBJECT

public:
    explicit SignalDisplayWidget(QWidget *parent = nullptr);

    ~SignalDisplayWidget() override;

public:
    std::shared_ptr<cps::Signal> signal() const;

    void setSignal(const std::shared_ptr<cps::Signal>& newSignal);

    void setSecondarySignal(const std::shared_ptr<cps::Signal>& newSignal);

    void setDisplayInfo(const std::string& info) const;

private:
    Ui::SignalDisplayWidget *ui;
    void plotSignal(cps::Signal& signal, const QString& signalName, bool histogram = true) const;

private slots:
    void on_comboBox_currentTextChanged(const QString& text);
    void on_createButton_clicked();
    void on_saveButton_clicked();

private:
    std::shared_ptr<cps::Signal> mSignalStored;
    std::shared_ptr<cps::Signal> mSignalForComparisonStored;
};


#endif //SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP
