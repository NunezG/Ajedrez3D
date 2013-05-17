#include "../../headers/Modelo/JugadorHumano.h"



JugadorHumano::JugadorHumano(Tablero* tablero) :
    Jugador(tablero)
  , ventanaJaque(NULL)
  
  
  
{
    
}

JugadorHumano::~JugadorHumano()
{
    
    
}

//void JugadorHumano::setVentana(Ventana* obj){
//ventana = obj;
//}

void JugadorHumano::mueveFicha(float time){
    
    //HA CAPTUURADO MOVIMIENTO??
    
    // if (miTablero->g)
    
    //esperaEleccion = true;
    
    //punteroVentana.capture();
    
}

void JugadorHumano::sobreVuelaCasilla(){
    miTablero->getNodoCasillaSobrevolada()->iluminaCasilla();
    //  miTablero->getNodoCasillaSobrevolada()->seleccionada = false;

}

void JugadorHumano::autorizaCasilla(tipoFicha tipo, posicion seleccionado, posicion sobrevolado){
    
    //Autoriza la casilla sobrevolada para mover ficha (no mira si la casilla está ocupada)
    bool autorizado= true;


    if (ventanaJaque != NULL)
        ventanaJaque->setVisible(false);

    miTablero->casillasInt = miTablero->traduceTablero();

    if (miTablero->getTurnoNegras())normalizaTablero(miTablero->casillasInt);

    autorizado = Autorizaciones::autorizaCasilla(miTablero, tipo, seleccionado, sobrevolado);
    
    std::cout << "autorizado en autorizacasilla: "<<autorizado << std::endl;

    
    if(autorizado)
    {
        //EVALUA EL JAQUE CON LA FICHA YA MOVIDA

        //si esta ocupado y no es comestible

        int* tableroInt = miTablero->mueveYTraduceTablero();
        
        if(!miTablero->getTurnoNegras())Autorizaciones::normalizaTablero(tableroInt);

        std::cout << "evalua jaque" << std::endl;
        
        //EVALUA JAQUE
        if (!Autorizaciones::evaluaJaque(tableroInt, !miTablero->getTurnoNegras()))
        {
            
            // miTablero->getNodoCasillaSobrevolada()->seleccionada = true;
            //ILUMINA LA CASILLA
            sobreVuelaCasilla();

            std::cout << "ES COMESTIBLE" << std::endl;
        }else
        {

            std::cout << "JAQUE AL REY" << std::endl;

            //  ventanaJaque = NULL;

            if (!CEGUI::WindowManager::getSingleton().isWindowPresent("Jaque"))
            {
                std::cout << "VENTANA YA EXISTE" << std::endl;

                ventanaJaque = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueCEED.layout");
                //  newWindow->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

                CEGUI::System::getSingleton().getGUISheet()->addChildWindow(ventanaJaque);
            }else {
                ventanaJaque = CEGUI::WindowManager::getSingleton().getWindow("Jaque");
                ventanaJaque->setVisible(true);

            }


            
            
            
            
            
        }
    }
    std::cout << "sale de autorizado" << std::endl;
    
    
}


int* JugadorHumano::mueveTablero()
{

    int* tableroTraducido = traduceTablero();

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );

    int posFinal = 24+(getNodoCasillaSobrevolada()->getPosicion().Fila*12) + getNodoCasillaSobrevolada()->getPosicion().Columna+2;

    int posInicial = 24+(getNodoCasillaSeleccionada()->getPosicion().Fila*12) + getNodoCasillaSeleccionada()->getPosicion().Columna+2;


    tableroTraducido[posFinal]= tableroTraducido[posInicial];
    tableroTraducido[posInicial] = 0;




    return tableroTraducido;
}


void JugadorHumano::aplicaSeleccion()
{
    // esperaEleccion = false;
    miTablero->actualizaTablero(miTablero->getNodoCasillaSeleccionada()->getPosicion(), miTablero->getNodoCasillaSobrevolada()->getPosicion());
    miTablero->fichaSeleccionada = false;
    std::cout << "cambiatur 4 "<< std::endl;
    std::cout << "cambiatur 5 "<< std::endl;
    
    std::cout << "cambiatur 6"<< std::endl;
    miTablero->cambiaTurno();
    
    if(miTablero->getTurnoNegras()) miTablero->casillasInt = miTablero->traduceTablero();
    
    Autorizaciones::generaMovimientos(static_cast<ModeloTablero*>(miTablero));
    
    std::cout << "cambiatur 7 "<< std::endl;
    
    if (miTablero->vectorMov.size() == 0)
    {
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS (JAQUE MATE O AHOGADO)!!!: " << std::endl;
        
        std::cout << "JAQUE EVALUADO!!"<< std::endl;
        CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout("JaqueMateCEED.layout");
        CEGUI::System::getSingleton().getGUISheet()->addChildWindow(newWindow);
        
    }else {
        miTablero->rotacionCamara = Ogre::Real(180.0f);
    }
    
    
    std::cout << "FIN cambiatur 4 "<< std::endl;
}



bool JugadorHumano::esHumano()
{
    return true;
}

void JugadorHumano::sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada)
{
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
    
}
