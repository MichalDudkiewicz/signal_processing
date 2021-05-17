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

private:
    Ui::SignalDisplayWidget *ui;
    void plotSignal(const cps::Signal& signal, const QString& signalName) const;

private slots:
    void on_comboBox_currentTextChanged(const QString& text);
    void on_createButton_clicked();

private:
    std::unique_ptr<cps::Signal> mSignalStored;
};


#endif //SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP
