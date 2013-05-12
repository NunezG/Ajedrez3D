#include "../../headers/Modelo/Tablero.h"



Tablero::Tablero() :
    ObjetoOgre("Tablero")
  //,alPaso(0)
  //, turnoNegras(false)
  ,  _nodoNuevo(0)
  , _selectedNode(0)
  , peonesPromocionados(0)
  ,    fichaSeleccionada(false)
  , rotacionCamara(0)
{



}
Tablero::~Tablero()
{
    std::cout << "DESTRUYE TABLERO" << std::endl;


    //delete mSceneMgr;
}



Casilla* Tablero::getNodoCasillaSeleccionada(){
    return _selectedNode;

}

Casilla* Tablero::getNodoCasillaSobrevolada(){

    return _nodoNuevo;
}


int Tablero::getAlPaso()
{
    return alPaso;
}

void Tablero::setAlPaso(int casilla)
{
    alPaso = casilla;

}


bool Tablero::getTurnoNegras(){
    return turnoN;
}



void Tablero::setNodoCasillaSeleccionada(Casilla* nodo)
{
    _selectedNode = nodo;

}
void Tablero::setNodoCasillaSobrevolada(Casilla* nodo)
{
    _nodoNuevo = nodo;
}

bool Tablero::creaTableroYCasillas(Ogre::SceneManager* sceneMgr)
{
    mSceneMgr = sceneMgr;
    creaModelo3D(mSceneMgr, "Tablero", TABLERO);

    mSceneMgr->getRootSceneNode()->addChild(getNodoOgre());
    creaCasillas();


    creaVasallos();
    creaNobleza();
      creaPeones();


}

//-------------------------------------------------------------------------------------
bool Tablero::FichaComestible()
{

    if (!getNodoCasillaSobrevolada()->sinHijos())
    {
        // Casilla* casilla = getNodoCasillaSobrevolada()->getHijo(0);

        //Mira si la casilla está ocupada y por quién
        // Ogre::SceneNode* child = static_cast<Ogre::SceneNode *> (_nodoNuevo->getChild(0));
        Ficha* ent = static_cast<Ficha*> (getNodoCasillaSobrevolada()->getHijo(0));

        if((!getTurnoNegras() && ent->esNegra)
                || (getTurnoNegras() && !ent->esNegra))
        {

            return true;
        }
    }

    return false;
}

void Tablero::creaCasillas()
{
    std::string columnas ="ABCDEFGH";

    int contFila = 0;
    enColummas contColumna = COL_A;
    std::stringstream saux;
    Casilla* objeto;

    for (int i = 0; i < 64; ++i)
    {

        saux.str("");
        saux  << Ogre::StringConverter::toString( contFila + 1 )<<  columnas[contColumna];
        std::cout  <<(contFila*8)+contColumna<< std::ends;



        objeto = new Casilla(saux.str());
        objeto->creaModelo3D(mSceneMgr, "Casilla", CASILLA);

        //SI ES COLUMNA PAR Y FILA IMPAR: CASILLA NEGRA
        if ((i%2 == 0
             && contFila % 2 != 0)
                ||(i%2 != 0
                   && contFila % 2 == 0) )
        {
            objeto->esNegra = true;
            objeto->cambiaMaterial("MaterialCasillaNegra");
        }
        objeto->setPosicion(contFila, contColumna);
        objeto->trasladarAPunto();
        agregaHijo(objeto);

        if (contColumna == COL_H)
        {
            contFila++;
            contColumna = COL_A;
            std::cout  <<"/"<< std::endl;

        }else contColumna = enColummas(static_cast<int>(contColumna)+1);
    }
}


void Tablero::creaVasallos()
{
    std::stringstream saux;
    //Ogre::String posCasilla;
    int posCasilla;

    Ficha* objeto;

    //CREA LAS PIEZAS DOBLES
    for (int i = 0; i < 4; ++i)
    {
        saux.str("");
        saux <<"(T)Torre"<< Ogre::StringConverter::toString(i);

        objeto = new FichaTorre(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr, "Torre", BLANCAS);

            posCasilla = (7*(i/2));
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Torre",NEGRAS);

            objeto->cambiaMaterial("MaterialFichaNegra");

            objeto->rota(180);

            objeto->trasladar(70,70);
            posCasilla = (7*(i/2))+ (7*8);
        }
        std::cout  << "gethijo " << std::endl;


        getHijo(posCasilla)->agregaHijo(objeto);

        std::cout  << "acabarModoCamara " << std::endl;

        saux.str("");
        saux <<"(C)Caballo"<< Ogre::StringConverter::toString(i);

        objeto = new FichaCaballo( saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Caballo",BLANCAS);

            posCasilla = (1+5*(i/2));
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Caballo",NEGRAS);

            objeto->cambiaMaterial("MaterialFichaNegra");

            objeto->rota(180);
            objeto->trasladar(70,70);
            posCasilla = (1+5*(i/2))+ (7*8);
        }
        getHijo(posCasilla)->agregaHijo(objeto);

        saux.str("");
        saux <<"(A)Alfil"<< Ogre::StringConverter::toString(i);

        objeto = new FichaAlfil(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Alfil",BLANCAS);
            posCasilla = (2+3*(i/2));
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Alfil",NEGRAS);
            objeto->cambiaMaterial("MaterialFichaNegra");
            objeto->rota(180);
            objeto->trasladar(70,70);
            posCasilla = (2+3*(i/2))+ (7*8);
        }

        getHijo(posCasilla)->agregaHijo(objeto);
    }
}

