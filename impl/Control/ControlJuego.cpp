
#include "../../headers/Control/ControlJuego.h"

//-------------------------------------------------------------------------------------
ControlJuego::ControlJuego(void) :
    BaseJuego()


{
}
//-------------------------------------------------------------------------------------
ControlJuego::~ControlJuego(void)
{




}

ControlJuego& ControlJuego::getControlSingleton()
{
    static ControlJuego miControlJuego_;
    return miControlJuego_;
}






