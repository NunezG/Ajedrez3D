#ifndef __ControlJuego_
#define __ControlJuego_

#include <CEGUI/CEGUISystem.h>
#include "BaseJuego.h"
#include "../Modelo/Modelo.h"
#include "../ModuloIA.h"



class  ControlJuego : public BaseJuego
{
public:
    //Destructor
    ~ControlJuego(void);

    //Singleton
    static ControlJuego& getControlSingleton();


    void inicio(void);
    bool iniciaModeloAjedrez();
    bool iniciaModelo();
private:
    //Singleton
    void operator=(const ControlJuego& controlJuego ) ;
    ControlJuego(const ControlJuego& control);
    ControlJuego(void);



     EscenaAjedrez* escenaAjedrez;

    Ogre::SceneManager* mSceneMgr;

    void calculaMovimiento();

    bool esperaCalculo;

    void createScene(void);

    //BUCLE PRINCIPAL
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

#endif
