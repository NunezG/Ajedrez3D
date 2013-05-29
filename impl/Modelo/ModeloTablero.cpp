#include "../../headers/Modelo/ModeloTablero.h"

ModeloTablero::ModeloTablero() :
    //numeroHijos(0),
    Score(0),
    //fichaMovida(""),
    //vectorMov(NULL),
    turnoN(false),
    alPaso(-1),
    nodoInicial(true)
{
    jugada = new int[2];
    jugada[0] = -1;
    jugada[1] = -1;

    //vectorMov.clear();
}

ModeloTablero::ModeloTablero( const ModeloTablero& original ):
    //  numeroHijos(0),
    Score(0),
    // fichaMovida(""),
    //  vectorMov(NULL),
    turnoN(!original.turnoN),
    alPaso(-1)
  , nodoInicial(false)

{


    // std::cout << "turnoN al copiar: "<<turnoN<<" Original: "<<original.turnoN << std::endl;
    casillasInt = new int[144];
    jugada = new int[2];
    jugada[0] = -1;
    jugada[1] = -1;

    for(int i=0; i<144;i++)
    {
        //NORMALIZA EL TABLERO, CAMBIA EL SIGNO DE LAS FICHAS
        if (original.casillasInt[i] != 0 && original.casillasInt[i] != 99)
        {
            casillasInt[i] = -original.casillasInt[i];
        }
        else
        {

            casillasInt[i] = original.casillasInt[i];


        }
    }
}

ModeloTablero::~ModeloTablero()
{
    if (!vectorMov.empty())
    {

        for(int i = 0; i < vectorMov.size(); i++)
        {
            if (vectorMov.at(i) != NULL)
            {
                delete vectorMov.at(i);

                vectorMov.at(i) = NULL;
            }
        }

        //  numeroHijos=0;
        vectorMov.clear();
    }

}
