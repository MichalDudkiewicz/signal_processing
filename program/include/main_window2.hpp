#ifndef SIGNAL_PROCESSING_MAIN_WINDOW2_HPP
#define SIGNAL_PROCESSING_MAIN_WINDOW2_HPP

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow2 : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);

    ~MainWindow2() override;

private:
    Ui::MainWindow *ui;
};


#endif //SIGNAL_PROCESSING_MAIN_WINDOW2_HPP
