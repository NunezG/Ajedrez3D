/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
    : BaseApplication(),
      mRaySceneQuery(0),
      _selectedNode(0),
      fichaSeleccionada(false),
      _nodoNuevo(0),
      turnoNegras(0),
      textoOverlay("VACIO")
{
    std::cout << "CONTRUCTOR HIJO" << std::endl;
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{

    Ogre::Entity *entTablero = mSceneMgr->createEntity("test12", "Tablero.mesh");
    entTablero->setQueryFlags(TABLERO);


    Ogre::SceneNode *nodo1 = mSceneMgr->createSceneNode("NodoTablero");

    nodo1->attachObject(entTablero);

    mSceneMgr->getRootSceneNode()->addChild(nodo1);

    Ogre::SceneNode *nodo2 = mSceneMgr->createSceneNode("NodoCasillero");
    creaCasillas(nodo2);
    creaFichas(nodo2);
    nodo1->addChild(nodo2);






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

    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());


}

void TutorialApplication::creaFichas(Ogre::SceneNode* nodoBase){

    Ogre::Entity *mFicha;
    Ogre::SceneNode *mNodoFicha;
    std::stringstream saux;



    //CREA LAS PIEZAS DOBLES
    for (int i = 0; i < 4; ++i)
    {
        saux.str("");
        saux <<"(T)Torre"<< Ogre::StringConverter::toString(i);
        mFicha = mSceneMgr->createEntity(saux.str(), "Torre.mesh");
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 != 0){
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(0,0,70*(i/2));
        }else{

            mFicha->setQueryFlags(BLANCAS);
            mNodoFicha->translate(0,0,-70*(i/2));
        }
        mNodoFicha->attachObject(mFicha);
        nodoBase->addChild(mNodoFicha);

        saux.str("");
        saux <<"(C)Caballo"<< Ogre::StringConverter::toString(i);

        mFicha = mSceneMgr->createEntity( saux.str(), "Caballo.mesh");
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        if (i%2 != 0){
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(0,0,10+50*(i/2));
        }else{

            mFicha->setQueryFlags(BLANCAS);
            mNodoFicha->translate(0,0,-10-50*(i/2));
        }
        mNodoFicha->attachObject(mFicha);
        nodoBase->addChild(mNodoFicha);

        saux.str("");
        saux <<"(A)Alfil"<< Ogre::StringConverter::toString(i);

        mFicha = mSceneMgr->createEntity(saux.str(), "Alfil.mesh");
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());

        if (i%2 != 0){
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
          //  mNodoFicha->yaw(Ogre::Degree(180));
         //   mNodoFicha->translate(0,0,20+30*(i/2));
        }else{

            mFicha->setQueryFlags(BLANCAS);
           // mNodoFicha->translate(0,0,-20-30*(i/2));
        }
        mNodoFicha->attachObject(mFicha);
        nodoBase-> getChild(i*10)->addChild(mNodoFicha);
    }


    //CREA LOS PEONES
    for (int i = 0; i < 16; ++i)
    {
        saux.str("");
        saux <<"(P)Peon_"<< Ogre::StringConverter::toString(i);
        mFicha = mSceneMgr->createEntity(saux.str(), "Peon.mesh");
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());


        if (i%2 != 0){
            mFicha->setMaterialName("MaterialFichaNegra");
            mFicha->setQueryFlags(NEGRAS);
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(10,0,10*(i/2));
        }else {

            mFicha->setQueryFlags(BLANCAS);
            mNodoFicha->translate(-10,0,-10*(i/2));

        }
        mNodoFicha->attachObject(mFicha);
        nodoBase->addChild(mNodoFicha);
    }


    //CREA LAS PIEZAS UNICAS

    for (int i = 0; i < 2; ++i)
    {
        mFicha = mSceneMgr->createEntity("Reina"+Ogre::StringConverter::toString(i), "Reina.mesh");
        mNodoFicha = mSceneMgr->createSceneNode("(N)Reina"+Ogre::StringConverter::toString(i));
        if (i%2 != 0){
            mFicha->setQueryFlags(BLANCAS);
            mNodoFicha->translate(0,0,-40);
        }else{
            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(0,0, 30);
        }

        mNodoFicha->attachObject(mFicha);
        nodoBase->addChild(mNodoFicha);

        saux.str("");
        saux <<"(R)Rey_"<< Ogre::StringConverter::toString(i);
        mFicha = mSceneMgr->createEntity(saux.str(), "Rey.mesh");
        mNodoFicha = mSceneMgr->createSceneNode(saux.str());
        if (i%2 != 0){
            mFicha->setQueryFlags(BLANCAS);
            mNodoFicha->translate(0,0,-30);
        }else{
            mFicha->setQueryFlags(NEGRAS);
            mFicha->setMaterialName("MaterialFichaNegra");
            mNodoFicha->yaw(Ogre::Degree(180));
            mNodoFicha->translate(0,0,40);
        }
        mNodoFicha->attachObject(mFicha);
        nodoBase->addChild(mNodoFicha);
    }
}


