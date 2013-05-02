#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:

    ~JugadorHumano(void);
    JugadorHumano(Tablero* tablero);

    bool esHumano();


    //void setVentana(Ventana* obj);
    void mueveFicha(float time);

    void aplicaSeleccion();

    void autorizaCasilla();

    void sobreVuelaCasilla();


protected:




private:  
   // Ventana* ventana;



};


#endif
