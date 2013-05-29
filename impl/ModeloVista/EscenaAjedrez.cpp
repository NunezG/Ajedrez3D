
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
  , ventanaEmergente(NULL)
  ,tableroModelo(NULL)


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


void EscenaAjedrez::sobreVuelaCasilla()
{


    //  miTablero->getNodoCasillaSobrevolada()->seleccionada = false;
}


void EscenaAjedrez::setSceneManager()
{


    mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "MANAGER");
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

    //  std::cout << "espera"<<std::endl;
    // std::cout << "jugadores.size()"<< modelo->jugadores.size()<<std::endl;

    if (tableroModelo == NULL)
    {

        std::cout << "NUEVO TABLERO QUE CORRESPONDE CON CAMBIO DE TURNO"<<std::endl;

        apagaLayout();
        tableroModelo = new ModeloTablero();

        tableroModelo->casillasInt = tablero->traduceTablero();

        tableroModelo->alPaso = tablero->getAlPaso();

        tableroModelo->turnoN = tablero->getTurnoNegras();


        std::cout << "NTURNO: "<< tableroModelo->turnoN <<std::endl;


      //  if (tableroModelo->turnoN)
      //     casillas = Calculos::normalizaTablero(casillas);


      //  tableroModelo->jugada = new int[2];
       // tableroModelo->jugada[0] = -1;
    }



    if (modelo->jugadores.size() == 2)
    {


        Jugador* jugador = modelo->jugadores.at(tableroModelo->turnoN);
        if(jugador != NULL)
        {
           //  std::cout  << "mueveficha " << std::endl;

            /* tableroModelo = */jugador->mueveFicha(tableroModelo);

         //   std::cout  << "miramov " << std::endl;


            //HAY RESULTADO
            if(tableroModelo->jugada[0] != -1)
            {

                std::cout  << "HA DETECTADO UN MOVIMIENTO EN EL BUCLE!!! " << std::endl;


                aplicaCambio();
                //  tableroModelo->movimiento[0] = -99;
                // std::cout  << "BORRA tablromov" << std::endl;

                delete tableroModelo;
                //  std::cout  << "nullea tablromov" << std::endl;

                tableroModelo = NULL;
                //  std::cout  << "ACABA EL MOV!!! " << std::endl;

            }



            //  Casilla



            // tablero->setNodoCasillaSeleccionada();
            // tablero->setNodoCasillaSobrevolada();
            //  tablero->actualizaTablero();

        }
    }

    //MIRA LAS DIFERENCIAS:





    //  std::cout  << "finespera " << std::endl;

    //   modelo->mueveJugador(tablero->getTurnoNegras());


}


//bool EscenaAjedrez::mueveTableroEscena()
//{
//MUEVEFICHA SI ESTA PERMITIDO (showboundingbox = true)
//if (tablero->fichaSeleccionada && tablero->getNodoCasillaSobrevolada()!=NULL && tablero->getNodoCasillaSobrevolada()->getNodoOgre()->getShowBoundingBox())
//   {
// bool resultado = escenaAjedrez->aplicaCambio();


//  modelo->jugadores.at(tablero->getTurnoNegras())->

//    }

//}





