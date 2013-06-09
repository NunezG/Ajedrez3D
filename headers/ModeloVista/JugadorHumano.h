#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:
    ~JugadorHumano();
    JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo);

    bool esHumano();
    void mueveFicha();
    bool activaMovimiento();
   bool casillaSobrevolada(const std::string nombreCasilla);

protected:



private:  




};


#endif
