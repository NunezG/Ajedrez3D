#include "../../headers/ModeloVista/Jugador.h"



Jugador::Jugador(EscenaAjedrez* miEscena) :
    jugadorNegras(false),
    nombre(""),
   // miTablero(0)
  //tableroModelo(modeloTablero)
   escena(miEscena)

  //esperaEleccion(false)



{
tablero = escena->tablero;



tableroModelo



        =  escena->

}

Jugador::~Jugador()
{


}


bool Jugador::activaMovimiento()
{



    tableroModelo->jugadaAutorizada = true;




}


bool Jugador::casillaSobrevolada(const std::string nombreCasilla)
{

    Casilla* casillaSobrevolada = static_cast<Casilla*>(tablero->getHijo(nombreCasilla));


    Casilla* casillaSobreAnterior = tablero->getNodoCasillaSobrevolada();

    std::cout << "autorizaCasillaSobrevolada 1111"<<   casillaSobrevolada->getNombre()  << std::endl;
    std::cout << "autorizaCasillaSobrevolada ANTERIOR: "<<   casillaSobreAnterior  << std::endl;

    if (!casillaSobreAnterior || casillaSobrevolada->getNombre() != casillaSobreAnterior-> getNombre())
    {
        if (casillaSobreAnterior)
        {
            casillaSobreAnterior->apagaCasilla();
            //tablero->setNodoCasillaSobrevolada(-1);
        }

        tablero->setNodoCasillaSobrevolada(casillaSobrevolada);


    }else return false;



return true;
}


void Jugador::esperaJugador()
{
    //  std::cout << "espera"<<std::endl;
    // std::cout << "jugadores.size()"<< modelo->jugadores.size()<<std::endl;



            //  std::cout  << "mueveficha " << std::endl;
            mueveFicha();
            //   std::cout  << "miramov " << std::endl;
            //HAY RESULTADO
            if(tableroModelo->jugadaAutorizada)
            {

                std::cout  << "HA AUTORIZADO UN MOVIMIENTO EN EL BUCLE!!! " << std::endl;
                aplicaCambio();
                //  tableroModelo->movimiento[0] = -99;
                // std::cout  << "BORRA tablromov" << std::endl;
            }
            // tablero->setNodoCasillaSeleccionada();
            // tablero->setNodoCasillaSobrevolada();
            //  tablero->actualizaTablero();


    //   modelo->mueveJugador(tablero->getTurnoNegras());

}



std::string Jugador::getNombre()
{

    return nombre;


}



void Jugador::setNombre( std::string unNombre)
{


    nombre = unNombre;
}


int Jugador::aplicaSeleccion()
{

    tableroModelo->mueveTablero();

    std::cout << "cambiatur 6"<< tableroModelo->turnoN<<std::endl;
    // tablero->cambiaTurno();



    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);


    //CAMBIA DE TURNO

    ModeloTablero* turnoSiguiente = new ModeloTablero(*tableroModelo);
    //   tablero->turnoN = !tablero->turnoN;
    bool Jaque = false;

    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);


    std::cout << "cambiatur 7 "<< turnoSiguiente->turnoN<<std::endl;

    if (turnoSiguiente->evaluaJaque())
    {//JAQUE AL REY

        std::cout << "!!!!HA EVALUADO JAQUE AL MOVER FICHA" << std::endl;


        Jaque = true;

    }
    std::cout << "!!!!!!pasa! " << std::endl;

    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Movimientos::pruebaJaqueMate(turnoSiguiente))
    {
        delete turnoSiguiente;
        std::cout << "!!!!!!!!!!!!!!!!!!NO QUEDAN MOVIMIENTOS PARA EL TURNO SIGUIENTE(JAQUE MATE O AHOGADO)!!!: " << std::endl;

        //SE EVALUA EL JAQUE Y SI EL REY NO ESTA EN JAQUE ES QUE ES AHOGADO
        //EVALUA JAQUE
        if (Jaque)
        {
            std::cout << "!!!!!!!!!DEVUELVE JAQUE MATE! " << std::endl;

            //JAQUE MATE
            return 2;
        }
        else
        { //NO HAY JAQUE, AHOGADO, RESULTADO EN TABLAS
            std::cout << "!!!!!!!!!DEVUELVE REY AHOGADO! " << std::endl;

            return 3;
        }

    }else
    {
        delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
            return 4;
        }
        else
        {
            std::cout << "!!!!!!!!!!!!!!!!!!NO HAY JAQUE Y MUEVE BIEN!!!: " << std::endl;

            //Mueve sin jaque
            return 1;
        }
    }


    return 0;

    std::cout << "FIN cambiatur 4 "<< std::endl;
}




