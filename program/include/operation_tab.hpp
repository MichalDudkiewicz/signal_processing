#ifndef SIGNAL_PROCESSING_OPERATION_TAB_HPP
#define SIGNAL_PROCESSING_OPERATION_TAB_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class OperationTab; }
QT_END_NAMESPACE

class OperationTab : public QWidget {
    Q_OBJECT

public:
    explicit OperationTab(QWidget *parent = nullptr);

    ~OperationTab() override;

private:
    Ui::OperationTab *ui;

private slots:
    void on_operateButton_clicked();
};


#endif //SIGNAL_PROCESSING_OPERATION_TAB_HPP
