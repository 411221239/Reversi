#include <stdio.h>
#include <string.h>

#define Chessboard_size 8
#define Empty 0
#define Black 1
#define White 2
#define Color Piece_color(p_row,p_col)
#define Enter -1
#define Search -2

int p_row,p_col,z,c;
int chess[Chessboard_size][Chessboard_size]={
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,2,0,0,0},
    {0,0,0,2,1,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}};
int chess_next[Chessboard_size][Chessboard_size]={0};
    
//輸出指定位置的棋子顏色
int Piece_color(int r,int c){
    return chess[r][c];
}

//當找到可以走的方向時，向前尋找空格
//若遇見與自己相同顏色，直接跳出
int Possible(int slopeX,int slopeY,int function,int a,int b){
    for(int m=2;slopeX*m+p_row>=0 && slopeX*m+p_row<8 && slopeY*m+p_col<8 && slopeY*m+p_col>=0;m++){
        if(function==Enter){
            if(chess[p_row+slopeX*m][p_col+slopeY*m] == Color) break;
            if(chess[p_row+slopeX*m][p_col+slopeY*m] == Empty) {
                chess_next[p_row+slopeX*m][p_col+slopeY*m]=Color;
                c++;
                //printf("(%d, %d) ",p_row+slopeX*m,p_col+slopeY*m);
                break;
            }
        }
        if(function==Search){
            if(chess[a+slopeX*m][b+slopeY*m] == Piece_color(a,b)) break;
            if(chess[a+slopeX*m][b+slopeY*m] == Empty) {
                chess_next[a+slopeX*m][b+slopeY*m]=Piece_color(a,b);
                if(Piece_color(a,b)==Black) c++;
                if(Piece_color(a,b)==White) z++;
                break;
            }
        }
    }
}

//尋找可以走的方向，re_color為相反顏色
int Find_location(int re_color,int function,int a,int b){
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(function==Enter){
                if((i==0 && j==0) || chess[p_row+i][p_col+j] == Empty) continue;
                if(chess[p_row+i][p_col+j] == re_color) {
                    Possible(i,j,function,Empty,Empty);
                }
            }
            if(function==Search){
                if((i==0 && j==0) || chess[a+i][b+j] == Empty) continue;
                if(chess[a+i][b+j] == re_color) {
                    Possible(i,j,function,a,b);
                }
            }
        }
   }
}

int Check_Color(int function){
    c=0,z=0;
    memset(chess_next,0,sizeof(chess_next));
    for(int i=0;i<Chessboard_size;i++){
        for(int j=0;j<Chessboard_size;j++){
            if(chess[i][j] == Black){
                
                Find_location(White,function,i,j);
                
            }
            if(chess[i][j] == White){
                
                Find_location(Black,function,i,j);
            }
        }
    }
}

void Print_board(int function){
    if(function==Enter) {
        for(int i=0;i<Chessboard_size;i++){
            for(int j=0;j<Chessboard_size;j++){
                if(chess_next[i][j] != Empty){ 
                    //printf("%d ",c);
                    printf("(%d, %d)",i,j);
                    c--;
                    if(c>0) printf(", ");
                }
            }
            
        }
        printf("\n");
    }
    if(function==Search) {
        printf("白子可以下的位置：\n");
        for(int i=0;i<Chessboard_size;i++){
            for(int j=0;j<Chessboard_size;j++){
                if(chess_next[i][j] == White){ 
                    //printf("%d ",c);
                    printf("(%d, %d)",i,j);
                    z--;
                    if(z>0) printf(", ");
                }
            }
            
        }
        printf("\n");
        printf("黑子可以下的位置：\n");
        for(int i=0;i<Chessboard_size;i++){
            for(int j=0;j<Chessboard_size;j++){
                if(chess_next[i][j] == Black){
                    //printf("%d ",c);
                    printf("(%d, %d)",i,j);
                    c--;
                    if(c>0) printf(", ");
                }
            }
            
        }
    }
}


int main(){
    
    char position[3];
    scanf("%s",position);
    
    //將輸入的文字轉換座標
    p_row = position[0]-'0';
    p_col = position[2]-'0';
    
    switch(Piece_color(p_row,p_col)){
        case Empty :
            printf("不能下");
            break;
        case Black :
            c=0;
            memset(chess_next,0,sizeof(chess_next));
            Find_location(White,Enter,Empty,Empty);
            Print_board(Enter);
            break;
            //因為要尋找可以翻轉的棋子，所以輸入相反顏色
        case White :
            c=0;
            memset(chess_next,0,sizeof(chess_next));
            Find_location(Black,Enter,Empty,Empty);
            Print_board(Enter);
            break;
            //因為要尋找可以翻轉的棋子，所以輸入相反顏色
    }
    
    //開始找黑白棋各自可以下哪裡
    Check_Color(Search);
    Print_board(Search);
    return 0;
}



