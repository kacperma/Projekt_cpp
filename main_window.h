#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QList>
#include <QMainWindow>

class paint_area;

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    main_window(QWidget *parent = nullptr);
    ~main_window();

protected:
    void close_event(QCloseEvent *event);

private slots:
    void set_main_color();
    void set_second_color();
    void set_width();
    void simple_tool();
    void flood_fill_tool();
    void eraser_tool();
    void air_brush_tool();
    void plaid_tool();
    void scratch_tool();
    void rectangle_tool();
    void circle_tool();
    void straight_line_tool();
    void triangle_tool();
    void rectangular_triangle_tool();



    void text_tool();
    void open();
    void save();

private:
    void create_actions();
    void create_menu();
    bool check_save(); //sprawdza czy są zmiany do zapisania
    bool save_file(const QByteArray &file_format); //otwiera okno zapisu

    QMenu *option_menu;
    QMenu *save_menu;
    QMenu *file_menu;
    paint_area *paint_Area;
    QAction *exit_action;
    QAction *main_color_act;
    QAction *second_color_act;
    QAction *draw_width_act;
    QAction *simple_tool_act;
    QAction *flood_fill_tool_act;
    QAction *eraser_tool_act;
    QAction *air_brush_tool_act;
    QAction *plaid_tool_act;
    QAction *scratch_tool_act;
    QAction *draw_rectangle_act;
    QAction *draw_circle_act;
    QAction *draw_straight_line_act;
    QAction *draw_triangle_act;
    QAction *draw_rectangular_triangle_act;

    QAction *open_act;
    QAction *text_tool_act;
    QList<QAction *> save_act;




};
#endif // MAIN_WINDOW_H
