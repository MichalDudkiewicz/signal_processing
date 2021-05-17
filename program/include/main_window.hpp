#ifndef SIGNAL_PROCESSING_MAIN_WINDOW_HPP
#define SIGNAL_PROCESSING_MAIN_WINDOW_HPP

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

private slots:
    void on_operateButton_clicked();
};


#endif //SIGNAL_PROCESSING_MAIN_WINDOW_HPP
