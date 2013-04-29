#ifndef __Ficha_
#define __Ficha_

#include <Ogre.h>
#include "ObjetoOgre.h"

enum ColorFicha
{
    Blanco,
    Negro
};

enum tipoFicha
{
    Vacio,
    Peon,
    Caballo,
    Alfil,
    Torre,
    Reina,
    Rey
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
    Ficha(  const Ficha& fichaOriginal, std::string nombre, tipoFicha tipo);

    void creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask);



    virtual bool mueveFicha() = 0;
    virtual bool autorizaFicha(int diferencia[2]) = 0;

  //  virtual bool setEntidad(Ogre::Entity* entidad);
  //  virtual Ogre::Entity* getEntidad();

   // virtual bool setNodoOgre(Ogre::Entity* entidad);
  //  virtual Ogre::SceneNode* getNodoOgre();

    virtual bool setCasilla(int fila, int col);
    bool esNegra;


    bool salto;
    tipoFicha tipo_Ficha;




protected:


    Ficha(std::string nombre, tipoFicha tipo);




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

    static short CalculatePieceActionValue(tipoFicha pieceType);
    static short CalculatePieceValue(tipoFicha pieceType);




};

#endif
