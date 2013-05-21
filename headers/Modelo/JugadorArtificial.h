#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
//#include "../Modelo/ModuloIA.h"


class JugadorArtificial : public Jugador
{
public:

    ~JugadorArtificial(void);
    JugadorArtificial();

    bool esHumano();
    void mueveFicha();
    //void setVentana(Ventana* obj);

    int dificultad;

   // void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);


private:
    void calculaMovimiento();
    int* mueveIA(int origen, int destino);

    int evaluaTablero(const int casillasInt[144], bool turnoN);

    int alphaBeta(ModeloTablero* table,int alpha,int beta,const int depthleft );

    short valorFicha(const tipoFicha tipo);


    bool construyeArbol(ModeloTablero* tableroPadre);


    ModeloTablero* tableroElegido;
ModeloTablero* miTablero;

   // bool BorraArbol();



};


#endif
