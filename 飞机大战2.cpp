#include"stdc++.h" 
#include"game_struct.h"
#include"game_funcation.h"
#include"game_class.h" 

int main()  
{  
    //游戏准备  
    srand((int)time(0));    //随机种子  
    HideCursor();   //隐藏光标  
    
    Game game;  
    int a = drawMenu();  
    if(a == 2)  
        game.rank = 20;  
    system("cls");  
    drawPlaying();  
    game.Playing();  
}  