bool Jugador::aplicaCambio()
{
    std::cout << "APLICA YA EL MOVIMIENTO DEFINITIVO" << std::endl;

    if (tablero->getNodoCasillaSobrevolada() != NULL)
        tablero->getNodoCasillaSobrevolada()->apagaCasilla();

    tablero->fichaSeleccionada = false;

    // ModeloTablero* tableroModelo = new ModeloTablero();

    //  tableroModelo->casillasInt = tablero->traduceTablero();

    //  tableroModelo->alPaso = tablero->getAlPaso();

    //  tableroModelo->turnoN = tablero->getTurnoNegras();

    int filaSel;
    int colSel;

    int filaNueva;
    int colNueva;

    /* if (tableroModelo->movimiento == NULL)
    {

        filaSel=tablero->getNodoCasillaSeleccionada()->getPosicion().Fila;

        colSel = tablero->getNodoCasillaSeleccionada()->getPosicion().Columna;

        filaNueva = tablero->getNodoCasillaSobrevolada()->getPosicion().Fila;

        colNueva = tablero->getNodoCasillaSobrevolada()->getPosicion().Columna;

    }else
    {*/
    std::cout << "tableroModelo->jugada[0] " << tableroModelo->jugada[0]<< std::endl;
    std::cout << "tableroModelo->jugada[1] " << tableroModelo->jugada[1]<< std::endl;

    filaSel = (tableroModelo->jugada[0]/12)-2;

    colSel = (tableroModelo->jugada[0]%12)-2;

    filaNueva = (tableroModelo->jugada[1]/12)-2;

    colNueva = (tableroModelo->jugada[1]%12)-2;

    std::cout << " ficha que se va a mover: " <<tableroModelo->casillasInt[tableroModelo->jugada[0]]<< std::endl;

    // }

    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    int resultado = aplicaSeleccion();
    std::cout << "ACTUALIZA TABLERO1" << std::endl;

    delete tableroModelo;
    //  std::cout  << "nullea tablromov" << std::endl;
    tableroModelo = NULL;
    //  std::cout  << "ACABA EL MOV!!! " << std::endl;


    //JUGADOR ARTIFICIAL
    if (tablero->getNodoCasillaSeleccionada() == NULL)
    {
        // std::cout << "tableroModelo->jugada[0] en escenaajedrez al aplicar: "<< tableroModelo->jugada[0] << " tableroModelo->jugada[0]/12: "<< tableroModelo->jugada[0]/12 << " tableroModelo->jugada[0]%12 " << tableroModelo->jugada[0]%12 << std::endl;
        // std::cout << "tableroModelo->jugada[1]en escenaajedrez al aplicar: "<< tableroModelo->jugada[1] << " tableroModelo->jugada[1]/12: "<< tableroModelo->jugada[1]/12 << " tableroModelo->jugada[1]%12 " << tableroModelo->jugada[1]%12 << std::endl;

        std::cout << "SELECT 1 FILA: "<< (filaSel*8)+colSel <<std::endl;

        tablero->setNodoCasillaSeleccionada((filaSel * 8) + colSel);

        std::cout << "nombre: "<< tablero->getNodoCasillaSeleccionada()->getNombre()<<std::endl;

        //    seleccionaFichaEnPosicion(filaSel, colSel);

        std::cout << "SELECT 2 FILA: "<< (filaNueva * 8) + colNueva <<std::endl;

        tablero->setNodoCasillaSobrevolada((filaNueva * 8) + colNueva);

        std::cout << "nombre: "<< tablero->getNodoCasillaSobrevolada()->getNombre()<<std::endl;

        //tablero->setNodoCasillaSobrevolada(seleccionaCasillaEnPosicion(filaNueva, colNueva));
    }
    std::cout << "ACTUALIZA TABLERO2" << std::endl;

    tablero->actualizaTablero();

    if (resultado == 1 || resultado == 4)
    {//FICHA MOVIDA

        if (resultado == 4)
        {//JAQUE AL REY
            escena->muestraVentanaEmergente("Jaque");
        }
        //   tablero->actualizaTablero();

        tablero->rotacionCamara = Ogre::Real(180.0f);
        std::cout << "cambia turno" << std::endl;

        tablero->cambiaTurno();
        std::cout << "sale" << std::endl;

        return true;
    }
    else if (resultado == 2)
    {//JAQUE MATE
        std::cout << "JAQUE EVALUADO!!"<< std::endl;
        escena->muestraVentanaEmergente("JaqueMate");

        return false;

    }else if (resultado == 3)
    {
        //REY AHOGADO (TABLAS)
        std::cout << "REY AHOGADO (TABLAS)!!"<< std::endl;
        escena->muestraVentanaEmergente("Tablas");

    }
    return false;
}
