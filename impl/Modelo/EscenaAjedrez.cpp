
#include "../../headers/Modelo/EscenaAjedrez.h"

//-------------------------------------------------------------------------------------
EscenaAjedrez::EscenaAjedrez(void) :
    mRaySceneQuery(0),
    mCamera(0),
    mInputMan(0)
  , mOrbiting(false)
  , mGoingLeft(false)
  , mGoingRight(false)

  , columnas("ABCDEFGH")
  , peonesPromocionados(0)
{


    modelo = Modelo::getSingletonPtr();
    tablero = modelo->getTablero();

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

    tablero->creaFichasAjedrez(mSceneMgr);

    creaIluminacion();
}




//-------------------------------------------------------------------------------------
bool EscenaAjedrez::FichaComestible()
{

    if (!tablero->getNodoCasillaSobrevolada()->sinHijos())
    {
        // Casilla* casilla = getNodoCasillaSobrevolada()->getHijo(0);

        //Mira si la casilla está ocupada y por quién
        // Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
        Ficha* ent = static_cast<Ficha*> (tablero->getNodoCasillaSobrevolada()->getHijo(0));

        if((!tablero->getTurnoNegras() && ent->esNegra)
                || (tablero->getTurnoNegras() && !ent->esNegra))
        {

            return true;
        }
    }

    return false;
}

EscenaAjedrez* EscenaAjedrez::getSingletonPtr()
{
    static EscenaAjedrez miEscena;
    static EscenaAjedrez* miEscenaPtr = &miEscena;
    return miEscenaPtr;
}

void iluminaCasillaSobrevolada()
{


}

void EscenaAjedrez::apagaCasilla(Casilla* casilla)
{


    casilla->getNodoOgre()->showBoundingBox(false);
    // Casilla *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    // const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();
    if (!casilla->esNegra){

        casilla->cambiaMaterial("MaterialCasillaBlanca");
    }else casilla->cambiaMaterial("MaterialCasillaNegra");
}

void EscenaAjedrez::iluminaCasilla(Casilla* casilla)
{


    casilla->getNodoOgre()->showBoundingBox(true);
    // Ogre::Entity *mEntidadCasilla = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    // const Ogre::String mNombreEntidad =  mEntidadCasilla->getName();

    if (casilla->esNegra)
    {


        casilla->cambiaMaterial("MaterialCasillaNegraIlum");
    }else casilla->cambiaMaterial("MaterialCasillaBlancaIlum");
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


void EscenaAjedrez::cambiaTurno(){
    //CAMBIA TURNO

    Casilla* casilla = static_cast<Casilla*>(tablero->getNodoCasillaSobrevolada());

    if(!casilla->sinHijos())
    {
        //PROMOCIONA PEON
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));
        if(ficha->tipo_Ficha == Peon
                && ((!tablero->getTurnoNegras()
                     && tablero->getNodoCasillaSobrevolada()->getPosicion().Fila == 7)
                    || (tablero->getTurnoNegras()
                        && tablero->getNodoCasillaSobrevolada()->getPosicion().Fila == 0 )))
        {
            std::cout  << "promociona " << std::endl;

            casilla->eliminaHijo(0);
            ficha = promocionaPeon(ficha);
            casilla->agregaHijo(ficha);
        }

    }



    apagaCasilla(tablero->getNodoCasillaSobrevolada());
    std::cout  << "apagada " << std::endl;

    tablero->setNodoCasillaSobrevolada(NULL);
    tablero->setNodoFichaSeleccionada(NULL);


    std::cout << "fin cambia "<< std::endl;

    tablero-> setTurnoNegras(!tablero-> getTurnoNegras());
    std::cout << "fin "<< std::endl;

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
//Casilla* EscenaAjedrez::casillaOcupada(Casilla* nodoCasilla)
//{
//Mira si la casilla está ocupada y por quién
//  Ficha* child = static_cast<Casilla*> (nodoCasilla->getHijo(0));
// Ogre::Entity* ent = static_cast<Ogre::Entity*>(child->getAttachedObject(0));

//  if(child->getAttachedObject(0) != NULL)
//   {
//      return child;
//   }
//}

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