bool EscenaAjedrez::aplicaCambio()
{
    std::cout << "APLICA YA EL MOVIMIENTO DEFINITIVO" << std::endl;

    if (tablero->getNodoCasillaSobrevolada() != NULL)
        tablero->getNodoCasillaSobrevolada()->apagaCasilla();

    tablero->fichaSeleccionada = false;

    // ModeloTablero* tableroModelo = new ModeloTablero();

    //  tableroModelo->casillasInt = tablero->traduceTablero();

    //  tableroModelo->alPaso = tablero->getAlPaso();

    //  tableroModelo->turnoN = tablero->getTurnoNegras();

    int filaSel;
    int colSel;

    int filaNueva;
    int colNueva;

    /* if (tableroModelo->movimiento == NULL)
    {

        filaSel=tablero->getNodoCasillaSeleccionada()->getPosicion().Fila;

        colSel = tablero->getNodoCasillaSeleccionada()->getPosicion().Columna;

        filaNueva = tablero->getNodoCasillaSobrevolada()->getPosicion().Fila;

        colNueva = tablero->getNodoCasillaSobrevolada()->getPosicion().Columna;

    }else
    {*/
    std::cout << "tableroModelo->jugada[0] " << tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << tableroModelo->jugada[1]<< std::endl;

    filaSel = (tableroModelo->jugada[0]/12)-2;




    colSel = (tableroModelo->jugada[0]%12)-2;

    filaNueva = (tableroModelo->jugada[1]/12)-2;

    colNueva = (tableroModelo->jugada[1]%12)-2;

    std::cout << " ficha que se va a mover: " <<tableroModelo->casillasInt[tableroModelo->jugada[0]]<< std::endl;


    // }

    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    int resultado = static_cast<JugadorHumano*>(modelo->jugadores.at(tablero->getTurnoNegras()))-> aplicaSeleccion(tableroModelo, filaSel, colSel, filaNueva, colNueva);
    std::cout << "ACTUALIZA TABLERO1" << std::endl;

    //  delete tableroModelo;



    //JUGADOR ARTIFICIAL
    if (tablero->getNodoCasillaSeleccionada() == NULL)
    {


        std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
        std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;



        std::cout << "SELECT 1 FILA: "<< (filaSel*8)+colSel <<std::endl;



        tablero->setNodoCasillaSeleccionada((filaSel * 8) + colSel);


        std::cout << "nombre: "<< tablero->getNodoCasillaSeleccionada()->getNombre()<<std::endl;

    //    seleccionaFichaEnPosicion(filaSel, colSel);


        std::cout << "SELECT 2 FILA: "<< (filaNueva * 8) + colNueva <<std::endl;


        tablero->setNodoCasillaSobrevolada((filaNueva * 8) + colNueva);

        std::cout << "nombre: "<< tablero->getNodoCasillaSobrevolada()->getNombre()<<std::endl;


        //tablero->setNodoCasillaSobrevolada(seleccionaCasillaEnPosicion(filaNueva, colNueva));
    }
    std::cout << "ACTUALIZA TABLERO2" << std::endl;


    tablero->actualizaTablero();

    if (resultado == 1 || resultado == 4)
    {//FICHA MOVIDA

        if (resultado == 4)
        {//JAQUE AL REY
            //JAQUE
            if (!CEGUI::WindowManager::getSingleton().isWindowPresent("Jaque"))
            {
                std::cout << "JAQUE AL APLICAR CAMBIO" << std::endl;

                ventanaEmergente = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueCEED.layout");
                //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

                CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaEmergente);
            }else
            {
                ventanaEmergente = CEGUI::WindowManager::getSingleton().getWindow("Jaque");
                ventanaEmergente->setVisible(true);
            }
        }

        //   tablero->actualizaTablero();

        tablero->rotacionCamara = Ogre::Real(180.0f);
        std::cout << "cambia turno" << std::endl;

        tablero->cambiaTurno();
        std::cout << "sale" << std::endl;

        return true;

    }
    else if (resultado == 2)
    {//JAQUE MATE
        std::cout << "JAQUE EVALUADO!!"<< std::endl;
        CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueMateCEED.layout");
        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);

        return false;

    }else if (resultado == 3)
    {
        //REY AHOGADO (TABLAS)
        std::cout << "REY AHOGADO (TABLAS)!!"<< std::endl;

        ventanaEmergente = CEGUI::WindowManager::getSingleton().loadWindowLayout("TablasCEED.layout");
        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaEmergente);
    }



    return false;
}

void EscenaAjedrez::muestraLayout(std::string nombreLayout)
{

    ventanaEmergente = CEGUI::WindowManager::getSingleton().getWindow(nombreLayout);
    ventanaEmergente->setVisible(true);


}


