#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void){
    int steps = 0, xytab[10][2]={0}, i, j, table[6][12] = { '.','.','@','.','.','.','.','#','.','.','7','.',
                                                            '.','.','.','.','.','.','.','#','.','.','.','.',
                                                            '#','#','#','#','.','#','#','#','.','.','.','.',
                                                            '.','.','.','.','.','.','.','.','.','.','@','.',
                                                            '.','B','.','.','.','.','.','#','.','.','.','.',
                                                            '.','.','.','.','.','.','@','#','.','.','.','.'};
    int hx = 4, hy = 1;
    int mx = 0, my = 10;
    int n = 6;
    int m = 12;
    int cmx = mx, cmy = my, flagx=0, flagy =0;
    if(hx> mx){
        flagx = hx - mx;
    }
    else{
        flagx = mx - hx;
    }
    if(hy > my){
        flagy = hy - my;
    }
    else{
        flagy = my - hy;
    }
    while(hx != mx || hy != my && steps !=10){
        for(i=1; i< flagx+1; i++){
            if(table[mx+i][my] == '#' || table[mx+i][my] == '@'){
                break;
            }
            else{
                cmx++;
                steps++;
            }
        }
        for(i=0; i<flagy; i++){
            if(table[mx][my+i] == '#' || table[mx][my+i] == '@'){
                break;
            }
            else{
                cmy++;
                steps++;
            }
        }
    }
    return 0;
}