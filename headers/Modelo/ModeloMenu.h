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


    void creaBoton(CEGUI::Event::Subscriber evento, Ogre::String nombre);

    int posBoton;

    CEGUI::FrameWindow* ventana;
    void creaVentana();


private:  

    //Singleton;
    ModeloMenu(void);
    void operator=(const ModeloMenu& miModeloMenu) ;
    ModeloMenu(const ModeloMenu& miModeloMenu);

};

#endif
