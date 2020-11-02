#include "paint_area.h"
#include "main_window.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>

paint_area::paint_area(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

//event wciskania lewego przycisku
void paint_area::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_point = event->pos();
        drawing = true;
    }
}

//event przy ruszaniu myszką
void paint_area::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && drawing == true)
    {
        draw_line(event->pos());
    }
}

//event przy puszczeniu lewego przycisku
void paint_area::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && drawing == true)
    {
        draw_line(event->pos());
        drawing = false;
    }
}

void paint_area::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect draw_rect = event->rect();
    painter.drawImage(draw_rect, image, draw_rect);
}

//event przy zmianie wielkości okna, głupio działa dla zwiększenia -> zmienjszenia -> zwiększenia
void paint_area::resizeEvent(QResizeEvent *event)
{
    if(width() > image.width() || height() > image.height())
    {
        int new_width = qMax(width() + 128, image.width());
        int new_height = qMax(height() + 128, image.height());
        resize_image(&image, QSize(new_width, new_height));
        update();
    }
    QWidget::resizeEvent(event);
}

//rysowanie linii
void paint_area::draw_line(const QPoint &end_point)
{
    QPainter painter(&image);
    painter.setPen(QPen(draw_color, draw_width));
    painter.drawLine(last_point, end_point);
    int rad = (draw_width / 2) + 2;
    update(QRect(last_point, end_point).normalized().adjusted(-rad,-rad,+rad,+rad));
    last_point = end_point;
}

//zmiana wielkości okna
void paint_area::resize_image(QImage *image, const QSize &new_size)
{
    if(image->size() == new_size)
        return;
    QImage new_image(new_size, QImage::Format_RGB32);
    new_image.fill(qRgb(255, 255, 255));
    QPainter painter(&new_image);
    painter.drawImage(QPoint(0, 0), *image);
    *image = new_image;
}

//zmiana koloru pędzla
void paint_area::set_draw_color(const QColor &new_color)
{
    draw_color = new_color;
}

//zmiana grubości pędzla
void paint_area::set_draw_width(int new_width)
{
    draw_width = new_width;
}
















