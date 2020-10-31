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
    setWindowTitle(tr("JAPIERDOLE DLACZEGO TO KURWA NIE DZIAŁAAAAA"));
    resize(500,500);
}

//stworzenie akcji które użytkownik może wykonać
void main_window::create_actions()
{
    exit_action = new QAction(tr("E&xit"), this);
    connect(exit_action, &QAction::triggered, this, &main_window::close);
}

main_window::~main_window()
{
}










