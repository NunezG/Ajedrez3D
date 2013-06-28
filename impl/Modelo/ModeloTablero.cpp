#include "../../headers/Modelo/ModeloTablero.h"

ModeloTablero::ModeloTablero() :
    //numeroHijos(0),
    //Score(0),
    //fichaMovida(""),
    //vectorMov(NULL),
    turnoN(false),
    alPaso(-1),
    nodoInicial(true)
{
    jugada = new unsigned char[2];
    jugada[0] = -1;
    jugada[1] = -1;


}

ModeloTablero::ModeloTablero( const ModeloTablero& original, int casInicial, int casFinal ):
    //  numeroHijos(0),
    //Score(0),
    // fichaMovida(""),
    //  vectorMov(NULL),
    alPaso(-1)
  , nodoInicial(false)
{

    //for(int i = 0; i < table->vectorMov.size(); i++)
   // {
   //     if (table->vectorMov.at(i) != NULL)
  //      {
   //         delete table->vectorMov.at(i);
   //         table->vectorMov.at(i) = NULL;
//        }
//    }
    std::cout << "copia " <<std::endl;
   // std::cout << "!!VECTOR JUGADAS AL COPIAR: "<<vectorJugadas.empty() << std::endl;

      //   std::cout << "!!VECTOR JUGADAS AL COPIAR: "<<vectorJugadas.size() << std::endl;


   // vectorJugadas.clear();
    // std::cout << "turnoN al copiar: "<<turnoN<<" Original: "<<original.turnoN << std::endl;
    //casillasInt = new char[144];

         //NORMALIZA EL TABLERO PARA EL CAMBIO DE TURNO
         for(int i=0; i<144;i++)
         {

                 casillasInt[i] = original.casillasInt[i];

         }

    jugada = new unsigned char[2];
    jugada[0] = -1;
    jugada[1] = -1;

    cambiaTurno();

}

ModeloTablero::~ModeloTablero()
{
    //std::cout << "deletein"<< std::endl;

    if (!vectorJugadas.empty())
    {
        for(int i = 0; i < vectorJugadas.size(); i++)
        {
            if (vectorJugadas.at(i) != NULL)
            {
                delete vectorJugadas.at(i);
                vectorJugadas.at(i) = NULL;
            }
        }
        //  numeroHijos=0;
        vectorJugadas.clear();
    }

    delete jugada;
    jugada = NULL;
    //std::cout << "deleteout"<< std::endl;

}


bool ModeloTablero::cambiaTurno()
{

    casillasInt[jugada[1]]= casillasInt[jugada[0]];
    casillasInt[jugada[0]] = 0;
    turnoN = !turnoN;

    //NORMALIZA EL TABLERO PARA EL CAMBIO DE TURNO
    for(int i=26; i<121;i++)
    {
        //NORMALIZA EL TABLERO, CAMBIA EL SIGNO DE LAS FICHAS
        if (casillasInt[i] != 0 && casillasInt[i] != 99)
        {
            casillasInt[i] = -casillasInt[i];
        }
    }
    jugada[0] = -1;
    jugada[1] = -1;
}

bool ModeloTablero::evaluaJaque()
{
    int posRey = 999;
    int fichaRey = -6;

    int fichaReina = -5;
    int fichaPeon = -1;
    int fichaAlfil = -3;
    int fichaCaballo = -2;
    int fichaTorre = -4;

    for (int i=0; i<144;i++)
    {
     //  if (casillasInt[i] != 99) std::cout << "jaque mira la casilla:  " << i<< " valor: "<< casillasInt[i] <<std::endl;

        if (casillasInt[i] == -fichaRey)
        {
            posRey = i;
            break;
        }
    }
    if (posRey != 999)
    {
        //N
        int ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*12)];
            if(ficha != 0)
            {
                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //cualquier otra ficha en medio

                break;
            }

        }

        //S
        ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*12)];

            if(ficha != 0)
            {
                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //ficha en medio
                break;
            }
        }

        //E
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+i];

            if(ficha != 0)
            {
                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                break;
            }

        }

        //O
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-i];

            if(ficha != 0)
            {
                //REY
                if (i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //ficha en medio

                break;
            }
        }

        //NE
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*11)];
            if(ficha != 0)
            {
                //REY                               //PEON NEGRO
                if(i==1 && (ficha == fichaRey || (!turnoN && ficha == fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                else if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //NO
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*13)];
            if(ficha != 0)
            {
                //REY                               //PEON NEGRO
                if(i==1 && (ficha == fichaRey || (!turnoN && ficha ==fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //SE

        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*11)];

            if(ficha != 0)
            {
                //REY                               //PEON BLANCO
                if(i==1 && (ficha == fichaRey || (turnoN && ficha ==fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //SO
        ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*13)];

            if(ficha != 0)
            {
                //REY                               //PEON BLANCO
                if(i==1 && (ficha == fichaRey || (turnoN && ficha ==fichaPeon)))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }
        int caballo;

        caballo= posRey-10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey-14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey-23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;



        caballo= posRey-25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;

        caballo= posRey+10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;
    }

    return false;
}


