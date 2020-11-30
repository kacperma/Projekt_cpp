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
    setWindowTitle(tr("iks de de umrzeć mi sie chce"));
    resize(500,500);
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

    open_act = new QAction(tr("&Open..."), this);
    open_act->setShortcuts(QKeySequence::Open);
    connect(open_act, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        save_act.append(action);
    }



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



//tworzy pasek menu
void main_window::create_menu()
{
    option_menu = new QMenu(tr("&Brushes"), this);
    option_menu->addAction(simple_tool_act);
    option_menu->addAction(air_brush_tool_act);
    option_menu->addAction(plaid_tool_act);
    option_menu->addAction(scratch_tool_act);
    menuBar()->addMenu(option_menu);

    save_menu = new QMenu(tr("&Save as"), this);
    foreach (QAction *action, save_act)
        save_menu->addAction(action);
    menuBar()->addMenu(save_menu);
    menuBar()->addAction(open_act);



    menuBar()->addAction(draw_color_act);
    menuBar()->addAction(draw_width_act);
    menuBar()->addAction(flood_fill_tool_act);
    menuBar()->addAction(eraser_tool_act);
    menuBar()->addAction(exit_action);

}

bool main_window::check_save()
{
    if (paint_Area->check_modified())
    {
        QMessageBox::StandardButton ret;

        ret = QMessageBox::warning(this, tr("Picture"), tr("The image has been modified.\n" "Do you want to save your changes?"),
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
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save As"),
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

