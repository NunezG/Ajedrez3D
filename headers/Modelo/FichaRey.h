#ifndef __FichaRey_
#define __FichaRey_

#include "Ficha.h"

class FichaRey : public Ficha
{
public:

    ~FichaRey(void);
    FichaRey(std::string nombre);

protected:

    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);


private:  



};

#endif
