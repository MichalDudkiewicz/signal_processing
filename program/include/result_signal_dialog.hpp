#ifndef SIGNAL_PROCESSING_RESULT_SIGNAL_DIALOG_HPP
#define SIGNAL_PROCESSING_RESULT_SIGNAL_DIALOG_HPP

#include <QDialog>
#include <memory>
#include "custom_signal.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class ResultSignalDialog; }
QT_END_NAMESPACE

class ResultSignalDialog : public QDialog {
Q_OBJECT

public:
    explicit ResultSignalDialog(QWidget *parent = nullptr);

    ~ResultSignalDialog() override;

public:
    void setSignal(std::shared_ptr<cps::CustomSignal> signal);

private:
    Ui::ResultSignalDialog *ui;
};


#endif //SIGNAL_PROCESSING_RESULT_SIGNAL_DIALOG_HPP
