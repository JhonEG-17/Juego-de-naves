#include<stdio.h>
#include<windows.h>
#include<conio.h>

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

void OcultarCursor(){
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	
	cci.dwSize = 2;
	
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon, &cci);
	
}

//UNA CLASE ES LA DEFINICION DE OBJETOS OSEA DEFINIR LO QUE ES UNA CASA UN BARCO ETC, DENTRO DE ESTA CLASE PODEMOS DEFINIRLOS TRIBUTOS Y LOS METODOSQUE SON LAS FORMAS EN QUE ACTUAN EN CIERTA CIRCUNSTANCIA
//UN EJEMPLO ES UNA PELOTA NOSOTROS DEFINIMOS QUE TENEMOS UNA PELOTA CON COORDENADAS QUE SERIAN LOS ATRIBUTOS Y SUS METODOS SERIAN QUE SE VE AFECTADA POR LA GRABEDAD Y LA FUERZA DE IMPULSO 

//PARA DEFINIR NUESTRO OBJETO "NAVE" AREMOS LO SIGUIENTE...
//COLOCAREMOS NUESTRA CLASE "CLASS" PARA DEFINIR NUESTRO OBJETO LLAMADO "NAVE"

class NAVE{
	
	//AHORA DAREMOS LOS ATRIBUTOS QUE SON NUESTRAS COORDENADAS
	//los datos dentro de este int son de caracter "privados" llamados asi por que no se les podra hacer uso fuera de nuestra estructura de codigo "clase"
	int x,y;
	//sin embargo se puede hacer publico o accecible un tipo de dato de nuestra clase que sera la siguiente y de la siguiente porma colocando la estructura "public" y todo lo que este dentro del mismo sera accecible fuera de la estructura de cogido
public:
	//ahora necesitamos un constructor que es el que nos pintara o hara visible nuestra nave a este se le da el mismo nombre que le damos a la clase en este caso sera "NAVE"
	NAVE(int _x, int _y);
	void pintar();
	void borrar();
	void mover();
	
};

//AHORA CREAMOS NUESTRO CONSTRUCTOR PARA ESTO HAY DOS FORMAS POEMOS USAR CUALQUIERA DE LAS DOS AMBAS FUNCIONAN IGUAL SOLO UNA ES MAS ESTETICA A LA VISTA DEL DESARROLLADOR Y OTRA UN POCO MENOS
//esta es la opcion 1

//NAVE::NAVE(int _x, int _y): x(_x),y(_Y){}

//esta es la opcion 2 para el constructor
//esta parte se puede colocar en esta parte del codigo o dentro de la clase en la parte publica
NAVE::NAVE(int _x, int _y){
	
	x = _x;
	y = _y;
	
}

//AHORA VAMOS A DEFINIR LAS FUNCIONES PARA ESTO SE HACE USO DEL VOID Y DE NUESTRA CLASE SEGUIDO DE NUESTRA FUNCION AREMOS LO MISMO PARA CADA FUNCION COMO PODEMOS OBSERVAR
void NAVE::pintar(){
	//ahora para imprimirlo aremos uso de nuestro gotoxy y de la funcion printf asi como de el coddigo ascii
	gotoxy(x,y);   printf("  %c",30);
	gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);
	
}

void NAVE::borrar(){
	
	gotoxy(x,y);   printf("     ");
	gotoxy(x,y+1); printf("     ");
	gotoxy(x,y+2); printf("     ");
	
}

//para esta parte vamos a cambiar la funcion de movimiento de nuestras flechas a esta parte y reemplaaremos la funcion de gotoxy de borrar y de impirmir el asterisco poor nuestras nuevas funciones para borrar y pintar

void NAVE::mover(){
	
	if(kbhit()){
		
		char tecla = getch();
		
			borrar(); 
			
				if(tecla == IZQUIERDA) x--;
				if(tecla == DERECHA) x++;
				if(tecla == ARRIBA) y--;
				if(tecla == ABAJO) y++;
			
			pintar();
	}
	
}

int main(){

	OcultarCursor();
	
	//esta parte que teniamos anteriormente para imprimir el asterisco de nuestro juego ya no nos sirve por lo que se elimina
	//int x = 10,y = 10;
	//
	//gotoxy(x,y);
	//	printf("*");
	
	//AHORA LLAMAREMOS A NUESTRA NAVE U OBJETO PARA INICIALIZARLA EN NUESTRO MAIN
	NAVE N(7,7);
	//HACEMOS USO DE LA FUNCION PINTAR PARA QUE NUESTRA NAVE APARESCA COLOCANDO N.pintar() 
	N.pintar();
	
	bool game_over = false;
	while(!game_over){
		
		//AHORA PARA PODER MOVER NUESTRA NAVE COMO MOVIMOS DE LUGAR LAS FUNCIONES DE MOVER VAMOS A SOLO LLAMAR A LA FUNCION MOVER DE LA SIGUIENTE FORMA
		N.mover();
				
		Sleep(30);	
	}
	return 0;
	
}