

#include "qdoublerangeslider.h"

QDoubleRangeSlider::QDoubleRangeSlider(QWidget *parent)
    : QWidget (parent)
{
    Init();
}

QDoubleRangeSlider::QDoubleRangeSlider() {
    Init();
}

QDoubleRangeSlider::~QDoubleRangeSlider() {

}

void QDoubleRangeSlider::Init() {

    active_color_ = QColor(0xffFF9FA0);
    inactive_color_ = QColor(0xffF39799);


    border_line_wide_ = 2;
    border_line_wide_half_ = border_line_wide_ / 2;
    boder_color_  =  QColor(Qt::gray);
    content_color_ = inactive_color_;
    background_color_ =  QColor(Qt::white);
    resize_length_ = 10;
    head_ratio_ = 0.0;
    tail_ratio_ = 1.0;
    disable_head_ = false;
    disable_tail_ = false;
}

void QDoubleRangeSlider::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event)
   // I << "resizeEvent";
    content_rect_  = this->rect().adjusted(border_line_wide_half_, border_line_wide_half_,
                                                     -border_line_wide_half_, -border_line_wide_half_);
    move_x_min_ = content_rect_.x();
    move_x_max_ = content_rect_.x() + content_rect_.width(); //y2 of content_rect

    int anchor_count = 0;
    if(!disable_head_ && !disable_tail_) anchor_count = 2;
    if(!disable_head_ && disable_tail_) anchor_count = 1;
    if(disable_head_ && !disable_tail_) anchor_count = 1;

    int total_ratio_len = content_rect_.width() - resize_length_*anchor_count;
    head_pos_ = content_rect_.x() + static_cast<int>(total_ratio_len * head_ratio_);

    int temp_tail_pos = static_cast<int>(total_ratio_len * tail_ratio_);
    tail_pos_ = content_rect_.x() + temp_tail_pos + resize_length_*anchor_count;//add base pos of start
}

void QDoubleRangeSlider::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event)
    QPainter painter(this);

    //draw bg
    QRect frame_rect = this->rect();
    painter.fillRect(frame_rect, QBrush(background_color_));

    //draw view border
    painter.setPen(QPen(boder_color_, border_line_wide_));
    painter.drawRect(frame_rect);

    //draw move block
    QRect move_block = QRect(head_pos_, content_rect_.y(),
                             tail_pos_ - head_pos_, content_rect_.height());
    painter.fillRect(move_block, QBrush(content_color_));

    //draw mark line
    int mark_line_lr_margin = 6;
    int mark_line_ud_margin = 4;

    if(!disable_head_) {
        QPoint point_h_1 = QPoint(head_pos_ + mark_line_lr_margin, content_rect_.y() + mark_line_ud_margin);
        QPoint point_h_2 = QPoint(head_pos_ + mark_line_lr_margin, content_rect_.y()+content_rect_.height() - mark_line_ud_margin);
        painter.drawLine(point_h_1, point_h_2);
    }

    if(!disable_tail_) {
        QPoint point_t_1 = QPoint(tail_pos_ - mark_line_lr_margin, content_rect_.y() + mark_line_ud_margin);
        QPoint point_t_2 = QPoint(tail_pos_ - mark_line_lr_margin, content_rect_.y()+content_rect_.height() - mark_line_ud_margin);
        painter.drawLine(point_t_1, point_t_2);
    }
}

void QDoubleRangeSlider::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {

        emit BeforeRangeChange();

        QRect left_resize_rect = QRect(head_pos_, content_rect_.y(),
                                                            resize_length_, content_rect_.height());
        QRect right_resize_rect = QRect(tail_pos_ - resize_length_, content_rect_.y(),
                                        tail_pos_, content_rect_.height());

        QPoint press_pos = event->pos();

        if (!disable_head_ && left_resize_rect.contains(press_pos)) { //adjsut head
            move_type_ = MoveType::Head;
        } else if (!disable_tail_ && right_resize_rect.contains(press_pos)) { //adjust tail
            move_type_ = MoveType::Tail;
        } else {
            move_type_ = MoveType::None;
        }
    }
}

