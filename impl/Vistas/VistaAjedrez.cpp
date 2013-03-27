
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez( Ogre::RenderWindow* mWindow) :
        fichaSeleccionada(false),
      textoOverlay("VACIO")
    , rotaTurno(0)
    , mWindow(mWindow)



{
    escenaAjedrez = EscenaAjedrez::getSingletonPtr();

}

VistaAjedrez::~VistaAjedrez(void)
{    
}


bool VistaAjedrez::cambiaTurno(){
    std::cout << "cambiatur "<< std::endl;

    rotaTurno = Ogre::Real(180.0f);
    escenaAjedrez->cambiaTurno();
    //mediaVuelta();
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{    

    if (arg.key == OIS::KC_A || arg.key == OIS::KC_LEFT)
    {
        escenaAjedrez->mueveCamaraIzquierda();
        //   mCamera->moveRelative(Ogre::Vector3(-1,0,0));//yaw(Ogre::Degree(-1.25f));
    }

    if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
    {
        escenaAjedrez->mueveCamaraDerecha();

        // mCamera->moveRelative(Ogre::Vector3(1,0,0));
        // mCamera->pitch(Ogre::Degree(1.025f));
    }



    // escenaAjedrez->mueveIzquierda();
    // mInputMan->injectKeyDown(arg);
    return true;
}

bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 

    escenaAjedrez->noMueveCamara();

    /*
   if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT)
    {
         escenaAjedrez->noMueveCamaraIzquierda();
        // mCamera->yaw(Ogre::Degree(-10.25f));
    }
    if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT)
    {
         escenaAjedrez->noMueveCamaraIzquierda();
        // mCamera->pitch(Ogre::Degree(10.025f));
    }
*/

    // mInputMan->injectKeyUp(arg);
    return true;
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{


    std::cout << "mouseMoved vista" << std::endl;



    if (escenaAjedrez->esModoCamara())   // yaw around the target, and pitch locally
    {

        escenaAjedrez->rotacionCamara(Ogre::Degree(arg.state.X.rel)); // con grados?


    }


    else if (fichaSeleccionada)
    {

        int posx = arg.state.X.abs;   // Posicion del puntero
        int posy = arg.state.Y.abs;   //  en pixeles.

        // escenaAjedrez->executeRay(posx, posy, "casilla");

        // Ogre::uint32 mask;
        // mask = CASILLA;

        //  Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);

        Ogre::RaySceneQueryResult &result = escenaAjedrez->executeRay(posx, posy, 'C');


        //  Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end()) {
            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

            if (escenaAjedrez->getNodoCasillaSobrevolada()==NULL || nodoSobrevolado->getName() != escenaAjedrez->getNodoCasillaSobrevolada() -> getName()){

                if (escenaAjedrez->getNodoCasillaSobrevolada()!=NULL){
                    escenaAjedrez->apagaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());
                    escenaAjedrez->setNodoCasillaSobrevolada(NULL);
                }
                escenaAjedrez->setNodoCasillaSobrevolada(nodoSobrevolado);

                //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
                bool autorizado= true;
                autorizado = Autorizaciones::autorizaCasilla(escenaAjedrez->getNodoFichaSeleccionada() , escenaAjedrez->getNodoCasillaSobrevolada(), escenaAjedrez->esTurnoNegras());


                if(autorizado)
                    if  (escenaAjedrez->getNodoCasillaSobrevolada()->getChildIterator().hasMoreElements()){

                        if (escenaAjedrez->FichaComestible()) escenaAjedrez->iluminaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());

                    } else{ escenaAjedrez->iluminaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());
                        std::cout << "ES COMESTIBLE" << std::endl;

                    }
            }
        }
    }





    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        // the further the camera is, the faster it moves
        escenaAjedrez->DistanciaCamara(arg.state.Z.rel);
    }



    //  mInputMan->injectMouseMove(arg); //CAMBIA NOMBRE POR MUEVECAMARA

    return true;
}

