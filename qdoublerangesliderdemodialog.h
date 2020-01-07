#ifndef QDOUBLERANGESLIDERDEMODIALOG_H
#define QDOUBLERANGESLIDERDEMODIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QApplication>

#include <QVBoxLayout>
#include <QLabel>
#include "views/qdoublerangeslider/qdoublerangeslider.h"


class QDoubleRangeSliderDemoDialog : public QDialog
{
    Q_OBJECT

public:
    QDoubleRangeSliderDemoDialog(QWidget *parent = nullptr);
    ~QDoubleRangeSliderDemoDialog();

    void setupUi(QDialog *QDoubleRangeSliderDemoDialog);
    void retranslateUi(QDialog *QDoubleRangeSliderDemoDialog);


private slots:
    void on_double_range_slider_onRangeChanged(int type, int index, float headRatio, float tailRatio);

private:

    QLabel *head_value;
    QLabel *tail_value;
    QDoubleRangeSlider *double_range_slider;

};
#endif // QDOUBLERANGESLIDERDEMODIALOG_H
