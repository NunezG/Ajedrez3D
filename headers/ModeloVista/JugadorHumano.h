#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:
    ~JugadorHumano();
    JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo);
private:  
    bool esHumano();
   bool casillaSobrevolada(const std::string nombreCasilla);


};


#endif
