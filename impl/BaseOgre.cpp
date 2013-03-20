/*
-----------------------------------------------------------------------------
Filename:    BaseOgre.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "../headers/BaseOgre.h"

//-------------------------------------------------------------------------------------
BaseOgre::BaseOgre(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : //CreacionJuego(),

      mSceneMgr(mSceneMgr),
      mWindow(mWindow),
      _nodoNuevo(0)

{
}

BaseOgre::~BaseOgre(void)
{
}

//-------------------------------------------------------------------------------------
bool BaseOgre::iniciaVista(void)
{
   // mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    std::cout << "INICIA VISTA 1 " << std::endl;

    escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    std::cout << "INICIA VISTA 2 " << std::endl;

    escenaAjedrez->setSceneManager(mSceneMgr);

    escenaAjedrez->createRayQuery();
    std::cout << "INICIA VISTA 3 " << std::endl;

    escenaAjedrez->createCamera();
   // mInputMan = new InputMan::SdkCameraMan(escenaAjedrez->createCamera());   // create a default camera controller
    //mInputMan->setTopSpeed(100);

    std::cout << "INICIA VISTA 4 " << std::endl;

    escenaAjedrez->createViewports(mWindow);
    std::cout << "INICIA VISTA 5 " << std::endl;

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::cout << "INICIA VISTA 6 " << std::endl;

    createScene();

    return true;
}

//-------------------------------------------------------------------------------------
void BaseOgre::FichaComestible()
{

   Ogre::SceneNode* child = escenaAjedrez->casillaOcupada(_nodoNuevo);

    //Mira si la casilla está ocupada y por quién
   // Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
    Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

    if((!turnoNegras && ent->getName()[1] == 'N')
            || (turnoNegras && ent->getName()[1] == 'B'))
    {
        escenaAjedrez->iluminaCasilla(_nodoNuevo);
    }
}

void BaseOgre::createScene(void)
{
    escenaAjedrez->createScene(mSceneMgr);
}
