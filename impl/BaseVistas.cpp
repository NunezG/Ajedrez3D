#include "../headers/BaseVistas.h"

BaseVistas::BaseVistas() :
    modoJuego(0)


{  
    modelo = Modelo::getSingletonPtr();
}

BaseVistas::~BaseVistas()
{

}
