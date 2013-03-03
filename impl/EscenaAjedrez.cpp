
#include "../headers/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(void)
{
}
//-------------------------------------------------------------------------------------
EscenaAjedrez::~EscenaAjedrez(void)
{

}


void EscenaAjedrez::createScene(Ogre::SceneManager* mSceneMgr)
{

    std::cout  << "EMPIEZA LA ESCENA: " << mSceneMgr->getName() <<std::endl;

    /*   mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
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

     */
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
     std::cout  << "tablero" << std::endl;
    Ogre::Entity *entTablero = this->mSceneMgr->createEntity("test12", "Tablero.mesh");
    entTablero->setQueryFlags(TABLERO);


    Ogre::SceneNode *nodo1 = this->mSceneMgr->createSceneNode("NodoTablero");

    nodo1->attachObject(entTablero);

    this->mSceneMgr->getRootSceneNode()->addChild(nodo1);

    Ogre::SceneNode *nodo2 = this->mSceneMgr->createSceneNode("NodoCasillero");
    creaCasillas(nodo2);
    creaFichas(nodo2);
    nodo1->addChild(nodo2);


    std::cout  << "ACABA LA ESCENA" << std::endl;



    // _sceneManager->getRootSceneNode()->attachObject(ent1);
    //_sceneManager->getRootSceneNode()->attachObject(ent2);
    //    _sceneManager->getRootSceneNode()->attachObject(ent3);
    /*  _sceneManager->getRootSceneNode()->attachObject(ent4);
  _sceneManager->getRootSceneNode()->attachObject(ent5);
  _sceneManager->getRootSceneNode()->attachObject(ent6);
  _sceneManager->getRootSceneNode()->attachObject(ent7);
  _sceneManager->getRootSceneNode()->attachObject(ent8);
  _sceneManager->getRootSceneNode()->attachObject(ent9);
  _sceneManager->getRootSceneNode()->attachObject(ent10);
  _sceneManager->getRootSceneNode()->attachObject(ent11);
      _sceneManager->getRootSceneNode()->attachObject(ent12);
      _sceneManager->getRootSceneNode()->attachObject(ent13);
      _sceneManager->getRootSceneNode()->attachObject(ent14);
*/




}

void EscenaAjedrez::creaFichas(Ogre::SceneNode* nodoBase)
{

    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;
    const Ogre::String columnas = "ABCDEFGH";
    Ogre::String nombreFicha;


    //CREA LAS PIEZAS DOBLES
    for (int i = 0; i < 4; ++i)
    {

        //  std::cout  << " i = " << i  << " i/2 = " << i/2 << " i%2 = " << i%2 << std::endl;

        saux.str("");
        saux <<"(T)Torre"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0){
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Torre.mesh");
            //    std::cout  << "TORRE BLANCA" << std::endl;
            mFicha->setQueryFlags(BLANCAS);
            //       mNodoFicha->translate(0,0,-70*(i/2));
            nombreFicha = columnas[7*(i/2)]+ Ogre::String("1");
        }else{
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Torre.mesh");
            //    std::cout  << "TORRE NEGRA" << std::endl;

            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[7*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);


        //   std::cout  << "AÑADE HIJO " << nombreFicha <<std::endl;
        //   std::cout  << "NOMBRE CASILLA DONDE SE VA A COLOCAR: " <<   nodoBase->getChild(nombreFicha)->getName() <<  std::endl;

        nodoBase->getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(C)Caballo"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 == 0){

            mFicha = mSceneMgr->createEntity("(B)"+ saux.str(), "Caballo.mesh");
            mFicha->setQueryFlags(BLANCAS);
            // mNodoFicha->translate(0,0,-10-50*(i/2));
            nombreFicha = columnas[1+5*(i/2)]+ Ogre::String("1");
        }else{

            mFicha = mSceneMgr->createEntity("(N)"+ saux.str(), "Caballo.mesh");
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[1+5*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoBase->getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(A)Alfil"<< Ogre::StringConverter::toString(i);

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        if (i%2 == 0){

            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Alfil.mesh");

            nombreFicha = columnas[2+3*(i/2)]+ Ogre::String("1");
            mFicha->setQueryFlags(BLANCAS);
        }else{

            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Alfil.mesh");

            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
            nombreFicha = columnas[2+3*(i/2)]+ Ogre::String("8");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoBase-> getChild(nombreFicha)->addChild(mNodoFicha);
    }

    // std::cout  << "CREA LOS PEONES "  <<std::endl;
    //CREA LOS PEONES
    for (int i = 0; i < 16; ++i)
    {
        saux.str("");
        saux <<"(P)Peon_"<< Ogre::StringConverter::toString(i);
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        if (i%2 == 0){
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Peon.mesh");
            nombreFicha = columnas[i/2]+ Ogre::String("2");
            mFicha->setQueryFlags(BLANCAS);

        }else {
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Peon.mesh");
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);

            nombreFicha = columnas[i/2]+ Ogre::String("7");
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoBase-> getChild(nombreFicha)->addChild(mNodoFicha);
    }

    //std::cout  << "CREA LAS PIEZAS UNICAS "  <<std::endl;
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
        nodoBase-> getChild(nombreFicha)->addChild(mNodoFicha);

        saux.str("");
        saux <<"(R)Rey"<< Ogre::StringConverter::toString(i);

        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 != 0){
            mFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Rey.mesh");
            mFicha->setQueryFlags(BLANCAS);
            nombreFicha = columnas[4]+ Ogre::String("1");
        }else{
            mFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Rey.mesh");
            nombreFicha = columnas[4]+ Ogre::String("8");
            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(70,0,70);
        }
        mFicha->setCastShadows(true);
        mNodoFicha->attachObject(mFicha);
        nodoBase-> getChild(nombreFicha)->addChild(mNodoFicha);

    }
}


void EscenaAjedrez::creaCasillas(Ogre::SceneNode* nodoBase)
{

    Ogre::Entity *mCasilla;
    Ogre::SceneNode *mNodoCasilla;
    int contFila = 0;
    int contColumna = 0;
    const char* columnas = "ABCDEFGH";
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
        // if (i%2 == 0){
        //       saux << "(B)" << columnas[contColumna] << Ogre::StringConverter::toString(contFila+1);
        // }  else
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
        nodoBase->addChild(mNodoCasilla);

        if (inversa) contFila--;
        else contFila++;
    }


}
