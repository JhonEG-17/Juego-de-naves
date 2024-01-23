#include<stdio.h>
#include<windows.h>
#include<conio.h>


//DEFINIMOS ALGUNAS FUNCIONES QUE SERAN NUESTRAS FLECHAS DIRECCIONALES DE NUESTRO TECLADO PARA SUSTITUIR LAS LETRAS POR LAS FLECHAS  PARA MOVERNOS DENTRO DEL JUEGO
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y){
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
}

//ahora para ocultar el cursor utilizaremos la funcion void de nueva cuenta dandole nombre a nuestra funcion como ocultar cursor para hacerlo mas entendible
void OcultarCursor(){
	
	//volvemos a colocar nuestro handle para poder usar la funcion que tenemos en nuestra biblioteca que see llama gestorcursorinfo con el que podemos controlar las caracteristicas de nuestrop cursor y que se muestre en pantalla
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	//para hacer uso de nuestra nueva funcion "SetConsoleCursorInfo" vamos a realizar algo similar a lo que realizamos con "dwPos" solo que ahora en lugar de coordenadas seran otras instrucciones referentes a la visibilidad de nuestro cursor
	CONSOLE_CURSOR_INFO cci;
	
	//el primer atributo es par adarle un grosor a nuestro cursor mientras mas grande mas grueso y visible sera
	cci.dwSize = 2;
	//el segundo atributo es para darle visibilidad por ello "false" significa apagado o desactivado y "true" activado, visible, o encendido
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon, &cci);
	
}



int main(){
	
	OcultarCursor();
	int x = 10,y = 10;
	
	gotoxy(x,y);
		printf("*");
		
	bool game_over = false;
	while(!game_over){
		
		if(kbhit()){
			
			char tecla = getch();
			
			gotoxy(x,y);
				printf(" ");
			
			//AHORA PODEMOS MOVERNOS CON LAS FLECHAS HACIENDO REFERENCIA A LAS FUNCIONES QUE PREDEFINIMOS AL COMIENZO DEL CODIGO PODEMOS HACER USO DEL NUMERO O DE LA PALABRA CORRESPNDIENTE POR EJEMPO PODEMOS PONER "ARRIBA" O EL NUMERO "72" Y FUNCIONARA DE IGUAL FORMA
			if(tecla == IZQUIERDA) x--;
			if(tecla == DERECHA) x++;
			if(tecla == ARRIBA) y--;
			if(tecla == ABAJO) y++;
			
			gotoxy(x,y);
				printf("*");
		}
		Sleep(30);	
	}
	return 0;
	
}