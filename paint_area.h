#ifndef PAINT_AREA_H
#define PAINT_AREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <iostream>
#include <string>

//typ wybranego narzędzia
enum tool_type
{
    simple_drawing_tool_type,
    flood_fill_tool_type,
    eraser_tool_type,
    air_brush_tool_type,
    plaid_tool_type,
    scratch_tool_type,
<<<<<<< HEAD
    draw_rectangle_tool_type,
    draw_cricle_tool_type,
    draw_straight_line_tool_type,
    draw_triangle_tool_type,
    draw_rectangular_triangle_tool_type,

=======
    text_tool_type
>>>>>>> edPaw
};

class paint_area : public QWidget
{
    Q_OBJECT

public:
    paint_area(QWidget *parent = nullptr);

    void set_main_color(const QColor &new_color);
    void set_second_color(const QColor &new_color);
    void set_draw_width(int new_width);
    void set_tool_type(tool_type new_tool);
    bool open_image(const QString &file_name);
    bool save_image(const QString &file_name, const char *file_format);
    bool check_modified() const {return modified;};

    //zwracanie wartości koloru pędzla
    QColor return_main_color() const {return main_color;};
    QColor return_second_color() const {return second_color;};
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
<<<<<<< HEAD
    void draw_rectangle(const QPoint &end_point);
    void draw_circle(const QPoint &endpoint);
    void draw_straight_line(const QPoint &endpoint);
    void draw_triangle(const QPoint &endpoint);
    void draw_rectangular_triangle(const QPoint &endpoint);
=======
    void generate_text(const QPoint &end_point);

>>>>>>> edPaw


    //czy użytkownik rysuje
    bool drawing = false;
    //grubość pędzla
    int draw_width = 10;

    //kolor pędzla
    QColor main_color = Qt::black;
    QColor second_color = Qt::transparent;

    //tymczasowy kolor, potrzebny do gumki
    QColor temp = main_color;
    QImage image;
    //ostatni punkt
    QPoint last_point;
    //początkowy punkt, potrzebny do rysowania figur
    QPoint start_point;

    tool_type drawing_tool = simple_drawing_tool_type;

    //zmienia się zależnie od tego czy zapisano ostatnie zmiany
    bool modified = false;
};

#endif // PAINT_AREA_H