void TutorialApplication::creaCasillas(Ogre::SceneNode* nodoBase){

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
        saux << columnas[contColumna] << Ogre::StringConverter::toString(contFila+1);
        mCasilla = mSceneMgr->createEntity(saux.str(), "Casilla.mesh");
        mCasilla->setQueryFlags(CASILLA);


        //SI ES IMPAR SE USA LA CASILLA NEGRA
        if (i%2 != 0){
            mCasilla->setMaterialName("MaterialNegro");
        }
        mNodoCasilla = mSceneMgr->createSceneNode(saux.str());
        mNodoCasilla->translate(-10*contFila,0,-10*contColumna);
        mNodoCasilla->attachObject(mCasilla);
        nodoBase->addChild(mNodoCasilla);

        if (inversa) contFila--;
        else contFila++;
    }


}


//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{



    /*
    // Setup the scene query
    Ogre::Vector3 camPos = mCamera->getPosition();
    Ogre::Ray cameraRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
    mRaySceneQuery->setRay(cameraRay);
    // Perform the scene query
    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr = result.begin();

    // Get the results, set the camera height
    if (itr != result.end() && itr->worldFragment)
    {
        Ogre::Real terrainHeight = itr->worldFragment->singleIntersection.y;
        if ((terrainHeight + 10.0f) > camPos.y)
            mCamera->setPosition( camPos.x, terrainHeight + 10.0f, camPos.z );
    }
*/



    // Gestion del overlay ---------------------------------------------
    Ogre::OverlayElement *oe;

    //  oe = mOverlayManager->getOverlayElement("fpsInfo");
    //  oe->setCaption(Ogre::StringConverter::toString(fps));
    mOverlayManager-> hasOverlayElement("objectInfo");
    oe = mOverlayManager->getOverlayElement("objectInfo");


    oe->setCaption(textoOverlay);
    mDetailsPanel->setParamValue(7, textoOverlay);


    return  BaseApplication::frameRenderingQueued(evt);




}


Ogre::Ray TutorialApplication::setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win) {


    Ogre::Ray rayMouse = mCamera->getCameraToViewportRay
            (posx/float(win->getWidth()), posy/float(win->getHeight()));


    mRaySceneQuery->setRay(rayMouse);

    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);
    return (rayMouse);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
        return true;
    }


    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }


    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPLEFT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }




    return BaseApplication::keyPressed( arg );
}


bool TutorialApplication::keyReleased( const OIS::KeyEvent &arg )
{

    return BaseApplication::keyReleased( arg );

}




