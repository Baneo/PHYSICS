#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "precision.h"

class Vector3D
{
private:
    real x; //Composante X
    real y; //Composante Y
    real z; //Composante Z
    real pad; //4 word alignment

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
    Vector3D unit() const;//Renvoie une version unitaire du vecteur appelant
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
    Vector3D component_product(const Vector3D&) const; //Calcul du produit des deux vecteur (x*x,y*y,z*z) et retourne le resultat
    void component_product_update(const Vector3D&); //meme calcul mais le resultat es mis dans l'objet appelant
    real operator*(const Vector3D&);//ca c'est du produit scalaire
    Vector3D vector_product(const Vector3D&) const; //produit vectoriel
    void operator%=(const Vector3D&);//ca c'est un produit vectoriel (avec un % comme operateur)
    Vector3D operator%(const Vector3D&) const;//same shit bruh
    real operator[](unsigned i) const;//operateur d'acces en mode tableau
    real& operator[](unsigned i);//same but different
    void trim (real);//tronque le vecteur a la valeur passee en argument
    bool operator==(const Vector3D&) const; //operateur == enfin !
    bool operator!=(const Vector3D&) const; //du coup operateur != en meme temps
    bool operator<(const Vector3D&) const;//idem pour <
    bool operator>(const Vector3D&) const;//et >
    bool operator<=(const Vector3D&) const;//et <=
    bool operator>=(const Vector3D&) const;//et enfin >=
    void clear();//donne le vecteur (0,0,0)
};

#endif // VECTOR3_H