FichaReina* EscenaAjedrez::promocionaPeon(Ficha* nodoFicha)
{
    Ogre::Entity *entidadFicha;
    std::cout << "PROMOCION" << std::endl;

    //HAZ UN CONSTRUCTOR DE COPIA PORQUE HAY QUE CAMBIAR EL TIPO DE FICHA, METE ESNEGRA Y TIPO_FICHA Y PUEDE QUE ALGO MAS
    std::stringstream saux;

    saux.str("");
    saux << "ReinaPR_" << peonesPromocionados;

    FichaReina* nodoNuevo =new FichaReina(*nodoFicha, saux.str());

    //    nodo = mSceneMgr->createSceneNode(saux.str());

    //nodoNuevo->getNodoOgre()->detachAllObjects();

    std::cout << "fin getnodoogre" << std::endl;

    // entidadFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Reina.mesh");

    // nodoFicha

    if (!tablero->getTurnoNegras())
    {
        std::cout << "blanca" << std::endl;

        nodoNuevo->creaModelo3D(mSceneMgr,"Reina",BLANCAS);
        // entidadFicha = mSceneMgr->createEntity("(B)"+saux.str(), "Reina.mesh");
        // entidadFicha->setQueryFlags(BLANCAS);
    }else
    {
        std::cout << "negra" << std::endl;

        nodoNuevo->creaModelo3D(mSceneMgr,"Reina",NEGRAS);
        nodoNuevo->cambiaMaterial("MaterialFichaNegra");
        // entidadFicha = mSceneMgr->createEntity("(N)"+saux.str(), "Reina.mesh");
        // entidadFicha->setQueryFlags(NEGRAS);
        //mNodoFicha->yaw(Ogre::Degree(180));
        //  mNodoFicha->translate(70,0,70);
    }
    std::cout << "fin" << std::endl;

    delete nodoFicha;

    //  *nodoFicha = static_cast<FichaReina&>(*nodoNuevo);
    //entidadFicha->setCastShadows(true);

    //nodoFicha->getNodoOgre()->attachObject(entidadFicha);
    peonesPromocionados++;


    std::cout << "fin fin" << std::endl;
    return static_cast<FichaReina*>(nodoNuevo);

}

int* EscenaAjedrez::mueveIA(int origen, int destino)
{

    std::cout  << "MUEVE IA " << std::endl;

    /*
            int colOrigen = tableroElegido->movimiento[0]/12;

            int filaOrigen = tableroElegido->movimiento[0]%12;

            int colDestino = tableroElegido->movimiento[1]/12;

            int filaDestino = tableroElegido->movimiento[1]%12;


        */


    posicion orig;
    orig.Fila = (origen/12)-2;
    orig.Columna = (origen%12)-2;

    posicion dest;
    dest.Fila = (destino/12)-2;
    dest.Columna = (destino%12)-2;
    //int columanOrigen = (origen%12)-2;
    // int filaOrigen =   ;






    // std::stringstream origenBaseOcho;

    //char letra = tablero->columnas[columanOrigen];


    //std::cout  << "letra: "<< letra << std::endl;

    //origenBaseOcho.str("");

    //origenBaseOcho<< filaOrigen;
    // origenBaseOcho<< letra ;

    // char columna = ;


    //char letraDestino = tablero->columnas[columanDestino];

    //std::cout  << "letraDestino: "<< letraDestino << std::endl;


    //std::stringstream destinoBaseOcho;

    //destinoBaseOcho.str("");

    //destinoBaseOcho<<filaDestino;
    //destinoBaseOcho <<letraDestino;

    //std::cout  << "columanOrigen "<< columanOrigen << std::endl;

    //std::cout  << "filaOrigen " << filaOrigen << std::endl;



    //std::cout  << "origenBaseOcho "<< origenBaseOcho.str() << std::endl;
    //std::cout  << "destinoBaseOcho "<< destinoBaseOcho.str() << std::endl;


    actualizaTablero(orig,dest );

    cambiaTurno();


}



