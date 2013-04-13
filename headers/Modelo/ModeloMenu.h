#ifndef __ModeloMenu_
#define __ModeloMenu_
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <OgreRenderWindow.h>



#include <CEGUI/CEGUI.h>
#include <Ogre.h>

class ModeloMenu
{
public:

    ~ModeloMenu(void);

    //Singleton
    static ModeloMenu* getSingletonPtr();


    void creaBoton(CEGUI::Event::Subscriber evento, Ogre::String nombre, CEGUI::FrameWindow* ventana);
    CEGUI::Listbox* creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre,std::vector<std::string*> listaElementos, CEGUI::FrameWindow* ventana);

    int posBoton;

    int numVentana;

    CEGUI::ListboxTextItem* elementoLista[];

  //  CEGUI::FrameWindow* ventana;
    CEGUI::FrameWindow* creaVentana(std::string nombre);


private:  

    //Singleton;
    ModeloMenu(void);
    void operator=(const ModeloMenu& miModeloMenu) ;
    ModeloMenu(const ModeloMenu& miModeloMenu);

};

#endif
