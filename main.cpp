#include "main_window.h"
#include "paint_area.h"
#include <QApplication>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_window w;
    w.show();
    return a.exec();
}
