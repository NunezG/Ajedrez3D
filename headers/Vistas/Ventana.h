#ifndef __Ventana_
#define __Ventana_


#include <iostream>

#include <Ogre.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#include <OIS.h>
#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreConfigFile.h>

#include "MenuInicio.h"
//#include "EscenaAjedrez.h"

#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"

class Ventana :  public Ogre::WindowEventListener
{
public:
    Ventana(ModeloVista* modeloVista);

     ~Ventana(void);

    void loadResources(void);

    void destroyScene(void);
    //Iniciación

    bool start(void);

    bool resetOgre(void);
    bool initOgre(void);

    //Pantallas
    bool muestraVentana();

    int pantallaActual();


  //  int mPantalla;
    BaseVistas* vista;
   // BaseApplication* Create(Ogre::String type);

    void destruyeVista();
    void creaVista();

    Ogre::Root *mRoot;

private:

    ModeloVista* modeloVista;


  //  Ogre::SceneManager* mSceneMgr;
  //  Ogre::Root* mRoot;
   // Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()



   // MenuInicio* menu;

};

#endif
