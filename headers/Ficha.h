#ifndef __Ficha_
#define __Ficha_

#include <Ogre.h>

class Ficha
{
public:
    ~Ficha(void);
    Ficha(bool esNegra);

    virtual bool mueveFicha() = 0;
    virtual bool autorizaFicha(int diferencia[2]) = 0;

    virtual bool setEntidad(Ogre::Entity* entidad);
    virtual Ogre::Entity* getEntidad();
    virtual bool setCasilla(int fila, int col);

protected:

    virtual bool creaEntidad(Ogre::String nombre);

    Ogre::String Tipo;
    Ogre::Entity* entFicha;
    bool esNegra;

    bool muerta;

    int casilla[2];


private:
};

#endif