void Tablero::creaNobleza()
{
    std::stringstream saux;
    int posCasilla;
    Ficha* objeto;

    //CREA LAS PIEZAS UNICAS
    for (int i = 0; i < 2; ++i)
    {
        saux.str("");
        saux <<"(D)Reina"<< Ogre::StringConverter::toString(i);
        objeto = new FichaReina(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Reina",BLANCAS);
            posCasilla = 3;
        }else
        {
            objeto->creaModelo3D(mSceneMgr,"Reina",NEGRAS);
            posCasilla = 3+ (7*8);
            objeto->cambiaMaterial("MaterialFichaNegra");
            objeto->rota(180);
            objeto->trasladar(70,70);
        }
        getHijo(posCasilla)->agregaHijo(objeto);

        saux.str("");
        saux <<"(R)Rey"<< Ogre::StringConverter::toString(i);

        objeto = new FichaRey(saux.str());
        if (i%2 != 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Rey",BLANCAS);
            posCasilla = 4;
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Rey",NEGRAS);
            objeto->cambiaMaterial("MaterialFichaNegra");
            posCasilla = 4+(7*8);
            objeto->rota(180);
            objeto->trasladar(70,70);
        }
        getHijo(posCasilla)->agregaHijo(objeto);
    }
}

void Tablero::creaPeones()
{
    std::stringstream saux;
    int posCasilla;

    Ficha* objeto;

    //CREA LOS PEONES
    for (int i = 0; i < 16; ++i)
    {
        saux.str("");
        saux <<"(P)Peon_"<< Ogre::StringConverter::toString(i);
        objeto = new FichaPeon(saux.str());

        if (i%2 == 0)
        {
            objeto->creaModelo3D(mSceneMgr,"Peon",BLANCAS);
            posCasilla = (i/2)+ 8;
        }
        else
        {
            objeto->creaModelo3D(mSceneMgr,"Peon",NEGRAS);
            objeto->cambiaMaterial("MaterialFichaNegra");
            //objeto->rota(180);
            // objeto->trasladar(70,70);
            posCasilla = (i/2)+(6*8);
        }
        getHijo(posCasilla)->agregaHijo(objeto);
    }
}
/*
bool Tablero::verificaCamino(int diferencia[2], int final[2], int camino)
{
    //Ogre::SceneNode* nodoCasillero = static_cast<Ogre::SceneNode*>(_nodoNuevo->getParent());
    // Ogre::Vector3 nuevo = _nodoNuevo->getPosition();
    // const String columnas = "ABCDEFGH";

    int colDestino = -(final[1]/10);
    int filaDestino = -(final[0]/10)+1;
    int numCasillasX = diferencia[0]/10;
    int numCasillasZ = diferencia[1]/10;

    int colZ, filaX, dist;

    if (camino == 1)  //MOVIMIENTO A LA DERECHA
    {
        colZ = colDestino;
        dist = -numCasillasX;
    }
    else if (camino == 2) //MOVIMIENTO A LA IZQUIERDA
    {
        colZ = colDestino;
        dist = numCasillasX;
    }
    else if (camino == 3) //MOVIMIENTO HACIA ARRIBA
    {
        filaX = filaDestino;
        dist = numCasillasZ;
    }
    else if (camino == 4) //MOVIMIENTO HACIA ABAJO
    {
        filaX = filaDestino;
        dist = -numCasillasZ;
    }
    else if (camino == 5) dist = numCasillasZ; //MOVIMIENTO DIAGONAL ARRIBA IZQUIERDA
    else if (camino == 6) dist = numCasillasZ; //MOVIMIENTO DIAGONAL ARRIBA DERECHA
    else if (camino == 7) dist = -numCasillasZ; //MOVIMIENTO DIAGONAL ABAJO IZQUIERDA
    else if (camino == 8) dist = -numCasillasZ; //MOVIMIENTO DIAGONAL ABAJO DERECHA

    for (int i = 1; i < dist; i++)
    {
        if (camino == 1) filaX = filaDestino-i;  // DERECHA
        else if (camino == 2) filaX = filaDestino+i; // IZQUIERDA
        else if (camino == 3) colZ = colDestino+i; // MOVIMIENTO HACIA ARRIBA
        else if (camino == 4) colZ = colDestino-i; // MOVIMIENTO HACIA ABAJO
        else if (camino == 5)
        { //MOVIMIENTO DIAGONAL ARRIBA IZQUIERDA
            colZ = colDestino+i;
            filaX = filaDestino+i;
        }
        else if (camino == 6)
        { //MOVIMIENTO DIAGONAL ARRIBA DERECHA
            colZ = colDestino+i;
            filaX = filaDestino-i;
        }
        else if (camino == 7) //MOVIMIENTO DIAGONAL ABAJO IZQUIERDA
        {
            colZ = colDestino-i;
            filaX = filaDestino+i;
        }
        else if (camino == 8) //MOVIMIENTO DIAGONAL ABAJO DERECHA
        {
            colZ = colDestino-i;
            filaX = filaDestino-i;
        }

        // Ogre::SceneNode* nodoTrayectoria = static_cast<Ogre::SceneNode*>(nodoCasillero->getChild(columnas[colZ] + Ogre::StringConverter::toString(filaX)));
        if (casillas[colZ][filaX] > 0)
            return false;
    }
    return true;
}
*/

