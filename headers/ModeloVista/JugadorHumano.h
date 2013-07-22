#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:
    ~JugadorHumano();
    JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo);
    bool aplicaSeleccion();
bool iniciaTurno();
private:  
    bool esHumano();
   bool casillaSobrevolada(const std::string nombreCasilla);

   bool botonIzquierdo(CEGUI::Vector2<float> pos);
   bool botonDerecho();


};




#endif