bool TutorialApplication::mouseMoved( const OIS::MouseEvent &arg )
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

            if (_nodoNuevo==NULL || it->movable->getParentSceneNode()->getName() != _nodoNuevo->getName()){

                //AÑADE EL NOMBRE A LA PANTALLA
                textoOverlay = it->movable->getParentSceneNode()->getName();


                bool autorizado;
                if (_nodoNuevo!=NULL){
                    autorizado= false;
                    _nodoNuevo->showBoundingBox(false);
                }

                _nodoNuevo = it->movable->getParentSceneNode();
                Ogre::Vector3 seleccionado = _selectedNode->getPosition();
                Ogre::Vector3 nuevo = _nodoNuevo->getPosition();

                int x = _nodoNuevo->getPosition().x-_selectedNode->getPosition().x;
                int z = _nodoNuevo->getPosition().z-_selectedNode->getPosition().z;

/*
                 std::cout << "posicion del nodo sobevolado 1: "<< nuevo <<std::endl;
                 std::cout << "posicion del nodo seleccionadov 1: "<< seleccionado <<std::endl;
                 std::cout <<"Diferencia: "<< diferencia <<std::endl;
                 */
                if (turnoNegras) {

                    nuevo = -Ogre::Vector3(70,0,70)-_nodoNuevo->getPosition();
                       seleccionado = -seleccionado;
                     std::cout << "posicion del nodo SOBREVOLADO DESPUES de cambiar: "<< nuevo <<std::endl;

               }
                Ogre::Vector3 diferencia = nuevo-seleccionado;

             const Ogre::String mNombreUsado =  _selectedNode->getName();

                std::cout << "NOmbre NODO usado" << mNombreUsado << "diferencia" << diferencia<<std::endl;

                switch (mNombreUsado[1]){
                case 'R':
                    std::cout << "CASE REY" << std::endl;
                    if ((diferencia.x==10||diferencia.x==-10||diferencia.x==0) && (diferencia.z==10||diferencia.z==-10||diferencia.z==0)){
                       std::cout << "ESTA AUTORIZADO!!!" << std::endl;
                        _nodoNuevo->scale(0.5,0,0.5 );
                        autorizado= true;
                    }

                    break;

                case 'N': if (diferencia.z==0||diferencia.x==0||diferencia.z-diferencia.x==0||diferencia.x-diferencia.z==0||diferencia.x+diferencia.z==0||diferencia.z+diferencia.x==0){
                        std::cout << "ESTA AUTORIZADO!!!" << std::endl;
                        _nodoNuevo->scale(0.5,0,0.5);
                        autorizado= true;
                    }
                    break;

                case 'A':
                    if (diferencia.z-diferencia.x==0||diferencia.x-diferencia.z==0||diferencia.x+diferencia.z==0||diferencia.z+diferencia.x==0){
                                            _nodoNuevo->scale(0.5,0,0.5);
                                            autorizado= true;
                                        }

                    break;

                case 'T':
                    if (diferencia.z==0||diferencia.x==0){
                                            _nodoNuevo->scale(0.5,0,0.5);
                                            autorizado= true;
                                        }

                    break;

                case 'C':
                    if (diferencia==Ogre::Vector3(-20,0,10) || diferencia==Ogre::Vector3(20,0,10) || diferencia==Ogre::Vector3(-20,0,-10) || diferencia==Ogre::Vector3(20,0,-10) || diferencia==Ogre::Vector3(10,0,20)
                            || diferencia==Ogre::Vector3(10,0,-20) || diferencia==Ogre::Vector3(-10,0,20) || diferencia==Ogre::Vector3(-10,0,-20)){
                                            _nodoNuevo->scale(0.5,0,0.5);
                                            autorizado= true;
                                        }

                    break;

                case 'P':
                    std::cout << "ENTRA EN EL SWITCH DE PEON" << std::endl;
                    if (diferencia==Ogre::Vector3(-10,0,0) || (diferencia==Ogre::Vector3(-20,0,0) && _selectedNode->getPosition().x == 0)){
                        _nodoNuevo->scale(0.5,0,0.5);
                        std::cout << "ESTA AUTORIZADO" << std::endl;
                        autorizado= true;
                    }

                    break;


                default:
                    true;

                }

                if (autorizado){
                    _nodoNuevo=it->movable->getParentSceneNode();
                    _nodoNuevo->showBoundingBox(true);

                }

            }
        }
    }

    return BaseApplication::mouseMoved( arg );
}