int Tablero::evaulaTablero(const int casillasInt[144])
{

    bool BlackCheck;
    bool BlackMate;
    bool WhiteCheck;
    bool WhiteMate;
    bool StaleMate;


    int suma = 0;


    //EMPIEZA CONTANDO LAS FICHAS DEL TABLERO Y HACIENDO UNA SUMA SIMPLE...

    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {

            //MIRA SI ATACAN A LA
            if (turnoN){
                if (casillasInt[(i*12)+y]  == 6)
                {


                    //    suma =  suma - valorFicha(tipoF(-casillasInt[(i*12)+y]));

                }else if (casillasInt[(i*12)+y] > 0){

                    //    suma =  suma + valorFicha(tipoF(casillasInt[(i*12)+y]));

                }

            }

        }

    }

    // std::cout << "ESTE TABLERO HA ACUMULADO UN VALOR DE: " << suma<< std::endl;


    return suma;
}



void Tablero::cambiaTurno()
{
    //CAMBIA TURNO
    //NOTIFICAR A LAS VISTAS?? AL FUNCIONAR EN BUCLE EN REALIDAD NO HACE FALTA NOTIFICAR
    //COMPRUEBA JAQUE MATE

    promocionaPeon();


    std::cout  << "apagada " << std::endl;

    setNodoCasillaSobrevolada(NULL);
    setNodoCasillaSeleccionada(NULL);


    std::cout << "fin cambia "<< std::endl;

    turnoN = !turnoN;
    std::cout << "fin "<< std::endl;

}

void Tablero::promocionaPeon()
{
    Casilla* casilla = static_cast<Casilla*>(getNodoCasillaSobrevolada());

    if(!casilla->sinHijos())
    {
        //PROMOCIONA PEON
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

        if(ficha->tipo_Ficha == Peon
                && ((!getTurnoNegras()
                     && getNodoCasillaSobrevolada()->getPosicion().Fila == 7)
                    || (getTurnoNegras()
                        && getNodoCasillaSobrevolada()->getPosicion().Fila == 0 )))
        {
            std::cout  << "promociona " << std::endl;

            casilla->eliminaHijo(0);

            // ficha = tablero->promocionaPeon(ficha);

            Ogre::Entity *entidadFicha;
            std::cout << "PROMOCION" << std::endl;

            std::stringstream saux;

            saux.str("");
            saux << "ReinaPR_" << peonesPromocionados;

            FichaReina* nodoNuevo =new FichaReina(*ficha, saux.str());

            if (!getTurnoNegras())
            {
                std::cout << "blanca" << std::endl;

                nodoNuevo->creaModelo3D(mSceneMgr,"Reina",BLANCAS);

                std::cout << "ha creado modelo" << std::endl;

            }else
            {
                std::cout << "negra" << std::endl;

                nodoNuevo->creaModelo3D(mSceneMgr,"Reina",NEGRAS);
                nodoNuevo->cambiaMaterial("MaterialFichaNegra");

            }
            std::cout << "DELETE FICHA" << std::endl;

            delete ficha;

            std::cout << "aumenta peones" << std::endl;


            peonesPromocionados++;

            std::cout << "agrega hijo " << std::endl;


            casilla->agregaHijo(nodoNuevo);
            std::cout << "fin hijo " << std::endl;

        }

    }
    //return static_cast<FichaReina*>(nodoNuevo);

}

