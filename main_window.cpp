#include "main_window.h"
#include "./ui_main_window.h"
#include "paint_area.h"
#include <QtWidgets>


#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>

//główne okno, konstruktor
main_window::main_window(QWidget *parent) : QMainWindow(parent), paint_Area(new paint_area(this))
{

    setCentralWidget(paint_Area);
    create_actions();
    create_menu();
    setWindowTitle(tr("Nasz super pejnt 10/10"));
    resize(500,500);
}

//okno zmiany koloru narzędzia
void main_window::drawing_color()
{
    QColor new_color = QColorDialog::getColor(paint_Area->drawing_color());
    if (new_color.isValid())
        paint_Area->set_draw_color(new_color);
}

//okno zmiany grobuści narzędzia
void main_window::drawing_width()
{
    bool ok;

    //minimum = 1, max = 50, zmiana co 1
    int new_width = QInputDialog::getInt(this, tr("Pic"), tr("Select pen width: "),
                                         paint_Area->drawing_width(), 1, 50, 1, &ok);

    if (ok)
        paint_Area->set_draw_width(new_width);
}

//stworzenie akcji które użytkownik może wykonać
void main_window::create_actions()
{
    exit_action = new QAction(tr("E&xit"), this);
    connect(exit_action, &QAction::triggered, this, &main_window::close);

    draw_color_act = new QAction(tr("&Pen Color..."), this);
    connect(draw_color_act, SIGNAL(triggered()), this, SLOT(drawing_color()));

    draw_width_act = new QAction(tr("Pen &Width..."), this);
    connect(draw_width_act, SIGNAL(triggered()), this, SLOT(drawing_width()));

}


main_window::~main_window()
{
}


//tworzy pasek manu
void main_window::create_menu()
{
    option_menu = new QMenu(tr("&Options"), this);
    option_menu->addAction(draw_color_act);
    option_menu->addAction(draw_width_act);

    menuBar()->addMenu(option_menu);
}






