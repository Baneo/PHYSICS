#ifndef VECTOR3D_H
#define VECTOR3D_H


class Vector3D
{
private:
    float x; //Composante X
    float y; //Composante Y
    float z; //Composante Z

public:
    float getX() const; //Getter X
    float getY() const; //Getter Y
    float getZ() const; //Getter Z
    Vector3D(); //Constructeur par défaut
    Vector3D(const float x, const float y, const float z); //COnstructeur avec 3 composantes
    void invert(); //Fonction inverse
    void print(); //Affiche les composantes du vecteur
    void add(Vector3D*); //Ajoute un vecteur
    void sub(Vector3D*); //Soustrait un vecteur
    void normalize(); //Normalise le vecteur
    float magnitude(); //Calcule la norme
    float square_magnitude(); //Calcule la norme au carré
    void operator*=(const float); //Multiplication par un scalaire
    Vector3D operator*(const float) const; //Multiplication par un scalaire
    bool isEqual(Vector3D*); //Opérateur égalité
    float scalar_product(Vector3D*); //Produit scalaire
    void operator+=(const Vector3D&); //operateur de +=
    Vector3D operator+(const Vector3D&) const;//operateur +
    void operator-=(const Vector3D&); //operateur de -=
    Vector3D operator-(const Vector3D&) const;//operateur -
    void add_scaled_vector(const Vector3D&, float); //ajout d'un vecteur multiplie par un scalaire
    Vector3D component_product(const Vector3D&) const;
    void component_product_update(const Vector3D&);
    float operator*(const Vector3D&);
    Vector3D vector_product(const Vector3D&) const;
    void operator%=(const Vector3D&);
    Vector3D operator%(const Vector3D&) const;
};

#endif // VECTOR3_H
