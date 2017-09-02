#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include "comportamientos/comportamiento.hpp"

using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      ultimaAccion = actIDLE;
      girar_derecha = false;
      bien_situado = false;
      tiempo = 0;
      mochila = 0;
      tirar = false; noRey = true;
    }


        struct Estado{
        	int fila;
        	int columna;
        	int orientacion;
        };

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);

    void rellena(Sensores s);

    void rellena2(Sensores s);

    bool avanza(Sensores sensores);

    void pintaBordes();

    void pintaBosque();

    Action objetoMochila();

    Action recorreMapa(Sensores s, bool puedo, int tiempo);

    void copiaMapa(int f_, int c_);

    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula, tiempo, mochila;
    Action ultimaAccion;
    bool girar_derecha,next,tirar;
    bool bien_situado;
    int MAX_SIZE;
    int miMapa[200][200];
    unsigned char mapaInicial[200][200];
    bool misObjetos[5], noRey;;
    vector<pair<int,int>> reyes;
    Action encerrado;


    // Para el plan
    bool tengo_regalo;
    bool encerrau;
    bool estoy_ejecutando_plan;
    bool error_plan;
    stack<Action> plan;


    //bool pathFinding(const Estado &origen, const Estado &destino, list<Action> &plan);

    void Reiniciar();

};


#endif
