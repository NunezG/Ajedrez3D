#ifndef __BaseJuego_h_
#define __BaseJuego_h_

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
//#include "MenuInicio.h"

#include "Ventana.h"

//#include "MenuInicial.h"
#include <OgreRoot.h>


class BaseJuego : public Ogre::FrameListener
{
public:
    void go(void);

protected:   
    Ventana* punteroVentana;

    Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()
    virtual void inicio(void) = 0;

    BaseJuego(void);
    ~BaseJuego(void);

    void destroyScene(void);
    void setupResources(void);
    void loadResources(void);
    bool setup();
    bool configuraGraficos(const char *desiredRenderer);
    bool configureOpenGL();
    bool configureOgre(void);
    void chooseSceneManager(void);

    Ogre::Root *mRoot;

    //BUCLE PRINCIPAL
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;

private:   
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
};

#endif // #ifndef __BaseJuego_h_
