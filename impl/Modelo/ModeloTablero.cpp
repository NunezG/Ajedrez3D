#include "../../headers/Modelo/ModeloTablero.h"

ModeloTablero::ModeloTablero() :
    //numeroHijos(0),
    Score(0),
    //fichaMovida(""),
    //vectorMov(NULL),
    turnoN(false),
    alPaso(0),
    movimiento(NULL)
{
    //vectorMov.clear();
}

ModeloTablero::ModeloTablero( const ModeloTablero& original ):
    //  numeroHijos(0),
    Score(0),
    // fichaMovida(""),
    //  vectorMov(NULL),
    turnoN(!original.turnoN),
    alPaso(original.alPaso)
{


    // std::cout << "turnoN al copiar: "<<turnoN<<" Original: "<<original.turnoN << std::endl;
    casillasInt = new int[144];
    movimiento = new int[2];

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

    std::cout  << "delete tablromovIN" << std::endl;

    std::cout  << "vectorMov.empty()" <<vectorMov.empty()<<std::endl;

    std::cout  << "vectorMov.size()" <<vectorMov.size()<<std::endl;

    if (!vectorMov.empty())
    {

        for(int i = 0; i < vectorMov.size(); i++)
        {
            delete vectorMov.at(i);

            vectorMov.at(i) = NULL;
        }

        //  numeroHijos=0;
        vectorMov.clear();
    }


    std::cout  << "fin" <<std::endl;

}

