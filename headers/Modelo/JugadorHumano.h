#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"


class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano(void);
    JugadorHumano(Tablero* tabl);
 bool esHumano();

 bool esperaSeleccion;



 void movimientoSeleccionado();





protected:
    void mueveFicha(float frecuencia);




private:  



};


#endif
