#include "../../headers/Modelo/ModeloMenu.h"

ModeloMenu::ModeloMenu() : posBoton(0) 
  ,numVentana(0)
{
}

ModeloMenu::~ModeloMenu()
{

    std::cout  << "DESTRUYE MODELOMENU " << std::endl;

}

void ModeloMenu::creaBoton(CEGUI::Event::Subscriber evento, Ogre::String nombre, CEGUI::FrameWindow* ventana)
{
    //  Ogre::LogManager::getSingletonPtr()->logMessage("*** CRcfbhfbxbet***");

    CEGUI::ButtonBase* quitButton;

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


    //  Ogre::LogManager::getSingletonPtr()->logMessage("*** C222222***");

    quitButton = static_cast<CEGUI::ButtonBase*>(wmgr.createWindow("WindowsLook/Button", nombre));
    quitButton->setText(nombre);
    quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2*posBoton,0)));

    quitButton->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.05,0)));
    quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, evento);

    // Ogre::LogManager::getSingletonPtr()->logMessage("*** C222222***");


    // Ogre::LogManager::getSingletonPtr()->logMessage("*** casi final***");

    //  botones[posBoton] = quitButton;

    posBoton++;

    //Atsstaching buttons
    ventana->addChildWindow(quitButton);
    // Ogre::LogManager::getSingletonPtr()->logMessage("***  final***");

    // CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this)
}

void ModeloMenu::creaTexto(Ogre::String texto, CEGUI::FrameWindow* ventana){









}


CEGUI::Listbox* ModeloMenu::creaMenuDesplegable(CEGUI::Event::Subscriber evento, Ogre::String nombre, std::vector<std::string*> listaElementos, CEGUI::FrameWindow* ventana)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** MENU DESPLEGABLE***");
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

    CEGUI::Listbox* listaReal = static_cast<CEGUI::Listbox*>(wmgr.createWindow("WindowsLook/Listbox",nombre));

    // new  CEGUI::Listbox("TaharezLook/Listbox","ListaDesplegabl");
    //
    //

    listaReal->show();
    //   listaReal->setRenderingSurface();

    CEGUI::colour col;

    col.setBlue(100.0f);
    col.setGreen(50.0f);
    col.setRed(50.0f);
    col.setAlpha(50.0f);

    Ogre::LogManager::getSingletonPtr()->logMessage("*** for***");


CEGUI::ListboxTextItem* elementoLista;


    for (int i = 0; i < listaElementos.size(); i++)
    {

        Ogre::LogManager::getSingletonPtr()->logMessage("*** un for***");

         elementoLista= new CEGUI::ListboxTextItem(std::string(*listaElementos.at(i)));

        //elementoLista->setSelectionColours(col );

        if (i== 1)elementoLista->setSelected(true);

        // elementoLista->setText();

        Ogre::LogManager::getSingletonPtr()->logMessage("*** agrega a lista***");

        listaReal->addItem(elementoLista);
        listaReal->handleUpdatedItemData();

    }

    Ogre::LogManager::getSingletonPtr()->logMessage("*** MENU 2***");

    //  lista = wmgr.createWindow("TaharezLook/Listbox", nombre);
    // lista->setText(nombre);

    listaReal->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-0.15/2,0),CEGUI::UDim(0.2*posBoton,0)));

    listaReal->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0),CEGUI::UDim(0.2,0)));

    listaReal->subscribeEvent(CEGUI::Listbox::EventMouseMove, evento);

    Ogre::LogManager::getSingletonPtr()->logMessage("*** casi final***");

    //  botones[posBoton] = quitButton;

    ventana->addChildWindow(listaReal);

    posBoton = posBoton+1;

    //Atsstaching buttons
    Ogre::LogManager::getSingletonPtr()->logMessage("***  final***");



    return listaReal;
    // CEGUI::Event::Subscriber(&MenuInicio::botonSalir, this)
}

CEGUI::FrameWindow* ModeloMenu::creaVentana(std::string nombre)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREdddddddddddddddddddAftghet***");


    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREAftghet***");

    CEGUI::FrameWindow* ventana = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow( "OgreTray/FrameWindow", nombre));

    Ogre::LogManager::getSingletonPtr()->logMessage("*** CREATE GUcvcfdfI dentro 5***");


    // fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );

    ventana->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

    CEGUI::System* sys = CEGUI::System::getSingletonPtr();

    sys->getGUISheet()->addChildWindow( ventana );

    return ventana;
}

