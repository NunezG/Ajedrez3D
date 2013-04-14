
#include "../../headers/Vistas/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio() : salirPulsado(0),
    numVentana(0),
    ventanaConfig(NULL),
    listaResoluciones(NULL)

{
    iniciaVista();
}
//-------------------------------------------------------------------------------------
MenuInicio::~MenuInicio(void)
{

}

bool MenuInicio::iniciaVista()
{
    // Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro ***");


    std::cout  << "PINICIA VISTA "<< std::endl;

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    // Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 2***");

    // fWnd = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

    // Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 3***");

    // fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );

    //fWnd->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

    Ogre::LogManager::getSingletonPtr()->logMessage( "*** CREATE GUI dentro 3***");

    CEGUI::FrameWindow* ventana;

    ventana = modelo->menu->creaVentana("Inicio");

    std::cout  << "ventana creada "<< std::endl;

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUI dentro 5***");

    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this), "Salir", ventana);

    Ogre::LogManager::getSingletonPtr()->logMessage("***sigue**");
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this),"Jugar por turnos", ventana);
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoSolo, this), "contra su puta madre", ventana);

    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonConfig, this), "Configuracion", ventana);

    /*
    //Boton Jugar por turnos
    mBotonJTurnos = wmgr.createWindow("TaharezLook/Button", "CEGUI/BotonJuegoPorTurnos");
    mBotonJTurnos->setText("Jugar por turnos");
    mBotonJTurnos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.4,0)));
    mBotonJTurnos->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    mBotonJTurnos->subscribeEvent(CEGUI::PushButton::EventClicked,
                                  );
*/

    /*
    //Boton Jugar contra la máquina
    mBotonJSolo = wmgr.createWindow("TaharezLook/Button", "CEGUI/BotonJuegoContraIA");
    mBotonJSolo->setText("Jugar solo");
    mBotonJSolo->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.5,0)));
    mBotonJSolo->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    mBotonJSolo->subscribeEvent(CEGUI::PushButton::EventClicked,
                              );

    */

    Ogre::LogManager::getSingletonPtr()->logMessage("***añade**");

    //Atsstaching buttons
    // fWnd->addChildWindow(quitButton);
    // fWnd->addChildWindow(mBotonJTurnos);
    // fWnd->addChildWindow(mBotonJSolo);

    //  CEGUI::System* sys = CEGUI::System::getSingletonPtr();

    //sys->getGUISheet()->addChildWindow( fWnd );
    Ogre::LogManager::getSingletonPtr()->logMessage("***acacacaba**");

    return true;
}


bool MenuInicio::pantallaConfig()
{

    if (ventanaConfig != NULL)
    {
        std::cout  << "ventanaconfig creado "<< std::endl;
        ventanaConfig->show();
        ventanaConfig->activate();

    }else
    {

      //  std::string string1 = "240 x 480";

        listaElementos.push_back(new std::string("240 x 480"));
        listaElementos.push_back(new std::string("800 x 600"));
        listaElementos.push_back(new std::string("1024 x 768"));
        listaElementos.push_back(new std::string("1200 x 1024"));
        listaElementos.push_back(new std::string("1600 x 1024"));
        listaElementos.push_back(new std::string("1920 x 1080"));

        ventanaConfig = modelo->menu->creaVentana("VentanaConfig");


        std::cout  << "listares1 "<< std::endl;
        modelo->menu->posBoton =1;


      listaResoluciones =   modelo->menu->creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaLista, this), "Lista_Resoluciones", listaElementos ,ventanaConfig);

      listaResoluciones->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaResolucion, this));


      std::cout  << "listares "<< std::endl;


      listaResoluciones->handleUpdatedItemData();
      std::cout  << "handle "<< std::endl;


      listaElementos.clear();
      listaElementos.push_back(new std::string("Facil"));
      listaElementos.push_back(new std::string("Media"));
      listaElementos.push_back(new std::string("Dificil"));
;


      std::cout  << "listares1 "<< std::endl;


    listaDificultades =   modelo->menu->creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaDificultad, this), "Lista_Dificultad", listaElementos ,ventanaConfig);
    std::cout  << "listaredddss "<< std::endl;

    listaDificultades->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaDificultad, this));


    std::cout  << "listares aaa"<< std::endl;

    listaDificultades->handleUpdatedItemData();





        modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonVolver, this), "Cancelar",  ventanaConfig);

        modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonAplicarCambios, this), "Aplicar cambios", ventanaConfig);

    }
    return true;
}

