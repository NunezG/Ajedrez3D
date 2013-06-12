#ifndef __MenuInicio_
#define __MenuInicio_

#include "BaseVistas.h"

class MenuInicio : public BaseVistas
{
public:
    MenuInicio(ModeloVista* modeloV);//Ventana* mFrameListener);
    ~MenuInicio(void);

   // CEGUI::FrameWindow* createGUI(void);
    //bool salir();
    bool pantallaInicio();

private:
    bool iniciaVentana();
    bool botonSalir(const CEGUI::EventArgs    &e);
    bool botonJuegoTurnos(const CEGUI::EventArgs &e);
    bool botonJuegoSolo(const CEGUI::EventArgs &e);
    bool botonConfig(const CEGUI::EventArgs &e);
    bool botonVolver(const CEGUI::EventArgs &e);
    bool botonAplicarCambios(const CEGUI::EventArgs &e);
    bool sobrevuelaLista(const CEGUI::EventArgs &e);
    bool seleccionaResolucion(const CEGUI::EventArgs &e);
    bool sobrevuelaListaDificultad(const CEGUI::EventArgs &e);
    bool seleccionaDificultad(const CEGUI::EventArgs &e);
    bool pantallaConfig();
    CEGUI::Listbox* creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre,std::vector<std::string*> listaElementos, CEGUI::Listbox* listaReal);

    CEGUI::Window* ventanaConfig;
    CEGUI::Listbox *listaResoluciones;
    CEGUI::Listbox *listaDificultades;
};

#endif
