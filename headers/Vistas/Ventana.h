#ifndef __Ventana_
#define __Ventana_

#include <OgreWindowEventUtilities.h>

#include "MenuInicio.h"
#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"

class Ventana :  public Ogre::WindowEventListener
{
public:
    Ventana();
     ~Ventana(void);
    void go(void);


private:
    void creaVista();
    bool destruyeVista(void);
    bool iniciaListeners(void);
    bool muestraVentana();

    BaseVistas* vista;
    ModeloVista* modeloVista;
};

#endif