bool MenuInicio::salir(){
    return salirPulsado;
}

bool MenuInicio::esMenuInicio(){

    return true;
}

bool MenuInicio::keyPressed( const OIS::KeyEvent &arg ) {

}

bool MenuInicio::keyReleased( const OIS::KeyEvent &arg ){

}

bool MenuInicio::mouseMoved( const OIS::MouseEvent &arg ){

}

bool MenuInicio::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){

}

bool MenuInicio::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){

}

bool MenuInicio::frameRenderingQueued(const Ogre::FrameEvent& evt){

}

bool MenuInicio::botonSalir(const CEGUI::EventArgs &e)
{
    salirPulsado = true;
    return true;
}

bool MenuInicio::botonJuegoTurnos(const CEGUI::EventArgs &e)
{

    //modelo->modoJuego = 1;
    modoJuego = 1;
    return true;
}

bool MenuInicio::botonJuegoSolo(const CEGUI::EventArgs &e)
{
    modoJuego = 2;
    return true;
}

bool MenuInicio::botonConfig(const CEGUI::EventArgs &e)
{
    pantallaConfig();
    return true;
}

bool MenuInicio::botonVolver(const CEGUI::EventArgs &e)
{
    ventanaConfig->hide();

    return true;
}


bool MenuInicio::botonAplicarCambios(const CEGUI::EventArgs &e)
{

    return true;
}


bool MenuInicio::sobrevuelaLista(const CEGUI::EventArgs &e)
{
    return IluminaSeleccion(listaResoluciones);
}


bool MenuInicio::sobrevuelaListaDificultad(const CEGUI::EventArgs &e)
{

    // Reset all list items to undetected colour
    for(int i=0; i<listaDificultades->getItemCount(); i++)
    {

      CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(listaDificultades->getListboxItemFromIndex(i));

      // If the item is selected then it maintains its selected colour
      if(!item->isSelected()){


        item->setTextColours(CEGUI::colour(1.0, 1.0, 1.0, 1.0));
      }
    }
listaDificultades->handleUpdatedItemData();


    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));

    std::cout  << "mouse: "<< mousePosLocal.d_x  << std::endl;
    std::cout  << "mouse: "<< mousePosLocal.d_y  << std::endl;

    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(listaDificultades->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem ){

        std::cout  << "ITEM DETECTADO: "<< mousePosLocal.d_x  << std::endl;

      detectedItem->setTextColours(CEGUI::colour(0.0, 1.0, 0.0, 1.0));
    }

    listaDificultades->handleUpdatedItemData();

    return true;

}



bool MenuInicio::seleccionaResolucion(const CEGUI::EventArgs &e)
{

    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));


    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(listaResoluciones->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem ){

      detectedItem->setSelected(true);
    }

    listaResoluciones->handleUpdatedItemData();

    return true;


}


bool MenuInicio::seleccionaDificultad(const CEGUI::EventArgs &e)
{

    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));


    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(listaDificultades->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem ){

      detectedItem->setSelected(true);
    }

    listaDificultades->handleUpdatedItemData();

    return true;


}




bool MenuInicio::IluminaSeleccion(CEGUI::Listbox *list)
  {



    // Reset all list items to undetected colour
    for(int i=0; i<list->getItemCount(); i++)
    {

      CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(list->getListboxItemFromIndex(i));

      // If the item is selected then it maintains its selected colour
      if(!item->isSelected()){


        item->setTextColours(CEGUI::colour(1.0, 1.0, 1.0, 1.0));
      }
    }
list->handleUpdatedItemData();


    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));

    std::cout  << "mouse: "<< mousePosLocal.d_x  << std::endl;
    std::cout  << "mouse: "<< mousePosLocal.d_y  << std::endl;

    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(list->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem ){

        std::cout  << "ITEM DETECTADO: "<< mousePosLocal.d_x  << std::endl;

      detectedItem->setTextColours(CEGUI::colour(0.0, 1.0, 0.0, 1.0));
    }

    list->handleUpdatedItemData();

    return true;
  }
