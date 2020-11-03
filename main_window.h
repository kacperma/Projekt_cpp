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
    void drawing_color();
    void drawing_width();

private:
    void create_actions();
    void create_menu();

    QMenu *option_menu;
    paint_area *paint_Area;
    QAction *exit_action;
    QAction *draw_color_act;
    QAction *draw_width_act;


};
#endif // MAIN_WINDOW_H