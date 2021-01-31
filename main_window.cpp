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


//główne okno
main_window::main_window(QWidget *parent) : QMainWindow(parent), paint_Area(new paint_area(this))
{

    setCentralWidget(paint_Area);
    create_actions();
    create_menu();
    setWindowTitle(tr("Paint"));
    resize(800,800);
}

//przy próbie zamknięcia okna sprawdź -> czy wprowadzono zmiany
//jeśli tak zapytaj czy użytkownik chce zapisac
void main_window::close_event(QCloseEvent *event)
{
    if (check_save())
        event->accept();
    else
        event->ignore();
}

//sprawdź czy zmiany w aktualnym pliku zostały zapisane
//otwórz okno wybory pliku do otwarcia
void main_window::open()
{
    if (check_save())
    {
        QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if (!file_name.isEmpty())
            paint_Area->open_image(file_name);
    }
}

//zapisywanie pliku
void main_window::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray file_format = action->data().toByteArray();
    save_file(file_format);
}

//okno zmiany koloru narzędzia
void main_window::set_main_color()
{
    QColor new_color = QColorDialog::getColor(paint_Area->return_main_color());
    if (new_color.isValid())
        paint_Area->set_main_color(new_color);
}

//ustawienie drugiego koloru
void main_window::set_second_color()
{
    QColor new_color = QColorDialog::getColor(paint_Area->return_second_color());
    if (new_color.isValid())
        paint_Area->set_second_color(new_color);
}

//okno zmiany grobuści narzędzia
void main_window::set_width()
{
    bool ok;

    //minimum = 1, max = 50, zmiana co 1
    int new_width = QInputDialog::getInt(this, tr(""), tr("Wybierz grubość: "),
                                         paint_Area->return_draw_width(), 1, 50, 1, &ok);

    if (ok)
        paint_Area->set_draw_width(new_width);
}


void main_window::simple_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/pencil.png")));
    paint_Area->set_tool_type(simple_drawing_tool_type);
}

void main_window::flood_fill_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/fill.png")));
    paint_Area->set_tool_type(flood_fill_tool_type);
}

void main_window::eraser_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/eraser.png")));
    paint_Area->set_tool_type(eraser_tool_type);
}

void main_window::air_brush_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/airbrush.png")));
    paint_Area->set_tool_type(air_brush_tool_type);
}

void main_window::plaid_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/airbrush.png")));
    paint_Area->set_tool_type(plaid_tool_type);
}

void main_window::scratch_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/airbrush.png")));
    paint_Area->set_tool_type(scratch_tool_type);
}

void main_window::rectangle_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/square.png")));
    paint_Area->set_tool_type(draw_rectangle_tool_type);
}

void main_window::circle_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/circle.png")));
    paint_Area->set_tool_type(draw_cricle_tool_type);
}

void main_window::straight_line_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/line.png")));
    paint_Area->set_tool_type(draw_straight_line_tool_type);
}

void main_window::triangle_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/triangle.png")));
    paint_Area->set_tool_type(draw_triangle_tool_type);
}

void main_window::text_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/text.png")));
    paint_Area->set_tool_type(text_tool_type);
}

void main_window::rectangular_triangle_tool()
{
    QWidget::setCursor(QCursor(QPixmap("resources/cursor/recttriangle.png")));
    paint_Area->set_tool_type(draw_rectangular_triangle_tool_type);
}

