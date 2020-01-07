
#ifndef QDOUBLERANGESLIDER_H
#define QDOUBLERANGESLIDER_H

#include "qglobal.h"

#include <QtWidgets/qwidget.h>
#include <QPainter>
#include <QKeyEvent>


class QDoubleRangeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit QDoubleRangeSlider(QWidget *parent);
    ~QDoubleRangeSlider() override;
    QDoubleRangeSlider();

    enum MoveType {
        None,
        Head,
        Tail
    };

    //color proterty qss usage(qss code example):
    /*
         MyRangeSlider
        {
            qproperty-bg_color:#A1A1A1;
            qproperty-bar_active_color:#ff0000;
            qproperty-bar_inactive_color:#00ff00;
        }
    */
    Q_PROPERTY(QColor bg_color WRITE SetBackgroundColor READ GetBackgroundColor)
    Q_PROPERTY(QColor bar_active_color WRITE SetActiveColor READ GetActiveColor)
    Q_PROPERTY(QColor bar_inactive_color WRITE SetInactiveColor READ GetInactiveColor)

    void SetBackgroundColor(const QColor &color);
    void SetActiveColor(const QColor &color);
    void SetInactiveColor(const QColor &color);

    QColor GetBackgroundColor();
    QColor GetActiveColor();
    QColor GetInactiveColor();



    void DisableHead(bool disable);
    void DisableTail(bool disable);

    void SetExtraDataIndex(int index);
    void SetTailRatio(float ratio);
    void SetHeadRatio(float ratio);

signals:
    void onRangeChanged(int type, int index, float headRatio, float tailRatio);
    void BeforeRangeChange();
    void AfterRangeChange();


protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent * ) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void CalcRatio(MoveType type);
    void Init();

private:
    Q_DISABLE_COPY(QDoubleRangeSlider)

    int border_line_wide_;
    int border_line_wide_half_;
    QColor boder_color_;
    QColor content_color_;
    QColor background_color_;

    int move_type_;
    int move_x_min_;
    int move_x_max_;

    int head_pos_;
    int tail_pos_;

    float head_ratio_;
    float tail_ratio_;

    int resize_length_;
    QRect content_rect_;


    QColor active_color_;
    QColor inactive_color_;

    bool disable_head_;
    bool disable_tail_;

    int extra_data_index_;
};

#endif // QDOUBLERANGESLIDER_H
