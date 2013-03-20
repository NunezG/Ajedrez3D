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
BaseOgre::BaseOgre(Ogre::RenderWindow* mWindow)
    : //CreacionJuego(),

      mWindow(mWindow)

{
    escenaAjedrez = EscenaAjedrez::getSingletonPtr();

}

BaseOgre::~BaseOgre(void)
{
}

//-------------------------------------------------------------------------------------
bool BaseOgre::FichaComestible()
{

   Ogre::SceneNode* child = escenaAjedrez->casillaOcupada(escenaAjedrez->getNodoCasillaSobrevolada());

    //Mira si la casilla está ocupada y por quién
   // Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
    Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

    if((!escenaAjedrez->esTurnoNegras() && ent->getName()[1] == 'N')
            || (escenaAjedrez->esTurnoNegras() && ent->getName()[1] == 'B'))
    {
        return true;
    }
}
