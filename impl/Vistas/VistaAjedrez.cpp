
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(ModeloVista* modeloV) :
    BaseVistas(modeloV, "Root Ajedrez")
{
    std::cout   << "   ESCNA EN VISTAAJEDREZ" << std::endl;
    
    //  modelo =Modelo::getSingletonPtr();
    
    //  mWindow = mRoot->initialise(true, "Root Ajedrez");
    
    // escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    //  BaseVistas::iniciaOIS();
    
    
    escenaAjedrez = new EscenaAjedrez();
    
    std::cout   << "   fin escena" << std::endl;
    
    //modeloVista = modeloV;
    
    modeloVista->escena = escenaAjedrez;
    
    //escenaAjedrez= modelov
    
    //modeloVista->escena = escenaAjedrez;
    //escena
    std::cout   << "   creaTablero" << std::endl;
    
}

VistaAjedrez::~VistaAjedrez(void)
{    
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{    
    
    BaseVistas::keyPressed(arg);
    
    if (arg.key == OIS::KC_A || arg.key == OIS::KC_LEFT)
    {
        escenaAjedrez->setCamaraIzquierda();
        //  escenaAjedrez->mueveCamaraIzquierda();
        //   mCamera->moveRelative(Ogre::Vector3(-1,0,0));//yaw(Ogre::Degree(-1.25f));
    }else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
    {
        escenaAjedrez->setCamaraDerecha();

        //  escenaAjedrez->mueveCamaraDerecha();
        
        // mCamera->moveRelative(Ogre::Vector3(1,0,0));
        // mCamera->pitch(Ogre::Degree(1.025f));
    }else if (arg.key == OIS::KC_C)
    {
        if (escenaAjedrez->getModoCamara())
            escenaAjedrez->setModoCamara(false);
        else
            escenaAjedrez->setModoCamara(true);
        
    }else if (arg.key == OIS::KC_P)
    {
        // IMPLEMENTAR PAUSA
    }
    return true;
}

//void VistaAjedrez::rotar


bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 
    BaseVistas::keyReleased(arg);
    escenaAjedrez->noMueveCamara();
    return true;
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{  
    BaseVistas::mouseMoved(arg);
    
    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();



    if (escenaAjedrez->getModoCamara())   // yaw around the target, and pitch locally
    {
        //      std::cout << "camara" << std::endl;
        escenaAjedrez->rotacionCamara(Ogre::Degree(mCursorPosition.d_x));
    }
    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        escenaAjedrez->DistanciaCamara(arg.state.Z.rel);
    }
    else{

        const std::string casilla = escenaAjedrez->encuentraCasillaSobrevolada(mCursorPosition);

        if (casilla != "")
        modeloVista->JugadorActivo->casillaSobrevolada(casilla);


    }

    return true;
}

bool VistaAjedrez::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if (!BaseVistas::frameRenderingQueued(evt)) return false;
    else
    {
        Tablero* tablero = escenaAjedrez->getTablero();

        if(escenaAjedrez->getCamaraIzquierda())
            tablero->rotacionCamara = Ogre::Degree(18 * evt.timeSinceLastFrame);

        else if (escenaAjedrez->getCamaraDerecha())
            tablero->rotacionCamara = Ogre::Degree(18 * -evt.timeSinceLastFrame);

        if(tablero->rotacionCamara != Ogre::Degree(0))
        {
            Ogre::Degree rot = Ogre::Degree(Ogre::Real(80.0f) * evt.timeSinceLastFrame);

            //Rota la camara
            if (rot > tablero->rotacionCamara)
            {
                escenaAjedrez->rotacionCamara(tablero->rotacionCamara);
                tablero->rotacionCamara = Ogre::Real(0.0f);
            }
            else
            {
                escenaAjedrez->rotacionCamara(rot);
                tablero->rotacionCamara = tablero->rotacionCamara - rot;
            }
        }
    }
    return true;
}

bool VistaAjedrez::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  
    BaseVistas::mousePressed(arg, id);
    
    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();
    
    //int posx = arg.state.X.abs;   // Posicion del puntero
    //int posy = arg.state.Y.abs;   //  en pixeles.
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho -------------
        // HAY QUE CAMBIAR ESTO PARA QUE SE HAGA CASI TODO EN ESCENAAJEDREZ
        modeloVista->JugadorActivo->botonIzquierdo(mCursorPosition);

        // std::cout  << "FILA CASILLA SOBRE LA QUE SE HACE CLICK: "<< tablero->getNodoCasillaSeleccionada()->getPosicion().Fila <<std::endl;
        //  std::cout  << "COLUMNA CASILLA SOBRE LA QUE SE HACE CLICK: "<< tablero->getNodoCasillaSeleccionada()->getPosicion().Columna <<std::endl;
    }
    else if (id == OIS::MB_Right)
    {
        std::cout << "BOTON DERECHO"<< std::endl;
        
        if (modeloVista->JugadorActivo->botonDerecho())
        {
            std::cout << "APLICA CAMBIO"<< std::endl;

            modeloVista->aplicaCambio();
        }
        // escenaAjedrez->tableroModelo->jugada[0] = 24+(escenaAjedrez->tablero->getNodoCasillaSeleccionada()->getPosicion().Fila*12)+escenaAjedrez->tablero->getNodoCasillaSeleccionada()->getPosicion().Columna + 2;
        // escenaAjedrez->tableroModelo->jugada[1] = 24+(escenaAjedrez->tablero->getNodoCasillaSobrevolada()->getPosicion().Fila*12)+escenaAjedrez->tablero->getNodoCasillaSobrevolada()->getPosicion().Columna + 2;
        
    }else if (id == OIS::MB_Middle)
    {
        escenaAjedrez->setModoCamara(true);
    }
    //  mInputMan->injectMouseDown(arg, id);
    
    return true;
}

bool VistaAjedrez::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{   
    BaseVistas::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);
    
    if(mbMiddle) escenaAjedrez->setModoCamara(false);

    //  mInputMan->injectMouseUp(arg, id);
    
    return true;
}
