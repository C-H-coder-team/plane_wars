#include"stdc++.h" 
#include"game_struct.h"
#include"game_funcation.h"
#include"game_class.h" 

int main()  
{  
    //��Ϸ׼��  
    srand((int)time(0));    //�������  
    HideCursor();   //���ع��  
    
    Game game;  
    int a = drawMenu();  
    if(a == 2)  
        game.rank = 20;  
    system("cls");  
    drawPlaying();  
    game.Playing();  
}  
