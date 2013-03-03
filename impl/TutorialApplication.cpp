
#include "../headers/TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mWindow)
    : BaseApplication(mSceneMgr),
      _selectedNode(0),
      fichaSeleccionada(false),
      _nodoNuevo(0),
      turnoNegras(0),
      textoOverlay("VACIO"),
      mWindow(mWindow)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
    if (mInputMan) delete mInputMan;

}







void TutorialApplication::createGUI(void){


    std::cout << "CREATEGUI!!!!!!!!!!!!!! "<<std::endl;
}










//-------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------
bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg )
{
    // if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up


    /*
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mOutputDebugPanel->getParamValue(9).asUTF8()[0])
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
        mOutputDebugPanel->setParamValue(9, newVal);
    }


    */


    mInputMan->injectKeyDown(arg);



    return BaseApplication::keyPressed( arg );
}


bool TutorialApplication::keyReleased( const OIS::KeyEvent &arg )
{

    return BaseApplication::keyReleased( arg );

}



//-------------------------------------------------------------------------------------
void TutorialApplication::createViewports(void)
{
    std::cout << "createViewports "<<std::endl;

    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}





bool TutorialApplication::mouseMoved( const OIS::MouseEvent &arg ){





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
                Ogre::Vector3 seleccionado = _selectedNode->getParent()->getPosition();
                Ogre::Vector3 nuevo = nodoSobrevolado->getPosition();

                //AÑADE EL NOMBRE DE LA CASILLA AL OVERLAY
                textoOverlay = nodoSobrevolado->getName();

                Ogre::Vector3 diferencia= nuevo-seleccionado;
                const Ogre::String mNombreUsado =  _selectedNode->getName();
                bool autorizado= true;

                /*    std::cout << "posicion del nodo sobevolado: "<< nuevo <<std::endl;
                    std::cout << "posicion del nodo seleccionado: "<< seleccionado <<std::endl;
                    std::cout << "diferencia: "<< diferencia <<std::endl;
*/

                switch (mNombreUsado[1]){
                case 'R': //REY SELECCIONADO

                    if ((diferencia.x==10||diferencia.x==-10||diferencia.x==0)
                            && (diferencia.z==10||diferencia.z==-10||diferencia.z==0)){

                        autorizado= true;

                    }else autorizado= false;

                    break;

                case 'N': //REINA SELECCIONADO

                    if (diferencia.z==0
                            && diferencia.x < 0 ){

                        //MOVIMIENTO A LA DERECHA
                        autorizado = Movimientos::caminoDerecha(diferencia, _nodoNuevo);

                    }else if (diferencia.z==0
                              && diferencia.x > 0 ){

                        //MOVIMIENTO A LA IZQUIERDA
                        autorizado = Movimientos::caminoIzquierda(diferencia, _nodoNuevo);

                    }  else if (diferencia.x==0
                                && diferencia.z > 0 ){

                        //MOVIMIENTO ARRIBA
                        autorizado = Movimientos::caminoArriba(diferencia, _nodoNuevo);

                    }  else if (diferencia.x==0
                                && diferencia.z < 0 ){

                        //MOVIMIENTO ABAJO
                        autorizado = Movimientos::caminoAbajo(diferencia, _nodoNuevo);

                    }else  if (diferencia.z - diferencia.x == 0
                               && diferencia.z > 0){

                        //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES
                        autorizado = Movimientos::caminoDiagArrIzq(diferencia, _nodoNuevo);

                    }else if (diferencia.z + diferencia.x == 0
                              && diferencia.z > 0){

                        //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES
                        autorizado = Movimientos::caminoDiagArrDer(diferencia, _nodoNuevo);

                    }else if(diferencia.z + diferencia.x == 0
                             && diferencia.z < 0){

                        //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES
                        autorizado = Movimientos::caminoDiagAbIzq(diferencia, _nodoNuevo);

                    }else if(diferencia.z - diferencia.x == 0
                             && diferencia.z < 0){

                        //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES
                        autorizado = Movimientos::caminoDiagAbDer(diferencia, _nodoNuevo);

                    }else autorizado= false;

                    break;

                case 'A': //ALFIL SELECCIONADO

                    if (diferencia.z - diferencia.x == 0
                            && diferencia.z > 0){

                        //LETRAS DESCENDENTES Y NUMEROS DESCENDENTES
                        autorizado = Movimientos::caminoDiagArrIzq(diferencia, _nodoNuevo);

                    }else if (diferencia.z + diferencia.x == 0
                              && diferencia.z > 0){

                        //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES
                        autorizado = Movimientos::caminoDiagArrDer(diferencia, _nodoNuevo);

                    }else if(diferencia.z + diferencia.x == 0
                             && diferencia.z < 0){

                        //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES
                        autorizado = Movimientos::caminoDiagAbIzq(diferencia, _nodoNuevo);

                    }else if(diferencia.z - diferencia.x == 0
                             && diferencia.z < 0){

                        //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES
                        autorizado = Movimientos::caminoDiagAbDer(diferencia, _nodoNuevo);

                    }else autorizado= false;

                    break;

                case 'T': //TORRE SELECCIONADA

                    if (diferencia.z==0
                            && diferencia.x < 0 ){

                        //MOVIMIENTO A LA DERECHA
                        autorizado = Movimientos::caminoDerecha(diferencia, _nodoNuevo);

                    }else if (diferencia.z==0
                              && diferencia.x > 0 ){

                        //MOVIMIENTO A LA IZQUIERDA
                        autorizado = Movimientos::caminoIzquierda(diferencia, _nodoNuevo);

                    }  else if (diferencia.x==0
                                && diferencia.z > 0 ){

                        //MOVIMIENTO ARRIBA
                        autorizado = Movimientos::caminoArriba(diferencia, _nodoNuevo);

                    }  else if (diferencia.x==0
                                && diferencia.z < 0 ){

                        //MOVIMIENTO ABAJO
                        autorizado = Movimientos::caminoAbajo(diferencia, _nodoNuevo);

                    }else autorizado= false;

                    break;

                case 'C': //CABALLO SELECCIONADO

                    if (diferencia==Ogre::Vector3(-20,0,10)
                            || diferencia==Ogre::Vector3(20,0,10)
                            || diferencia==Ogre::Vector3(-20,0,-10)
                            || diferencia==Ogre::Vector3(20,0,-10)
                            || diferencia==Ogre::Vector3(10,0,20)
                            || diferencia==Ogre::Vector3(10,0,-20)
                            || diferencia==Ogre::Vector3(-10,0,20)
                            || diferencia==Ogre::Vector3(-10,0,-20)){
                        autorizado= true;
                    }else autorizado= false;

                    break;

                case 'P': //PEON SELECCIONADO

                    if (!turnoNegras){

                        if (diferencia==Ogre::Vector3(-10,0,0)
                                || (diferencia==Ogre::Vector3(-20,0,0)
                                    && seleccionado.x == -10)){

                            // std::cout << "AUTORIZA POR LA VIA HABITUAL!!!!!" << std::endl;

                            if (nodoSobrevolado->getChildIterator().hasMoreElements()){

                                //  std::cout << "ENCUENTRA UNA FICHA JUSTO DELANTE Y SE SUPONE QUE NO AUTORIZA" << std::endl;
                                autorizado= false;

                            }else autorizado= true;

                        } else if (nodoSobrevolado->getChildIterator().hasMoreElements()
                                   && (diferencia==Ogre::Vector3(-10,0,10)
                                       || diferencia==Ogre::Vector3(-10,0,-10))){

                            // std::cout << "AUTORIZA POR LA VIA COMESTIBLE!!!!!" << std::endl;
                            autorizado = FichaComestible();

                        }else autorizado= false;

                    }else if (turnoNegras){

                        if  (diferencia==Ogre::Vector3(10,0,0)
                             || (diferencia==Ogre::Vector3(20,0,0)
                                 && seleccionado.x == -60)){

                            //  std::cout << "AUTORIZA POR LA VIA HABITUAL!!!!!" << std::endl;

                            if (nodoSobrevolado->getChildIterator().hasMoreElements()){

                                //   std::cout << "ENCUENTRA UNA FICHA JUSTO DELANTE Y SE SUPONE QUE NO AUTORIZA" << std::endl;
                                autorizado= false;

                            }else autorizado= true;

                        } else if (nodoSobrevolado->getChildIterator().hasMoreElements()
                                   && (diferencia==Ogre::Vector3(10,0,10)
                                       || diferencia==Ogre::Vector3(10,0,-10))){

                            // std::cout << "AUTORIZA POR LA VIA COMESTIBLE!!!!!" << std::endl;
                            autorizado = FichaComestible();

                        }else autorizado= false;

                    }else autorizado= false;

                    break;

                default:
                    autorizado= false;
                    break;
                }

                if(autorizado
                        && nodoSobrevolado->getChildIterator().hasMoreElements()) autorizado = FichaComestible();

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






bool TutorialApplication::FichaComestible(){

    Ogre::Node::ChildNodeIterator iterator = _nodoNuevo->getChildIterator();

    if(iterator.hasMoreElements()){
        Ogre::SceneNode* child = (Ogre::SceneNode *)iterator.getNext();
        Ogre::SceneNode::ObjectIterator oi = child->getAttachedObjectIterator();

        if(oi.hasMoreElements()){
            Ogre::Entity* ent = (Ogre::Entity *)oi.getNext();


            if(!turnoNegras && ent->getName()[1] == 'N'){
                //  std::cout << "FICHA NEGRA ATACADA POR UNA BLANCA!!!!!!" << std::endl;

                _nodoNuevo->showBoundingBox(true);

                Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(_nodoNuevo->getAttachedObject(0));
                if (_nodoNuevo->getAttachedObject(0)->getName()[1] == 'B'){
                    mEntidadCasilla->setMaterialName("MaterialBlancoIluminado");
                }else mEntidadCasilla->setMaterialName("MaterialNegroIluminado");
                return true;
            }else if(turnoNegras && ent->getName()[1] == 'B'){
                // std::cout << "FICHA BLANCA ATACADA POR UNA NEGRA!!!!!!" << std::endl;

                _nodoNuevo->showBoundingBox(true);

                Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(_nodoNuevo->getAttachedObject(0));
                if (_nodoNuevo->getAttachedObject(0)->getName()[1] == 'B'){
                    mEntidadCasilla->setMaterialName("MaterialBlancoIluminado");
                }else mEntidadCasilla->setMaterialName("MaterialNegroIluminado");
                return true;
            }

            // std::cout << "ENTIDAD DEL NODO ENCONTRADA!!!!!!" << std::endl;
            // std::cout << " NODO ENCONTRADO!!!!!! : "<< ent->getName() << std::endl;
        }
    }
    return false;
}

/*

void mueveFicha(){


     if (diferencia.x==0 && diferencia.z > 0 ){

                                for (int i = 0; i < -diferencia.x/10; i++){
                                    std::cout << "NOMBRE CASILLA INTERMEDIA: " << columnas[-(nuevo.z/10)-i] + Ogre::StringConverter::toString(-(nuevo.x/10)+1) << std::endl;
                                    Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(it->movable->getParentSceneNode()->getParent());
                                    Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[-(nuevo.z/10)-i] + Ogre::StringConverter::toString(-(nuevo.x/10)+1)));
                                    if   (nodoTrayectoria->getChildIterator().hasMoreElements()){
                                        autorizado= false;
                                        std::cout << "HA ENCONTRADO UN NODO INTERMEDIO!!!" << std::endl;
                                    }else std::cout << "nodo vacío!!!" << std::endl;

                                }



}
*/






//-------------------------------------------------------------------------------------
void TutorialApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    std::cout << "CREA LA CAMARA" << std::endl;


    mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    mInputMan->setTopSpeed(100);
}


