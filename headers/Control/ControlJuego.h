#ifndef __ControlJuego_
#define __ControlJuego_

#include "BaseJuego.h"
#include "../ModeloVista/EscenaAjedrez.h"

class  ControlJuego : public BaseJuego
{
public:
    //Destructor
    ~ControlJuego(void);
    //Singleton
    static ControlJuego& getControlSingleton();

private:

    //Singleton
    void operator=(const ControlJuego& controlJuego ) ;
    ControlJuego(const ControlJuego& control);
    ControlJuego(void);

};

#endif
