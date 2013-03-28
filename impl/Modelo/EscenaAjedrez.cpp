
#include "../../headers/Modelo/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(void) :
    mRaySceneQuery(0),
    mCamera(0),
    mInputMan(0)
  , mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)
  , turnoNegras(false)
  ,  _nodoNuevo(0)
  , _selectedNode(0)
  , columnas("ABCDEFGH")
{
}
//-------------------------------------------------------------------------------------
EscenaAjedrez::~EscenaAjedrez(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);
    if (mInputMan) delete mInputMan;

}

void EscenaAjedrez::setSceneManager(Ogre::SceneManager* sceneMgr)
{
    mSceneMgr = sceneMgr;

}


Ogre::SceneNode* EscenaAjedrez::getNodoFichaSeleccionada(){
    return _selectedNode;

}

Ogre::SceneNode* EscenaAjedrez::getNodoCasillaSobrevolada(){

    return _nodoNuevo;
}


void EscenaAjedrez::setNodoFichaSeleccionada(Ogre::SceneNode* nodo)
{
    _selectedNode = nodo;

}
void EscenaAjedrez::setNodoCasillaSobrevolada(Ogre::SceneNode* nodo)
{
    _nodoNuevo = nodo;
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

    tablero = new Tablero();

    tablero->creaTableroYCasillas(mSceneMgr);

    tablero->creaFichasAjedrez(mSceneMgr);

    creaIluminacion();
}


//-------------------------------------------------------------------------------------
bool EscenaAjedrez::FichaComestible()
{

    Ogre::SceneNode* child = casillaOcupada(getNodoCasillaSobrevolada());

    //Mira si la casilla está ocupada y por quién
    // Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
    Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

    if((!esTurnoNegras() && ent->getName()[1] == 'N')
            || (esTurnoNegras() && ent->getName()[1] == 'B'))
    {
        std::cout << "ES COMESTIBLE" << std::endl;

        return true;
    }
    return false;
}

EscenaAjedrez* EscenaAjedrez::getSingletonPtr()
{
    static EscenaAjedrez miEscena;
    static EscenaAjedrez* miEscenaPtr = &miEscena;
    return miEscenaPtr;
}

void EscenaAjedrez::apagaCasilla(Ogre::SceneNode* casilla)
{
    std::cout << "APAGA CASILLA " << std::endl;

    casilla->showBoundingBox(false);
    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    if (mNombreEntidad[1] == 'B'){
        std::cout << "BLANCA " << std::endl;

        mEntidadCasilla->setMaterialName("MaterialCasillaBlanca");
    }else mEntidadCasilla->setMaterialName("MaterialCasillaNegra");
}

