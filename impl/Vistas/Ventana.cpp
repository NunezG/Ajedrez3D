#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana() :
    modeloVista(modeloVista),
    vista(NULL)

{
    this->modeloVista = new ModeloVista();
}


Ventana::~Ventana()
{
    destruyeVista();
}

void Ventana::go(void)
{
    //ModeloVista* modeloVista = new ModeloVista();

    while(!modeloVista->getApagar())
    {
        creaVista();
        destruyeVista();
    }

    delete modeloVista;
}

void Ventana::creaVista()
{  
    if (modeloVista->getNumPantalla() == 0)
        vista = new MenuInicio(modeloVista);
    else
    {
        if (modeloVista->getNumPantalla() == 1)
        {
            std::cout << "pantalla 1" << std::endl;
            vista= new VistaAjedrez(modeloVista);
        }

        else if (modeloVista->getNumPantalla() == 2)
        {
            std::cout << "pantalla 2" << std::endl;
            //EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
            vista= new VistaAjedrezSolo(modeloVista);
        }

        modeloVista->escena->createCamera();
        std::cout << "p331" << std::endl;

        modeloVista->escena->createViewports(vista->mWindow);

        modeloVista->modelo = Modelo::getSingletonPtr();

        modeloVista->generaJugadores();
    }

    muestraVentana();
    vista->empieza();
}

bool Ventana::muestraVentana()
{
    iniciaListeners();
    vista->iniciaCEGUI();

    if (modeloVista->getNumPantalla() == 0)
        static_cast<MenuInicio*>(vista)->pantallaInicio();
    else
    {
        modeloVista->escena->createScene();
        modeloVista->creaModeloTablero();
    }
    return true;
}

bool Ventana::iniciaListeners()
{
    vista->mRoot->addFrameListener(vista);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    vista->mMouse->setEventCallback(vista);
    vista->mKeyboard->setEventCallback(vista);
}

bool Ventana::destruyeVista(void)
{
    if (vista)
    {
        Ogre::WindowEventUtilities::removeWindowEventListener(vista->mWindow, this);
        delete vista;
        vista = NULL;
    }
}
