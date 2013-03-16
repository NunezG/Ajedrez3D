
#include "../headers/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(void) : columnas("ABCDEFGH")
{
}
//-------------------------------------------------------------------------------------
EscenaAjedrez::~EscenaAjedrez(void)
{    
}

void EscenaAjedrez::createScene(Ogre::SceneManager* mSceneMgr)
{
       mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
      mSceneMgr->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5) );
      mSceneMgr->setAmbientLight(Ogre::ColourValue(0.9, 0.9, 0.9));

      mSceneMgr->setShadowTextureCount(2);
      mSceneMgr->setShadowTextureSize(512);

      Ogre::Light* light2 = mSceneMgr->createLight("Light2");
      light2->setPosition(65,35,55);
     // light2->setDiffuseColour(0.9,0.9,0.9);
      light2->setType(Ogre::Light::LT_SPOTLIGHT);
      light2->setDirection(Ogre::Vector3(-4,-1,-4));
      light2->setSpotlightInnerAngle(Ogre::Degree(30.0f));
      light2->setSpotlightOuterAngle(Ogre::Degree(60.0f));
      light2->setSpotlightFalloff(0.1f);
      light2->setCastShadows(true);


    /*
      Ogre::Light* light = mSceneMgr->createLight("Light1");
      light->setPosition(20,15,-20);
      light->setType(Ogre::Light::LT_SPOTLIGHT);
      light->setDirection(Ogre::Vector3(1,-1,0));
      light->setSpotlightInnerAngle(Ogre::Degree(25.0f));
      light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
      light->setSpotlightFalloff(0.8f);
      light->setCastShadows(true);
*/

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
            mCasilla->setMaterialName("MaterialNegro");
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
