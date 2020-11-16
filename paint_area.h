#ifndef PAINT_AREA_H
#define PAINT_AREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <iostream>
#include <string>
enum tool_type
{
    simple_drawing_tool_type,
    flood_fill_tool_type,
    eraser_tool_type,
    air_brush_tool_type,
    plaid_tool_type,
    scratch_tool_type
};

class paint_area : public QWidget
{
    Q_OBJECT

public:
    paint_area(QWidget *parent = nullptr);


    void set_draw_color(const QColor &new_color);
    void set_draw_width(int new_width);
    void set_tool_type(tool_type new_tool);

    //zwracanie wartości koloru pędzla
    QColor return_draw_color() const {return draw_color;};
    //zwracanie wartości grubości pędzla
    int return_draw_width() const {return draw_width;};
    int return_last_point_x() const {return last_point.x();};
    int return_last_point_y() const {return last_point.y();};

protected:
    //funkjcie dziedziczone z klasy QWidget
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void draw_line(const QPoint &end_point);
    void draw_air_brush_line(const QPoint &end_point);
    void draw_plaid_line(const QPoint &end_point);
    void draw_scratch_line(const QPoint &end_point);
    void resize_image(QImage *image, const QSize &new_size);
    void flood_fill(QPoint point);



    //czy użytkownik rysuje
    bool drawing = false;
    //grubość pędzla
    int draw_width = 10;
    //kolor pędzla
    QColor draw_color = Qt::black;
    QColor temp = Qt::black;
    QImage image;
    //ostatni punkt
    QPoint last_point;

    tool_type drawing_tool = simple_drawing_tool_type;
};

#endif // PAINT_AREA_H
