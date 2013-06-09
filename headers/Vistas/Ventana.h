#ifndef __Ventana_
#define __Ventana_

#include <iostream>

#include <OgreWindowEventUtilities.h>

#include "MenuInicio.h"
#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"



class Ventana :  public Ogre::WindowEventListener
{
public:
    Ventana(ModeloVista* modeloVista);

     ~Ventana(void);

    void loadResources(void);

    //Iniciación

    bool start(void);

    bool destruyeVista(void);
    bool iniciaListeners(void);

    //Pantallas
    bool muestraVentana();



  //  int mPantalla;

   // BaseApplication* Create(Ogre::String type);

    void creaVista();

    BaseVistas* vista;

private:

    ModeloVista* modeloVista;


  //  Ogre::SceneManager* mSceneMgr;
  //  Ogre::Root* mRoot;
   // Ogre::Timer* mTimer;                  // Root::getSingleton().getTimer()



   // MenuInicio* menu;

};

#endif
