#ifndef __BaseJuego_h_
#define __BaseJuego_h_

//#include <Ogre.h>
//#include <OIS.h>
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
//#include "MenuInicio.h"

#include "../Vistas/Ventana.h"

//#include "MenuInicial.h"
//#include <OgreRoot.h>



class BaseJuego : public Ogre::FrameListener
{
public:
    void go(void);

protected:

    BaseJuego(void);
    ~BaseJuego(void);



   // virtual void inicio(void) = 0;

    void destroyScene(void);
    void setupResources(void);
    void loadResources(void);
    bool setup();
    bool configuraGraficos(const char *desiredRenderer);
    bool configureOpenGL();
    bool configureOgre(void);
    void chooseSceneManager(void);
    void inicio(void);

    void agregaJugador();


    //BUCLE PRINCIPAL
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

   // void destruyeTablero(void);


    Ventana* punteroVentana;

    Ogre::Root *mRoot;
    Modelo* modelo;
    Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()
    Ogre::SceneManager* mSceneMgr;

};

#endif // #ifndef __BaseJuego_h_
