#include "qdoublerangesliderdemodialog.h"

#include <QDebug>

QDoubleRangeSliderDemoDialog::QDoubleRangeSliderDemoDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}

QDoubleRangeSliderDemoDialog::~QDoubleRangeSliderDemoDialog()
{
}

void QDoubleRangeSliderDemoDialog::setupUi(QDialog *QDoubleRangeSliderDemoDialog)
{
    if (QDoubleRangeSliderDemoDialog->objectName().isEmpty())
        QDoubleRangeSliderDemoDialog->setObjectName(QString::fromUtf8("QDoubleRangeSliderDemoDialog"));
    QDoubleRangeSliderDemoDialog->resize(400, 100);

    QVBoxLayout *main_v_layout;
    main_v_layout = new QVBoxLayout(QDoubleRangeSliderDemoDialog);//a layout that represent the dialog

    QHBoxLayout *info_text_layout;
    info_text_layout = new QHBoxLayout();
    main_v_layout->addLayout(info_text_layout);

    head_value = new QLabel(QDoubleRangeSliderDemoDialog);
    head_value->setObjectName(QString::fromUtf8("head_value"));
    head_value->setText("head value: 0");
    tail_value = new QLabel(QDoubleRangeSliderDemoDialog);
    tail_value->setObjectName(QString::fromUtf8("tail_value"));
    tail_value->setText("tail value: 0");

    info_text_layout->addWidget(head_value);
    info_text_layout->addWidget(tail_value);

    QHBoxLayout *slider_layout;
    slider_layout = new QHBoxLayout();
    main_v_layout->addLayout(slider_layout);

    double_range_slider = new QDoubleRangeSlider(QDoubleRangeSliderDemoDialog);
    double_range_slider->setObjectName(QString::fromUtf8("double_range_slider"));
    QSizePolicy range_slider_size_policy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    double_range_slider->setSizePolicy(range_slider_size_policy);
    double_range_slider->setMaximumHeight(24);
    double_range_slider->setMinimumHeight(24);
    double_range_slider->setMinimumWidth(100);
    slider_layout->addWidget(double_range_slider);


    retranslateUi(QDoubleRangeSliderDemoDialog);

    QMetaObject::connectSlotsByName(QDoubleRangeSliderDemoDialog);
} // setupUi

void QDoubleRangeSliderDemoDialog::retranslateUi(QDialog *QDoubleRangeSliderDemoDialog)
{
    QDoubleRangeSliderDemoDialog->setWindowTitle(QApplication::translate("QDoubleRangeSliderDemoDialog", "QDoubleRangeSliderDemoDialog", nullptr));
} // retranslateUi

void QDoubleRangeSliderDemoDialog::on_double_range_slider_onRangeChanged(int type, int index, float headRatio, float tailRatio) {
    Q_UNUSED(index)

    if(type == QDoubleRangeSlider::Head) {
        head_value->setText("head value: " + QString::number(static_cast<double>(headRatio)));
    } else {
        tail_value->setText("tail value: " + QString::number(static_cast<double>(tailRatio)));
    }
}