bool EscenaAjedrez::seleccionaFichaEnPosicion(int posX, int posY)
{

    std::cout << "SELECCIONA FICHA "<<std::endl;

    tablero->fichaSeleccionada = false;

    if (tablero->getNodoCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...

        Ficha* ficha = static_cast<Ficha*>(tablero->getNodoCasillaSeleccionada()->getHijo(0));
        ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setNodoCasillaSeleccionada(-1);
    }

    std::cout << "SELECCIONA FICHA  2"<<std::endl;

    Casilla* casilla = seleccionaCasillaEnPosicion(posX, posY);
    std::cout << "SELECCIONA FICHA 3 "<<std::endl;


    if (casilla != NULL && !casilla->sinHijos())
    {

        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));


        std::cout << "SELECCIONA FICHA INTERIOR 1"<<std::endl;


        if ((tablero->getTurnoNegras()
             && ficha->esNegra)
                || (!tablero->getTurnoNegras() && !ficha->esNegra))
        {

            std::cout << "SELECCIONA FICHA INTERIOR 2"<<std::endl;

            tablero->setNodoCasillaSeleccionada(casilla);

            ficha->getNodoOgre()->showBoundingBox(true);
            tablero->fichaSeleccionada = true;
            return true;
        }
        std::cout << "SALE SELECCIONA FICHA INTERIOR "<<std::endl;

    }
    std::cout << "SELECCIONA FICHA 4 "<<std::endl;


    return false;
}



Casilla* EscenaAjedrez::seleccionaCasillaEnPosicion(int posX, int posY)
{

    //EMPIEZA RAYO
    Ogre::RaySceneQueryResult &result =executeRay(posX,posY,'C');
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();

    if (it != result.end())
    {
        //Busca la casilla que tenga ese nombre
        return static_cast<Casilla*>(tablero->getHijo(it->movable->getParentSceneNode()->getName()));

    }
    // return false;
}

bool EscenaAjedrez::autorizaCasillaSobrevolada(CEGUI::Vector2 mCursorPosition)
{



    if (tablero->fichaSeleccionada)
    {

        // escenaAjedrez->apagaAvisos();

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
            apagaLayout();


            if (casillaSobreAnterior==NULL || casillaSobrevolada->getNombre() != casillaSobreAnterior-> getNombre())
            {
                if (casillaSobreAnterior!=NULL)
                {
                    casillaSobreAnterior->apagaCasilla();
                    tablero->setNodoCasillaSobrevolada(-1);
                }


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
                int resultado = static_cast<JugadorHumano*>(modelo->jugadores.at(tablero->getTurnoNegras()))->autorizaCasilla(tablero->traduceTablero(),tipo, nodoSeleccionado->getPosicion().Fila,nodoSeleccionado->getPosicion().Columna, casillaSobrevolada->getPosicion().Fila, casillaSobrevolada->getPosicion().Columna, tablero->getTurnoNegras(), tablero->getAlPaso());

                //  ventanaEmergente = NULL;
                if (resultado == 1)
                {
                    tablero->setNodoCasillaSobrevolada(casillaSobrevolada);
                    tablero->getNodoCasillaSobrevolada()->iluminaCasilla();
                }
                else if (resultado == 3)
                {
                    //JAQUE
                    if (!CEGUI::WindowManager::getSingleton().isWindowPresent("Jaque"))
                    {
                        std::cout << "JAQUE AL SOBREVOLAR CASILLA" << std::endl;

                        ventanaEmergente = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueCEED.layout");
                        //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

                        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaEmergente);
                    }else
                    {
                        ventanaEmergente = CEGUI::WindowManager::getSingleton().getWindow("Jaque");
                        ventanaEmergente->setVisible(true);
                    }
                }
            }
        }
    }
}


void EscenaAjedrez::apagaLayout()
{

    //CEGUI::System::getSingleton().getGUISheet()->cleanupChildren();


    if (ventanaEmergente != NULL && ventanaEmergente->isVisible())
    {
        //   std::cout << "apagaavisos dentro"<< std::endl;

        ventanaEmergente->setVisible(false);

    }


}