int* EscenaAjedrez::actualizaTablero(posicion casillaOrigen,posicion casillaDestino)
{




    //    Ogre::SceneNode* nodoCasillas = tablero->nodoCasillero;

    // std::cout  << "actualizaTablero  : "<< casillaOrigen<< std::endl;
    //std::cout  << "actualizaTablero  : "<< casillaDestino<< std::endl;

    Casilla* nodoCasillaTemporal = static_cast<Casilla*>(tablero->getHijo((casillaOrigen.Fila*8)+casillaOrigen.Columna));
    Casilla* casillaDestinoTemp = static_cast<Casilla*>(tablero->getHijo((casillaDestino.Fila*8)+casillaDestino.Columna));

    std::cout  << "nodoCasillaTemporal  : "<< nodoCasillaTemporal->getNombre()<< std::endl;



    if (!nodoCasillaTemporal->sinHijos())
    {


        std::cout  << "actualizaTablero3333333333333333 " << std::endl;

         Ficha* ficha =  static_cast<Ficha*>(nodoCasillaTemporal->getHijo(0));


      //  if (nodoFichaTemporal->salto) nodoFichaTemporal->salto = false;



        // Ogre::Entity* entidadFichaTemporal =  static_cast<Ogre::Entity*>(nodoFichaTemporal->getAttachedObject(0));

        std::cout  << "actualizaTablero 4444444444444444444" << std::endl;



        //BORRA FICHA DE LA CASILLA
        nodoCasillaTemporal->eliminaHijo(0);

        // columna = tablero->columnas[casillaDestino[0]];


        tablero->setNodoFichaSeleccionada(nodoCasillaTemporal);


        std::cout  << "casilla: " << (casillaDestino.Fila*8)+casillaDestino.Columna <<std::endl;





        //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
        if (!casillaDestinoTemp->sinHijos())
        {
            std::cout  << "come " << std::endl;

            Ficha* ficha = static_cast<Ficha*>(casillaDestinoTemp->getHijo(0));
            casillaDestinoTemp->eliminaHijo(0);
            delete ficha;
            ficha = NULL;
        }





        std::cout  << "actualizaTablero 5555555555555555555555555555555555555555" << std::endl;

        //if (!nodoCasillaTemporal->sinHijos()) nodoCasillaTemporal->eliminaHijo(0);

        casillaDestinoTemp->agregaHijo(ficha);

        //  casillas[numCasilla] = traduceFicha(entidadFichaTemporal->getName()[4]);

        //  nodoCasillas
        //tableroElegido->casillasInt;

        tablero->setNodoCasillaSobrevolada(casillaDestinoTemp);




    if (ficha->tipo_Ficha ==Rey)
    {


        std::cout  << "en rey" << std::endl;

        int difCol = tablero->getNodoCasillaSobrevolada()->getPosicion().Columna - tablero->getNodoFichaSeleccionada()->getPosicion().Columna;
        // if (difCol<0 ) difCol = -difCol;

        int fila =tablero->getNodoCasillaSobrevolada()->getPosicion().Fila;


        if (difCol == 2){
            Casilla* casillaTorre = static_cast<Casilla*>(tablero->getHijo((fila*8)+7));
            Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
            casillaTorre->eliminaHijo(0);

            casillaTorre = static_cast<Casilla*>(tablero->getHijo((fila*8) +tablero->getNodoCasillaSobrevolada()->getPosicion().Columna-1));
            casillaTorre->agregaHijo(fichaTorre);
        }

        if (difCol == -2){
            //Casilla* casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8)));

            Casilla* casillaTorre = static_cast<Casilla*>(tablero->getHijo(fila*8));
            Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
            casillaTorre->eliminaHijo(0);

            casillaTorre = static_cast<Casilla*>(tablero->getHijo((fila*8) +tablero->getNodoCasillaSobrevolada()->getPosicion().Columna+1));
            casillaTorre->agregaHijo(fichaTorre);
        }


    }




    if (ficha->tipo_Ficha ==Peon)
    {

        std::cout  << "dif" << std::endl;



        std::cout  << "dif:" << tablero->getNodoCasillaSobrevolada()->getPosicion().Fila<< std::endl;

        std::cout  << "dif:" << tablero->getNodoFichaSeleccionada()->getPosicion().Fila<< std::endl;


        int dif = tablero->getNodoCasillaSobrevolada()->getPosicion().Fila - tablero->getNodoFichaSeleccionada()->getPosicion().Fila;

        std::cout  << "dif:" << dif<< std::endl;



        int difCol = tablero->getNodoCasillaSobrevolada()->getPosicion().Columna - tablero->getNodoFichaSeleccionada()->getPosicion().Columna;
        std::cout  << "difcol: " << difCol<<std::endl;

        if (dif < 0 ) dif = -dif;
        if (difCol<0 ) difCol = -difCol;



        if(tablero->alPaso > 0 && dif == 1 && difCol == 1)
        {
            //SOLO COMER AL PASO
            int fila =tablero->getNodoFichaSeleccionada()->getPosicion().Fila;
            int columna =tablero->getNodoCasillaSobrevolada()->getPosicion().Columna;

            Casilla* casillaAux = static_cast<Casilla*>(tablero->getHijo((fila*8)+columna));

            if (!casillaAux->sinHijos())
            {
                //* fichaAux = static_cast<Ficha*>(casillaAux->getHijo(0));
                casillaAux->eliminaHijo(0);

            }

        }
        tablero->alPaso = -1;


        if( dif == 2) tablero->alPaso = ( tablero->getNodoCasillaSobrevolada()->getPosicion().Fila*8) +  tablero->getNodoCasillaSobrevolada()->getPosicion().Columna;


    }else tablero->alPaso = -1;


    //DESELECCIONA FICHA Y CASILLA
    ficha->getNodoOgre()->showBoundingBox(false);



    }


}