bool TutorialApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    bool mbleft = (id == OIS::MB_Left);
    bool mbright = (id == OIS::MB_Right);
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    Ogre::uint32 mask;

    if (mbleft) {  // Boton izquierdo o derecho -------------

        if (turnoNegras) {
            mask = NEGRAS;  // Podemos elegir todo
        } else mask =BLANCAS;

        if (_selectedNode != NULL) {  // Si habia alguno seleccionado...

            _selectedNode->showBoundingBox(false);  _selectedNode = NULL;
            fichaSeleccionada = false;
        }

    //    std::cout << "EMPIEZA RAYO" << std::endl;

        Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();
  //      std::cout << "RESULTADO" << std::endl;

        if (it != result.end()) {
            /*    if (mbleft) {
                  if (it->movable->getParentSceneNode()->getName() == "Col_Suelo") {
                    Ogre::SceneNode *nodeaux = mSceneMgr->createSceneNode();
                    int i = rand()%2;   std::stringstream saux;
                    saux << "Cube" << i+1 << ".mesh";
                    Ogre::Entity *entaux = mSceneMgr->createEntity(saux.str());
                    entaux->setQueryFlags(i?CUBE1:CUBE2);
                    nodeaux->attachObject(entaux);
                    nodeaux->translate(r.getPoint(it->distance));
                    mSceneMgr->getRootSceneNode()->addChild(nodeaux);
                }
            }*/
            if (it->movable->getParentSceneNode()->getName().size()>2) {

   //             std::cout << "HA DETECTADO UNA FICHA" << std::endl;
                _selectedNode = it->movable->getParentSceneNode();
                _selectedNode->showBoundingBox(true);
                fichaSeleccionada = true;
            }
        }

    } else if (mbright){
        if (_selectedNode != NULL && _nodoNuevo!=NULL) {  // Si habia alguno seleccionado...

            _selectedNode->showBoundingBox(false);
            fichaSeleccionada = false;

            /*


            std::cout << "EMPIEZA RAYO" << std::endl;

            Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
            Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
            Ogre::RaySceneQueryResult::iterator it;
            it = result.begin();
            std::cout << "RESULTADO" << std::endl;

            while (it != result.end()) {



                std::cout << "ITERADOR: " << it->movable->getParentSceneNode()->getName() << std::endl;
                std::cout << "TAMAÑO: " << it->movable->getParentSceneNode()->getName().size() << std::endl;

                if (it->movable->getParentSceneNode()->getName().size()==2){
                    _nodoNuevo = it->movable->getParentSceneNode();
                    break;

                }else it++;


            }

            */



     //       std::cout << "SALE DEL ITERADOR: "  << std::endl;
            /*

                Ogre::SceneNode::ObjectIterator it2 = _nodoNuevo->getAttachedObjectIterator();
                while (it2.hasMoreElements()){
          //    const Ogre::Entity entidadDePrueba =  _nodoNuevo->getAttachedObjectIterator().getNext();
                    Ogre::Entity* entity = static_cast<Ogre::Entity*>(it2.getNext());

                 std::cout << "ENTIDAD DE PRUEBA: " <<  entity->getName()<< std::endl;
                }

*/

            _nodoNuevo->showBoundingBox(true);
    //        std::cout <<  _nodoNuevo->getName() << std::endl;





            //  Ogre::Node::TransformSpace relativeTo = Ogre::Node::TransformSpace.TS_WORLD;




            int contFila = 0;
            int contColumna = 0;



            // String nombreNodo;

            //  _nodoNuevo->getName()[0];


            // const std::basic_string miputostring=  _nodoNuevo->getName().c_str();


            Ogre::Vector3 vector;

            if (turnoNegras){
                vector = Ogre::Vector3(70,0,70)+_nodoNuevo->getPosition();
            }else vector =_nodoNuevo->getPosition();
            _selectedNode->getParent()->removeChild(_selectedNode);
             _nodoNuevo->addChild(_selectedNode);
         //   _selectedNode->setPosition(vector);
            turnoNegras= !turnoNegras;
    //        std::cout << "NUEVA POS"<< _selectedNode->getPosition() << std::endl;
            //_selectedNode->translate(_nodoNuevo->getPosition(),_selectedNode->TS_WORLD);




            //  _selectedNode = NULL;
        }

        /*   std::cout << "Boton Derecho" << std::endl;
        mask = ~STAGE;   // Seleccionamos todo menos el escenario
        std::cout << "FIN Boton Derecho" << std::endl;
       */



    }

    return BaseApplication::mousePressed( arg , id);

}




bool TutorialApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return BaseApplication::mouseReleased( arg, id );
}



int TutorialApplication::traduceCoordenadas(Ogre::String coord){
    const Ogre::String columnas = "ABCDEFGH";

    Ogre::String nombrechungNodo = _nodoNuevo->getName();
  //  std::cout << "nombreNodo"<<nombrechungNodo << std::endl;
  //  std::cout << "PRIMERA CASILLA"<<nombrechungNodo[0] << std::endl;
 //   std::cout << "SEGUNDA CASILLA"<<nombrechungNodo[1] << std::endl;


    Ogre::String::size_type loc = columnas.find(coord[0],0);
    if( loc != Ogre::String::npos ) {
   //     std::cout << "LETRA ENCONTRADA EN POSICION: " << loc << std::endl;

        int t = 45;

    } else {
  //      std::cout << "Didn't find Omega" << std::endl;
    }


    return loc;


}


int TutorialApplication::muevePeon(Ogre::String coord){
    if (turnoNegras){
        //  _selectedNode->
        // _nodoNuevo
        // coord
    }


}




#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
{
    // Create application object
    TutorialApplication app;

    try {
        std::cout << "GO" << std::endl;
        app.go();
    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " <<
                     e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
