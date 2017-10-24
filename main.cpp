#include "mainwindow.h"
#include <QApplication>
#include "vector3D.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Vector3D vect;//In stack for short time use (return object)
    Vector3D *vect2 = new Vector3D(0,1,0);//In heap for long time use (return pointer)
    Vector3D *vect3 = new Vector3D(0,0,1);

    if(vect2->isEqual(vect3))
    {
        std::cout << "true\n";
    }
    else
    {
        std::cout << "false\n";
    }
    vect2->print();
    vect3->print();
    w.show();
    std::cout << "" << vect2->scalar_product(vect3);
    //vect.print();
    //vect2->print();
    //vect2->invert();
    //vect2->print();
    //vect2->add(vect2);
    //vect2->print();

    return a.exec();
}
