
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

VistaAjedrez::~VistaAjedrez(void)
{    
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{    
    return BaseApplication::keyPressed( arg );
}

bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 
    return BaseApplication::keyReleased( arg );
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{
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
                    apagaCasilla(_nodoNuevo);
                    _nodoNuevo=NULL;
                }
                _nodoNuevo=nodoSobrevolado;

                //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
                bool autorizado= true;
                autorizado = Autorizaciones::autorizaCasilla(_selectedNode , _nodoNuevo, turnoNegras);

                //Mira si la casilla está ocupada y por quién
                if(autorizado)
                    if  (_nodoNuevo->getChildIterator().hasMoreElements()) autorizado = Autorizaciones::FichaComestible(nodoSobrevolado, turnoNegras);
                    else Autorizaciones::iluminaCasilla(_nodoNuevo);
            }
        }
    }
    return BaseApplication::mouseMoved( arg );
}


void VistaAjedrez::apagaCasilla(Ogre::SceneNode* casilla)
{
    casilla->showBoundingBox(false);
    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    if (mNombreEntidad[1] == 'B'){
        mEntidadCasilla->setMaterialName("MaterialBlanco");
    }else mEntidadCasilla->setMaterialName("MaterialNegro");
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::frameRenderingQueued(const Ogre::FrameEvent& evt)
{   
    mInputMan->frameRenderingQueued(evt);
    return true;
}

bool VistaAjedrez::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  
    bool mbleft = (id == OIS::MB_Left);
    bool mbright = (id == OIS::MB_Right);
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    Ogre::uint32 mask;
    if (mbleft)
    {  // Boton izquierdo o derecho -------------
        std::cout << "mbleft "<< turnoNegras<< std::endl;
        if (turnoNegras)
        {
            mask = NEGRAS;  // Podemos elegir todo
        } else mask =BLANCAS;

        if (_selectedNode != NULL)
        {  // Si habia alguno seleccionado...

            _selectedNode->showBoundingBox(false);  _selectedNode = NULL;
            fichaSeleccionada = false;
        }
        //EMPIEZA RAYO
        Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
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
        //COME LA FICHA
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
            turnoNegras= !turnoNegras;
            _selectedNode->showBoundingBox(false);

            apagaCasilla(_nodoNuevo);

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
