﻿#include "../../headers/Vistas/MenuInicio.h"

//-------------------------------------------------------------------------------------
MenuInicio::MenuInicio(ModeloVista* modeloV) :
    BaseVistas(modeloV,  "Root Menu")
  ,    ventanaConfig(NULL),
    listaResoluciones(NULL)
{
}

MenuInicio::~MenuInicio(void)
{
    //¿¿¿BORRA MEJOR CON EL PUNTERO ventanaEmergente???

          //CEGUI::Window*CEGUI = CEGUI::WindowManager::getSingleton();
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuInicio")->getChild("VentanaMenu")->setVisible(false);
      CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuInicio")->setVisible(false);
      CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuInicio")->destroyChild("VentanaMenu");
      CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->destroyChild("MenuInicio");
}

bool MenuInicio::pantallaInicio()
{
    //CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->layou

    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicioAjedrezCEED.layout");
    //ENLAZA LOS BOTONES
    newWindow->getChild("VentanaMenu")->getChild("Salir")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this));
    newWindow->getChild("VentanaMenu")->getChild("UnJugador")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonJuegoSolo, this));
    newWindow->getChild("VentanaMenu")->getChild("DosJugadores")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonJuegoTurnos, this));
    newWindow->getChild("VentanaMenu")->getChild("Configura")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonConfig, this));


    newWindow->getChild("VentanaMenu")->setMouseCursor("Vanilla-Images/MouseArrow");
     newWindow->setMouseCursor("Vanilla-Images/MouseArrow");

    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(newWindow);
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
        ventanaConfig = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ConfiguraAjedrezCEED.layout");

        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(ventanaConfig);
        listaResoluciones = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("ListaResol"));
        listaDificultades = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("ListaDific"));
        listaBlancas = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("ListaJugadorBlancas"));
        listaNegras = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("ListaJugadorNegras"));
        ventanaConfig->getChild("VentanaConf")->getChild("BotonAceptar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonAplicarCambios, this));
        ventanaConfig->getChild("VentanaConf")->getChild("BotonCancelar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuInicio::botonVolver, this));
     }
    std::vector<std::string>  listaElementos;

    listaElementos.push_back(std::string("240 x 480"));
    listaElementos.push_back(std::string("800 x 600"));
    listaElementos.push_back(std::string("1024 x 768"));
    listaElementos.push_back(std::string("1200 x 1024"));
    listaElementos.push_back(std::string("1600 x 1024"));
    listaElementos.push_back(std::string("1920 x 1080"));
    creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaResoluciones, this), CEGUI::Event::Subscriber(&MenuInicio::seleccionaResolucion, this), listaElementos ,listaResoluciones, modeloVista->resolucion);

    listaElementos.clear();
    listaElementos.push_back(std::string("Facil"));
    listaElementos.push_back(std::string("Media"));
    listaElementos.push_back(std::string("Dificil"));
    creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaDificultad, this), CEGUI::Event::Subscriber(&MenuInicio::seleccionaDificultad, this), listaElementos ,listaDificultades, listaElementos.at(modeloVista->dificultad) );

    listaElementos.clear();
    listaElementos.push_back(std::string("Humano"));
    listaElementos.push_back(std::string("Maquina"));
    creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaBlancas, this),CEGUI::Event::Subscriber(&MenuInicio::seleccionaBlancas, this), listaElementos ,listaBlancas, listaElementos.at(0));
    creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuInicio::sobrevuelaListaNegras, this), CEGUI::Event::Subscriber(&MenuInicio::seleccionaNegras, this), listaElementos ,listaNegras, listaElementos.at(0));

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
    //for(int i=0; i<listaResoluciones->getItemCount(); i++)
  //  {
        //CEGUI::ListboxItem* item = static_cast<CEGUI::ListboxItem*>(listaResoluciones->getListboxItemFromIndex(i));

        //  std::cout  << "item: " <<item->getText() <<std::endl;

        // If the item is selected then it maintains its selected colour
      //  if(item->isSelected())

    //    {
            // std::cout  << "SE HA APLICADO Y SELECCIONADO LA RESOLUCION ("<< item->getText() <<  ")" << std::endl;

   CEGUI::ListboxItem* item =  listaResoluciones->getFirstSelectedItem();

    if(item!= NULL)
    {
            modeloVista->resolucion = item->getText().c_str();
    }
            //  renderSystem->setConfigOption("Video Mode", modelo->resolucion);
        //}
    //}

    item =  listaDificultades->getFirstSelectedItem();

     if(item!= NULL)
     {

             modeloVista->dificultad = item->getID();
     }

    // modeloVista->jugadores[0]

     item =  listaBlancas->getFirstSelectedItem();
     int modoJuego = 0;

      if(item!= NULL)
      {
             modoJuego = item->getID();
      }

      item =  listaNegras->getFirstSelectedItem();

       if(item!= NULL)
       {
           if (item->getID() == 1)
               modeloVista->modoJuego = 2 + item->getID();
           else modeloVista->modoJuego = modoJuego;
       }


    ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("EditNegras")->getText().c_str();

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
            item->setTextColours(CEGUI::Colour(1.0, 1.0, 1.0, 1.0));
        }
    }
    //  listaResoluciones->handleUpdatedItemData();

    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Vector2<float> mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
    CEGUI::Vector2<float> mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                    CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));

    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(lista->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem )
    {
        detectedItem->setTextColours(CEGUI::Colour(0.0, 1.0, 0.0, 1.0));
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

    CEGUI::Vector2<float>   mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
       CEGUI::Vector2<float> mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
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

void MenuInicio::creaMenuDesplegable(CEGUI::Event::Subscriber eventoAlSobrevolar,CEGUI::Event::Subscriber eventoAlPulsar, std::vector<std::string> listaElementos, CEGUI::Listbox* lista, std::string preSeleccionado)
{
    CEGUI::Colour col;

    col.setBlue(100.0f);
    col.setGreen(50.0f);
    col.setRed(50.0f);
    col.setAlpha(50.0f);

    CEGUI::ListboxTextItem* elementoLista;

    for (int i = 0; i < listaElementos.size(); i++)
    {
        std::string texto = listaElementos.at(i);
        elementoLista= new CEGUI::ListboxTextItem(texto);

        //elementoLista->setSelectionColours(col );

        if (texto == preSeleccionado)
        {
            elementoLista->setTextColours(CEGUI::Colour(0.0, 1.0, 0.0, 1.0));
            elementoLista->setSelected(true);
        }

        elementoLista->setID(i);
        lista->addItem(elementoLista);
        lista->handleUpdatedItemData();
    }


    lista->subscribeEvent(CEGUI::Listbox::EventMouseMove, eventoAlSobrevolar);
    lista->subscribeEvent(CEGUI::Listbox::EventMouseClick, eventoAlPulsar);

    lista->handleUpdatedItemData();

    //return listaReal;
}