void Tablero::actualizaTablero(posicion casillaOrigen,posicion casillaDestino)
{
    //NOTIFICAR A LAS VISTAS??
    std::cout  << "actualizaTablero" << std::endl;


    //    Ogre::SceneNode* nodoCasillas = tablero->nodoCasillero;

    std::cout  << "actualizaTablero  : "<< casillaOrigen.Fila<< " "<< casillaOrigen.Columna<<std::endl;
    std::cout  << "actualizaTablero  : "<< casillaDestino.Fila<< " "<< casillaDestino.Columna <<std::endl;

    std::cout  << "actualizaTablero  : "<< (casillaOrigen.Fila*8)+casillaOrigen.Columna<< std::endl;
    std::cout  << "actualizaTablero  : "<< (casillaDestino.Fila*8)+casillaDestino.Columna<< std::endl;


    Casilla* nodoCasillaTemporal = static_cast<Casilla*>(getHijo((casillaOrigen.Fila*8)+casillaOrigen.Columna));
    Casilla* casillaDestinoTemp = static_cast<Casilla*>(getHijo((casillaDestino.Fila*8)+casillaDestino.Columna));

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

        setNodoCasillaSeleccionada(nodoCasillaTemporal);

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

        setNodoCasillaSobrevolada(casillaDestinoTemp);

        if (ficha->tipo_Ficha ==Rey)
        {
            std::cout  << "en rey" << std::endl;

            int difCol = getNodoCasillaSobrevolada()->getPosicion().Columna - getNodoCasillaSeleccionada()->getPosicion().Columna;
            // if (difCol<0 ) difCol = -difCol;

            int fila =getNodoCasillaSobrevolada()->getPosicion().Fila;


            if (difCol == 2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>(getHijo((fila*8)+7));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>(getHijo((fila*8) +getNodoCasillaSobrevolada()->getPosicion().Columna-1));
                casillaTorre->agregaHijo(fichaTorre);
            }

            if (difCol == -2)
            {
                //Casilla* casillaTorre = static_cast<Casilla*>(escenaAjedrez->tablero->getHijo((fila*8)));

                Casilla* casillaTorre = static_cast<Casilla*>(getHijo(fila*8));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>(getHijo((fila*8) +getNodoCasillaSobrevolada()->getPosicion().Columna+1));
                casillaTorre->agregaHijo(fichaTorre);
            }

        }

        if (ficha->tipo_Ficha ==Peon)
        {

            std::cout  << "dif" << std::endl;



            std::cout  << "fila seleccionada:" << getNodoCasillaSeleccionada()->getPosicion().Fila<< std::endl;

            std::cout  << "col seleccionada:" << getNodoCasillaSeleccionada()->getPosicion().Columna<< std::endl;

            std::cout  << "fila sobrevolada:" << getNodoCasillaSobrevolada()->getPosicion().Fila<< std::endl;

            std::cout  << "col sobrevolada:" << getNodoCasillaSobrevolada()->getPosicion().Columna<< std::endl;


            int dif = getNodoCasillaSobrevolada()->getPosicion().Fila - getNodoCasillaSeleccionada()->getPosicion().Fila;

            std::cout  << "dif:" << dif<< std::endl;

            int difCol = getNodoCasillaSobrevolada()->getPosicion().Columna - getNodoCasillaSeleccionada()->getPosicion().Columna;
            std::cout  << "difcol: " << difCol<<std::endl;

            if (dif < 0 ) dif = -dif;
            if (difCol<0 ) difCol = -difCol;


            std::cout  << "COMPRUEBA ALPASO: " <<alPaso<<std::endl;

            if(alPaso > 0 && dif == 1 && difCol == 1)
            {
                std::cout  << "ENTRA" <<std::endl;

                //SOLO COMER AL PASO
                int fila =getNodoCasillaSeleccionada()->getPosicion().Fila;
                int columna =getNodoCasillaSobrevolada()->getPosicion().Columna;

                if (alPaso = 24+(fila*12)+columna+2)
                {
                    std::cout  << "ALPASO VA BIEN " <<std::endl;

                    Casilla* casillaAux = static_cast<Casilla*>(getHijo((fila*8)+columna));

                    if (!casillaAux->sinHijos())
                    {
                        //* fichaAux = static_cast<Ficha*>(casillaAux->getHijo(0));
                        casillaAux->eliminaHijo(0);

                    }


                }


            }
            setAlPaso(-1);


            if( dif == 2){

                setAlPaso(24+(getNodoCasillaSobrevolada()->getPosicion().Fila*12) +  getNodoCasillaSobrevolada()->getPosicion().Columna+2);
                std::cout  << "ALPASO EN TABLERO: " <<alPaso<<std::endl;

            }

        }else setAlPaso(-1);

        //DESELECCIONA FICHA Y CASILLA
        ficha->getNodoOgre()->showBoundingBox(false);
    }
}

