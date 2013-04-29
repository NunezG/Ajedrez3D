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

    bool iniciaModeloAjedrez();
private:
    //Singleton
    void operator=(const ControlJuego& controlJuego ) ;
    ControlJuego(const ControlJuego& control);
    ControlJuego(void);

    void calculaMovimiento();


    //BUCLE PRINCIPAL
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);


     EscenaAjedrez* escenaAjedrez;



    bool esperaCalculo;

};

#endif
