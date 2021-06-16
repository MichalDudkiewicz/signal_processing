#ifndef SIGNAL_PROCESSING_FILTERING_TAB_HPP
#define SIGNAL_PROCESSING_FILTERING_TAB_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class FilteringTab; }
QT_END_NAMESPACE

class FilteringTab : public QWidget {
    Q_OBJECT

public:
    explicit FilteringTab(QWidget *parent = nullptr);

    ~FilteringTab() override;

private:
    Ui::FilteringTab *ui;

private slots:
    void on_filterButton_clicked();
};


#endif //SIGNAL_PROCESSING_FILTERING_TAB_HPP
