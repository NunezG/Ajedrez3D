#ifndef __Ficha_
#define __Ficha_

#include "ObjetoOgre.h"

enum ColorFicha
{
    Blanco,
    Negro
};

struct FichaPrueba{
    Ogre::String Tipo;
    Ogre::Entity* entFicha;
    bool esNegra;
    bool muerta;
    int casilla[2];
};

struct ListaPosiciones{
    ListaPosiciones* anterior;
    int posicion[2];
};

class Ficha : public ObjetoOgre
{
public:

    ~Ficha(void);
    //constructor de copia
    Ficha(const Ficha& fichaOriginal, std::string nombre, int tipo);

    virtual bool setCasilla(int fila, int col);

    void creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask);
    virtual bool autorizaFicha(int diferencia[2]) = 0;

    bool esNegra;
    bool salto;
    int tipo_Ficha;
protected:

    Ficha(std::string nombre, int tipo);

    bool Selected;
    //PARA EVALUAR:
    bool Moved;
    short PieceActionValue;
    short AttackedValue;
    short DefendedValue;
    short valorFicha;
   //  Stack<byte> ValidMoves; // lista de movimientos válidos
    bool muerta;
    int casilla[2];

private: 
    ObjetoOgre* objetoOgreAsociado;
};

#endif