void TutorialApplication::createScene(void)
{


    EscenaAjedrez EscAjedrez;

    EscAjedrez.createScene(mSceneMgr);





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
  //  Ogre::OverlayElement *oe;




    // mOverlayManager-> hasOverlayElement("objectInfo");
    // oe = mOverlayManager->getOverlayElement("objectInfo");
    //  oe->setCaption(textoOverlay);


    //  oe = mOverlayManager->getOverlayElement("fpsInfo");
    //   oe->setCaption(s);

    //   mOutputDebugPanel->setParamValue(7, textoOverlay);



    mInputMan->frameRenderingQueued(evt);

    return true;


    //return  BaseApplication::frameRenderingQueued(evt);

}

//void TutorialApplication::createMainMenu(void)
//{
//}

bool TutorialApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{




    //std::cout << "MODO DE JUEGO : "<<mModoJuego << std::endl;

    //if(mModoJuego==1){
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

        //    std::cout << "EMPIEZA RAYO" << std::endl;

        Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
        Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();
        std::cout << "RESULTADO" << std::endl;

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

                std::cout << "HA DETECTADO UNA FICHA" << std::endl;
                _selectedNode = it->movable->getParentSceneNode();
                _selectedNode->showBoundingBox(true);
                fichaSeleccionada = true;
            }
        }

    } else if (mbright){

        if (_selectedNode != NULL && _nodoNuevo!=NULL && _nodoNuevo->getShowBoundingBox()) {  // Si habia alguno seleccionado...



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

            //   _nodoNuevo->showBoundingBox(true);
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



            //  _selectedNode = NULL;
        }

        /*   std::cout << "Boton Derecho" << std::endl;
       mask = ~STAGE;   // Seleccionamos todo menos el escenario
       std::cout << "FIN Boton Derecho" << std::endl;
      */



        //    }




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