bool EscenaAjedrez::seleccionaFichaEnPosicion(int posX, int posY)
{

    if (tablero->getNodoFichaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...

        std::cout  << "fichasel" << std::endl;
        Ficha* ficha = static_cast<Ficha*>(tablero->getNodoFichaSeleccionada()->getHijo(0));
        ficha->getNodoOgre()->showBoundingBox(false);
        tablero->setNodoFichaSeleccionada(NULL);
    }

    std::cout  << "mpouse2" << std::endl;

    //EMPIEZA RAYO
    //Ogre::Ray r = setRayQuery(posx, posy, mask, mWindow);
    Ogre::RaySceneQueryResult &result =executeRay(posX,posY,'C');//mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();
    std::cout  << "mpouse3" << std::endl;


    if (it != result.end())
    {
        std::cout  << "mpouse31121: "<< it->movable->getParentSceneNode()->getName()<< std::endl;


        std::cout  << "mpouse31121: "<< it->movable->getName()<< std::endl;



        Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(it->movable->getParentSceneNode()->getName()));

        std::cout  << "mpouse31: "<< casilla->getNombre() << std::endl;



        if (casilla != NULL && !casilla->sinHijos())
        {

            Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

            std::cout  << "tiene hijos" << std::endl;


            if ((tablero->getTurnoNegras()
                 && ficha->esNegra)
                    || (!tablero->getTurnoNegras() && !ficha->esNegra))
            {


                tablero->setNodoFichaSeleccionada(casilla);
                ficha->getNodoOgre()->showBoundingBox(true);
                return true;

            }

        }
    }
return false;

}

int* EscenaAjedrez::mueveYTraduceTablero()
{

    //ESTO SE PUEDE CAMBIAR MUCHO
    int *casillas = new int[144];
    int numCasilla = 0;




    //    Ogre::SceneNode* nodoTest = tablero->nodoCasillero;

    // Ogre::Node::ChildNodeIterator iterator = _nodoNuevo->getChildIterator();
    Ogre::Node::ChildNodeIterator iterator = tablero->getNodoOgre()->getChildIterator();



    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {

        for (int y = 0; y<12; y++)
        {



            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {
                casillas[(i*12)+y] = 99;

            }else {


                Casilla* casilla= static_cast<Casilla*>(tablero->getHijo(((i-2)*8)+y-2));

                int filaTemp = casilla->getPosicion().Fila;

                int columnaTemp = casilla->getPosicion().Columna+2;

                int numeroCasilla = 24+(filaTemp*12)+columnaTemp;

                if (!casilla->sinHijos())
                {
                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //Ogre::SceneNode* nodoFichaTemporal =  static_cast<Ogre::SceneNode*>(nodoCasillaTemporal->getChild(0));

                    //Ogre::Entity* entidadFichaTemporal =  static_cast<Ogre::Entity*>(nodoFichaTemporal->getAttachedObject(0));

                    casillas[numeroCasilla] = traduceFicha(ficha->tipo_Ficha);
                    if (ficha->esNegra){
                        casillas[numeroCasilla] = -casillas[numeroCasilla];

                    }




                    //  casillas[numCasilla] = traduceFicha(entidadFichaTemporal->getName()[4]);

                }else casillas[numeroCasilla] = 0;
                // casillas[numCasilla] = 0;
                numCasilla++;


            }


            //  std::cout << tablero->casillasInt[((i-2)*8)+y-2] << std::endl;
        }


    }



    std::cout << "traducido" << std::endl;


    for(int i=0; i<12;i++)
    {
        std::cout  << casillas[(i*12)+2]<<"    "<<casillas[(i*12)+3]<<"    "<<casillas[(i*12)+4]<<"    "<<casillas[(i*12)+5]<<"    "<<casillas[(i*12)+6]<<"    "<<casillas[(i*12)+7] <<"    " <<casillas[(i*12)+8]<<"    " << casillas[(i*12)+9]<<"    " << std::endl;
    }


    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );

    int posFinal = ((tablero->getNodoCasillaSobrevolada()->getPosicion().Fila+2)*12) + tablero->getNodoCasillaSobrevolada()->getPosicion().Columna+2;




    int posInicial = ((tablero->getNodoFichaSeleccionada()->getPosicion().Fila+2)*12) + tablero->getNodoFichaSeleccionada()->getPosicion().Columna+2;

    std::cout << "inicial:" << posInicial<<std::endl;


    std::cout << "final:" << posFinal<<std::endl;




    casillas[posFinal]= casillas[posInicial];
    casillas[posInicial] = 0;





            return casillas;





}