bool VistaAjedrez::salir(){
    //return salirPulsado;
}
bool VistaAjedrez::esMenuInicio(){

    return false;
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::frameRenderingQueued(const Ogre::FrameEvent& evt)
{   
    std::cout << "frameRenderingQueued "<< std::endl;

    //   if (mGoingRight) accel += mCamera->getRight();

    //    if (mGoingLeft) accel -= mCamera->getRight();

    //   if (rotaTurno > Ogre::Real(0.0f))
    //   {
    //    std::cout << "cambiaturnorota "<< accel<< std::endl;



    //ROTACION MIENTRAS SE PULSEN LAS FLECHAS
    if(escenaAjedrez->vaIzquierda()){
        escenaAjedrez->rotacionCamara(Ogre::Degree(1));
    }

    if(escenaAjedrez->vaDerecha()){
        escenaAjedrez->rotacionCamara(Ogre::Degree(-1));

    }

    if (rotaTurno != Ogre::Degree(0))
    {
        //std::cout << "cambiaturnorota "<< accel<< std::endl;


        //  mCambiaTurno = false;
        // accel += mCamera->getRight();

        //   accel -= mCamera->getRight();


        //  escenaAjedrez->mInputMan->rotaCamara(rotaTurno);

        Ogre::Degree rot = Ogre::Degree(Ogre::Real(120.0f) * evt.timeSinceLastFrame);

        //Rota la camara
        if (rot > rotaTurno){

            escenaAjedrez->rotacionCamara(rotaTurno);
            rotaTurno = Ogre::Real(0.0f);


        }else {
            escenaAjedrez->rotacionCamara(rot);
            rotaTurno = rotaTurno - rot;
        }

        //Devuelve la camara a su posicion ¿z? original
        // mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.025f));




        std::cout << "rotaTurno "<< rotaTurno<< std::endl;
        //  std::cout << "Ogre::Real(120.0f) * evt.timeSinceLastFrame "<< Ogre::Real(120.0f) * evt.timeSinceLastFrame<< std::endl;


    }











    //mInputMan->rotaCamara(evt);
    return true;
}

bool VistaAjedrez::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  
    bool mbleft = (id == OIS::MB_Left);
    bool mbright = (id == OIS::MB_Right);
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    char mask;
    if (mbleft)
    {  // Boton izquierdo o derecho -------------
        //std::cout << "mbleft "<< turnoNegras<< std::endl;
        if (escenaAjedrez->esTurnoNegras())
        {
            mask = 'N';  // Podemos elegir todo
        } else mask ='B';

        if (escenaAjedrez->getNodoFichaSeleccionada() != NULL)
        {  // Si habia alguno seleccionado...

            escenaAjedrez->getNodoFichaSeleccionada()->showBoundingBox(false);  escenaAjedrez->setNodoFichaSeleccionada(NULL);
            fichaSeleccionada = false;
        }
        //EMPIEZA RAYO
        //Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result =escenaAjedrez->executeRay(posx,posy,mask);//mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end())
        {
            if (it->movable->getParentSceneNode()->getName().size()>2)
            {
                escenaAjedrez->setNodoFichaSeleccionada(it->movable->getParentSceneNode());
                escenaAjedrez->getNodoFichaSeleccionada()->showBoundingBox(true);
                fichaSeleccionada = true;
            }
        }
    } else if (mbright)
    {
        //MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
        if (fichaSeleccionada && escenaAjedrez->getNodoCasillaSobrevolada()!=NULL && escenaAjedrez->getNodoCasillaSobrevolada()->getShowBoundingBox())
        {
            //BORRA FICHA DE LA CASILLA ANTERIOR
            escenaAjedrez->getNodoFichaSeleccionada()->getParent()->removeChild(escenaAjedrez->getNodoFichaSeleccionada());

            //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
            if (escenaAjedrez->getNodoCasillaSobrevolada()->getChildIterator().hasMoreElements())
            {
                escenaAjedrez->getNodoCasillaSobrevolada()->removeAllChildren();
            }

            //AÑADE FICHA A LA CASILLA NUEVA
            escenaAjedrez->getNodoCasillaSobrevolada()->addChild(escenaAjedrez->getNodoFichaSeleccionada());

            //PROMOCION DE PEON
          //  std::cout << "_nodoNuevo->getName() "<< _nodoNuevo->getName()<< std::endl;


            if(escenaAjedrez->getNodoCasillaSobrevolada()->getName()[1] == '8'){

                escenaAjedrez->promocionaPeon(escenaAjedrez->getNodoFichaSeleccionada());
            }





            cambiaTurno();

            //  mCamera->moveRelative(Ogre::Degree(30));


            //DESELECCIONA FICHA Y CASILLA
            escenaAjedrez->getNodoFichaSeleccionada()->showBoundingBox(false);
            escenaAjedrez->apagaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());
            escenaAjedrez->setNodoCasillaSobrevolada(NULL);
            escenaAjedrez->setNodoFichaSeleccionada(NULL);
            fichaSeleccionada = false;
        }
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
