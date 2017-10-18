#include "mainwindow.h"
#include <QApplication>
#include "vector3D.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Vector3D vect;//In stack for short time use (return object)
    Vector3D *vect2 = new Vector3D(1,2,1);//In heap for long time use (return pointer)

    vect.print();
    vect2->print();
    vect2->invert();
    vect2->print();
    vect2->add(vect2);
    vect2->print();
    std::cout << "" << vect2->square_magnitude() << " + " << vect2->magnitude();
    w.show();


    return a.exec();
}
