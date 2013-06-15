#include "../../headers/ModeloVista/Tablero.h"

Tablero::Tablero() :
    ObjetoOgre("Tablero")
  ,  _nodoNuevo(0)
  , _selectedNode(0)
  , peonesPromocionados(0)
  ,    fichaSeleccionada(false)
  , rotacionCamara(0)
  , turnoNegras(false)
{
}
Tablero::~Tablero()
{
}

bool Tablero::getTurnoNegras()
{
    return turnoNegras;
}


Casilla* Tablero::getNodoCasillaSeleccionada()
{
    return _selectedNode;

}

Casilla* Tablero::getNodoCasillaSobrevolada()
{

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

void Tablero::setNodoCasillaSeleccionada(Casilla* nodo)
{
    _selectedNode = nodo;

}
void Tablero::setNodoCasillaSobrevolada(Casilla* nodo)
{
    _nodoNuevo = nodo;
}

void Tablero::setNodoCasillaSeleccionada(int posicion)
{
    if (posicion < 0) _selectedNode = NULL;
    else _selectedNode = static_cast<Casilla*>(getHijo(posicion));

}
void Tablero::setNodoCasillaSobrevolada(int posicion)
{
    if (posicion < 0) _nodoNuevo = NULL;
    else _nodoNuevo = static_cast<Casilla*>(getHijo(posicion));
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
        saux  << Ogre::StringConverter::toString( contFila + 1 ) << columnas[contColumna];

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
        objeto->trasladar(-10*contFila,-10*contColumna);
        agregaHijo(objeto);

        if (contColumna == COL_H)
        {
            contFila++;
            contColumna = COL_A;
        }
        else contColumna = enColummas(static_cast<int>(contColumna)+1);
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


        getHijo(posCasilla)->agregaHijo(objeto);


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
            posCasilla = (2*8+3*(i/2));
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
            posCasilla = 3*8+3;
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
            posCasilla = 4+(5*8);
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

void Tablero::actualizaTablero()
{  
    Casilla* nodoCasillaTemporal = getNodoCasillaSeleccionada();
    Casilla* casillaDestinoTemp = getNodoCasillaSobrevolada();

    if (!nodoCasillaTemporal->sinHijos())
    {
        Ficha* ficha =  static_cast<Ficha*>(nodoCasillaTemporal->getHijo(0));

        //BORRA FICHA DE LA CASILLA
        nodoCasillaTemporal->eliminaHijo(0);

        //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
        if (!casillaDestinoTemp->sinHijos())
        {
            Ficha* ficha = static_cast<Ficha*>(casillaDestinoTemp->getHijo(0));
            casillaDestinoTemp->eliminaHijo(0);
            delete ficha;
            ficha = NULL;
        }

        casillaDestinoTemp->agregaHijo(ficha);

        if (ficha->tipo_Ficha == 6)
        {

            int difCol = casillaDestinoTemp->getPosicion().Columna - nodoCasillaTemporal->getPosicion().Columna;
            // if (difCol<0 ) difCol = -difCol;

            int fila =casillaDestinoTemp->getPosicion().Fila;


            if (difCol == 2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>(getHijo((fila*8)+7));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>(getHijo((fila*8) +casillaDestinoTemp->getPosicion().Columna-1));
                casillaTorre->agregaHijo(fichaTorre);
            }

            if (difCol == -2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>(getHijo(fila*8));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>(getHijo((fila*8) +casillaDestinoTemp->getPosicion().Columna+1));
                casillaTorre->agregaHijo(fichaTorre);
            }
        }

        if (ficha->tipo_Ficha == 1)
        {
            int dif = casillaDestinoTemp->getPosicion().Fila - nodoCasillaTemporal->getPosicion().Fila;
            int difCol = casillaDestinoTemp->getPosicion().Columna - nodoCasillaTemporal->getPosicion().Columna;
            if (dif < 0 ) dif = -dif;
            if (difCol<0 ) difCol = -difCol;

            if(alPaso > 0 && dif == 1 && difCol == 1)
            {
                //SOLO COMER AL PASO
                int fila =nodoCasillaTemporal->getPosicion().Fila;
                int columna =casillaDestinoTemp->getPosicion().Columna;

                if (alPaso = 24+(fila*12)+columna+2)
                {
                    Casilla* casillaAux = static_cast<Casilla*>(getHijo((fila*8)+columna));

                    if (!casillaAux->sinHijos())
                    {
                        casillaAux->eliminaHijo(0);
                    }
                }
            }
            setAlPaso(-1);

            if( dif == 2)
                setAlPaso(24+(casillaDestinoTemp->getPosicion().Fila*12) +  casillaDestinoTemp->getPosicion().Columna+2);
        }
        else setAlPaso(-1);

        //DESELECCIONA FICHA Y CASILLA
        ficha->getNodoOgre()->showBoundingBox(false);
    }
}
