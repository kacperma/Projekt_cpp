#ifndef PAINT_AREA_H
#define PAINT_AREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class paint_area : public QWidget
{
    Q_OBJECT

public:
    paint_area(QWidget *parent = nullptr);


    void set_draw_color(const QColor &new_color);
    void set_draw_width(int new_width);

    //zwracanie wartości koloru pędzla
    QColor drawing_color() const {return draw_color;};
    //zwracanie wartości grubości pędzla
    int drawing_width() const {return draw_width;};

protected:
    //funkjcie dziedziczone z klasy QWidget
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void draw_line(const QPoint &end_point);
    void resize_image(QImage *image, const QSize &new_size);

    //czy użytkownik rysuje
    bool drawing = false;
    //grubość pędzla
    int draw_width = 1;
    //kolor pędzla
    QColor draw_color = Qt::black;
    QImage image;
    //ostatni punkt
    QPoint last_point;
};

#endif // PAINT_AREA_H
