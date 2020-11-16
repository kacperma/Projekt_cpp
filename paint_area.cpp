#include "paint_area.h"
#include "main_window.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QStack>

paint_area::paint_area(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}

//event wciskania lewego przycisku
void paint_area::mousePressEvent(QMouseEvent *event)
{
    //std::cout << drawing_tool << "\n";
    switch(drawing_tool)
    {
        case simple_drawing_tool_type:
        {
            if(event->button() == Qt::LeftButton)
            {
                last_point = event->pos();
                drawing = true;

            }
            break;
        }
        case flood_fill_tool_type:
        {
            flood_fill(event->pos());
            break;
        }
        case eraser_tool_type:
        {
            temp = return_draw_color();
            if(event->button() == Qt::LeftButton)
            {
                draw_color = Qt::white;
                last_point = event->pos();
                drawing = true;
            }
            break;
        }
        case air_brush_tool_type:
        {

            if(event->button() == Qt::LeftButton)
            {
                last_point = event->pos();
                drawing = true;
            }
            break;
        }
        case plaid_tool_type:
        {
            if(event->button() == Qt::LeftButton)
            {
                last_point = event->pos();
                drawing = true;
            }
            break;
        }
        case scratch_tool_type:
        {
            if(event->button() == Qt::LeftButton)
            {
                last_point = event->pos();
                drawing = true;
            }
            break;
        }



    }


}

//event przy ruszaniu myszką
void paint_area::mouseMoveEvent(QMouseEvent *event)
{

    switch(drawing_tool)
    {
        case simple_drawing_tool_type:
        {
            if((event->buttons() & Qt::LeftButton) && drawing == true)
            {
                draw_line(event->pos());
            }
            break;
        }
        case flood_fill_tool_type:
        {
            break;
        }
        case eraser_tool_type:
        {
            if((event->buttons() & Qt::LeftButton) && drawing == true)
            {
                draw_line(event->pos());
            }
            break;
        }
        case air_brush_tool_type:
        {
            if((event->buttons() & Qt::LeftButton) && drawing == true)
            {
                draw_air_brush_line(event->pos());
            }
            break;
        }
        case plaid_tool_type:
        {
            if((event->buttons() & Qt::LeftButton) && drawing == true)
            {
                draw_plaid_line(event->pos());
            }
            break;
        }
        case scratch_tool_type:
        {
            if((event->buttons() & Qt::LeftButton) && drawing == true)
            {
                draw_scratch_line(event->pos());
            }
            break;
        }

    }
}

//event przy puszczeniu lewego przycisku
void paint_area::mouseReleaseEvent(QMouseEvent *event)
{

    switch(drawing_tool)
    {
        case simple_drawing_tool_type:
        {
            if(event->button() == Qt::LeftButton && drawing == true)
            {
                draw_line(event->pos());
                drawing = false;
            }
            break;
        }
        case flood_fill_tool_type:
        {
            break;
        }
        case eraser_tool_type:
        {
            if(event->button() == Qt::LeftButton && drawing == true)
            {
                draw_line(event->pos());
                draw_color = temp;
                drawing = false;
            }
            break;
        }
        case air_brush_tool_type:
        {
            if(event->button() == Qt::LeftButton && drawing == true)
            {
                draw_air_brush_line(event->pos());
                drawing = false;
            }
            break;
        }
        case plaid_tool_type:
        {
            if(event->button() == Qt::LeftButton && drawing == true)
            {
                draw_plaid_line(event->pos());
                drawing = false;
            }
            break;
        }
        case scratch_tool_type:
        {
            if(event->button() == Qt::LeftButton && drawing == true)
            {
                draw_scratch_line(event->pos());
                drawing = false;
            }
            break;
        }

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
    painter.setBrush(Qt::SolidPattern);
    painter.drawLine(last_point, end_point);
    int rad = (draw_width / 2) + 2;
    update(QRect(last_point, end_point).normalized().adjusted(-rad,-rad,+rad,+rad));
    last_point = end_point;
}

//rysowanie linii air brush
void paint_area::draw_air_brush_line(const QPoint &end_point)
{
    QPainter painter(&image);
    int rad = (draw_width / 2) + 2;
    int steps = 2 + (end_point - last_point).manhattanLength() / 2;
    painter.setBrush(QBrush(draw_color, Qt::Dense5Pattern));
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < steps; i++)
    {
        int x = last_point.x() + i * (end_point.x() - last_point.x()) / (steps - 1);
        int y = last_point.y() + i * (end_point.y() - last_point.y()) / (steps - 1);

        painter.drawEllipse(x - (rad), y - (rad), draw_width, draw_width);
        update(QRect(last_point, end_point).normalized().adjusted(-rad,-rad,+rad,+rad));
        last_point = end_point;
    }

}

