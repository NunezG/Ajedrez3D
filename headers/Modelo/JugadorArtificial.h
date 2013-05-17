#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../Modelo/ModuloIA.h"


class JugadorArtificial : public Jugador
{
public:

    ~JugadorArtificial(void);
    JugadorArtificial(ModeloTablero* tablero);

    bool esHumano();
    void mueveFicha();
    //void setVentana(Ventana* obj);

    int dificultad;

   // void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);


private:
    void calculaMovimiento();
    int* mueveIA(int origen, int destino);






};


#endif
