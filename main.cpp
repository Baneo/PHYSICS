#include "mainwindow.h"
#include <QApplication>
#include "vector3.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Vector3 vect;//In stack for short time use (return object)
    Vector3 *vect2 = new Vector3(1,2,1);//In heap for long time use (return pointer)

    vect.print();
    vect2->print();
    vect2->invert();
    vect2->print();
    vect2->add(vect2);
    vect2->print();
    w.show();


    return a.exec();
}
