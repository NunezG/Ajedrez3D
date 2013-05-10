#include "../../headers/Vistas/BaseVistas.h"

BaseVistas::BaseVistas()
    //modoJuego(0)


{  
    modelo = Modelo::getSingletonPtr();
}

BaseVistas::~BaseVistas()
{

}




bool BaseVistas::jaqueMate()
{
    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueMateCEED.layout");
  //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );


    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);

}
