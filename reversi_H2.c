#include <stdio.h>

#define Chessboard_size 8
#define Empty 0
#define Black 1
#define White 2
#define Color Piece_color(p_row,p_col)

int chess[Chessboard_size][Chessboard_size]={0};
int p_row,p_col;

//輸出指定位置的棋子顏色
int Piece_color(int r,int c){
    return chess[r][c];
}

//當找到可以走的方向時，向前尋找空格
//若遇見與自己相同顏色，直接跳出
int Possible(int slopeX,int slopeY){
    for(int m=2;slopeX*m+p_row>=0 && slopeX*m+p_row<8 && slopeY*m+p_col<8 && slopeY*m+p_col>=0;m++){
        if(chess[p_row+slopeX*m][p_col+slopeY*m] == Color) break;
        if(chess[p_row+slopeX*m][p_col+slopeY*m] == Empty) {
            printf("(%d,%d)",p_row+slopeX*m,p_col+slopeY*m);
            break;
        }
    }
}

//尋找可以走的方向，re_color為相反顏色
int Find_location(int re_color){
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if((i==0 && j==0) || chess[p_row+i][p_col+j] == Empty) continue;
            if(chess[p_row+i][p_col+j] == re_color) Possible(i,j);
        }
    }
}



int main()
{
    char position[3];
    
    for(int i=0;i<Chessboard_size;i++){
        for(int j=0;j<Chessboard_size;j++){
            scanf("%d",&chess[i][j]);
        }
    }
    
    scanf("%s",position);
    
    //將輸入的文字轉換座標
    p_row = position[0]-'0';
    p_col = position[2]-'0';
    
    switch(Piece_color(p_row,p_col)){
        case Empty :
            printf("不能下");
        case Black :
            Find_location(White);
            //因為要尋找可以翻轉的棋子，所以輸入相反顏色
        case White :
            Find_location(Black);
            //因為要尋找可以翻轉的棋子，所以輸入相反顏色
    }
    return 0;
}


