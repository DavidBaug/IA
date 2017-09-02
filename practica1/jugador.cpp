#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

// --------------------------------------------------------------------------------------------------------------------------------------


bool ComportamientoJugador::avanza(Sensores sensores){

	bool resultado = true;

	if (sensores.superficie[2]!='_')
		resultado = false;


	if (sensores.terreno[2] == 'B' && !misObjetos[2])
		resultado = false;
	else if (sensores.terreno[2] == 'A' && !misObjetos[1])
		resultado = false;
	else if (sensores.terreno[2] == 'P')
		resultado = false;
    else if (sensores.terreno[2] == 'M')
        resultado = false;

	return resultado;

}

// --------------------------------------------------------------------------------------------------------------------------------------


Action ComportamientoJugador::objetoMochila(){

	if (last_action == actPOP)
		return actPUSH;
	else if (last_action == actPUSH)
		return actPOP;

}

// --------------------------------------------------------------------------------------------------------------------------------------


Action ComportamientoJugador::recorreMapa(Sensores s, bool puedo){

	int left=0, right=0, front=0, minimo;
	Action accion;
	miMapa[fila][columna]+=1;

	switch(brujula){ // Norte
		case 0:
			left = miMapa[fila][columna-1];
			right = miMapa[fila][columna+1];
			front = miMapa[fila-1][columna];

			if(!avanza(s) && !puedo)
				miMapa[fila-1][columna] += 100;

			break;

		case 1: // Este
			left = miMapa[fila-1][columna];
			right = miMapa[fila+1][columna];
			front = miMapa[fila][columna+1];

			if(!avanza(s) && !puedo)
				miMapa[fila][columna+1] += 100;
			break;

		case 2: // Sur
			left = miMapa[fila][columna+1];
			right = miMapa[fila][columna-1];
			front = miMapa[fila+1][columna];

			if(!avanza(s) && !puedo)
				miMapa[fila+1][columna] += 100;

			break;

		case 3: // Oeste
			left = miMapa[fila+1][columna];
			right = miMapa[fila-1][columna];
			front = miMapa[fila][columna-1];

			if(!avanza(s) && !puedo)
				miMapa[fila][columna-1] += 100;

			break;

	}

	if (front <= left and front <=right and (avanza(s) or puedo)){
		accion = actFORWARD;
	}else if(left <= right){
		accion = actTURN_L;
	}else
		accion = actTURN_R;


	return accion;

}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::pintaBordes() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			mapaResultado[i][j] = 'P';
			mapaResultado[j][i] = 'P';
			if (i != 3) {
				mapaResultado[MAX_SIZE - i - 1][j] = 'P';
				mapaResultado[j][MAX_SIZE - i - 1] = 'P';
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::pintaBosque() {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (mapaResultado[i][j] == '?') {
				mapaResultado[i][j] = 'B';
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::actualizar(Action last, Sensores s){

	if (s.reset) {
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 200; j++) {
				miMapa[i][j] = 0;
				mapaInicial[i][j] = '?';
			}
		}
		fila = 99;
		columna = 99;
		brujula = 0;
	}

	switch(last){
		case actFORWARD:
		    if (!s.colision){
                switch(brujula){
                    case 0:
                        fila--; break;
                    case 1:
                        columna++; break;
                    case 2:
                        fila++; break;
                    case 3:
                        columna--; break;
                }
		    }
            break;
		case actTURN_L:
			brujula = (brujula+3)%4;
			break;
		case actTURN_R:
			brujula = (brujula+1)%4;
			break;
        case actIDLE:
            break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------


void ComportamientoJugador::capturaPK(Sensores s){

	fila = s.mensajeF;
	columna = s.mensajeC;
	orientado = true;

}
// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::copiaMapa(int f_, int c_){

	int dX, dY;

	if (fila - f_ < 0)
		dX = f_ - fila;
	else
		dX = fila - f_;

	if (columna - c_ < 0)
		dY = c_ - columna;
	else
		dY = columna - c_;


	pintaBordes();

	for (int i = 0; i < 100; ++i){
		for (int j = 0; j < 100; ++j){

			mapaResultado[i][j] = mapaInicial[i+dX][j+dY];
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::rellena2(Sensores s){

    switch(brujula){
        case 0:

            mapaInicial[fila-1][columna-1] = s.terreno[1];
            mapaInicial[fila-1][columna] = s.terreno[2];
            mapaInicial[fila-1][columna+1] = s.terreno[3];


            mapaInicial[fila-2][columna-2] = s.terreno[4];
            mapaInicial[fila-2][columna-1] = s.terreno[5];
            mapaInicial[fila-2][columna] = s.terreno[6];
            mapaInicial[fila-2][columna+1] = s.terreno[7];
            mapaInicial[fila-2][columna+2] = s.terreno[8];

            mapaInicial[fila-3][columna-3] = s.terreno[9];
            mapaInicial[fila-3][columna-2] = s.terreno[10];
            mapaInicial[fila-3][columna-1] = s.terreno[11];
            mapaInicial[fila-3][columna] = s.terreno[12];
            mapaInicial[fila-3][columna+1] = s.terreno[13];
            mapaInicial[fila-3][columna+2] = s.terreno[14];
            mapaInicial[fila-3][columna+3] = s.terreno[15];

            break;
        case 1:

            mapaInicial[fila-1][columna+1] = s.terreno[1];
            mapaInicial[fila][columna+1] = s.terreno[2];
            mapaInicial[fila+1][columna+1] = s.terreno[3];

            mapaInicial[fila-2][columna+2] = s.terreno[4];
            mapaInicial[fila-1][columna+2] = s.terreno[5];
            mapaInicial[fila][columna+2] = s.terreno[6];
            mapaInicial[fila+1][columna+2] = s.terreno[7];
            mapaInicial[fila+2][columna+2] = s.terreno[8];

            mapaInicial[fila-3][columna+3] = s.terreno[9];
            mapaInicial[fila-2][columna+3] = s.terreno[10];
            mapaInicial[fila-1][columna+3] = s.terreno[11];
            mapaInicial[fila][columna+3] = s.terreno[12];
            mapaInicial[fila+1][columna+3] = s.terreno[13];
            mapaInicial[fila+2][columna+3] = s.terreno[14];
            mapaInicial[fila+3][columna+3] = s.terreno[15];


            break;
        case 2:

            mapaInicial[fila+1][columna+1] = s.terreno[1];
            mapaInicial[fila+1][columna] = s.terreno[2];
            mapaInicial[fila+1][columna-1] = s.terreno[3];

            mapaInicial[fila+2][columna+2] = s.terreno[4];
            mapaInicial[fila+2][columna+1] = s.terreno[5];
            mapaInicial[fila+2][columna] = s.terreno[6];
            mapaInicial[fila+2][columna-1] = s.terreno[7];
            mapaInicial[fila+2][columna-2] = s.terreno[8];

            mapaInicial[fila+3][columna+3] = s.terreno[9];
            mapaInicial[fila+3][columna+2] = s.terreno[10];
            mapaInicial[fila+3][columna+1] = s.terreno[11];
            mapaInicial[fila+3][columna] = s.terreno[12];
            mapaInicial[fila+3][columna-1] = s.terreno[13];
            mapaInicial[fila+3][columna-2] = s.terreno[14];
            mapaInicial[fila+3][columna-3] = s.terreno[15];

            break;
        case 3:

            mapaInicial[fila+1][columna-1] = s.terreno[1];
            mapaInicial[fila][columna-1] = s.terreno[2];
            mapaInicial[fila-1][columna-1] = s.terreno[3];

            mapaInicial[fila+2][columna-2] = s.terreno[4];
            mapaInicial[fila+1][columna-2] = s.terreno[5];
            mapaInicial[fila][columna-2] = s.terreno[6];
            mapaInicial[fila-1][columna-2] = s.terreno[7];
            mapaInicial[fila-2][columna-2] = s.terreno[8];

            mapaInicial[fila+3][columna-3] = s.terreno[9];
            mapaInicial[fila+2][columna-3] = s.terreno[10];
            mapaInicial[fila+1][columna-3] = s.terreno[11];
            mapaInicial[fila][columna-3] = s.terreno[12];
            mapaInicial[fila-1][columna-3] = s.terreno[13];
            mapaInicial[fila-2][columna-3] = s.terreno[14];
            mapaInicial[fila-3][columna-3] = s.terreno[15];

            break;


    }

}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::rellena(Sensores s){

    switch(brujula){
        case 0:

            mapaResultado[fila-1][columna-1] = s.terreno[1];
            mapaResultado[fila-1][columna] = s.terreno[2];
            mapaResultado[fila-1][columna+1] = s.terreno[3];


            mapaResultado[fila-2][columna-2] = s.terreno[4];
            mapaResultado[fila-2][columna-1] = s.terreno[5];
            mapaResultado[fila-2][columna] = s.terreno[6];
            mapaResultado[fila-2][columna+1] = s.terreno[7];
            mapaResultado[fila-2][columna+2] = s.terreno[8];

            mapaResultado[fila-3][columna-3] = s.terreno[9];
            mapaResultado[fila-3][columna-2] = s.terreno[10];
            mapaResultado[fila-3][columna-1] = s.terreno[11];
            mapaResultado[fila-3][columna] = s.terreno[12];
            mapaResultado[fila-3][columna+1] = s.terreno[13];
            mapaResultado[fila-3][columna+2] = s.terreno[14];
            mapaResultado[fila-3][columna+3] = s.terreno[15];

            break;
        case 1:

            mapaResultado[fila-1][columna+1] = s.terreno[1];
            mapaResultado[fila][columna+1] = s.terreno[2];
            mapaResultado[fila+1][columna+1] = s.terreno[3];

            mapaResultado[fila-2][columna+2] = s.terreno[4];
            mapaResultado[fila-1][columna+2] = s.terreno[5];
            mapaResultado[fila][columna+2] = s.terreno[6];
            mapaResultado[fila+1][columna+2] = s.terreno[7];
            mapaResultado[fila+2][columna+2] = s.terreno[8];

            mapaResultado[fila-3][columna+3] = s.terreno[9];
            mapaResultado[fila-2][columna+3] = s.terreno[10];
            mapaResultado[fila-1][columna+3] = s.terreno[11];
            mapaResultado[fila][columna+3] = s.terreno[12];
            mapaResultado[fila+1][columna+3] = s.terreno[13];
            mapaResultado[fila+2][columna+3] = s.terreno[14];
            mapaResultado[fila+3][columna+3] = s.terreno[15];


            break;
        case 2:

            mapaResultado[fila+1][columna+1] = s.terreno[1];
            mapaResultado[fila+1][columna] = s.terreno[2];
            mapaResultado[fila+1][columna-1] = s.terreno[3];

            mapaResultado[fila+2][columna+2] = s.terreno[4];
            mapaResultado[fila+2][columna+1] = s.terreno[5];
            mapaResultado[fila+2][columna] = s.terreno[6];
            mapaResultado[fila+2][columna-1] = s.terreno[7];
            mapaResultado[fila+2][columna-2] = s.terreno[8];

            mapaResultado[fila+3][columna+3] = s.terreno[9];
            mapaResultado[fila+3][columna+2] = s.terreno[10];
            mapaResultado[fila+3][columna+1] = s.terreno[11];
            mapaResultado[fila+3][columna] = s.terreno[12];
            mapaResultado[fila+3][columna-1] = s.terreno[13];
            mapaResultado[fila+3][columna-2] = s.terreno[14];
            mapaResultado[fila+3][columna-3] = s.terreno[15];

            break;
        case 3:

            mapaResultado[fila+1][columna-1] = s.terreno[1];
            mapaResultado[fila][columna-1] = s.terreno[2];
            mapaResultado[fila-1][columna-1] = s.terreno[3];

            mapaResultado[fila+2][columna-2] = s.terreno[4];
            mapaResultado[fila+1][columna-2] = s.terreno[5];
            mapaResultado[fila][columna-2] = s.terreno[6];
            mapaResultado[fila-1][columna-2] = s.terreno[7];
            mapaResultado[fila-2][columna-2] = s.terreno[8];

            mapaResultado[fila+3][columna-3] = s.terreno[9];
            mapaResultado[fila+2][columna-3] = s.terreno[10];
            mapaResultado[fila+1][columna-3] = s.terreno[11];
            mapaResultado[fila][columna-3] = s.terreno[12];
            mapaResultado[fila-1][columna-3] = s.terreno[13];
            mapaResultado[fila-2][columna-3] = s.terreno[14];
            mapaResultado[fila-3][columna-3] = s.terreno[15];

            break;


    }

}

// --------------------------------------------------------------------------------------------------------------------------------------

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	actualizar(last_action, sensores);

	if (sensores.vida == 1){
		pintaBosque();
	}

	// Orientar
	if (!orientado && sensores.terreno[0] == 'K'){
		int f_ = fila;
		int c_ = columna;

		capturaPK(sensores);
		copiaMapa(f_,c_);
	}

	if (orientado){
        rellena(sensores);
	}else
        rellena2(sensores);

	if (next){					//Guarda objeto tras cogerlo
    	next = false;
    	accion = actPUSH;
    }else{
		switch (sensores.superficie[2]){
			case '0':
				if(!misObjetos[0]){
					accion = actPICKUP;
					misObjetos[0] = true;
					next = true;
				}

				break;

			case '1':
				if(!misObjetos[1]){
					accion = actPICKUP;
					misObjetos[1] = true;
					next = true;
				}

				break;

			case '2':
				if(!misObjetos[2]){
					accion = actPICKUP;
					misObjetos[2] = true;
					next = true;
				}

				break;

			case '3':
				if(!misObjetos[3]){
					accion = actPICKUP;
					misObjetos[3] = true;
					next = true;
				}

				break;

		}
	}


    if(accion == actIDLE){

		//*************************** AGUA + BIKINI

		if (sensores.terreno[2] == 'A' && sensores.objetoActivo == '1'){
			accion = recorreMapa(sensores,true);
		}else if (sensores.terreno[2] == 'A' && misObjetos[1]){
			accion = objetoMochila();

		//***************************  BOSQUE + ZAPATILLAS

		}else if (sensores.terreno[2] == 'B' && sensores.objetoActivo == '2'){				// 0 - Hueso
			accion = recorreMapa(sensores,true);											// 1 - Bikini
		}else if(sensores.terreno[2] == 'B' && misObjetos[2]){								// 2 - Zapatillas
			accion = objetoMochila();														// 3 - Llave
	    }else if (sensores.superficie[2] == 'a'){
	    	accion = actIDLE;
	    }else{
	        accion = recorreMapa(sensores,false);
	    
	    }

    }


    









	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Mochila: " << sensores.mochila << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
	cout << endl;



	last_action = accion;

	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
