
#include "../../headers/ModeloVista/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(Modelo* mod) :
    //  mRoot(root),
    modelo(mod)
  , mCamera(0)
  //, mInputMan(0)
  , tablero(NULL)
  , mTarget(0)
  , mTopSpeed(150)
  ,   mRaySceneQuery(0)
  , mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)
  , columnas("ABCDEFGH")
  , ventanaJaque(NULL)


{


    // modelo = Modelo::getSingletonPtr();
    tablero = new Tablero();


}
//-------------------------------------------------------------------------------------
EscenaAjedrez::~EscenaAjedrez(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);

    // if (mInputMan) delete mInputMan;

}



Tablero* EscenaAjedrez::getTablero()
{
    return tablero;

}


void EscenaAjedrez::destruyeTablero()
{
    //delete mSceneMgr;

    delete tablero;

    tablero = NULL;


}


void EscenaAjedrez::sobreVuelaCasilla(){
    tablero->getNodoCasillaSobrevolada()->iluminaCasilla();
    //  miTablero->getNodoCasillaSobrevolada()->seleccionada = false;

}


void EscenaAjedrez::setSceneManager(/*Ogre::Root* mRoot*/)
{
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MANAGER");
}



void EscenaAjedrez::creaIluminacion()
{
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setShadowColour(Ogre::ColourValue(0.75, 0.75, 0.75) );
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.55, 0.55, 0.55));

    mSceneMgr->setShadowTextureCount(2);
    mSceneMgr->setShadowTextureSize(1024);

    Ogre::Light* light2 = mSceneMgr->createLight("Light2");
    light2->setPosition(600,5000,600);
    //  light2->setDiffuseColour(0.1,0.1,0.1);
    light2->setType(Ogre::Light::LT_POINT);
    light2->setDirection(Ogre::Vector3(0,0,0));
    //  light2->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    //light2->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    //light2->setSpotlightFalloff(1.0f);
    light2->setCastShadows(true);

    Ogre::Light* light = mSceneMgr->createLight("Light1");
    light->setPosition(-600,5000,-600);
    light->setType(Ogre::Light::LT_POINT);
    light->setDirection(Ogre::Vector3(0,0,0));
    // light2->setDiffuseColour(0.1,0.1,0.1);
    // light->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    // light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    // light->setSpotlightFalloff(1.0f);
    light->setCastShadows(true);
}

void EscenaAjedrez::createScene()
{
    // mSceneMgr = sceneMgr;


    tablero->creaTableroYCasillas(mSceneMgr);

    // tablero->creaFichasAjedrez(mSceneMgr);

    creaIluminacion();
}


void EscenaAjedrez::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    // the further the camera is, the faster it moves
    mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}

void EscenaAjedrez::setTarget(Ogre::SceneNode* target)
{
    if (target != mTarget)
    {
        mTarget = target;
        if(target)
        {
            setYawPitchDist(Ogre::Degree(90), Ogre::Degree(50), 110);
            mCamera->setAutoTracking(true, mTarget);
        }
        else
        {
            mCamera->setAutoTracking(false);
        }
    }
}


void EscenaAjedrez::setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist)
{
    mCamera->setPosition(mTarget->_getDerivedPosition());
    mCamera->setOrientation(mTarget->_getDerivedOrientation());
    mCamera->yaw(yaw);
    mCamera->pitch(-pitch);
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}

void EscenaAjedrez::rotacionCamara(Ogre::Degree angulo)
{

    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    //Mueve la camara a la posicion central
    mCamera->setPosition(mTarget->_getDerivedPosition());
    //ANGULO Ogre::Real(120.0f) * evt.timeSinceLastFrame

    //Rota la camara

    mCamera->yaw(-angulo);

    //Devuelve la camara a su posicion ¿z? original
    // mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.025f));
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));

    //return true;
}



Ogre::Camera* EscenaAjedrez::createCamera(void){
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    setTarget(mTarget ? mTarget : mCamera->getSceneManager()->getRootSceneNode());
    mCamera->setFixedYawAxis(true);

    // mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    //  mTopSpeed = topSpeed;

    return mCamera;
}


//-------------------------------------------------------------------------------------
void EscenaAjedrez::createViewports(Ogre::RenderWindow* window)
{
    mWindow = window;
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}






Ogre::RaySceneQuery* EscenaAjedrez::createRayQuery(void)
{
    // Create the camera
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    return mRaySceneQuery;
}


Ogre::RaySceneQueryResult& EscenaAjedrez::executeRay(int posx, int posy, char mascara)
{

    Ogre::uint32 mask;


    switch (mascara)
    {

    case 'C':
        mask = CASILLA;
        break;


    case 'N':
        mask =  NEGRAS;
        break;


    case 'B':
        mask = BLANCAS;
        break;

    default:
        mask = TABLERO;

        break;
    }

    Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
    return result;
}

Ogre::Ray EscenaAjedrez::setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win)
{
    Ogre::Ray rayMouse = mCamera->getCameraToViewportRay
            (posx/float(win->getWidth()), posy/float(win->getHeight()));

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);
    return (rayMouse);
}

bool EscenaAjedrez::vaIzquierda(){

    return mGoingLeft;
}

bool EscenaAjedrez::vaDerecha(){
    return mGoingRight;
}

bool EscenaAjedrez::esModoCamara()
{
    return mOrbiting;
}


void EscenaAjedrez::mueveCamaraIzquierda()
{
    mGoingLeft = true;
}

void EscenaAjedrez::mueveCamaraDerecha()
{
    mGoingRight = true;
}

void EscenaAjedrez::noMueveCamara()
{
    mGoingRight = false;
    mGoingLeft = false;
}

