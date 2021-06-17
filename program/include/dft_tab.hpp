#ifndef SIGNAL_PROCESSING_DFT_TAB_HPP
#define SIGNAL_PROCESSING_DFT_TAB_HPP

#include <QWidget>


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
};


#endif //SIGNAL_PROCESSING_DFT_TAB_HPP
