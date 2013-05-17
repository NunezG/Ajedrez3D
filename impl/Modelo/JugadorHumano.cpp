#include "../../headers/Modelo/JugadorHumano.h"



JugadorHumano::JugadorHumano(ModeloTablero* tablero) :
    Jugador(tablero)
  
  
  
{
    
}

JugadorHumano::~JugadorHumano()
{
    
    
}

//void JugadorHumano::setVentana(Ventana* obj){
//ventana = obj;
//}

void JugadorHumano::mueveFicha()
{



    
    //HA CAPTUURADO MOVIMIENTO??
    
    // if (miTablero->g)
    
    //esperaEleccion = true;
    
    //punteroVentana.capture();
    
}



//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int JugadorHumano::autorizaCasilla(tipoFicha tipo, int filaSel, int colSel, int filaNueva, int colNueva){
    
    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    bool autorizado= true;


   // miTablero->casillasInt = miTablero->traduceTablero();

    if (miTablero->turnoN)Autorizaciones::normalizaTablero(miTablero->casillasInt);

    autorizado = Autorizaciones::autorizaCasilla(miTablero, tipo, filaSel, colSel, filaNueva, colNueva);
    
    std::cout << "autorizado en autorizacasilla: "<<autorizado << std::endl;

    
    if(autorizado)
    {
        //EVALUA EL JAQUE CON LA FICHA YA MOVIDA

        //si esta ocupado y no es comestible

        int* tableroInt = mueveTablero(filaSel, colSel, filaNueva, colNueva);
        
        if(!miTablero->turnoN)Autorizaciones::normalizaTablero(tableroInt);
        else return 0;

        std::cout << "evalua jaque" << std::endl;
        
        //EVALUA JAQUE
        if (!Autorizaciones::evaluaJaque(tableroInt, !miTablero->turnoN))
        {

            
            // miTablero->getNodoCasillaSobrevolada()->seleccionada = true;
            //ILUMINA LA CASILLA


            std::cout << "ES COMESTIBLE" << std::endl;
            return 1;
        }else
        {

            std::cout << "JAQUE AL REY" << std::endl;


            
            
            
            return 3;

        }
    }
    std::cout << "sale de autorizado" << std::endl;
    
    
}



int JugadorHumano::aplicaSeleccion( int filaSel, int colSel, int filaNueva, int colNueva)
{
    // esperaEleccion = false;

    miTablero->casillasInt == mueveTablero( filaSel,  colSel,  filaNueva,  colNueva);


    
    std::cout << "cambiatur 6"<< std::endl;
   // miTablero->cambiaTurno();
    
    miTablero->turnoN = miTablero->turnoN;

   // if(miTablero->getTurnoNegras()) miTablero->casillasInt = miTablero->traduceTablero();
    
    Autorizaciones::generaMovimientos(static_cast<ModeloTablero*>(miTablero));
    
    std::cout << "cambiatur 7 "<< std::endl;
    
    if (miTablero->vectorMov.size() == 0)
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;

        return 2;
        

        
    }else
    {
        return 1;

    }
    
    
    std::cout << "FIN cambiatur 4 "<< std::endl;
}



bool JugadorHumano::esHumano()
{
    return true;
}

//void JugadorHumano::sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada)
//{
    /*if(miTablero->fichaSeleccionada)
        {
        
        
                Casilla* casilla = static_cast<Casilla*>(miTablero->getHijo(casillaSobrevolada->getName()));
                
                if (miTablero->getNodoCasillaSobrevolada()==NULL || casilla->getNombre() != miTablero->getNodoCasillaSobrevolada() -> getNombre())
                {
                    if (miTablero->getNodoCasillaSobrevolada()!=NULL){
                        miTablero->getNodoCasillaSobrevolada()->apagaCasilla();
                        miTablero->setNodoCasillaSobrevolada(NULL);
                    }
                    miTablero->setNodoCasillaSobrevolada(casilla);
                    
                    //AUTORIZA
                     static_cast<JugadorHumano*>(modelo->jugadores.at(miTablero->getTurnoNegras()))->autorizaCasilla();
                }
            }
        }
*/
    
//}
