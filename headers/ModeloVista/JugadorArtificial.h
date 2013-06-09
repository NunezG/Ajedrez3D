#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../Modelo/ArbolBusqueda.h"


class JugadorArtificial : public Jugador
{
public:

    ~JugadorArtificial();
    JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo);

    bool esHumano();
    void mueveFicha();
    //void setVentana(Ventana* obj);



   // void sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada);

    bool activaMovimiento();
    bool casillaSobrevolada(const std::string nombreCasilla);

    int dificultad;

private:
    void calculaMovimiento();



//    ModeloTablero* tableroElegido;
//ModeloTablero* miTablero;

   // bool BorraArbol();



};


#endif
