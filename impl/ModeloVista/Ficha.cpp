#include "../../headers/ModeloVista/Ficha.h"
Ficha::Ficha(std::string nombre, int tipo) :
    esNegra(0),
    //muerta(0),
    tipo_Ficha(tipo),
    ObjetoOgre(nombre)
   // salto(false)
    // ,casilla(0)
{
}

Ficha::~Ficha()
{
}

Ficha::Ficha( const Ficha& fichaOriginal, std::string nombre, int tipo ):
    esNegra(fichaOriginal.esNegra),
   // muerta(0),
    tipo_Ficha(tipo),
    ObjetoOgre(nombre)
   // salto(false)
  //  tipo_Ficha = fichaOriginal
{
}

void Ficha::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{
    if (mask == NEGRAS) esNegra = true;
    else if (mask == BLANCAS )esNegra = false;

   ObjetoOgre::creaModelo3D(sceneMgr, nombreMalla, mask);
}
