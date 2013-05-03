
#include "../../headers/Vistas/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio() :
    BaseVistas(),
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

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


    CEGUI::FrameWindow* ventana;

    ventana = modelo->menu->creaVentana("Inicio");

    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this), "Salir", ventana);

    Ogre::LogManager::getSingletonPtr()->logMessage("***sigue**");
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this),"Jugar por turnos", ventana);
    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonJuegoSolo, this), "contra la IA", ventana);

    modelo->menu->creaBoton(CEGUI::Event::Subscriber(&MenuInicio::botonConfig, this), "Configuracion", ventana);

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



        modelo->menu->creaTexto("Prueba de texto",ventanaConfig);

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
    modelo->setSalir(true);
    return true;
}

bool MenuInicio::botonJuegoTurnos(const CEGUI::EventArgs &e)
{
    //modelo->modoJuego = 1;
    modelo->setNumPantalla(1);
    //modoJuego = 1;
    return true;
}

bool MenuInicio::botonJuegoSolo(const CEGUI::EventArgs &e)
{
    modelo->setNumPantalla(2);
  //  modoJuego = 2;
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

        CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(listaResoluciones->getListboxItemFromIndex(i));

        // If the item is selected then it maintains its selected colour
        if(item->isSelected()){
            std::cout  << "SE HA APLICADO Y SELECCIONADO LA RESOLUCION ("<< item->getText() <<  ")" << std::endl;

            modelo->resolucion = item->getText().c_str();
          //  renderSystem->setConfigOption("Video Mode", modelo->resolucion);


        }
    }


    return true;
}


bool MenuInicio::sobrevuelaLista(const CEGUI::EventArgs &e)
{
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

    std::cout  << "mouse: "<< mousePosLocal.d_x  << std::endl;
    std::cout  << "mouse: "<< mousePosLocal.d_y  << std::endl;

    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(listaResoluciones->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem ){

        std::cout  << "ITEM DETECTADO: "<< mousePosLocal.d_x  << std::endl;

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



//-------------------------------------------------------------------------------------
bool MenuInicio::mueveCamara(float frecuencia)
{

}
