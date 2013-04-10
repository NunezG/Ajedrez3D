
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

            Casilla* casillaSobrevolada = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo(nodoSobrevolado->getName()));

            if (escenaAjedrez->getNodoCasillaSobrevolada()==NULL || casillaSobrevolada->getNombre() != escenaAjedrez->getNodoCasillaSobrevolada() -> getNombre())
            {

                std::cout << "IF" << std::endl;


                if (escenaAjedrez->getNodoCasillaSobrevolada()!=NULL){
                    escenaAjedrez->apagaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());
                    escenaAjedrez->setNodoCasillaSobrevolada(NULL);
                }
                escenaAjedrez->setNodoCasillaSobrevolada(casillaSobrevolada);

                //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
                bool autorizado= true;
                autorizado = Autorizaciones::autorizaCasilla(escenaAjedrez->tablero, escenaAjedrez->getNodoFichaSeleccionada() , escenaAjedrez->getNodoCasillaSobrevolada(), escenaAjedrez->esTurnoNegras());

                std::cout << "autorizado: "<<autorizado << std::endl;


                if(autorizado)
                {

                    if  (escenaAjedrez->getNodoCasillaSobrevolada()->sinHijos() != true)
                    {


                        if (escenaAjedrez->FichaComestible()) escenaAjedrez->iluminaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());

                    } else{ escenaAjedrez->iluminaCasilla(escenaAjedrez->getNodoCasillaSobrevolada());
                        std::cout << "ES COMESTIBLE" << std::endl;

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
        // if (escenaAjedrez->esTurnoNegras())
        //   {
        //        mask = 'N';  // Podemos elegir todo
        // } else mask ='B';

        mask = 'C';

        std::cout  << "mpouse1" << std::endl;

        if (escenaAjedrez->getNodoFichaSeleccionada() != NULL)
        {  // Si habia alguno seleccionado...

            std::cout  << "fichasel" << std::endl;
            Ficha* ficha = static_cast<Ficha*>(escenaAjedrez->getNodoFichaSeleccionada()->getHijo(0));
            ficha->getNodoOgre()->showBoundingBox(false);
            escenaAjedrez->setNodoFichaSeleccionada(NULL);
            fichaSeleccionada = false;
        }

        std::cout  << "mpouse2" << std::endl;

        //EMPIEZA RAYO
        //Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result =escenaAjedrez->executeRay(posx,posy,mask);//mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();
        std::cout  << "mpouse3" << std::endl;


        if (it != result.end())
        {
            std::cout  << "mpouse31121: "<< it->movable->getParentSceneNode()->getName()<< std::endl;


            std::cout  << "mpouse31121: "<< it->movable->getName()<< std::endl;



            Casilla* casilla = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo(it->movable->getParentSceneNode()->getName()));

            std::cout  << "mpouse31: "<< casilla->getNombre() << std::endl;



            if (casilla != NULL && !casilla->sinHijos())
            {

                Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                std::cout  << "tiene hijos" << std::endl;


                if ((escenaAjedrez->esTurnoNegras()
                     && ficha->esNegra)
                        || (!escenaAjedrez->esTurnoNegras() && !ficha->esNegra)){


                    escenaAjedrez->setNodoFichaSeleccionada(casilla);
                    ficha->getNodoOgre()->showBoundingBox(true);
                    fichaSeleccionada = true;
                }

            }
        }
        std::cout  << "fin mousepressed" << std::endl;

    } else if (mbright)
    {
        //MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
        if (fichaSeleccionada && escenaAjedrez->getNodoCasillaSobrevolada()!=NULL && escenaAjedrez->getNodoCasillaSobrevolada()->getNodoOgre()->getShowBoundingBox())
        {





            //Recupera ficha
            Ficha* ficha = static_cast<Ficha*>(escenaAjedrez->getNodoFichaSeleccionada()->getHijo(0));



            std::cout  << "antes:" << escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Fila<<std::endl;

            escenaAjedrez->actualizaTablero(escenaAjedrez->getNodoFichaSeleccionada()->getPosicion(), escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion());

            std::cout  << "borra" << std::endl;



            std::cout  << "desp:" << escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Fila<<std::endl;







            std::cout  << "MIRA SI SALTA: " <<ficha->getNombre()<< std::endl;

            if (ficha->tipo_Ficha ==Rey)
            {


                std::cout  << "en rey" << std::endl;

                int difCol = escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Columna - escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Columna;
                // if (difCol<0 ) difCol = -difCol;

                int fila =escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Fila;


                if (difCol == 2){
                    Casilla* casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8)+7));
                    Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                    casillaTorre->eliminaHijo(0);

                    casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8) +escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Columna-1));
                    casillaTorre->agregaHijo(fichaTorre);
                }

                if (difCol == -2){
                    //Casilla* casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8)));

                    Casilla* casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo(fila*8));
                    Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                    casillaTorre->eliminaHijo(0);

                    casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8) +escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Columna+1));
                    casillaTorre->agregaHijo(fichaTorre);
                }





            }

            std::cout  << "MIRA SI peon " << std::endl;


            if (ficha->tipo_Ficha ==Peon)
            {

                std::cout  << "dif" << std::endl;



                std::cout  << "dif:" << escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Fila<< std::endl;

                std::cout  << "dif:" << escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Fila<< std::endl;


                int dif = escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Fila - escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Fila;

                std::cout  << "dif:" << dif<< std::endl;



                int difCol = escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Columna - escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Columna;
                std::cout  << "difcol: " << difCol<<std::endl;

                if (dif < 0 ) dif = -dif;
                if (difCol<0 ) difCol = -difCol;


                if( dif == 2) ficha -> salto = true;

                if( dif == 1 && difCol == 1)
                {

                    int fila =escenaAjedrez->getNodoFichaSeleccionada()->getPosicion().Fila;
                    int columna =escenaAjedrez->getNodoCasillaSobrevolada()->getPosicion().Columna;

                    Casilla* casillaAux = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8)+columna));

                    if (!casillaAux->sinHijos())
                    {
                        Ficha* fichaAux = static_cast<Ficha*>(casillaAux->getHijo(0));
                        if (fichaAux->salto) casillaAux->eliminaHijo(0);

                    }





                }

            }

            std::cout  << "acaba de mirar " << std::endl;


            //escenaAjedrez->getNodoFichaSeleccionada()->getParent()->removeChild(escenaAjedrez->getNodoFichaSeleccionada());



            //PROMOCION DE PEON
            //  std::cout << "_nodoNuevo->getName() "<< _nodoNuevo->getName()<< std::endl;


            //  mCamera->moveRelative(Ogre::Degree(30));

            std::cout  << "fincambia " << std::endl;

            //DESELECCIONA FICHA Y CASILLA
            ficha->getNodoOgre()->showBoundingBox(false);
            std::cout  << "apagado " << std::endl;

            std::cout  << "nulleado " << std::endl;

            fichaSeleccionada = false;

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
