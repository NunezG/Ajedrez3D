
#include "../headers/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : BaseApplication(mSceneMgr, mWindow),
      _selectedNode(0),
      fichaSeleccionada(false),
      _nodoNuevo(0),
      turnoNegras(0),
      textoOverlay("VACIO")

{
}
//-------------------------------------------------------------------------------------
VistaAjedrez::~VistaAjedrez(void)
{
    if (mInputMan) delete mInputMan;

}

//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{

    // mInputMan->injectKeyDown(arg);

    return BaseApplication::keyPressed( arg );
}


bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{

    return BaseApplication::keyReleased( arg );

}




bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg ){


    if (fichaSeleccionada){

        int posx = arg.state.X.abs;   // Posicion del puntero
        int posy = arg.state.Y.abs;   //  en pixeles.
        Ogre::uint32 mask;
        mask = CASILLA;

        Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end()) {
            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

            if (_nodoNuevo==NULL || nodoSobrevolado->getName() != _nodoNuevo->getName()){

                if (_nodoNuevo!=NULL){
                    _nodoNuevo->showBoundingBox(false);
                    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(_nodoNuevo->getAttachedObject(0));
                    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
                    if (mNombreEntidad[1] == 'B'){
                        mEntidadCasilla->setMaterialName("MaterialBlanco");
                    }else mEntidadCasilla->setMaterialName("MaterialNegro");
                    _nodoNuevo=NULL;
                }

                _nodoNuevo=nodoSobrevolado;


                //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
                bool autorizado= true;
                autorizado = Movimientos::autorizaCasilla(_selectedNode , _nodoNuevo, turnoNegras);

                //Mira si la casilla está ocupada y por quién
                if(autorizado
                        && _nodoNuevo->getChildIterator().hasMoreElements()) autorizado = Movimientos::FichaComestible(nodoSobrevolado, turnoNegras);

                if (autorizado){

                    // std::cout << "ESTA AUTORIZADO!!!!!" << std::endl;
                    _nodoNuevo->showBoundingBox(true);

                    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(_nodoNuevo->getAttachedObject(0));
                    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
                    if (mNombreEntidad[1] == 'B'){
                        mEntidadCasilla->setMaterialName("MaterialBlancoIluminado");
                    }else mEntidadCasilla->setMaterialName("MaterialNegroIluminado");
                }
            }
        }
    }

    return BaseApplication::mouseMoved( arg );


}





//-------------------------------------------------------------------------------------
bool VistaAjedrez::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    std::cout << "frameRenderingQueued en VISTA AJEDREZ" << std::endl;


    mInputMan->frameRenderingQueued(evt);

    return true;

    //return  BaseApplication::frameRenderingQueued(evt);

}

bool VistaAjedrez::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{


    bool mbleft = (id == OIS::MB_Left);
    bool mbright = (id == OIS::MB_Right);
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    Ogre::uint32 mask;
    if (mbleft) {  // Boton izquierdo o derecho -------------
        std::cout << "mbleft "<< turnoNegras<< std::endl;
        if (turnoNegras) {
            mask = NEGRAS;  // Podemos elegir todo
        } else mask =BLANCAS;

        if (_selectedNode != NULL) {  // Si habia alguno seleccionado...

            _selectedNode->showBoundingBox(false);  _selectedNode = NULL;
            fichaSeleccionada = false;
        }

        //EMPIEZA RAYO
        Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();
        std::cout << "RESULTADO" << std::endl;

        if (it != result.end()) {
            if (it->movable->getParentSceneNode()->getName().size()>2) {

                std::cout << "HA DETECTADO UNA FICHA" << std::endl;
                _selectedNode = it->movable->getParentSceneNode();
                _selectedNode->showBoundingBox(true);
                fichaSeleccionada = true;
            }
        }

    } else if (mbright){

        if (_selectedNode != NULL && _nodoNuevo!=NULL && _nodoNuevo->getShowBoundingBox()) {  // Si habia alguno seleccionado...


            Ogre::Vector3 vector;

            if (turnoNegras){
                vector = Ogre::Vector3(70,0,70)+_nodoNuevo->getPosition();
            }else vector =_nodoNuevo->getPosition();
            _selectedNode->getParent()->removeChild(_selectedNode);
            if (_nodoNuevo->getChildIterator().hasMoreElements()){
                _nodoNuevo->removeAllChildren();
            }
            _nodoNuevo->addChild(_selectedNode);
            //   _selectedNode->setPosition(vector);
            turnoNegras= !turnoNegras;
            //        std::cout << "NUEVA POS"<< _selectedNode->getPosition() << std::endl;
            //_selectedNode->translate(_nodoNuevo->getPosition(),_selectedNode->TS_WORLD);
            _selectedNode->showBoundingBox(false);
            _nodoNuevo->showBoundingBox(false);
            Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(_nodoNuevo->getAttachedObject(0));
            const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
            if (mNombreEntidad[1] == 'B'){
                mEntidadCasilla->setMaterialName("MaterialBlanco");
            }else mEntidadCasilla->setMaterialName("MaterialNegro");
            _nodoNuevo=NULL;
            _selectedNode=NULL;
            fichaSeleccionada = false;

        }

    }

    return BaseApplication::mousePressed( arg , id);

}



bool VistaAjedrez::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseApplication::mouseReleased( arg, id );
}


int VistaAjedrez::muevePeon(Ogre::String coord){
    if (turnoNegras){
        //  _selectedNode->
        // _nodoNuevo
        // coord
    }
}
