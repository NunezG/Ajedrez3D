
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

bool VistaAjedrez::iniciaVentana()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("***SALE DE INICIA VENTANA DE LA BASE Y EMPIEZA CEGUI**");
}


//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{    

    BaseVistas::keyPressed(arg);

    if (arg.key == OIS::KC_A || arg.key == OIS::KC_LEFT)
    {
        escenaAjedrez->rotacionCamara(Ogre::Degree(1));
        //  escenaAjedrez->mueveCamaraIzquierda();
        //   mCamera->moveRelative(Ogre::Vector3(-1,0,0));//yaw(Ogre::Degree(-1.25f));
    }else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
    {
        escenaAjedrez->rotacionCamara(Ogre::Degree(-1));

        //  escenaAjedrez->mueveCamaraDerecha();

        // mCamera->moveRelative(Ogre::Vector3(1,0,0));
        // mCamera->pitch(Ogre::Degree(1.025f));
    }else if (arg.key == OIS::KC_C)
    {
        if (escenaAjedrez->esModoCamara())
            escenaAjedrez->acabarModoCamara();
        else
            escenaAjedrez->empezarModoCamara();

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

    //   std::cout << "mm"<< std::endl;

    if (escenaAjedrez == NULL) std::cout << "escena NULL"<< std::endl;

    if (escenaAjedrez->esModoCamara())   // yaw around the target, and pitch locally
    {
        //      std::cout << "camara" << std::endl;
        escenaAjedrez->rotacionCamara(Ogre::Degree(mCursorPosition.d_x)); // con grados?
    }

    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        //     std::cout << "Z" << std::endl;

        // the further the camera is, the faster it moves
        escenaAjedrez->DistanciaCamara(arg.state.Z.rel);
    }
    else
    {
        if (escenaAjedrez->getTablero()->fichaSeleccionada)
        {
            const std::string casilla = escenaAjedrez->encuentraCasillaSobrevolada(mCursorPosition);

            if (casilla != "")
            {
                //  std::cout << "cosas "<< casilla<<std::endl;

                if (modeloVista->JugadorActivo->casillaSobrevolada(casilla))
                {

                    //  std::cout << "dentro de cosas"<< std::endl;

                }
            }
        }
    }
    //  std::cout << "fin mousemoved" << std::endl;
    //  mInputMan->injectMouseMove(arg); //CAMBIA NOMBRE POR MUEVECAMARA

    return true;
}

bool VistaAjedrez::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if (!BaseVistas::frameRenderingQueued(evt)) return false;
    else if(escenaAjedrez->getTablero()->rotacionCamara != Ogre::Degree(0))
    {
        mueveCamara(evt.timeSinceLastFrame);
    }
    return true;
}

bool VistaAjedrez::salir()
{

}


//-------------------------------------------------------------------------------------
bool VistaAjedrez::mueveCamara(float frecuencia)
{   
    Tablero* tablero = escenaAjedrez->getTablero();

    Ogre::Degree rot = Ogre::Degree(Ogre::Real(80.0f) * frecuencia);


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


    return true;
}

bool VistaAjedrez::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  
    BaseVistas::mousePressed(arg, id);

    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();

    //int posx = arg.state.X.abs;   // Posicion del puntero
    //int posy = arg.state.Y.abs;   //  en pixeles.
    //char mask;
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho -------------
        std::cout << "SELECCIONAFICCCC en modelovista de mousepressed de vistaajedrez"<< std::endl;


        std::cout << modeloVista->escena->esModoCamara()<< std::endl;




        std::cout << "SELECCIONAFICCCC en modelovista de mousepressed de vistaajedrez"<< std::endl;

        // if (escenaAjedrez->getTurnoNegras())
        //   {
        //        mask = 'N';  // Podemos elegir todo
        // } else mask ='B';

        // HAY QUE CAMBIAR ESTO PARA QUE SE HAGA CASI TODO EN ESCENAAJEDREZ
        modeloVista->seleccionaFichaEnPosicion(mCursorPosition);

        // std::cout  << "FILA CASILLA SOBRE LA QUE SE HACE CLICK: "<< tablero->getNodoCasillaSeleccionada()->getPosicion().Fila <<std::endl;
        //  std::cout  << "COLUMNA CASILLA SOBRE LA QUE SE HACE CLICK: "<< tablero->getNodoCasillaSeleccionada()->getPosicion().Columna <<std::endl;

    }
    else if (id == OIS::MB_Right)
    {
        //     if (modelo->jugadorActual->esHumano())
        //    {
        //  int* resutaldoParaQuepase = new int(9999);
        std::cout << "BOTON DERECHO CON  CASILLA SOBREVOLADA"<< std::endl;

        modeloVista->botonIzquierdo();

        // escenaAjedrez->tableroModelo->jugada[0] = 24+(escenaAjedrez->tablero->getNodoCasillaSeleccionada()->getPosicion().Fila*12)+escenaAjedrez->tablero->getNodoCasillaSeleccionada()->getPosicion().Columna + 2;
        // escenaAjedrez->tableroModelo->jugada[1] = 24+(escenaAjedrez->tablero->getNodoCasillaSobrevolada()->getPosicion().Fila*12)+escenaAjedrez->tablero->getNodoCasillaSobrevolada()->getPosicion().Columna + 2;

    }else if (id == OIS::MB_Middle)
    {
        escenaAjedrez->empezarModoCamara();
    }
    //  mInputMan->injectMouseDown(arg, id);

    return true;
}

bool VistaAjedrez::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{

    BaseVistas::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);

    if(mbMiddle) escenaAjedrez->acabarModoCamara();


    //  mInputMan->injectMouseUp(arg, id);

    return true;
}
