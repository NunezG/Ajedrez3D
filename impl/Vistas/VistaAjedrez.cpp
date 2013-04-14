
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez( Ogre::RenderWindow* mWindow) :
    fichaSeleccionada(false),
    textoOverlay("VACIO")
  , rotaTurno(0)
  , mWindow(mWindow)



{
    escenaAjedrez = EscenaAjedrez::getSingletonPtr();
    modelo =Modelo::getSingletonPtr();



}

VistaAjedrez::~VistaAjedrez(void)
{    
}


bool VistaAjedrez::cambiaTurno(){
    std::cout << "cambiatur "<< std::endl;
    fichaSeleccionada = false;

    escenaAjedrez->apagaCasilla(modelo->getTablero()->getNodoCasillaSobrevolada());

    rotaTurno = Ogre::Real(180.0f);
    modelo->getTablero()->cambiaTurno();
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


    return true;
}

bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 

    escenaAjedrez->noMueveCamara();


    return true;
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{



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

        if (it != result.end())
        {
            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

            Casilla* casillaSobrevolada = static_cast<Casilla*>(modelo->getTablero()->getHijo(nodoSobrevolado->getName()));

            if (modelo->getTablero()->getNodoCasillaSobrevolada()==NULL || casillaSobrevolada->getNombre() != modelo->getTablero()->getNodoCasillaSobrevolada() -> getNombre())
            {

                std::cout << "IF" << std::endl;


                if (modelo->getTablero()->getNodoCasillaSobrevolada()!=NULL){
                    escenaAjedrez->apagaCasilla(modelo->getTablero()->getNodoCasillaSobrevolada());
                    modelo->getTablero()->setNodoCasillaSobrevolada(NULL);
                }
                modelo->getTablero()->setNodoCasillaSobrevolada(casillaSobrevolada);

                //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
                bool autorizado= true;
                autorizado = Autorizaciones::autorizaCasilla(modelo->getTablero(), modelo->getTablero()->getNodoFichaSeleccionada() , modelo->getTablero()->getNodoCasillaSobrevolada(), modelo->getTablero()->getTurnoNegras());

                std::cout << "autorizado: "<<autorizado << std::endl;


                if(autorizado)
                {

                    if  (modelo->getTablero()->getNodoCasillaSobrevolada()->sinHijos() != true)
                    {


                        if (modelo->getTablero()->FichaComestible()) {
                            //falta evaluar jaque y ahogado
                            if (!Autorizaciones::evaluaJaque(modelo->getTablero()->mueveYTraduceTablero(), modelo->getTablero()->getTurnoNegras()))
                            {
                                escenaAjedrez->iluminaCasilla(modelo->getTablero()->getNodoCasillaSobrevolada());
                                std::cout << "ES COMESTIBLE" << std::endl;
                            }else {
                                std::cout << "JAQUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;


                            }


                        }

                    } else{

                        //falta evaluar jaque y ahogado
                        if (!Autorizaciones::evaluaJaque(modelo->getTablero()->mueveYTraduceTablero(), modelo->getTablero()->getTurnoNegras()))
                        {
                            escenaAjedrez->iluminaCasilla(modelo->getTablero()->getNodoCasillaSobrevolada());
                            std::cout << "ES COMESTIBLE" << std::endl;
                        }else {
                            std::cout << "JAQUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;


                        }

                    }
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

        //  std::cout << "Ogre::Real(120.0f) * evt.timeSinceLastFrame "<< Ogre::Real(120.0f) * evt.timeSinceLastFrame<< std::endl;

    }

    //mInputMan->rotaCamara(evt);
    return true;
}

bool VistaAjedrez::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  

    //!!!!!!!!!!!!!!!!!!!BUSCA EN EL VECTOR DE HIJOS DEL TABLERO EL QUE COINCIDA EN EL NOMBRE (O TAMBIEN LA POSICION?)
    //
    //
    //
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    bool mbleft = (id == OIS::MB_Left);
    bool mbright = (id == OIS::MB_Right);
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    char mask;
    if (mbleft)
    {  // Boton izquierdo o derecho -------------
        //std::cout << "mbleft "<< turnoNegras<< std::endl;
        // if (escenaAjedrez->getTurnoNegras())
        //   {
        //        mask = 'N';  // Podemos elegir todo
        // } else mask ='B';


        fichaSeleccionada = false;

        // HAY QUE CAMBIAR ESTO PARA QUE SE HAGA CASI TODO EN ESCENAAJEDREZ
        if (escenaAjedrez->seleccionaFichaEnPosicion(posx, posy))
            fichaSeleccionada = true;


        std::cout  << "mpouse1" << std::endl;

        std::cout  << "fin mousepressed" << std::endl;

    } else if (mbright)
    {
        //MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
        if (fichaSeleccionada && modelo->getTablero()->getNodoCasillaSobrevolada()!=NULL && modelo->getTablero()->getNodoCasillaSobrevolada()->getNodoOgre()->getShowBoundingBox())
        {

            modelo->getTablero()->actualizaTablero(modelo->getTablero()->getNodoFichaSeleccionada()->getPosicion(), modelo->getTablero()->getNodoCasillaSobrevolada()->getPosicion());



            cambiaTurno();

            std::cout  << "acaba " << std::endl;

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
