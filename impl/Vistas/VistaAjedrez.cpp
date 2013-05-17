
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(EscenaAjedrez* escena) :
    BaseVistas()
  , escenaAjedrez(escena)
    , textoOverlay("VACIO")



{

  //  modelo =Modelo::getSingletonPtr();



   // escenaAjedrez = EscenaAjedrez::getSingletonPtr();


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

    BaseVistas::iniciaVentana();

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
    }

    if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
    {

        escenaAjedrez->rotacionCamara(Ogre::Degree(-1));


      //  escenaAjedrez->mueveCamaraDerecha();

        // mCamera->moveRelative(Ogre::Vector3(1,0,0));
        // mCamera->pitch(Ogre::Degree(1.025f));
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
    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();

    if (escenaAjedrez->esModoCamara())   // yaw around the target, and pitch locally
    {
        escenaAjedrez->rotacionCamara(Ogre::Degree(mCursorPosition.d_x)); // con grados?
    }


    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        // the further the camera is, the faster it moves
        escenaAjedrez->DistanciaCamara(arg.state.Z.rel);
    }
    else escenaAjedrez-> autorizaCasillaSobrevolada();




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

    //!!!!!!!!!!!!!!!!!!!BUSCA EN EL VECTOR DE HIJOS DEL TABLERO EL QUE COINCIDA EN EL NOMBRE (O TAMBIEN LA POSICION?)
    //
    //
    //
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    CEGUI::Vector2 mCursorPosition=CEGUI::MouseCursor::getSingleton().getPosition();

    bool mbleft = (id == OIS::MB_Left);
    bool mbright = (id == OIS::MB_Right);
    //int posx = arg.state.X.abs;   // Posicion del puntero
    //int posy = arg.state.Y.abs;   //  en pixeles.
    //char mask;
    if (mbleft)
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



    } else if (mbright)
    {
   //     if (modelo->jugadorActual->esHumano())
    //    {

        escenaAjedrez->mueveFicha();



           //   }
    }else {
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