//stworzenie akcji które użytkownik może wykonać
void main_window::create_actions()
{
    exit_action = new QAction(tr("E&xit"), this);
    connect(exit_action, &QAction::triggered, this, &main_window::close);

    main_color_act = new QAction(tr("Kolor"), this);
    connect(main_color_act, SIGNAL(triggered()), this, SLOT(set_main_color()));

    second_color_act = new QAction(tr("Kolor Wyp"), this);
    connect(second_color_act, SIGNAL(triggered()), this, SLOT(set_second_color()));

    open_act = new QAction(tr("&Otwórz"), this);
    connect(open_act, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        save_act.append(action);
    }




    draw_width_act = new QAction(tr("Grubość"), this);
    connect(draw_width_act, SIGNAL(triggered()), this, SLOT(set_width()));

    simple_tool_act = new QAction(tr("Simple"), this);
    simple_tool_act->setIcon(QIcon("resources/cursor/pencil.png"));
    connect(simple_tool_act, SIGNAL(triggered()), this, SLOT(simple_tool()));

    flood_fill_tool_act = new QAction(tr(""), this);
    flood_fill_tool_act->setIcon(QIcon("resources/cursor/fill.png"));
    connect(flood_fill_tool_act, SIGNAL(triggered()), this, SLOT(flood_fill_tool()));

    eraser_tool_act = new QAction(tr(""), this);
    eraser_tool_act->setIcon(QIcon("resources/cursor/eraser.png"));
    connect(eraser_tool_act, SIGNAL(triggered()), this, SLOT(eraser_tool()));

    air_brush_tool_act = new QAction(tr("Air"), this);
    air_brush_tool_act->setIcon(QIcon("resources/cursor/airbrush.png"));
    connect(air_brush_tool_act, SIGNAL(triggered()), this, SLOT(air_brush_tool()));

    plaid_tool_act = new QAction(tr("Plaid"), this);
    plaid_tool_act->setIcon(QIcon("resources/cursor/airbrush.png"));
    connect(plaid_tool_act, SIGNAL(triggered()), this, SLOT(plaid_tool()));

    scratch_tool_act = new QAction(tr("Scratch"), this);
    scratch_tool_act->setIcon(QIcon("resources/cursor/airbrush.png"));
    connect(scratch_tool_act, SIGNAL(triggered()), this, SLOT(scratch_tool()));

    draw_rectangle_act = new QAction(tr(""), this);
    draw_rectangle_act->setIcon(QIcon("resources/cursor/square.png"));
    connect(draw_rectangle_act, SIGNAL(triggered()), this, SLOT(rectangle_tool()));

    text_tool_act = new QAction(tr("Text"), this);
    text_tool_act->setIcon(QIcon("resources/cursor/text.png"));
    connect(text_tool_act, SIGNAL(triggered()), this, SLOT(text_tool()));


    draw_circle_act = new QAction(tr(""), this);
    draw_circle_act->setIcon(QIcon("resources/cursor/circle.png"));
    connect(draw_circle_act, SIGNAL(triggered()), this, SLOT(circle_tool()));

    draw_straight_line_act = new QAction(tr(""), this);
    draw_straight_line_act->setIcon(QIcon("resources/cursor/line.png"));
    connect(draw_straight_line_act, SIGNAL(triggered()), this, SLOT(straight_line_tool()));

    draw_triangle_act = new QAction(tr(""), this);
    draw_triangle_act->setIcon(QIcon("resources/cursor/triangle.png"));
    connect(draw_triangle_act, SIGNAL(triggered()), this, SLOT(triangle_tool()));

    draw_rectangular_triangle_act = new QAction(tr("Trójkąt kwadr"), this);
    draw_rectangular_triangle_act->setIcon(QIcon("resources/cursor/recttriangle.png"));
    connect(draw_rectangular_triangle_act, SIGNAL(triggered()), this, SLOT(rectangular_triangle_tool()));
}

//tworzy pasek menu
void main_window::create_menu()
{
    file_menu = new QMenu(tr("&Plik"), this);
    save_menu = new QMenu(tr("&Zapisz jako"), this);
    foreach (QAction *action, save_act)
        save_menu->addAction(action);
    file_menu->addAction(open_act);
    file_menu->addMenu(save_menu);
    menuBar()->addMenu(file_menu);

    option_menu = new QMenu(tr("&Pędzle"), this);
    option_menu->addAction(simple_tool_act);
    option_menu->addAction(air_brush_tool_act);
    option_menu->addAction(plaid_tool_act);
    option_menu->addAction(scratch_tool_act);

    menuBar()->addMenu(option_menu);
    menuBar()->addAction(draw_width_act);
    menuBar()->addAction(eraser_tool_act);
    menuBar()->addAction(flood_fill_tool_act);

    menuBar()->addAction(main_color_act);
    menuBar()->addAction(second_color_act);

    menuBar()->addAction(draw_rectangle_act);
    menuBar()->addAction(draw_circle_act);
    menuBar()->addAction(draw_straight_line_act);
    menuBar()->addAction(draw_triangle_act);
    menuBar()->addAction(draw_rectangular_triangle_act);

    menuBar()->addAction(text_tool_act);

    menuBar()->addAction(exit_action);

}

bool main_window::check_save()
{
    if (paint_Area->check_modified())
    {
        QMessageBox::StandardButton ret;

        ret = QMessageBox::warning(this, tr("Obraz"), tr("Obraz został zmodyfikowany.\n" "Czy chcesz zapisać swoje zmiany?"),
                                                        QMessageBox::Save | QMessageBox::Discard  | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save_file("png");
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool main_window::save_file(const QByteArray &file_format)
{
    QString initial_path = QDir::currentPath() + "/untitled." + file_format;
    QString file_name = QFileDialog::getSaveFileName(this, tr("Zapisz jako"),
                                                 initial_path,
                                                 tr("%1 Files (*.%2);;All Files (*)")
                                                 .arg(QString::fromLatin1(file_format.toUpper()))
                                                 .arg(QString::fromLatin1(file_format)));

    if (file_name.isEmpty())
        return false;
    else
        return paint_Area->save_image(file_name, file_format.constData());
}


main_window::~main_window()
{
}

