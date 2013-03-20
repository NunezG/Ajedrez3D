
#include "../headers/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : BaseOgre(mSceneMgr, mWindow),
      _selectedNode(0),
      fichaSeleccionada(false),
      textoOverlay("VACIO")
    , rotaTurno(0)


{
}

VistaAjedrez::~VistaAjedrez(void)
{    
}


bool VistaAjedrez::cambiaTurno(){
    std::cout << "cambiatur "<< std::endl;

    rotaTurno = Ogre::Real(180.0f);


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



    if (escenaAjedrez->mOrbiting)   // yaw around the target, and pitch locally
    {

        escenaAjedrez->mInputMan->rotaCamara(Ogre::Degree(arg.state.X.rel)); // con grados?


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

            if (_nodoNuevo==NULL || nodoSobrevolado->getName() != _nodoNuevo->getName()){

                if (_nodoNuevo!=NULL){
                    escenaAjedrez->apagaCasilla(_nodoNuevo);
                    _nodoNuevo=NULL;
                }
                _nodoNuevo=nodoSobrevolado;

                //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
                bool autorizado= true;
                autorizado = Autorizaciones::autorizaCasilla(_selectedNode , _nodoNuevo, turnoNegras);


                if(autorizado)
                    if  (_nodoNuevo->getChildIterator().hasMoreElements()) FichaComestible();
                    else escenaAjedrez->iluminaCasilla(_nodoNuevo);
            }
        }
    }





    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        // the further the camera is, the faster it moves
        escenaAjedrez->mInputMan->distanciaCamara(arg.state.Z.rel);
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


    if(escenaAjedrez->mGoingLeft){
        escenaAjedrez->mInputMan->rotaCamara(Ogre::Degree(1));
    }

    if(escenaAjedrez->mGoingRight){
        escenaAjedrez->mInputMan->rotaCamara(Ogre::Degree( -1));

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

            escenaAjedrez->mInputMan->rotaCamara(rotaTurno);
            rotaTurno = Ogre::Real(0.0f);


        }else {
            escenaAjedrez->mInputMan->rotaCamara(rot);
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
        std::cout << "mbleft "<< turnoNegras<< std::endl;
        if (turnoNegras)
        {
            mask = 'N';  // Podemos elegir todo
        } else mask ='B';

        if (_selectedNode != NULL)
        {  // Si habia alguno seleccionado...

            _selectedNode->showBoundingBox(false);  _selectedNode = NULL;
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
                _selectedNode = it->movable->getParentSceneNode();
                _selectedNode->showBoundingBox(true);
                fichaSeleccionada = true;
            }
        }
    } else if (mbright)
    {
        //MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
        if (fichaSeleccionada && _nodoNuevo!=NULL && _nodoNuevo->getShowBoundingBox())
        {
            //BORRA FICHA DE LA CASILLA ANTERIOR
            _selectedNode->getParent()->removeChild(_selectedNode);

            //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
            if (_nodoNuevo->getChildIterator().hasMoreElements())
            {
                _nodoNuevo->removeAllChildren();
            }

            //AÑADE FICHA A LA CASILLA NUEVA
            _nodoNuevo->addChild(_selectedNode);

            //PROMOCION DE PEON
            std::cout << "_nodoNuevo->getName() "<< _nodoNuevo->getName()<< std::endl;


            if(_nodoNuevo->getName()[1] == '8'){

                escenaAjedrez->promocionaPeon(_selectedNode);
            }


            //CAMBIA TURNO
            turnoNegras= !turnoNegras;

            std::cout << "LLEGA BIEN A PITCH "<< std::endl;


            cambiaTurno();

            //  mCamera->moveRelative(Ogre::Degree(30));


            //DESELECCIONA FICHA Y CASILLA
            _selectedNode->showBoundingBox(false);
            escenaAjedrez->apagaCasilla(_nodoNuevo);
            _nodoNuevo=NULL;
            _selectedNode=NULL;
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
