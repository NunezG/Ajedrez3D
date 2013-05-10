#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano(void);
    JugadorHumano(Tablero* tablero);

    bool esHumano();


    //void setVentana(Ventana* obj);
    void mueveFicha(float time);

    void aplicaSeleccion();

    void autorizaCasilla();

    void sobreVuelaCasilla();


protected:




private:  

    CEGUI::Window *ventanaJaque;
   // Ventana* ventana;



};


#endif
