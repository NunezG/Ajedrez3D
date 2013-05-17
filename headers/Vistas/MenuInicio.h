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
    bool iniciaVentana();

    bool esMenuInicio();


protected:
    int posBoton;

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


    bool mueveCamara(float frecuencia);

    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    CEGUI::Window* ventanaConfig;

    CEGUI::Listbox *listaResoluciones;
    CEGUI::Listbox *listaDificultades;

    std::vector<std::string*>  listaElementos;

    // std::vector<std::string>  listaElementos;

    CEGUI::Window *sheetWindow;
    CEGUI::Window *quitButton;
    CEGUI::Window *mBotonJTurnos;
    CEGUI::Window *mBotonJSolo;

    CEGUI::FrameWindow* fWnd;

    CEGUI::Listbox* creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre,std::vector<std::string*> listaElementos, CEGUI::Listbox* listaReal);

};

#endif