int* Tablero::mueveYTraduceTablero()
{

    int* tableroTraducido = traduceTablero();

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );

    int posFinal = 24+(getNodoCasillaSobrevolada()->getPosicion().Fila*12) + getNodoCasillaSobrevolada()->getPosicion().Columna+2;

    int posInicial = 24+(getNodoCasillaSeleccionada()->getPosicion().Fila*12) + getNodoCasillaSeleccionada()->getPosicion().Columna+2;

    std::cout << "inicial:" << posInicial<<std::endl;

    std::cout << "final:" << posFinal<<std::endl;

    tableroTraducido[posFinal]= tableroTraducido[posInicial];
    tableroTraducido[posInicial] = 0;

    return tableroTraducido;
}

int* Tablero::traduceTablero()
{
    //ESTO SE PUEDE CAMBIAR MUCHO
    int *casillas = new int[144];
    int numCasilla = 0;

    //    Ogre::SceneNode* nodoTest = tablero->nodoCasillero;

    // Ogre::Node::ChildNodeIterator iterator = _nodoNuevo->getChildIterator();
    // Ogre::Node::ChildNodeIterator iterator = getNodoOgre()->getChildIterator();

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

            }else
            {
                Casilla* casilla= static_cast<Casilla*>(getHijo(((i-2)*8)+y-2));

                int filaTemp = casilla->getPosicion().Fila;

                int columnaTemp = casilla->getPosicion().Columna;

                int numeroCasilla = 24+(filaTemp*12)+columnaTemp+2;

                if (!casilla->sinHijos())
                {
                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //Ogre::SceneNode* nodoFichaTemporal =  static_cast<Ogre::SceneNode*>(nodoCasillaTemporal->getChild(0));

                    //Ogre::Entity* entidadFichaTemporal =  static_cast<Ogre::Entity*>(nodoFichaTemporal->getAttachedObject(0));

                    casillas[numeroCasilla] = traduceFicha(ficha->tipo_Ficha);
                    if (ficha->esNegra)
                    {
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

    return casillas;

}

short Tablero::traduceFicha(tipoFicha tipo)
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




TableroPrueba::TableroPrueba() :
    //numeroHijos(0),
    Score(0),
    //fichaMovida(""),
    vectorMov(0),
    turnoN(false),
    alPaso(0)


{
}

TableroPrueba::TableroPrueba( const TableroPrueba& original ):
  //  numeroHijos(0),
    Score(0),
    // fichaMovida(""),
    vectorMov(0),
    turnoN(!original.turnoN),
    alPaso(original.alPaso)
{

   // std::cout << "turnoN al copiar: "<<turnoN<<" Original: "<<original.turnoN << std::endl;


    casillasInt = new int[144];


    for(int i=0; i<144;i++)
    {


        casillasInt[i] = original.casillasInt[i];
    }
}

TableroPrueba::~TableroPrueba()
{



    for(int i = 0; i < vectorMov.size(); i++)
    {

        delete vectorMov.at(i);

        vectorMov.at(i) = NULL;
    }

  //  numeroHijos=0;

    vectorMov.clear();


}


/*
board type
    This type contains all information specific to the current state of the game, including layout of the board and current player.

score type
    This data type indicates piece advantage, strategic advantage, and possible wins. In most games, strategic advantage includes the number of moves available to each player with the goal of minimizing the opponent's mobility.

neg_infinity and pos_infinity
    The most extreme scores possible in the game, each most disadvantageous for one player in the game.

generate_moves
    This function takes the current board and generates a list of possible moves for the current player.

apply_move
    This function takes a board and a move, returning the board with all the updates required by the given move.

null_move
    If the chosen game allows or requires a player to forfeit moves in the case where no moves are available, this function takes the current board and returns it, after switching the current player.

static_evaluation
    This function takes the board as input and returns a score for the game.

compare_scores
    This function takes 2 scores to compare and a player, returning the score that is more advantageous for the given player. If scores are stored as simple integers, this function can be the standard < and > operators.

*/
