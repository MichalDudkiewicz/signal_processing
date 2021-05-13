#ifndef SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP
#define SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP

#include <QWidget>


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

private slots:
    void on_comboBox_currentTextChanged(const QString& text);
};


#endif //SIGNAL_PROCESSING_SIGNAL_DISPLAY_WIDGET_HPP