void EscenaAjedrez::iluminaCasilla(Ogre::SceneNode* casilla){
    casilla->showBoundingBox(true);
    Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    std::cout << "ILUMINA CASILLA " << std::endl;

    if (mNombreEntidad[1] == 'B')
    {
        std::cout << "BLANCA " << std::endl;

        mEntidadCasilla->setMaterialName("MaterialCasillaBlancaIlum");
    }else mEntidadCasilla->setMaterialName("MaterialCasillaNegraIlum");
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

void EscenaAjedrez::DistanciaCamara(int distanciaRelativa)
{
    mInputMan->distanciaCamara(distanciaRelativa);
}

bool EscenaAjedrez::esTurnoNegras(){
    std::cout << "ES TURNO NEGRAS: " << std::endl;
    std::cout <<turnoNegras << std::endl;
    std::cout << "PASA " << std::endl;

    return turnoNegras;
}

void EscenaAjedrez::cambiaTurno(){
    //CAMBIA TURNO
    turnoNegras= !turnoNegras;
}

void EscenaAjedrez::rotacionCamara(Ogre::Degree angulo)
{
    mInputMan->rotaCamara(angulo);
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

void EscenaAjedrez::acabarModoCamara()
{
    std::cout  << "acabarModoCamara " << std::endl;
    //mInputMan->salirModoCamara();
    mOrbiting = false;
}

Ogre::Camera* EscenaAjedrez::createCamera(void){
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    mInputMan->setTopSpeed(100);

    return mCamera;
}

Ogre::RaySceneQuery* EscenaAjedrez::createRayQuery(void)
{
    // Create the camera
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    return mRaySceneQuery;
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

//-------------------------------------------------------------------------------------
Ogre::SceneNode* EscenaAjedrez::casillaOcupada(Ogre::SceneNode* nodoCasilla)
{
    //Mira si la casilla está ocupada y por quién
    Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (nodoCasilla->getChild(0));
    // Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

    if(child->getAttachedObject(0) != NULL)
    {
        return child;
    }
}

Ogre::RaySceneQueryResult& EscenaAjedrez::executeRay(int posx, int posy, char mascara){

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




void EscenaAjedrez::promocionaPeon(Ogre::SceneNode* nodoFicha)
{
    Ogre::Entity *entidadFicha;

    std::stringstream saux;

    saux.str("");
    saux <<"(N)Reina 3";

    //    nodo = mSceneMgr->createSceneNode(saux.str());

    nodoFicha->detachAllObjects();

    entidadFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Reina.mesh");

    nodoFicha->attachObject(entidadFicha);
}


int* EscenaAjedrez::traduceTablero()
{

    int *casillas = new int[64];
    int numCasilla = 0;
    std::cout  <<" traducTablero 1 " << std::endl;

    std::cout  <<" nombre tablero " << std::endl;

    // std::cout  <<    tablero->nodoTablero->getName() << std::endl;


    std::cout  <<" nombre casillero " << std::endl;




    Ogre::SceneNode* nodoTest = tablero->nodoCasillero;

    std::cout  <<    nodoTest->getName() << std::endl;


    std::cout  <<" traducTablero  2" << std::endl;

    // Ogre::Node::ChildNodeIterator iterator = _nodoNuevo->getChildIterator();
    Ogre::Node::ChildNodeIterator iterator = nodoTest->getChildIterator();


    std::cout  <<iterator.hasMoreElements() << std::endl;



    std::cout  <<" ITERADOR " << std::endl;


    while (iterator.hasMoreElements()){

        std::cout  <<" ENCUETNRA ELEMENTO " << std::endl;


        Ogre::SceneNode* nodoCasillaTemporal = static_cast<Ogre::SceneNode*>(iterator.getNext());

        std::cout  <<   nodoCasillaTemporal->getName() << std::endl;
        std::cout  <<   nodoCasillaTemporal->getPosition() << std::endl;

        int numeroCasilla = (-nodoCasillaTemporal->getPosition().x/10)*8+(-nodoCasillaTemporal->getPosition().z/10);

        if (nodoCasillaTemporal->getChildIterator().hasMoreElements()){

            Ogre::SceneNode* nodoFichaTemporal =  static_cast<Ogre::SceneNode*>(nodoCasillaTemporal->getChild(0));
            std::cout  << "ENCUENTRA FICHA EN LA CASILLA: " << std::endl;
            std::cout  << nodoFichaTemporal->getName() << std::endl;
            Ogre::Entity* entidadFichaTemporal =  static_cast<Ogre::Entity*>(nodoFichaTemporal->getAttachedObject(0));
            std::cout  << "TIPO FICHA: " << std::endl;
            std::cout  << entidadFichaTemporal->getName()[4] << std::endl;

            if (entidadFichaTemporal->getName()[1] == 'N'){
                casillas[numeroCasilla] = -traduceFicha(entidadFichaTemporal->getName()[4]);

            }else  casillas[numeroCasilla] = traduceFicha(entidadFichaTemporal->getName()[4]);




          //  casillas[numCasilla] = traduceFicha(entidadFichaTemporal->getName()[4]);

        }else casillas[numeroCasilla] = 0;
        // casillas[numCasilla] = 0;
        numCasilla++;

    }


    for(int i=0; i<8;i++){
        std::cout  <<(i*8)<<"    " << (i*8)+1<<"    " << (i*8)+2<<"    "<<(i*8)+3<<"    "<<(i*8)+4<<"    "<<(i*8)+5<<"    "<<(i*8)+6<<"    "<<(i*8)+7<<std::endl;
    }

    std::cout  <<"EL RESULTADO: " << std::endl;


    for(int i=0; i<8;i++){


        std::cout  <<casillas[i*8]<<"    " << casillas[(i*8)+1]<<"    " << casillas[(i*8)+2]<<"    "<<casillas[(i*8)+3]<<"    "<<casillas[(i*8)+4]<<"    "<<casillas[(i*8)+5]<<"    "<<casillas[(i*8)+6]<<"    "<<casillas[(i*8)+7]<<std::endl;


    }

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );



    return casillas;





}



short EscenaAjedrez::traduceFicha(char tipoFicha)
{
    switch (tipoFicha)
    {
    case 'P':
    {
        return 1;
    }
    case 'C':
    {
        return 2;
    }
    case 'A':
    {
        return 3;
    }
    case 'T':
    {
        return 4;
    }
    case 'D':
    {
        return 5;
    }
    case 'R':
    {
        return 6;
    }
    default:
    {
        return 0;
    }
    }
}


//bool EscenaAjedrez::creaFichas(){

//tablero = new Tablero();

//tablero->creaFichasAjedrez();


//tablero = Tablero.
//entFicha = mSceneMgr->createEntity(nombre, nombre.append(".mesh");
//}
