#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "precision.h"

class Vector3D
{
private:
    real x; //Composante X
    real y; //Composante Y
    real z; //Composante Z

public:
    real getX() const; //Getter X
    real getY() const; //Getter Y
    real getZ() const; //Getter Z
    Vector3D(); //Constructeur par défaut
    Vector3D(const real x, const real y, const real z); //COnstructeur avec 3 composantes
    void invert(); //Fonction inverse
    void print(); //Affiche les composantes du vecteur
    void add(Vector3D*); //Ajoute un vecteur
    void sub(Vector3D*); //Soustrait un vecteur
    void normalize(); //Normalise le vecteur
    real magnitude() const; //Calcule la norme
    real square_magnitude(); //Calcule la norme au carré
    void operator*=(const real); //Multiplication par un scalaire
    Vector3D operator*(const real) const; //Multiplication par un scalaire
    bool isEqual(Vector3D*); //Opérateur égalité
    real scalar_product(Vector3D*); //Produit scalaire
    void operator+=(const Vector3D&); //operateur de +=
    Vector3D operator+(const Vector3D&) const;//operateur +
    void operator-=(const Vector3D&); //operateur de -=
    Vector3D operator-(const Vector3D&) const;//operateur -
    void add_scaled_vector(const Vector3D&, real); //ajout d'un vecteur multiplie par un scalaire
    Vector3D component_product(const Vector3D&) const;
    void component_product_update(const Vector3D&);
    real operator*(const Vector3D&);
    Vector3D vector_product(const Vector3D&) const;
    void operator%=(const Vector3D&);
    Vector3D operator%(const Vector3D&) const;
};

#endif // VECTOR3_H