void QDoubleRangeSlider::mouseMoveEvent(QMouseEvent *event) {

    QPoint cursor_pos_at_widget = event->pos();

    int anchor_count = 0;
    if(!disable_head_ && !disable_tail_) anchor_count = 2;
    if(!disable_head_ && disable_tail_) anchor_count = 1;
    if(disable_head_ && !disable_tail_) anchor_count = 1;

    if (move_type_ == MoveType::Head) { //adjsut head

        head_pos_ = cursor_pos_at_widget.x();
        if (head_pos_ < move_x_min_) {
            head_pos_ = move_x_min_;
        }

        if(head_pos_ > (tail_pos_ - resize_length_*anchor_count)) {
            head_pos_ = tail_pos_ - resize_length_*anchor_count;
        }
        update();
        CalcRatio(MoveType::Head);
    } else if (move_type_ == MoveType::Tail) { //adjust tail
        tail_pos_ = cursor_pos_at_widget.x();
        if(tail_pos_ > move_x_max_) {
            tail_pos_ = move_x_max_;
        }
        if(tail_pos_  < (head_pos_ + resize_length_*anchor_count)) {
            tail_pos_  = (head_pos_ + resize_length_*anchor_count);
        }
        update();
        CalcRatio(MoveType::Tail);
    }
}

void QDoubleRangeSlider::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    emit AfterRangeChange();
}

void QDoubleRangeSlider::enterEvent(QEvent *event) {
    Q_UNUSED(event)
    content_color_ = active_color_;
    update();
}

void QDoubleRangeSlider::leaveEvent(QEvent *event) {
    Q_UNUSED(event)
    content_color_ = inactive_color_;
    update();
}

void QDoubleRangeSlider::CalcRatio(MoveType type) {

    int anchor_count = 0;
    if(!disable_head_ && !disable_tail_) anchor_count = 2;
    if(!disable_head_ && disable_tail_) anchor_count = 1;
    if(disable_head_ && !disable_tail_) anchor_count = 1;

    int total_ratio_len = content_rect_.width() - resize_length_*anchor_count;

    int temp_tail_pos_ = tail_pos_ - resize_length_*anchor_count;//add base pos of start

    head_ratio_ = static_cast<float>(head_pos_) / static_cast<float>(total_ratio_len);
    tail_ratio_ = static_cast<float>(temp_tail_pos_) / static_cast<float>(total_ratio_len);

    //convert to 0.00 format
    QString head_ratio_str = QString::number(static_cast<double>(head_ratio_), 'f', 2);
    head_ratio_ = head_ratio_str.toFloat();

    QString tail_ratio_str = QString::number(static_cast<double>(tail_ratio_), 'f', 2);
    tail_ratio_ = tail_ratio_str.toFloat();

    emit onRangeChanged(type, extra_data_index_, head_ratio_, tail_ratio_);
}

void QDoubleRangeSlider::DisableHead(bool disable) {
    disable_head_ = disable;
}

void QDoubleRangeSlider::DisableTail(bool disable) {
    disable_tail_ = disable;
}

void QDoubleRangeSlider::SetActiveColor(const QColor &color) {
    active_color_ = color;
    update();
}

void QDoubleRangeSlider::SetInactiveColor(const QColor &color) {
    inactive_color_ = color;
    content_color_ = inactive_color_;
    update();
}

void QDoubleRangeSlider::SetBackgroundColor(const QColor &color) {
    background_color_ = color;
    update();
}

QColor QDoubleRangeSlider::GetBackgroundColor() {
    return background_color_;
}

QColor QDoubleRangeSlider::GetActiveColor() {
    return active_color_;
}

QColor QDoubleRangeSlider::GetInactiveColor() {
    return inactive_color_;
}

void QDoubleRangeSlider::SetExtraDataIndex(int index) {
    extra_data_index_ = index;
}

void QDoubleRangeSlider::SetTailRatio(float ratio) {
    tail_ratio_ = ratio;

    int anchor_count = 0;
    if(!disable_head_ && !disable_tail_) anchor_count = 2;
    if(!disable_head_ && disable_tail_) anchor_count = 1;
    if(disable_head_ && !disable_tail_) anchor_count = 1;

    int total_ratio_len = content_rect_.width() - resize_length_*anchor_count;
    int temp_tail_pos = static_cast<int>(total_ratio_len * tail_ratio_);
    tail_pos_ = temp_tail_pos + resize_length_*anchor_count;//add base pos of start

    update();
}

void QDoubleRangeSlider::SetHeadRatio(float ratio) {
    head_ratio_ = ratio;
    int anchor_count = 0;
    if(!disable_head_ && !disable_tail_) anchor_count = 2;
    if(!disable_head_ && disable_tail_) anchor_count = 1;
    if(disable_head_ && !disable_tail_) anchor_count = 1;

    int total_ratio_len = content_rect_.width() - resize_length_*anchor_count;
    head_pos_ = static_cast<int>(total_ratio_len * head_ratio_);

    update();
}

