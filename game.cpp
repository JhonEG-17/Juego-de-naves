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
	//AHORA CREAREMOS UNA FUNCION QUE SE LLAME ¨VIDAS¨ PARA QUE NUESTRA NAVE TENGA SOLO UNAS CUANTAS OPORTUNIDADES DE JUEGO
	int vidas;
	
	
public:
	
	
//TAMBIEN EN EL CONSTRUCTOR INICIAMOS NUESTRA FUNCION VIDAS
	NAVE(int _x, int _y, int _corazones, int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	//AHORA AGREGAREMOS UNA FUNCION QUE ENLACE NUESTROS CORAZONES A LAS VIDAS Y EL NUMERO DE ESTAS DECRESCA CADA VES QUE PERDEMOS PARA ESTE CASO
	//PERDEREMOS UNA VIDA POR CADA 3 CORAZONES
	//PARA HACER ELLO AGREGAREMOS LA FUNCION "MORIR"
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
	
	
	//AHORA NOS ENCONTRAMSO EN LA FUNCION  DE PINTAR CORAZONES PUESTO QUE ESTA VA RELACIONADA CON NUSTRAS VIDAS EN EL JUEGO
	//AGREGAREMOS LA FUNCION GOTOXY JUNTO A NUESTRO PRINTF PARA MANDAR A IMPRIMIR LA FRASE "VIDAS" EN LA POCISION QUE MAS NOS CONVENGA
	//ADEMAS DE SEGUIDO COLOCAR QUE IMPRIMIREMOS UN NUMERO DE LA CLASE QUE ES NUESTRA FUNCION VIDAS
	gotoxy(50,2);   printf("VIDAS %d",vidas);
	gotoxy(64,2);   printf("Salud");
	gotoxy(70,2);   printf("      ");
	
	for(int i = 0 ; i < corazones; i++){
		
		gotoxy(70+i,2);   printf("%c",3);
	
	}
}

//AHORA CREAREMOS LA FUNCION QUE NOS DARA LAS VIDAS RESTANTES O EN OTRAS PALABRAS LA FUNCION MORIR
void NAVE::morir(){
	
	//AHORA INICIAREMOS UN IF PARA QUE ESTA FUNCION SSE PUEDA REPETIR A MANERA DE BUCLE CADA VES QUE UNA CONDICION SE CUMPLA
	if(corazones == 0){
		
		//AL MORIR AREMOS NOTAR AL USUARIO QUE A PERDIDO POR ELLO AREMOS QUE SE BORE LA NAVE PARA QUE EL USUARIO LO PUEDA IDENTIFICAR
		borrar();
		//POSTERIORMENTE A BORRAR LA NAVE AREMOS QUE SE IMPRIMA UNA ANIMACION PARA CREAR UNA EXPLOCION Y PARESCA QUE LA NAVE DEL JUGADOR EXPLOTO TRAS PERDER
		gotoxy(x,y);	printf("   **   ");
		//ponemos y+1 para indicar que vamos en la segunda linea de nuestra nave
		gotoxy(x,y+1);	printf("  ****  ");
		//asi tambien ponemos y+2 para indicar que vamos en la tercera linea de nuestra nave
		gotoxy(x,y+2);	printf("   **   ");
		//ahora daremos una pausa moentanea al sistema para que veamos bien la imagen que estamos imprimiendo para simular la explocion
		Sleep(200);
		
		//ahora repetimos el proceso pero cambiando de lugar los asteriscos para asi poder crear nuestra animacion
		borrar();
		gotoxy(x,y);	printf(" * ** *");
		gotoxy(x,y+1);	printf("  **** ");
		gotoxy(x,y+2);	printf(" * ** *");
		Sleep(200);
		
		//AHORA LLAMAMOS A NUESTRA FUNCION DE BORRADO PARA QUE SE ELIMINE LA EXPLOCION Y LA NAVE SE PINTE NUEVAMENTE DE FORMA CORRECTA
		borrar();
		//AHORA QUE FINALIZAMOS NUESTRA ANIMACION PUES AREMOS QUE EL ATRIBUTO VIDAS DECRESCA YA QUE EMOS PERDIDO
		//PARA ELLO AREMOS LO SIGUIENTE...
		//COLOCAMOS NUESTRA FUNCION VIDAS Y LE INDICAMOS QUE SIEMPRE QUE PERDAMOS DECRESCA ESTO LO HACEMOS DE LA SIGUIENTE FORMA...
		vidas--;
		//AHORA NUESTROS CORAZONES SE VOLVERAN A LLENAR COMPLETOS PUESTO QUE NOS QUEDAN 2 VIDAS MAS
		//ESO LO AREMOS DE LA SIGUIENTE FORMA LLAMANDO A CORAZONES Y INDICANDO QUE SERAN TRES DE NUEVA CUENTA USANDO UN =
		corazones = 3;
		//ahora los mandamos a imprimir de nuevo los corazones para que el usuario sepa que le quedan dichos intentos mas
		//esto ya que pueden llegarse a borrar o a imprimirse doble ves los corazones y no lo hacemos de esta forma
		//entonces para esto llamamos a nuestra funcion de pintar_corazones de nueva cuenta de la siguiente forma...
		pintar_corazones();
		//POR ULTIMO PINTAMOS DE NUEVA CUENTA A LA NAVE PARA QUE EL JUGADOR INICIE DE NUEVA CUENTA A JUGAR
		pintar();
		
	}
	
}

int main(){

	OcultarCursor();
	
	pintar_limites();
	
	//AHORA DEBEMOS MODIFICAR EL PARAMETRO EN EL MAIN DE NUESTRA NAVE YA QUE DEBEMOS AGREGAR NUESTRA FUNCION VIDAS QUE ESTARA DEL MISMO NUMERO QUE EL DE NUESTROS CORAZONES
	NAVE N(7,7,3,3);
	
	N.pintar();
	N.pintar_corazones();
	
	bool game_over = false;
	
	while(!game_over){
		
		//AHORA PARA TERMINAR CON ESTA ANIMACION Y ESTA FUNCION DE VIDAS VAMOS A LLAMAR A NUESTRA FUNCION MORIR EN EL MAIN PARA QUE ESTA FUNCIONE CORRECTAMENTE
		N.morir();
		N.mover();
				
		Sleep(30);	
	}
	
	return 0;
	
}