#ifndef SIGNAL_PROCESSING_DFT_TAB_HPP
#define SIGNAL_PROCESSING_DFT_TAB_HPP

#include <QWidget>
#include "signal.hpp"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class DftTab; }
QT_END_NAMESPACE

class DftTab : public QWidget {
    Q_OBJECT

public:
    explicit DftTab(QWidget *parent = nullptr);

    ~DftTab() override;

private:
    Ui::DftTab *ui;

private slots:
    void on_createButton_clicked();

private:
    std::shared_ptr<cps::Signal> mSignalStored;
};


#endif //SIGNAL_PROCESSING_DFT_TAB_HPP
