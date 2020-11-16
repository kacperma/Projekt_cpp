#include "main_window.h"
#include "./ui_main_window.h"
#include "paint_area.h"
#include <QtWidgets>
#include <iostream>

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
    setWindowTitle(tr("OwO idę popełnić sudoku"));
    resize(500,500);
}

//okno zmiany koloru narzędzia
void main_window::drawing_color()
{
    QColor new_color = QColorDialog::getColor(paint_Area->return_draw_color());
    if (new_color.isValid())
        paint_Area->set_draw_color(new_color);
}

//okno zmiany grobuści narzędzia
void main_window::drawing_width()
{
    bool ok;

    //minimum = 1, max = 50, zmiana co 1
    int new_width = QInputDialog::getInt(this, tr("Pic"), tr("Select pen width: "),
                                         paint_Area->return_draw_width(), 1, 50, 1, &ok);

    if (ok)
        paint_Area->set_draw_width(new_width);
}


void main_window::simple_tool()
{
    paint_Area->set_tool_type(simple_drawing_tool_type);
}

void main_window::flood_fill_tool()
{
    paint_Area->set_tool_type(flood_fill_tool_type);
}

void main_window::eraser_tool()
{
    paint_Area->set_tool_type(eraser_tool_type);
}

void main_window::air_brush_tool()
{
    paint_Area->set_tool_type(air_brush_tool_type);
}

void main_window::plaid_tool()
{
    paint_Area->set_tool_type(plaid_tool_type);
}

void main_window::scratch_tool()
{
    paint_Area->set_tool_type(scratch_tool_type);
}






//stworzenie akcji które użytkownik może wykonać
void main_window::create_actions()
{
    exit_action = new QAction(tr("E&xit"), this);
    connect(exit_action, &QAction::triggered, this, &main_window::close);

    draw_color_act = new QAction(tr("Color"), this);
    connect(draw_color_act, SIGNAL(triggered()), this, SLOT(drawing_color()));

    draw_width_act = new QAction(tr("Thickness"), this);
    connect(draw_width_act, SIGNAL(triggered()), this, SLOT(drawing_width()));

    simple_tool_act = new QAction(tr("Simple"), this);
    connect(simple_tool_act, SIGNAL(triggered()), this, SLOT(simple_tool()));

    flood_fill_tool_act = new QAction(tr("Flood Fill"), this);
    connect(flood_fill_tool_act, SIGNAL(triggered()), this, SLOT(flood_fill_tool()));

    eraser_tool_act = new QAction(tr("Eraser"), this);
    connect(eraser_tool_act, SIGNAL(triggered()), this, SLOT(eraser_tool()));

    air_brush_tool_act = new QAction(tr("Air brush"), this);
    connect(air_brush_tool_act, SIGNAL(triggered()), this, SLOT(air_brush_tool()));

    plaid_tool_act = new QAction(tr("Plaid brush"), this);
    connect(plaid_tool_act, SIGNAL(triggered()), this, SLOT(plaid_tool()));

    scratch_tool_act = new QAction(tr("Scratch brush"), this);
    connect(scratch_tool_act, SIGNAL(triggered()), this, SLOT(scratch_tool()));


}



//tworzy pasek manu
void main_window::create_menu()
{
    option_menu = new QMenu(tr("&Brushes"), this);
    option_menu->addAction(simple_tool_act);
    option_menu->addAction(air_brush_tool_act);
    option_menu->addAction(plaid_tool_act);
    option_menu->addAction(scratch_tool_act);
    menuBar()->addMenu(option_menu);



    menuBar()->addAction(draw_color_act);
    menuBar()->addAction(draw_width_act);
    menuBar()->addAction(flood_fill_tool_act);
    menuBar()->addAction(eraser_tool_act);

}






main_window::~main_window()
{
}

