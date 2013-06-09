#ifndef __BaseJuego_h_
#define __BaseJuego_h_

#include "../Vistas/Ventana.h"
#include "../Modelo/Modelo.h"

class BaseJuego
{
public:
    void go(void);
    BaseJuego(void);
    ~BaseJuego(void);

protected:

    Ventana* punteroVentana;
    ModeloVista* modeloVista;
    Modelo* modelo;
};

#endif // #ifndef __BaseJuego_h_