int* EscenaAjedrez::traduceTablero()
{

    //ESTO SE PUEDE CAMBIAR MUCHO
    int *casillas = new int[144];
    int numCasilla = 0;




    //    Ogre::SceneNode* nodoTest = tablero->nodoCasillero;

    // Ogre::Node::ChildNodeIterator iterator = _nodoNuevo->getChildIterator();
    Ogre::Node::ChildNodeIterator iterator = tablero->getNodoOgre()->getChildIterator();



    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {

        for (int y = 0; y<12; y++)
        {



            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {
                casillas[(i*12)+y] = 99;

            }else {


                Casilla* casilla= static_cast<Casilla*>(tablero->getHijo(((i-2)*8)+y-2));

                int filaTemp = casilla->getPosicion().Fila;

                int columnaTemp = casilla->getPosicion().Columna+2;

                int numeroCasilla = 24+(filaTemp*12)+columnaTemp;

                if (!casilla->sinHijos())
                {
                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //Ogre::SceneNode* nodoFichaTemporal =  static_cast<Ogre::SceneNode*>(nodoCasillaTemporal->getChild(0));

                    //Ogre::Entity* entidadFichaTemporal =  static_cast<Ogre::Entity*>(nodoFichaTemporal->getAttachedObject(0));

                    casillas[numeroCasilla] = traduceFicha(ficha->tipo_Ficha);
                    if (ficha->esNegra){
                        casillas[numeroCasilla] = -casillas[numeroCasilla];

                    }




                    //  casillas[numCasilla] = traduceFicha(entidadFichaTemporal->getName()[4]);

                }else casillas[numeroCasilla] = 0;
                // casillas[numCasilla] = 0;
                numCasilla++;


            }


            //  std::cout << tablero->casillasInt[((i-2)*8)+y-2] << std::endl;
        }


    }



    std::cout << "traducido" << std::endl;


    for(int i=0; i<12;i++){


        std::cout  << casillas[(i*12)+2]<<"    "<<casillas[(i*12)+3]<<"    "<<casillas[(i*12)+4]<<"    "<<casillas[(i*12)+5]<<"    "<<casillas[(i*12)+6]<<"    "<<casillas[(i*12)+7] <<"    " <<casillas[(i*12)+8]<<"    " << casillas[(i*12)+9]<<"    " << std::endl;


    }


    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );



    return casillas;





}



short EscenaAjedrez::traduceFicha(tipoFicha tipo)
{
    switch (tipo)
    {
    case Peon:
    {
        return 1;
    }
    case Caballo:
    {
        return 2;
    }
    case Alfil:
    {
        return 3;
    }
    case Torre:
    {
        return 4;
    }
    case Reina:
    {
        return 5;
    }
    case Rey:
    {
        return 6;
    }
    default:
    {
        return 0;
    }
    }
}


