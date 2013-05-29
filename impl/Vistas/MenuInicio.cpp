
#include "../../headers/Vistas/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio(ModeloVista* modeloV, Ogre::Root* mRoot) :
    BaseVistas(modeloV, mRoot,  "Root Menu")
,    ventanaConfig(NULL),
    listaResoluciones(NULL)

{
   // modeloV
  //  iniciaVista();
    // BaseVistas::iniciaOIS();

}
//-------------------------------------------------------------------------------------
MenuInicio::~MenuInicio(void)
{


}

bool MenuInicio::iniciaVentana()
{


    Ogre::LogManager::getSingletonPtr()->logMessage("***INICIAVENTAAN EN MENU INICIO**");


    //BaseVistas::iniciaVentana();

    return true;
}

bool MenuInicio::pantallaInicio()
{
    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("MenuInicioAjedrezCEED.layout");
    //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );



    // CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    /*
    CEGUI::FrameWindow* ventana;

    ventana = modelo->menu->creaVentana("Inicio");

    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this), "Salir", ventana);

    Ogre::LogManager::getSingletonPtr()->logMessage("***sigue**");
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this),"Jugar por turnos", ventana);
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoSolo, this), "contra la IA", ventana);

    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonConfig, this), "Configuracion", ventana);

    */

    //ENLAZA LOS BOTONES
    newWindow->getChild("MenuInicio/VentanaMenu")->getChild("MenuInicio/VentanaMenu/Salir")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this));
    newWindow->getChild("MenuInicio/VentanaMenu")->getChild("MenuInicio/VentanaMenu/UnJugador")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonJuegoSolo, this));
    newWindow->getChild("MenuInicio/VentanaMenu")->getChild("MenuInicio/VentanaMenu/DosJugadores")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this));
    newWindow->getChild("MenuInicio/VentanaMenu")->getChild("MenuInicio/VentanaMenu/Configura")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonConfig, this));

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);

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

        ventanaConfig = CEGUI::WindowManager::getSingleton().loadWindowLayout("ConfiguraAjedrezCEED.layout");
        // newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaConfig);

        // newWindow->getChild("MenuInicio/VentanaMenu")->getChild("MenuInicio/VentanaMenu/Cancel")


        listaResoluciones = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/ListaResol"));
        listaDificultades = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/ListaDific"));
      // std::string nombre1 = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Demo8")->getChild("Demo8/Window1")->getChild("Demo8/Window1/Listbox1"));
    //   std::string nombre2 = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Demo8")->getChild("Demo8/Window1")->getChild("Demo8/Window1/Listbox1"));


        //  listaDificultades->setMultiselectEnabled(false);
        //  listaResoluciones->setMultiselectEnabled(false);


        //istaResoluciones->addItem(new CEGUI::ListboxTextItem(std::string("240 x 480")));
        // listaResoluciones->addItem(new CEGUI::ListboxTextItem(std::string("800 x 600")));
        // listaResoluciones->addItem(new CEGUI::ListboxTextItem(std::string("1024 x 768")));



        // for (int i = 0; i< listaResoluciones->getChildCount(); i++){

        //     std::cout  << "una resolucion mas "<< std::endl;

        //     listaResoluciones->addItem(listaResoluciones->getChild(i));

        //  }

        //  newWindow->getChild("Demo8")->getChild("Demo8/Window1")->getChild("Demo8/Window1/Listbox")->subscribeEvent(CEGUI::Listbox::EventMouseMove,CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaLista, this));
        //   newWindow->getChild("Demo8")->getChild("Demo8/Window1")->getChild("Demo8/Window1/Listbox")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::seleccionaResolucion, this));

        //   newWindow->getChild("Demo8")->getChild("Demo8/Window1")->getChild("Demo8/Window1/Listbox1")->subscribeEvent(CEGUI::Listbox::EventMouseMove,CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaDificultad, this));
        //  newWindow->getChild("Demo8")->getChild("Demo8/Window1")->getChild("Demo8/Window1/Listbox1")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::seleccionaDificultad, this));


        ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/BotonAceptar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonAplicarCambios, this));
        ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/BotonCancelar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonVolver, this));

    }

    //  std::string string1 = "240 x 480";

    listaElementos.push_back(new std::string("240 x 480"));
    listaElementos.push_back(new std::string("800 x 600"));
    listaElementos.push_back(new std::string("1024 x 768"));
    listaElementos.push_back(new std::string("1200 x 1024"));
    listaElementos.push_back(new std::string("1600 x 1024"));
    listaElementos.push_back(new std::string("1920 x 1080"));

    // ventanaConfig = modelo->menu->creaVentana("VentanaConfig");


    std::cout  << "listares1 "<< std::endl;
    posBoton =1;



    // modelo->menu->creaTexto("Prueba de texto",ventanaConfig);

    listaResoluciones =   creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaLista, this), "Lista_Resoluciones", listaElementos ,listaResoluciones);

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


    listaDificultades =   creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaDificultad, this), "Lista_Dificultad", listaElementos ,listaDificultades);
    std::cout  << "listaredddss "<< std::endl;

    listaDificultades->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaDificultad, this));


    std::cout  << "listares aaa"<< std::endl;

    listaDificultades->handleUpdatedItemData();

    /*



        modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonVolver, this), "Cancelar",  ventanaConfig);

        modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonAplicarCambios, this), "Aplicar cambios", ventanaConfig);


     */
    return true;

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

