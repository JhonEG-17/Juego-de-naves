#include<stdio.h>
#include<windows.h>
#include<conio.h>
//PARA PODER HACER USO DE LOS RAD() O RANGOS NECESITAMOS DE UNA LIBRERIA NUEVA Y ESPECIAL PARA ELLO Y ES LA SIGUIENTE....
#include<stdlib.h>

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

void pintar_limites(){
	
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
	int corazones;
	int vidas;
	
	
public:
	
	NAVE(int _x, int _y, int _corazones, int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
	
		void pintar();
		void borrar();
		void mover();
		void pintar_corazones();
		void morir();
};

void NAVE::pintar(){
	
	gotoxy(x,y);   printf("  %c",30);
	gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2); printf("%c%c %c%c",30,190,190,30);
	
}

void NAVE::borrar(){
	
	gotoxy(x,y);   printf("        ");
	gotoxy(x,y+1); printf("        ");
	gotoxy(x,y+2); printf("        ");
	
}

void NAVE::mover(){
	
	if(kbhit()){
		
		char tecla = getch();
		
			borrar(); 
				
				if(tecla == IZQUIERDA && x>3) x--;
				if(tecla == DERECHA && x+6<77) x++;
				if(tecla == ARRIBA && y>4) y--;
				if(tecla == ABAJO && y+3<33) y++;
				if(tecla == 'e')corazones--;
				
			pintar();
			
			pintar_corazones();
	}
	
}

void NAVE::pintar_corazones(){
	
	gotoxy(50,2);   printf("VIDAS %d",vidas);
	gotoxy(64,2);   printf("Salud");
	gotoxy(70,2);   printf("      ");
	
	for(int i = 0 ; i < corazones; i++){
		
		gotoxy(70+i,2);   printf("%c",3);
	
	}
}

void NAVE::morir(){
	
	if(corazones == 0){
		
		borrar();
		gotoxy(x,y);	printf("   **   ");
		gotoxy(x,y+1);	printf("  ****  ");
		gotoxy(x,y+2);	printf("   **   ");
		Sleep(200);
		
		borrar();
		gotoxy(x,y);	printf(" * ** *");
		gotoxy(x,y+1);	printf("  **** ");
		gotoxy(x,y+2);	printf(" * ** *");
		Sleep(200);
		
		borrar();
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();
		
	}
	
}

//AHORA CREAREMOS UNA NUEVA CLASE PARA CREAR NUESTROS ASTEROIDES
class AST{
	
	//LE DAMOS UNAS COORDENADAS ANUESTRA CLASE
	int x,y;
	
//GENERAMOS LOS ASCPECTOS QUE SERAN PUBLICOS	
public:
	
	//CREAMOS NUESTRO CONSTRUCTOR
	AST(int _x, int _y):x(_x),y(_y){}
	
	//LLAMMOS A NUESTRA FUNCION PINTAR Y MOVER
	void pintar();
	void mover();
	
};

//AHORA CREAMOS NUESTRA FUNCION PINTAR PARA NUESTRO ASTEROIDE YA QUE NO PODEMOS USAR LA MISMA FUNCION DE LA NAVE POR OBVIAS RAZONES
void AST::pintar(){
	
	//NOS SITUAMOS EN LAS COORDENADAS Y MANDAMOS A IMPRIMIR NUESTRO ASTEROIDE EN DICHAS COORDENAS CON EL GOTOXY Y PRINTF
	gotoxy(x,y);
		printf("%c",154);
		
	
}

//AHORA REALIZAMOS NUESTRA FUNCION MOVER SIMILAR A LA ANTERIOR EN ESTRUCTURA
void AST::mover(){
	
	//PRIMERO BORRAREMOS EL RASTRO DEL ASTEROIDE IGUALMENTE USANDO GOTOXY Y PRINTF
	gotoxy(x,y);
		printf(" ");
		y++;
		//ahora hay que darle un limite para nuestro asteroide
		//para ello usaremos un if para dar los rango de coordenadas donde pueden caer nuestros asteroides
		if(y > 32){
			//nuestro rango debe estar limitado al de nuestro marco
			//como nuestro rango del marco del juego esta limitado de 2 a 77 entonces debemos indicar que no puede
			//pintar ni borrar mas alla de dicho rango para ello lo indicaremos de esta forma...
			x = rand()%71 + 4;
			y = 4;	
		}
	
	//AHORA AEMOS USO DE LA FUNCION PINTAR PARA HACER QUE SE PINTE NUESTRO ASTEROIDE
	pintar();
	
}

int main(){

	OcultarCursor();
	
	pintar_limites();
	
	NAVE N(7,7,3,3);
	
	N.pintar();
	N.pintar_corazones();
	
	//aora debemos llamar a nuestro objeto de los asteroides a la escena
	//esto junto a su constructor para ello lo haremos de la siguiente forma
	//podemos colocar un asteroide o do o tres o cuantos queramos para ello solo debemos
	//agregarlos de la siguiente forma por ejemplo "ast1(4,8),ast2(10,4),ast(15,10);"
	//y de igual forma llamar a cada uno con su funcion mover en nuestro while colocando "ast1.mover"
	//y asi consecutivamente
	AST ast(10,4);
	
	bool game_over = false;
	
	while(!game_over){
		
		//ahora para que se mueva debemos agregar su funcion mover de nuestro asteroide para ello aremos lo siguiente
		ast.mover();
		N.morir();
		N.mover();
				
		Sleep(30);	
	}
	
	return 0;
	
}