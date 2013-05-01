#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../ModuloIA.h"

class JugadorArtificial : public Jugador
{
public:

    ~JugadorArtificial(void);
    JugadorArtificial(Tablero* tabl);
    void calculaMovimiento();

    bool esHumano();


protected:
    void mueveFicha(float frecuencia);

    int* mueveIA(int origen, int destino);


private:  



};


#endif
