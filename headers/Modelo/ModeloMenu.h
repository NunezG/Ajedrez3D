#ifndef __ModeloMenu_
#define __ModeloMenu_
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>



#include <CEGUI/CEGUI.h>
#include <Ogre.h>

class ModeloMenu
{
public:

    ~ModeloMenu(void);
    ModeloMenu(void);

    void creaBoton(CEGUI::Event::Subscriber evento, Ogre::String nombre, CEGUI::FrameWindow* ventana);
    CEGUI::Listbox* creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre,std::vector<std::string*> listaElementos, CEGUI::FrameWindow* ventana);
    void creaTexto(Ogre::String texto, CEGUI::FrameWindow* ventana);

    CEGUI::FrameWindow* creaVentana(std::string nombre);

    int posBoton;

    int numVentana;

  //  CEGUI::FrameWindow* ventana;

private:  




};

#endif