//rysowanie linii plaid
void paint_area::draw_plaid_line(const QPoint &end_point)
{
    QPainter painter(&image);
    int rad = (draw_width / 2) + 2;
    int steps = 2 + (end_point - last_point).manhattanLength() / 2;
    painter.setBrush(QBrush(draw_color, Qt::CrossPattern));
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < steps; i++)
    {
        int x = last_point.x() + i * (end_point.x() - last_point.x()) / (steps - 1);
        int y = last_point.y() + i * (end_point.y() - last_point.y()) / (steps - 1);

        painter.drawEllipse(x - (rad), y - (rad), draw_width, draw_width);
        update(QRect(last_point, end_point).normalized().adjusted(-rad,-rad,+rad,+rad));
        last_point = end_point;
    }

}

//rysowanie 3. brush
void paint_area::draw_scratch_line(const QPoint &end_point)
{
    QPainter painter(&image);
    int rad = (draw_width / 2) + 2;
    int steps = 2 + (end_point - last_point).manhattanLength() / 2;
    painter.setBrush(QBrush(draw_color, Qt::FDiagPattern));
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < steps; i++)
    {
        int x = last_point.x() + i * (end_point.x() - last_point.x()) / (steps - 1);
        int y = last_point.y() + i * (end_point.y() - last_point.y()) / (steps - 1);

        painter.drawEllipse(x - (rad), y - (rad), draw_width, draw_width);
        update(QRect(last_point, end_point).normalized().adjusted(-rad,-rad,+rad,+rad));
        last_point = end_point;
    }

}

//wypełnienie danego obszaru, użycie sterty ponieważ rozwiązanie rekurencyjne powodowało stack overflow hehe
void paint_area::flood_fill(QPoint point)
{
    QColor color = image.pixelColor(point);
    if(draw_color != color)
    {
        QStack<QPoint> stack;
        stack.push(point);
        while(stack.count() > 0)
        {
            QPoint temp_point = stack.pop();
            if(image.pixelColor(temp_point) == color)
            {
                //zmiana koloru danego pixela
                image.setPixelColor(temp_point, draw_color);

                //sprawdzanie czy pixele sąsiednie są w zakresie obrazu oraz wrzucenie ich do stosu
                if(image.valid(temp_point.x() + 1, temp_point.y()))
                    stack.push(QPoint(temp_point.x() + 1, temp_point.y()));

                if(image.valid(temp_point.x() - 1, temp_point.y()))
                    stack.push(QPoint(temp_point.x() - 1, temp_point.y()));

                if(image.valid(temp_point.x(), temp_point.y() + 1))
                    stack.push(QPoint(temp_point.x(), temp_point.y() + 1));

                if(image.valid(temp_point.x(), temp_point.y() - 1))
                    stack.push(QPoint(temp_point.x(), temp_point.y() - 1));
            }
        }
    }
    update();
    return;
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

void paint_area::set_tool_type(tool_type new_tool)
{
    drawing_tool = new_tool;
}
