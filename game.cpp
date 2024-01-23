//BIBLIOTECA QUE USAMOS PARA FUNCIONES DE ENTRADA Y SALIDA
#include<stdio.h>

//NOS PERMITE DAR UNA POCISION AL CURSOR PARA PODER MANDAR A IMPRIMIR LAS COORDENADAS
#include<windows.h>

//agregamos esta libreria para poder hacer la interaccion con nuestro programa y el usuario y asi poder hacer que detecte si se han precionado las teclas
#include<conio.h>

//VOID ES FUNCION DE TIPO DE DATO QUE NO REGRESA NADA
//gotoxy es una funcion que viene en la biblioteca conio.h de los compiladores de borland
//al agregar dentro del gotxy parametros como son x,y mediante el int nosotros le estamos diciendo al programa que le pasaremos al main los parametros de las coordenadas que estamops colocando ahi
void gotoxy(int x, int y){
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	//los parametros de la estructura coord son los que se le pasan en automatico a nuestro gotoxy
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
}

int main(){
	
	//para controlar la posicion del asterisco vamos a crear dos variables de tipo entero que seran las siguientes x,y
	int x = 10,y = 10;
	
	//ahora gracias a la funcion que realizamos con el gotoxy podemos simplemente llamar a la funcion y colocar las coordenadas donde queramos de una forma mas practica
	gotoxy(x,y);
		printf("*");
		
	//como este es un juego tenemos que hacer que funcione por si solo determinado numero de veces por lo que vamos a tener que crear un bucle con un while o con una funcion de bucle que se adecue a nuestro proyecto
	
	bool game_over = false;
	while(!game_over){
		
		//ahora aremos uso de un if para que podamos interactuar con nuestras teclas y el proframa lo detecte y si se preciona determinada tecla el programa sepa que hacer	
		//la funcion kbhit{} sirve para decir que usaremos teclas
		if(kbhit()){
			
			char tecla = getch();
			
			//colocamos gotoxy como parametro para que al momento de desplazarnos no se quede impreso el asterisco por donde pasamos en luhar de * ponemos solo un espacio dentro de las comillas
			gotoxy(x,y);
				printf(" ");
			
			//ahora aremos que nos podamos desplazar a los lados izquierda y derecha
			//aqui le decimos al programa que si nuestra tecla j es precionada se mueva una posicion hacia la izquierda
			if(tecla == 'j') x--;
			//aqui le decimos al programa que si nuestra tecla l es precionada se mueva una posicion hacia la derecha
			if(tecla == 'l') x++;
			
			//ahora aremos que nos podamos desplazar hacia arriba y hacia abajo
			//aqui le decimos al programa que si nuestra tecla i es precionada se mueva una posicion hacia arriba
			//recuerda que las oordenadas y estan invertidas asi que se debe hacer de forma inversa es decir -- es arriba y ++ es abajo
			if(tecla == 'i') y--;
			//aqui le decimos al programa que si nuestra tecla k es precionada se mueva una posicion hacia abajo
			if(tecla == 'k') y++;
			
			//al colocar nuestro gotoxy aqui evitamos el parpadeo en pantalla de el asterisco al imprimirse muchas veces lo que hace fluido nuestro programa
			gotoxy(x,y);
				printf("*");
		
		}
		
		//para evitar el saturamiento de nuestro procesador y por ende optimizar nuestro juego utilizaremos esta funcion que nos ayudara a que el proceso se detenga cada 30 milisegundos
		Sleep(30);	
	}
	return 0;
	
}