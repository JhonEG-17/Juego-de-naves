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

//AHORA VAMOS A CREAR LOS LIMITES O LOS MARCOS DE NUESTRO VIDEOJUEGO PARA ELLO USAREMOS LA FUNCION VOID Y LE DAREMOS EL NOMBRE DE "pintar_limites"

void pintar_limites(){
	
	//PARA NO TENER QUE HACERLO UNO POR UNO VAMOS A HACER UsO DEl FOR PARA QUE SE PINTE TODOS LOS MARCOS DE UNA SOLA VES
	//COMENZAREMOS CON LOS MARCOS DE ARRIBA Y ABAJO ASI COMO LOS LATERALES
	
	for(int i = 2 ; i < 78 ; i++){
		
		gotoxy(i,3);
			printf("%c",205);
		
		gotoxy(i,33);
			printf("%c",205);
		
	}
	
	for(int i = 4 ; i < 33 ; i++){
		
		gotoxy(2,i);
			printf("%c",186);
		
		gotoxy(77,i);
			printf("%c",186);
			
	}
	
	//AHORA PINTAREMOS LOS BORDES O LA ESQUINAS
	
	gotoxy(2,3);
		printf("%c",201);
	gotoxy(2,33);
		printf("%c",200);
	gotoxy(77,3);
		printf("%c",187);
	gotoxy(77,33);
		printf("%c",188);
	
}

class NAVE{
	
	int x,y;
	//para nuestra barra de salud vamos a tener que agregar otra variable la llamaremos "corazones"
	int corazones;
	
public:
	
	//como podras notar nosotros hemos movido de lugar al constructor ahora dentro de nuestra clase en la seccion publica
	//ahi agregaremos los siguientes parametros "int _corazones" y "corazones(_corazones)"
	NAVE(int _x, int _y, int _corazones): x(_x),y(_y),corazones(_corazones){}
	void pintar();
	void borrar();
	void mover();
	//ahora aremos nuestra barra de salud con una funcion que se llamara "pintar_corazones"
	void pintar_corazones();
};

void NAVE::pintar(){
	
	gotoxy(x,y);   printf("  %c",30);
	gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);
	
}

void NAVE::borrar(){
	
	gotoxy(x,y);   printf("     ");
	gotoxy(x,y+1); printf("     ");
	gotoxy(x,y+2); printf("     ");
	
}

void NAVE::mover(){
	
	if(kbhit()){
		
		char tecla = getch();
		
			borrar(); 
				
				//AHORA AREMOS LOS LIMITES DE NUESTRO ESCENARIO PARA ELLO LE INDICAREMOS A NUESTRA FUNCION DE MOVER NE LA PARTE DE LOS IF LO SIGUIENTE
				//AREMOS QUE NUESTRA NAVE SE PUEDA MOVER SIEMPRE Y CUANDO SE PRECIONE LA TECLA QUE YA SELECCIONAMOS Y CON UN "&&"
				//Y POSTERIOR A ELLO INDICAREMOS QUE SOLO SI LA COORDENADA X ES MAYOR QUE 3 "X>3"
				if(tecla == IZQUIERDA && x>3) x--;
				if(tecla == DERECHA && x+6<77) x++;
				if(tecla == ARRIBA && y>4) y--;
				if(tecla == ABAJO && y+3<33) y++;
				//ahora agregamos un if que nos servira para despues crear la interaccion de perdida de vida
				if(tecla == 'e')corazones--;
			pintar();
			
			//de forma rapida colocaremos la funcion de pintar corazones en esta parte de aqui de la siguiente manera
			pintar_corazones();
	}
	
}

//ahora crearemos una funcion para pintar nuestros corazones de nueva cuenta usando un void con nuestra clase nave y nuestro parametro pintar_corazones
//usando el gotoxy imprimiremos la palabra salud y luego de un espacio colocaremos un for para que ahora si imprimamos nuestros corazones 

void NAVE::pintar_corazones(){
	
	gotoxy(64,2);   printf("Salud");
	gotoxy(70,2);   printf("      ");
	for(int i = 0 ; i < corazones; i++){
		
		gotoxy(70+i,2);   printf("%c",3);
		
	}
}

int main(){

	OcultarCursor();
	
	//AQUI AGREGAREMOS NUESTRA NUEVA FUNCION "pintar_limites" PARA QUE NUESTRO PROGRAMA LOS MUESTRE EN NUESTRA PANTALLA
	pintar_limites();
	
	NAVE N(7,7,3);
	N.pintar();
	//aqui agregamos nuestra funcion pintar corazones de igual forma para qu se muestre en pantalla una ves inicie el juego
	N.pintar_corazones();
	
	bool game_over = false;
	while(!game_over){
		
		N.mover();
				
		Sleep(30);	
	}
	return 0;
	
}