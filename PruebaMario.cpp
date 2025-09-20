#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>
#include "rlutil.h"

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;
/*
void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);

}
*/
void OcultarCursor (){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cci;///creo un objeto
    cci.dwSize = 2;///variable tipo entera que puede ir de 1 a 100
    cci.bVisible = FALSE;/// puede tomar dos valores, falso o verdadero (true se mostrara en pantalla)
    ///elimina el parpadeo del cursor
    SetConsoleCursorInfo(hCon, &cci);/// debemos pasar por referencia

}
void pintar_limites(){

    for(int i= 2 ; i<90; i++){
        gotoxy (i,3); printf("%c", 205);
        gotoxy (i,28); printf("%c", 205);
    }
    for(int i=4; i<28; i++){
        gotoxy (2,i); printf("%c", 186);
        gotoxy (89,i); printf("%c", 186);
    }
    gotoxy (2,3); printf("%c", 201);
    gotoxy (2,28); printf("%c", 200);
    gotoxy (89,3); printf("%c", 187);
    gotoxy (89,28); printf("%c", 188);
///rlutil::setBackgroundColor(rlutil::LIGHTBLUE);

}

class PERSONAJE{
    ///atributos privados
    int x,y;
    int corazones;
    int vidas;
public:
    ///constructor, inicializa los atributos de la clase del objeto
    PERSONAJE(int _x, int _y, int _corazones, int _vidas);
    int X(){ return x;}
    int Y(){ return y;}
    void COR(){ corazones--;}
    void pintar();
    void borrar();
    void mover();
    void pintarCorazones();
    void morir ();

};
///Dfiniendo el constructor
PERSONAJE::PERSONAJE(int _x, int _y, int _corazones, int _vidas){
    x = _x;
    y = _y;
    corazones = _corazones;
    vidas = _vidas;

}
/*otra forma de definir el constructor es esta
NAVE::NAVE(int _x, int _y): x (_x), y (_y){}

*/
void PERSONAJE::pintar(){///le digo que es una funcion de la clase
    gotoxy (x,y);    printf("   %c ", 210);
    gotoxy (x, y+1); printf(" %c %c %c ", 178, 177, 176);
    gotoxy (x, y+2); printf("%c %c %c %c", 60, 190, 190, 62);
    gotoxy (x, y+3); printf(" %c %c %c ", 219,178 ,219);
    gotoxy (x, y+4); printf(" %c %c %c ", 219,177, 219);
    gotoxy (x, y+5); printf(" %c    %c ", 219, 219);
    gotoxy (x, y+6); printf(" %c    %c ", 212, 212);


}
void PERSONAJE::borrar(){
    gotoxy(x,y);   printf("         ");
    gotoxy(x,y+1); printf("         ");
    gotoxy(x,y+2); printf("          ");
    gotoxy(x,y+3); printf("          ");
    gotoxy(x,y+4); printf("          ");
    gotoxy(x,y+5); printf("          ");
    gotoxy(x,y+6); printf("          ");
}
void PERSONAJE::mover(){
    if(kbhit()){///kbhit verifica si se presiono una tecla
            char tecla = getch();///funcion de biblioteca conio, guarda el valor de lo presionado en la variable tecla
            borrar();
            if(tecla == IZQUIERDA && x>3) x--;///si pongo el numero  igual lo toma
            if(tecla == DERECHA && x+6 < 85) x++;
            if(tecla == ARRIBA && y>4) y--;
            if(tecla == ABAJO && y+6 <27) y++;
            if(tecla == 'e') corazones--;
            pintar();
            pintarCorazones();
    }

}
void PERSONAJE::pintarCorazones(){
    gotoxy (50,2); printf("VIDAS %d", vidas);
    gotoxy (64,2); printf("Salud");
    gotoxy (70,2); printf("      ");
    for(int i=0; i<corazones; i++){
        gotoxy(70+i,2); printf("%c", 2661);
    }


}
void PERSONAJE::morir(){
    if(corazones == 0){
        borrar();
        gotoxy(x,y);    printf("   **    ");
        gotoxy(x,y+1);  printf("  ****   ");
        gotoxy(x,y+2);  printf("   **    ");
        Sleep(200);

        borrar();
        gotoxy(x,y);    printf(" * ** *");
        gotoxy(x,y+1);  printf("  **** ");
        gotoxy(x,y+2);  printf(" * ** *");
        Sleep(200);
        borrar();
        vidas--;
        corazones = 3 ;
        pintarCorazones ();
        pintar ();

    }


}

///clase OBSTACULOS
class OBSTACULOS{
    int x,y;
public:
    OBSTACULOS(int _x, int _y): x(_x), y (_y){}
    void pintar();
    void mover();
    int X(){return x;}
    int Y(){return y;}

};
void OBSTACULOS::pintar(){
    gotoxy (x,y); printf("%c", 178);
    gotoxy (x, y+1); printf("%C",178 );
    gotoxy (x, y+2); printf("%C",178 );
    gotoxy (x+1, y+1); printf("%C",178 );
    gotoxy (x+1, y+2); printf("%C",178 );
    gotoxy (x+2, y+1); printf("%C",178 );
    gotoxy (x+2, y+1); printf("%C",178 );
    gotoxy (x+1, y+1); printf("%C",178 );


}

void OBSTACULOS::mover(){
    gotoxy(x,y);printf(" ");
    y++;
    if(y > 22){
        x = rand()%71 + 4;
        y = 4;
    }
    pintar();

}/
int main(){
    ///rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
    OcultarCursor();
    pintar_limites();
    PERSONAJE MARIO(7, 10, 3, 3);/// Asigno un nombre al objeto
    MARIO.pintar();
    MARIO.pintarCorazones();
    OBSTACULOS LADRILLO(5,7);
    LADRILLO.pintar();

    bool game_over = false;
    while(!game_over){/// se ejecuta mientras la variable sea verdadera

            MARIO.mover();

            }
            MARIO.morir();
            MARIO.mover();

            Sleep(30);



    return 0;
}
