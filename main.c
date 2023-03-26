#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <term.h>

int array[6][6];
int komak[6][6];
int score = 0,n = 0;
void create();
void komaki(int array[6][6]);
void harekatw(int array[6][6],int k);
void harekata(int array[6][6],int k);
void harekats(int array[6][6],int k);
void harekatd(int array[6][6],int k);
void komaki(int komak[6][6]){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            komak[i][j] = array[i][j];
}
void chart(){
    system("clear");
    printf("           score = %d\n\n",score);
    for(int i = 0; i < 4; i++){
        printf("---------------------------------\n");
        for(int j = 0; j < 4; j++){
            if(array[i][j] != 0){
                int ctr = 0;
                int hold = array[i][j];
                while(hold > 0){
                    hold /= 10;
                    ctr++;
                }
                int z = ctr - 1;
                printf("|");
                for(int m = 0;m < 4 - ctr;m++){
                    printf(" ");
                }
                printf("%d", array[i][j]);
                for(int m = 0;m < 4 - (ctr - z) ;m++){
                    printf(" ");
                }
            }
            else
                printf("|      %s"," ");
        }
        printf("|");
        printf("\n");
    }
    printf("---------------------------------\n");
    printf("           up = w\n");
    printf("           down = s\n");
    printf("           right = a\n");
    printf("           left = d\n");
    if(n == 1){
        printf("You win!");
    }
    if(n == 0){
        for(int i = 0;i < 4 ;i++){
            for(int j = 0;j < 4;j++){
                if(array[i][j] == 2048){
                    printf("You win!");
                    n = 1;
                    break;
                }
            }
        }
    }
}
int main(){
    int m = 0;
    while(1){
        int m1 = 0, m2 = 0;
        int ctra = 0, ctrs = 0, ctrd = 0, ctrw = 0;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                if(array[i][j] == komak[i][j] && m != 0){
                    m1++;
                    if(array[i][j] != 0)
                        m2++;
                }
        if(m1 != 16){
            create();
            chart();
        }
        else{
            if(m2 != 16){
                chart();
                printf("You can't do this move. Please choose another one\n");
            }
            else{
                int checker = 0;
                int helper = 0;
                komaki(komak);
                harekata(komak, ctra);
                for(int i = 0; i < 4; i++)
                    for(int j = 0; j < 4; j++)
                        if(komak[i][j] == array[i][j])
                            helper++;
                if(helper != 16){
                    checker = 1;
                    ctra = 1;
                    ctrd = 1;
                }
                if(checker == 0){
                    helper = 0;
                    komaki(komak);
                    harekatw(komak, ctrw);
                    for(int i = 0; i < 4; i++)
                        for(int j = 0; j < 4; j++)
                            if(komak[i][j] == array[i][j])
                                helper++;
                    if(helper != 16){
                        checker = 1;
                        ctrw = 1;
                        ctrs = 1;
                    }
                }
                if(checker == 0){
                    printf("Game Over\n");
                }
            }
        }
        m++;
        if(m2 != 16){
            char x;
            x = getchar();
            if(x == '\n' || x == ' ')
                x = getchar();
            getchar();
            komaki(komak);

            switch(x){
                case'w':
                    harekatw(array, ctrw);
                    break;
                case'W':
                    harekatw(array, ctrw);
                    break;
                case'a':
                    harekata(array, ctra);
                    break;
                case'A':
                    harekata(array, ctra);
                    break;
                case's':
                    harekats(array, ctrs);
                    break;
                case'S':
                    harekats(array, ctrs);
                    break;
                case'd':
                    harekatd(array, ctrd);
                    break;
                    
                case'D':
                    harekatd(array, ctrd);
                    break;
            }
        }
        else{
            while(1){
                char x;
                x = getchar();
                if(x == '\n' || x == ' ')
                    x = getchar();
                getchar();
                if(x == 'w' || x == 'W'){
                    if(ctrw == 1){
                        harekatw(array, ctrw);
                        break;
                    }
                    else
                        printf("You can't do this move. Please choose another one\n");
                }
                if(x == 's' || x == 'S'){
                    if(ctrs == 1){
                        harekats(array, ctrs);
                        break;
                    }
                    else
                        printf("You can't do this move. Please choose another one\n");
                }
                if(x == 'd' || x == 'D'){
                    if(ctrd == 1){
                        harekatd(array, ctrd);
                        break;
                    }
                    else
                        printf("You can't do this move. Please choose another one\n");
                }
                if(x == 'a' || x == 'A'){
                    if(ctra == 1){
                        harekata(array, ctra);
                        break;
                    }
                    else
                        printf("You can't do this move. Please choose another one\n");
                }
            }

        }
    }
    return 0;
}
void create(){
    int  b = rand();
    b %= 10;
    if(b>7){
        while(1){
            int c = rand();
            int d = rand();
            c = c % 4;
            d = d % 4;
            if(array[c][d] == 0){
                array[c][d] = 4;
                break;
            }
        }
    }
    else{
        while(1){
            int c = rand();
            int d = rand();
            c = c % 4;
            d = d % 4;
            if(array[c][d] == 0){
                array[c][d] = 2;
                break;
            }
        }
    }
}
void harekatw(int array[6][6],int k){
    for(int j = 0;j < 4; j++){
        for(int i = 0;i < 4;i++){
            if(array[i][j] != 0){
                for(int k = 0 ; k < i ;k++){
                    if(array[k][j] == 0)
                    {
                        int help = array[k][j];
                        array[k][j] = array[i][j];
                        array[i][j] = help;
                    }
                }
            }
        }
        
    }
    for(int j = 0; j < 4; j++){
        if(array[0][j] == array[1][j]){
            array[0][j] *= 2;
            if(k == 0){
                score += array[0][j];
            }
            array[1][j] = array[2][j];
            array[2][j] = array[3][j];
            array[3][j] = 0;
        }
        if(array[1][j] == array[2][j]){
            array[1][j] *= 2;
            if(k == 0){
            score += array[1][j];
            }
            array[2][j] = array[3][j];
            array[3][j] = 0;
        }
        if(array[2][j] == array[3][j]){
            array[2][j] *= 2;
            if(k == 0){
            score += array[2][j];
            }
            array[3][j] = 0;
        }
    }
    
}
void harekata(int array[6][6],int k){
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4; j++){
            if(array[i][j] != 0){
                for(int k = 0; k < j; k++){
                    if(array[i][k] == 0){
                        int help = array[i][k];
                        array[i][k] = array[i][j];
                        array[i][j] = help;
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < 4; i++){
        if(array[i][0] == array[i][1]){
            array[i][0] *= 2;
             if(k == 0){
            score += array[i][0];
             }
            array[i][1] = array[i][2];
            array[i][2] = array[i][3];
            array[i][3] = 0;
        }
        if(array[i][1] == array[i][2]){
            array[i][1] *= 2;
             if(k == 0){
            score += array[i][1];
             }
            array[i][2] = array[i][3];
            array[i][3] = 0;
        }
        if(array[i][2] == array[i][3]){
            array[i][2] *= 2;
             if(k == 0){
            score += array[i][2];
             }
            array[i][3] = 0;
        }
    }
}
void harekats(int array[6][6],int k){
    for(int j = 3;j >= 0; j--){
        for(int i = 3;i >= 0;i--){
            if(array[i][j] != 0){
                for(int k = 3 ; k > i;k--){
                    if(array[k][j] == 0)
                    {   int help = array[k][j];
                        array[k][j] = array[i][j];
                        array[i][j] = help;
                        break;
                    }
                }
            }
        }
        
    }
    for(int j = 0; j < 4; j++){
        if(array[3][j] == array[2][j]){
            array[3][j] *= 2;
             if(k == 0){
            score += array[3][j];
             }
            array[2][j] = array[1][j];
            array[1][j] = array[0][j];
            array[0][j] = 0;
        }
        if(array[2][j] == array[1][j]){
            array[2][j] *= 2;
             if(k == 0){
            score += array[2][j];
             }
            array[1][j] = array[0][j];
            array[0][j] = 0;
        }
        if(array[1][j] == array[0][j]){
            array[1][j] *= 2;
             if(k == 0){
            score += array[1][j];
             }
            array[0][j] = 0;
        }
    }
}
void harekatd(int array[6][6],int k){
    for(int i = 3; i >= 0;i--){
        for(int j = 3; j >= 0; j--){
            if(array[i][j] != 0){
                for(int k = 3; k > j; k--){
                    if(array[i][k] == 0){
                        int help = array[i][k];
                        array[i][k] = array[i][j];
                        array[i][j] = help;
                    }
                }
            }
        }
    }
    for(int i = 0; i < 4; i++){
        if(array[i][3] == array[i][2]){
            array[i][3] *= 2;
             if(k == 0){
            score += array[i][3];
             }
            array[i][2] = array[i][1];
            array[i][1] = array[i][0];
            array[i][0] = 0;
        }
        if(array[i][2] == array[i][1]){
            array[i][2] *= 2;
             if(k == 0){
            score += array[i][2];
             }
            array[i][1] = array[i][0];
            array[i][0] = 0;
        }
        if(array[i][1] == array[i][0]){
            array[i][1] *= 2;
             if(k == 0){
            score += array[i][1];
             }
            array[i][0] = 0;
        }
    }
}

