
#include "../../headers/Vistas/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio(ModeloVista* modeloV) :
    BaseVistas(modeloV,  "Root Menu")
,    ventanaConfig(NULL),
    listaResoluciones(NULL)

{

}

MenuInicio::~MenuInicio(void)
{
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.getWindow("MenuInicio/VentanaMenu")->setVisible(false);
    wmgr.getWindow("MenuInicio")->setVisible(false);
    wmgr.destroyWindow("MenuInicio/VentanaMenu");
    wmgr.destroyWindow("MenuInicio");
}

bool MenuInicio::pantallaInicio()
{
    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("MenuInicioAjedrezCEED.layout");

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
        ventanaConfig->show();
        ventanaConfig->activate();
    }
    else
    {
        ventanaConfig = CEGUI::WindowManager::getSingleton().loadWindowLayout("ConfiguraAjedrezCEED.layout");

        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaConfig);

        listaResoluciones = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/ListaResol"));
        listaDificultades = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/ListaDific"));
        Ogre::LogManager::getSingletonPtr()->logMessage("*** BLANCAS11111**");

        listaBlancas = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/Jugadores")->getChild("Configuracion/VentanaConf/Jugadores/ListaJugadorBlancas"));
        Ogre::LogManager::getSingletonPtr()->logMessage("*** BLANCAS12222*");

        listaNegras = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/Jugadores")->getChild("Configuracion/VentanaConf/Jugadores/ListaJugadorNegras"));

        ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/BotonAceptar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonAplicarCambios, this));
        ventanaConfig->getChild("Configuracion/VentanaConf")->getChild("Configuracion/VentanaConf/BotonCancelar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonVolver, this));
    }
    std::vector<std::string*>  listaElementos;

    listaElementos.push_back(new std::string("240 x 480"));
    listaElementos.push_back(new std::string("800 x 600"));
    listaElementos.push_back(new std::string("1024 x 768"));
    listaElementos.push_back(new std::string("1200 x 1024"));
    listaElementos.push_back(new std::string("1600 x 1024"));
    listaElementos.push_back(new std::string("1920 x 1080"));

    listaResoluciones =   creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaResoluciones, this), "Lista_Resoluciones", listaElementos ,listaResoluciones);
    listaResoluciones->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaResolucion, this));
    listaResoluciones->handleUpdatedItemData();

    listaElementos.clear();
    listaElementos.push_back(new std::string("Facil"));
    listaElementos.push_back(new std::string("Media"));
    listaElementos.push_back(new std::string("Dificil"));

    listaDificultades =   creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaDificultad, this), "Lista_Dificultad", listaElementos ,listaDificultades);
    listaDificultades->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaDificultad, this));
    listaDificultades->handleUpdatedItemData();
    Ogre::LogManager::getSingletonPtr()->logMessage("*** BLANCAS**");

    listaElementos.clear();
    listaElementos.push_back(new std::string("Humano"));
    listaElementos.push_back(new std::string("Maquina"));

    listaBlancas =   creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaBlancas, this), "Lista_Blancas", listaElementos ,listaBlancas);
    listaBlancas->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaBlancas, this));
    listaBlancas->handleUpdatedItemData();

    listaNegras =   creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaNegras, this), "Lista_Negras", listaElementos ,listaNegras);
    listaNegras->subscribeEvent(CEGUI::Listbox::EventMouseClick, CEGUI::Event::Subscriber(&MenuInicio::seleccionaNegras, this));
    listaNegras->handleUpdatedItemData();

    return true;
}

bool MenuInicio::botonSalir(const CEGUI::EventArgs &e)
{
    modeloVista->setApagar(true);
    mWindow->setVisible(false);
    return true;
}

bool MenuInicio::botonJuegoTurnos(const CEGUI::EventArgs &e)
{
    modeloVista->setNumPantalla(1);
    mWindow->setVisible(false);

    //modoJuego = 1;
    return true;
}

bool MenuInicio::botonJuegoSolo(const CEGUI::EventArgs &e)
{
   modeloVista->setNumPantalla(2);
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
  //  modeloVista->setSalir(true);

    return true;
}



bool MenuInicio::sobrevuelaLista(CEGUI::Listbox *lista)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sobrevuelaLista**");

    // Reset all list items to undetected colour
    for(int i=0; i<lista->getItemCount(); i++)
    {
        CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(lista->getListboxItemFromIndex(i));

        // If the item is selected then it maintains its selected colour
        if(!item->isSelected())
        {
            item->setTextColours(CEGUI::colour(1.0, 1.0, 1.0, 1.0));
        }
    }
  //  listaResoluciones->handleUpdatedItemData();

    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));

    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(lista->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem )
    {
        detectedItem->setTextColours(CEGUI::colour(0.0, 1.0, 0.0, 1.0));
    }

    lista->handleUpdatedItemData();

    return true;
}

bool MenuInicio::sobrevuelaListaResoluciones(const CEGUI::EventArgs &e)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sobrevuelaLista**");

    return sobrevuelaLista(listaResoluciones);
}

bool MenuInicio::sobrevuelaListaBlancas(const CEGUI::EventArgs &e)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sobrevuelaLista**");

    return sobrevuelaLista(listaBlancas);

}


bool MenuInicio::sobrevuelaListaNegras(const CEGUI::EventArgs &e)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** sobrevuelaLista**");

    return sobrevuelaLista(listaNegras);

}

bool MenuInicio::sobrevuelaListaDificultad(const CEGUI::EventArgs &e)
{
    return sobrevuelaLista(listaDificultades);

}

bool MenuInicio::seleccionaResolucion(const CEGUI::EventArgs &e)
{
    return seleccionaElementoLista(listaResoluciones);
    return true;
}

bool MenuInicio::seleccionaDificultad(const CEGUI::EventArgs &e)
{
    return seleccionaElementoLista(listaDificultades);
}


bool MenuInicio::seleccionaBlancas(const CEGUI::EventArgs &e)
{
    return seleccionaElementoLista(listaBlancas);
}


bool MenuInicio::seleccionaNegras(const CEGUI::EventArgs &e)
{
    return seleccionaElementoLista(listaNegras);
}

bool MenuInicio::seleccionaElementoLista(CEGUI::Listbox *lista)
{
    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Point   mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
    CEGUI::Vector2 mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                 CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));
    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(lista->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem )
    {
        detectedItem->setSelected(true);
    }

    lista->handleUpdatedItemData();
    return true;
}


CEGUI::Listbox* MenuInicio::creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre, std::vector<std::string*> listaElementos, CEGUI::Listbox* listaReal)
{
    CEGUI::colour col;

    col.setBlue(100.0f);
    col.setGreen(50.0f);
    col.setRed(50.0f);
    col.setAlpha(50.0f);

    CEGUI::ListboxTextItem* elementoLista;

    for (int i = 0; i < listaElementos.size(); i++)
    {
        std::string texto = *listaElementos.at(i);
        elementoLista= new CEGUI::ListboxTextItem(texto);

        //elementoLista->setSelectionColours(col );

        if (texto == modeloVista->resolucion)
        {
            elementoLista->setTextColours(CEGUI::colour(0.0, 1.0, 0.0, 1.0));
            elementoLista->setSelected(true);
        }

        listaReal->addItem(elementoLista);
        listaReal->handleUpdatedItemData();
    }

    listaReal->subscribeEvent(CEGUI::Listbox::EventMouseMove, evento);

    return listaReal;
}
