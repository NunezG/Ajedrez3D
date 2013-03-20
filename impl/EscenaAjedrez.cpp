
#include "../headers/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(void) :
    columnas("ABCDEFGH"),
    mRaySceneQuery(0),
    mCamera(0),
    mInputMan(0)
  , mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)
  , turnoNegras(0)
  ,  _nodoNuevo(0)
 , _selectedNode(0)


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


void EscenaAjedrez::createScene(Ogre::SceneManager* mSceneMgr)
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


    this->mSceneMgr = mSceneMgr;
    Ogre::Entity *entTablero = this->mSceneMgr->createEntity("test12", "Tablero.mesh");
    entTablero->setQueryFlags(TABLERO);

    nodoTablero = this->mSceneMgr->createSceneNode("NodoTablero");

    nodoTablero->attachObject(entTablero);

    this->mSceneMgr->getRootSceneNode()->addChild(nodoTablero);

    nodoCasillero = this->mSceneMgr->createSceneNode("NodoCasillero");

    creaCasillas();
    creaFichas();

    nodoTablero->addChild(nodoCasillero);
}

void EscenaAjedrez::creaFichas()
{
    creaVasallos();
    creaPeones();
    creaNobleza();
}

void EscenaAjedrez::iluminaCasilla()
{


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
        return true;
    }
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




void EscenaAjedrez::mueveCamaraIzquierda(){

    mGoingLeft = true;



}



void EscenaAjedrez::mueveCamaraDerecha(){

    mGoingRight = true;





}

void EscenaAjedrez::noMueveCamara(){
    mGoingRight = false;
    mGoingLeft = false;

}



void EscenaAjedrez::empezarModoCamara()
{
    std::cout  << "empezarModoCamara " << std::endl;

    //mInputMan->entrarModoCamara();

    mOrbiting = true;




}
void EscenaAjedrez::DistanciaCamara(int distanciaRelativa)
{

    mInputMan->distanciaCamara(distanciaRelativa);


}

bool EscenaAjedrez::esTurnoNegras(){
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

    if(child->getAttachedObject(0) != NULL){
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

void EscenaAjedrez::creaVasallos(){
    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    Ogre::String nombreFicha;

    //CREA LAS PIEZAS DOBLES
    for (int i = 0; i < 4; ++i)
    {
        saux.str("");
        saux <<"(T)Torre"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Torre.mesh");
            mFicha->setQueryFlags(BLANCAS);
            // mFicha->setMaterialName("MaterialFichaBlanca");

            //       mNodoFicha->translate(0,0,-70*(i/2));
            nombreFicha = columnas[7*(i/2)]+ Ogre::String("1");
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Torre.mesh");

            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[7*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);

        nodoCasillero->getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(C)Caballo"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+ saux.str(), "Caballo.mesh");
            mFicha->setQueryFlags(BLANCAS);
            // mNodoFicha->translate(0,0,-10-50*(i/2));
            nombreFicha = columnas[1+5*(i/2)]+ Ogre::String("1");
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+ saux.str(), "Caballo.mesh");
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[1+5*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero->getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(A)Alfil"<< Ogre::StringConverter::toString(i);

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Alfil.mesh");

            nombreFicha = columnas[2+3*(i/2)]+ Ogre::String("1");
            mFicha->setQueryFlags(BLANCAS);
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Alfil.mesh");

            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[2+3*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero-> getChild(nombreFicha)->addChild(mNodoFicha);
    }
}

void EscenaAjedrez::creaNobleza(){

    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    Ogre::String nombreFicha;


    //CREA LAS PIEZAS UNICAS
    for (int i = 0; i < 2; ++i)
    {
        saux.str("");
        saux <<"(N)Reina"<< Ogre::StringConverter::toString(i);

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0){
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Reina.mesh");
            mFicha->setQueryFlags(BLANCAS);
            nombreFicha = columnas[3]+ Ogre::String("1");
        }else{
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Reina.mesh");
            nombreFicha = columnas[3]+ Ogre::String("8");

            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero-> getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(R)Rey"<< Ogre::StringConverter::toString(i);

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 != 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Rey.mesh");
            mFicha->setQueryFlags(BLANCAS);
            nombreFicha = columnas[4]+ Ogre::String("1");
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Rey.mesh");
            nombreFicha = columnas[4]+ Ogre::String("8");
            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero-> getChild(nombreFicha)->addChild(mNodoFicha);
    }


}

void EscenaAjedrez::creaPeones(){

    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    Ogre::String nombreFicha;


    //CREA LOS PEONES
    for (int i = 0; i < 16; ++i)
    {
        saux.str("");
        saux <<"(P)Peon_"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        if (i%2 == 0)
        {
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Peon.mesh");
            nombreFicha = columnas[i/2]+ Ogre::String("2");
            mFicha->setQueryFlags(BLANCAS);
        }
        else
        {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Peon.mesh");
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);

            nombreFicha = columnas[i/2]+ Ogre::String("7");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoCasillero -> getChild(nombreFicha)->addChild(mNodoFicha);
    }


}


void EscenaAjedrez::creaCasillas()
{
    Ogre::Entity *mCasilla;
    Ogre::SceneNode *mNodoCasilla;
    int contFila = 0;
    int contColumna = 0;
    //const char* columnas = "ABCDEFGH";
    bool inversa = false;
    std::stringstream saux;

    for (int i = 0; i < 64; ++i)
    {
        if (inversa){
            if (contFila < 0){
                contColumna++;
                contFila = 0;
                inversa = !inversa;
            }
        }else{
            if (contFila == 8){
                contColumna++;
                contFila = 7;
                inversa = !inversa;
            }
        }
        saux.str("");
        saux << columnas[contColumna] << Ogre::StringConverter::toString(contFila+1);

        //SI ES PAR SE USA LA CASILLA NEGRA
        if (i%2 == 0){
            mCasilla = mSceneMgr->createEntity("(N)"+saux.str(), "Casilla.mesh");
            mCasilla->setMaterialName("MaterialCasillaNegra");
        }else mCasilla = mSceneMgr->createEntity("(B)"+saux.str(), "Casilla.mesh");
        mCasilla->setQueryFlags(CASILLA);

        mNodoCasilla = mSceneMgr->createSceneNode(saux.str());
        mNodoCasilla->translate(-10*contFila,0,-10*contColumna);
        mNodoCasilla->attachObject(mCasilla);
        //std::cout  << "AÑADE CASILLA " << mCasilla->getName() << std::endl;
        nodoCasillero->addChild(mNodoCasilla);

        if (inversa) contFila--;
        else contFila++;
    }
}