void EscenaAjedrez::empezarModoCamara()
{
    //mInputMan->entrarModoCamara();
    mOrbiting = true;
}

void EscenaAjedrez::acabarModoCamara()
{
    std::cout  << "acabarModoCamara " << std::endl;
    //mInputMan->salirModoCamara();
    mOrbiting = false;
}


void EscenaAjedrez::esperaJugador()
{

    modelo->mueveJugador(tablero->getTurnoNegras());


}

void EscenaAjedrez::mueveFicha()
{
    //MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
    if (tablero->fichaSeleccionada && tablero->getNodoCasillaSobrevolada()!=NULL && tablero->getNodoCasillaSobrevolada()->getNodoOgre()->getShowBoundingBox())
    {
        tablero->getNodoCasillaSobrevolada()->apagaCasilla();
        tablero->fichaSeleccionada = false;
        int resultado = static_cast<JugadorHumano*>(modelo->jugadorActual)->aplicaSeleccion(tablero->getNodoCasillaSeleccionada()->getPosicion().Fila, tablero->getNodoCasillaSeleccionada()->getPosicion().Columna,tablero->getNodoCasillaSobrevolada()->getPosicion().Fila, tablero->getNodoCasillaSobrevolada()->getPosicion().Columna);


        if (resultado == 1)
        {//FICHA MOVIDA


            tablero->actualizaTablero(tablero->getNodoCasillaSeleccionada()->getPosicion(), tablero->getNodoCasillaSobrevolada()->getPosicion());

             tablero->rotacionCamara = Ogre::Real(180.0f);
             tablero->cambiaTurno();


        }else if (resultado == 2)
        {//JAQUE MATE
            std::cout << "JAQUE EVALUADO!!"<< std::endl;
            CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueMateCEED.layout");
            CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);


        }


    }
}

bool EscenaAjedrez::seleccionaFichaEnPosicion(int posX, int posY)
{
    tablero->fichaSeleccionada = false;


    if (tablero->getNodoCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...

        Ficha* ficha = static_cast<Ficha*>(tablero->getNodoCasillaSeleccionada()->getHijo(0));
        ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setNodoCasillaSeleccionada(NULL);
    }

    //EMPIEZA RAYO
    Ogre::RaySceneQueryResult &result =executeRay(posX,posY,'C');
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();

    if (it != result.end())
    {

        //Busca la casilla que tenga un hijo con ese nombre
        Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(it->movable->getParentSceneNode()->getName()));

        if (casilla != NULL && !casilla->sinHijos())
        {
            Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

            if ((tablero->getTurnoNegras()
                 && ficha->esNegra)
                    || (!tablero->getTurnoNegras() && !ficha->esNegra))
            {

                tablero->setNodoCasillaSeleccionada(casilla);

                ficha->getNodoOgre()->showBoundingBox(true);
                tablero->fichaSeleccionada = true;
                return true;
            }

        }
    }
    return false;

}

bool EscenaAjedrez::autorizaCasillaSobrevolada(CEGUI::Vector2 mCursorPosition)
{



    if (tablero->fichaSeleccionada)
    {

        // int posx = arg.state.X.abs;   // Posicion del puntero
        //  int posy = arg.state.Y.abs;   //  en pixeles.

        Ogre::RaySceneQueryResult &result = executeRay(mCursorPosition.d_x, mCursorPosition.d_y, 'C');

        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end())
        {
            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

            Casilla* casillaSobrevolada = static_cast<Casilla*>(tablero->getHijo(nodoSobrevolado->getName()));

            Casilla* casillaSobreAnterior = tablero->getNodoCasillaSobrevolada();


            if (casillaSobreAnterior==NULL || casillaSobrevolada->getNombre() != casillaSobreAnterior-> getNombre())
            {
                if (casillaSobreAnterior!=NULL){
                    casillaSobreAnterior->apagaCasilla();
                    tablero->setNodoCasillaSobrevolada(NULL);
                }
                tablero->setNodoCasillaSobrevolada(casillaSobrevolada);


                Casilla* nodoSeleccionado = tablero->getNodoCasillaSeleccionada();

                // elTablero = miTablero;
                //   posicion seleccionado = nodoSeleccionado->getPosicion();
                // Ogre::Vector3 nuevo = nodoSobrevolado->getNodoOgre()->getPosition();



                // if(diferencia.Fila != 0)   diferencia= diferencia;
                // else diferencia= diferenciaZ;

                Ficha *mFicha = static_cast<Ficha*>(nodoSeleccionado->getHijo(0));
                tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

                //tablero->validacasilla();

                //AUTORIZA
                int resultado = static_cast<JugadorHumano*>(modelo->jugadores.at(tablero->getTurnoNegras()))->autorizaCasilla(tipo, nodoSeleccionado->getPosicion().Fila,nodoSeleccionado->getPosicion().Columna, casillaSobrevolada->getPosicion().Fila, casillaSobrevolada->getPosicion().Columna);


                //  ventanaJaque = NULL;
                if (resultado == 1)
                {
                    sobreVuelaCasilla();


                }else if (resultado == 3)
                {
                    //JAQUE
                    if (!CEGUI::WindowManager::getSingleton().isWindowPresent("Jaque"))
                    {
                        std::cout << "VENTANA YA EXISTE" << std::endl;

                        ventanaJaque = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueCEED.layout");
                        //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

                        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaJaque);
                    }else {
                        ventanaJaque = CEGUI::WindowManager::getSingleton().getWindow("Jaque");
                        ventanaJaque->setVisible(true);

                    }


                }


            }
        }




    }
}
    void EscenaAjedrez::apagaAvisos()
    {

        if (ventanaJaque != NULL && ventanaJaque->isVisible())
            ventanaJaque->setVisible(false);

    }

