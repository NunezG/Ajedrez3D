#include "../../headers/Modelo/ModeloTablero.h"

ModeloTablero::ModeloTablero() :
    //numeroHijos(0),
    Score(0),
    //fichaMovida(""),
    vectorMov(0),
    turnoN(false),
    alPaso(0)
{
}

ModeloTablero::ModeloTablero( const ModeloTablero& original ):
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

ModeloTablero::~ModeloTablero()
{
    for(int i = 0; i < vectorMov.size(); i++)
    {
        delete vectorMov.at(i);

        vectorMov.at(i) = NULL;
    }
    //  numeroHijos=0;
    vectorMov.clear();
}
