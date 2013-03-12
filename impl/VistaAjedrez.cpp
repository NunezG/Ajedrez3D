
#include "../headers/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : BaseOgre(mSceneMgr, mWindow),
      _selectedNode(0),
      fichaSeleccionada(false),
      textoOverlay("VACIO")

{
}

VistaAjedrez::~VistaAjedrez(void)
{    
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed( const OIS::KeyEvent &arg )
{    
    return BaseOgre::keyPressed( arg );
}

bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 
    return BaseOgre::keyReleased( arg );
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


                if(autorizado)
                    if  (_nodoNuevo->getChildIterator().hasMoreElements()) FichaComestible();
                    else iluminaCasilla(_nodoNuevo);
            }
        }
    }
    return BaseOgre::mouseMoved( arg );
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
        //MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
        if (fichaSeleccionada && _nodoNuevo!=NULL && _nodoNuevo->getShowBoundingBox()) {

            //BORRA FICHA DE LA CASILLA ANTERIOR
            _selectedNode->getParent()->removeChild(_selectedNode);

            //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
            if (_nodoNuevo->getChildIterator().hasMoreElements()){
                _nodoNuevo->removeAllChildren();
            }

            //AÑADE FICHA A LA CASILLA NUEVA
            _nodoNuevo->addChild(_selectedNode);

            //CAMBIA TURNO
            turnoNegras= !turnoNegras;

            //DESELECCIONA FICHA Y CASILLA
            _selectedNode->showBoundingBox(false);
            apagaCasilla(_nodoNuevo);
            _nodoNuevo=NULL;
            _selectedNode=NULL;
            fichaSeleccionada = false;
        }
    }
    return BaseOgre::mousePressed( arg , id);
}

bool VistaAjedrez::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseOgre::mouseReleased( arg, id );
}
