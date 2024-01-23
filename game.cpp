#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y){
	
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
}

int main(){
	
	gotoxy(15,10);
		printf("*");
	
	int x = 10,y = 10;
	
	bool game_over = false;
	while(!game_over){
		
		gotoxy(x,y);
			printf("*");
		if(kbhit()){
			
			char tecla = getch();
			if(tecla == 'j') x--;
			if(tecla == 'l') x++;
			if(tecla == 'i') y--;
			if(tecla == 'k') y++;	
		}	
	}
	return 0;
	
}