bool MenuInicio::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

}

bool MenuInicio::botonSalir(const CEGUI::EventArgs &e)
{
    modeloVista->setApagar(true);
    mWindow->setVisible(false);
    return true;
}

bool MenuInicio::botonJuegoTurnos(const CEGUI::EventArgs &e)
{

    modeloVista->cambiaPantalla(1);
    mWindow->setVisible(false);


    //modoJuego = 1;
    return true;
}

bool MenuInicio::botonJuegoSolo(const CEGUI::EventArgs &e)
{

   modeloVista->cambiaPantalla(2);
   mWindow->setVisible(false);

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
    for(int i=0; i<listaResoluciones->getItemCount(); i++)
    {

        CEGUI::ListboxItem* item = static_cast<CEGUI::ListboxItem*>(listaResoluciones->getListboxItemFromIndex(i));

      //  std::cout  << "item: " <<item->getText() <<std::endl;

        // If the item is selected then it maintains its selected colour
        if(item->isSelected()){
           // std::cout  << "SE HA APLICADO Y SELECCIONADO LA RESOLUCION ("<< item->getText() <<  ")" << std::endl;

            modeloVista->resolucion = item->getText().c_str();
            //  renderSystem->setConfigOption("Video Mode", modelo->resolucion);

        }
    }

    ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/Jugadores")->getChild("Configuracion/VentanaConf/Jugadores/EditNegras")->getText().c_str();




    ventanaConfig->hide();
    mWindow->setVisible(false);
    modeloVista->setSalir(true);

    return true;
}


bool MenuInicio::sobrevuelaLista(const CEGUI::EventArgs &e)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sobrevuelaLista**");

    // Reset all list items to undetected colour
    for(int i=0; i<listaResoluciones->getItemCount(); i++)
    {

        CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(listaResoluciones->getListboxItemFromIndex(i));

        // If the item is selected then it maintains its selected colour
        if(!item->isSelected()){


            item->setTextColours(CEGUI::colour(1.0, 1.0, 1.0, 1.0));
        }
    }
    listaResoluciones->handleUpdatedItemData();


    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));


    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(listaResoluciones->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem ){

        detectedItem->setTextColours(CEGUI::colour(0.0, 1.0, 0.0, 1.0));
    }

    listaResoluciones->handleUpdatedItemData();

    return true;




}


bool MenuInicio::sobrevuelaListaDificultad(const CEGUI::EventArgs &e)
{

    // Reset all list items to undetected colour
    for(int i=0; i<listaDificultades->getItemCount(); i++)
    {

        CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(listaDificultades->getListboxItemFromIndex(i));

        // If the item is selected then it maintains its selected colour
        if(!item->isSelected())
        {
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
    if(detectedItem )
    {
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
    if(detectedItem )
    {
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
    if(detectedItem )
    {
        detectedItem->setSelected(true);
    }

    listaDificultades->handleUpdatedItemData();

    return true;


}


CEGUI::Listbox* MenuInicio::creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre, std::vector<std::string*> listaElementos, CEGUI::Listbox* listaReal)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** MENU DESPLEGABLE***");

    CEGUI::colour col;

    col.setBlue(100.0f);
    col.setGreen(50.0f);
    col.setRed(50.0f);
    col.setAlpha(50.0f);

    Ogre::LogManager::getSingletonPtr()->logMessage("*** for***");

    CEGUI::ListboxTextItem* elementoLista;

    for (int i = 0; i < listaElementos.size(); i++)
    {
        elementoLista= new CEGUI::ListboxTextItem(std::string(*listaElementos.at(i)));

        //elementoLista->setSelectionColours(col );

        if (i== 1)elementoLista->setSelected(true);

        listaReal->addItem(elementoLista);
        listaReal->handleUpdatedItemData();
    }

    listaReal->subscribeEvent(CEGUI::Listbox::EventMouseMove, evento);

        posBoton = posBoton+1;

    return listaReal;
}


//-------------------------------------------------------------------------------------
bool MenuInicio::mueveCamara(float frecuencia)
{

}
