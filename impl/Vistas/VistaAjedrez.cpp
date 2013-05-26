
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(ModeloVista* modeloV, Ogre::Root* mRoot) :
    BaseVistas(modeloV, mRoot, "Root Ajedrez")
  , textoOverlay("VACIO")



{
    std::cout   << "   ESCNA EN VISTAAJEDREZ" << std::endl;


    //  modelo =Modelo::getSingletonPtr();

    //  mWindow = mRoot->initialise(true, "Root Ajedrez");



    // escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    //  BaseVistas::iniciaOIS();
    escenaAjedrez = modeloV->escena;
    //escena
    std::cout   << "   creaTablero" << std::endl;




}

VistaAjedrez::~VistaAjedrez(void)
{    
}

bool VistaAjedrez::muestraInfo()
{


    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("InfoAjedrezCEED.layout");
    //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );


    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);

}

bool VistaAjedrez::iniciaVentana()
{
    //tablero = escenaAjedrez->getTablero();


    Ogre::LogManager::getSingletonPtr()->logMessage("***SALE DE INICIA VENTANA DE LA BASE Y EMPIEZA CEGUI**");

}

bool VistaAjedrez::muestraJaque()
{
    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueCEED.layout");
    //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{    

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

    escenaAjedrez->noMueveCamara();


    return true;
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{



    std::cout << "mousemov"<< std::endl;


    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();

    std::cout << "mm"<< std::endl;


    if (escenaAjedrez == NULL) std::cout << "escena NULL"<< std::endl;

    if (escenaAjedrez->esModoCamara())   // yaw around the target, and pitch locally
    {
        std::cout << "camara" << std::endl;

        escenaAjedrez->rotacionCamara(Ogre::Degree(mCursorPosition.d_x)); // con grados?
    }


    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        std::cout << "Z" << std::endl;

        // the further the camera is, the faster it moves
        escenaAjedrez->DistanciaCamara(arg.state.Z.rel);
    }
    else escenaAjedrez-> autorizaCasillaSobrevolada(mCursorPosition);




    std::cout << "fin mousemoved" << std::endl;

    //  mInputMan->injectMouseMove(arg); //CAMBIA NOMBRE POR MUEVECAMARA

    return true;
}

bool VistaAjedrez::salir(){

}
bool VistaAjedrez::esMenuInicio(){

    return false;
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::mueveCamara(float frecuencia)
{   



    if (escenaAjedrez->tablero->rotacionCamara != Ogre::Degree(0))
    {


        Ogre::Degree rot = Ogre::Degree(Ogre::Real(80.0f) * frecuencia);

        //Rota la camara
        if (rot > escenaAjedrez->tablero->rotacionCamara){

            escenaAjedrez->rotacionCamara(escenaAjedrez->tablero->rotacionCamara);
            escenaAjedrez->tablero->rotacionCamara = Ogre::Real(0.0f);


        }else {
            escenaAjedrez->rotacionCamara(rot);
            escenaAjedrez->tablero->rotacionCamara = escenaAjedrez->tablero->rotacionCamara - rot;
        }

    }

    return true;
}

bool VistaAjedrez::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  


    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();

    //int posx = arg.state.X.abs;   // Posicion del puntero
    //int posy = arg.state.Y.abs;   //  en pixeles.
    //char mask;
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho -------------
        //std::cout << "mbleft "<< turnoNegras<< std::endl;
        // if (escenaAjedrez->getTurnoNegras())
        //   {
        //        mask = 'N';  // Podemos elegir todo
        // } else mask ='B';


        // HAY QUE CAMBIAR ESTO PARA QUE SE HAGA CASI TODO EN ESCENAAJEDREZ
        escenaAjedrez->seleccionaFichaEnPosicion(mCursorPosition.d_x, mCursorPosition.d_y);


        // std::cout  << "FILA CASILLA SOBRE LA QUE SE HACE CLICK: "<< tablero->getNodoCasillaSeleccionada()->getPosicion().Fila <<std::endl;
        //  std::cout  << "COLUMNA CASILLA SOBRE LA QUE SE HACE CLICK: "<< tablero->getNodoCasillaSeleccionada()->getPosicion().Columna <<std::endl;



    } else if (id == OIS::MB_Right &&
               escenaAjedrez->tablero->getNodoCasillaSobrevolada() != NULL)
    {
        //     if (modelo->jugadorActual->esHumano())
        //    {

        //  int* resutaldoParaQuepase = new int(9999);

        escenaAjedrez->aplicaCambio(NULL);

    }else if (id == OIS::MB_Middle)
    {
        escenaAjedrez->empezarModoCamara();

    }
    //  mInputMan->injectMouseDown(arg, id);

    return true;
}





bool VistaAjedrez::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    bool mbMiddle= (id == OIS::MB_Middle);

    if(mbMiddle) escenaAjedrez->acabarModoCamara();


    //  mInputMan->injectMouseUp(arg, id);

    return true;
}



