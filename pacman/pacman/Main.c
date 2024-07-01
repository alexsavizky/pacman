#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
typedef struct Location {
    int x,y;
}Location;

typedef struct Charecter {
    Location location;
    int derection;    // 1 -> |2 <- |3 ^ |4 v   

    char token;
    ///*
    ///  pacman- >/</^/V
    /// kraken - X Z
    int krakenFlag ;
    char underkraken;
}Charecter;
typedef struct Mapgame {
    char map[13][28];
    int size_x;
    int size_y;
} MapGame;
typedef struct ScoreBoard {
    int lives, score, time,pill_time,max_tokens;
} ScoreBoard;


void printmap(MapGame mapgame);
void buildMap(MapGame *mapgame, Charecter pacman, Charecter kraken1, Charecter kraken2);
void printGameScrean(MapGame map, ScoreBoard score_board);
void printscore(ScoreBoard score_board);
int movepacman(MapGame* map, Charecter* pacman,ScoreBoard *score,int* flag_pill);
void releaseTheKraken( MapGame* map,Charecter *kraken1, Charecter* kraken2);
Location nextmove(Charecter anycharacter);
int ChooseDerctionSmartKraken(MapGame map,Charecter pacman, Charecter *kraken1);
void ChooseDerctionDumKraken(MapGame* map, Charecter* kraken1);
void changeRandomDerection(Charecter* kraken1);
int moveDumKraken(MapGame* map, Charecter* kraken1);
void startGame(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2);
void startAfterDead(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2, ScoreBoard* score_board, int* dead);
void killkraken(Charecter pacman, Charecter* kraken1, Charecter* kraken2);
void startpill(int* pill_flag);
int main() {
    MapGame map;
    Charecter pacman;
    Charecter kraken1;
    Charecter kraken2;
    ScoreBoard score_board;
    startGame(&map, &pacman, &kraken1, &kraken2, &score_board);
    printmap(map);
    int flag_pill = 0;
    score_board.pill_time = 0;
    int dead = 0;
    int pacman_movment=-15;
    int gameflag = 1;
    //game play 

     while (gameflag) {
         //pacman move
        if (_kbhit()) {
            char a = getch();
            //getch();
            switch (a) { // the real value
            case 77://->
                pacman.derection = 1;
                pacman_movment= movepacman(&map, &pacman, &score_board, &flag_pill);
                break;
            case 75://<-
                pacman.derection = 2;
                pacman_movment= movepacman(&map, &pacman, &score_board, &flag_pill);
                break;
            case 72:
                pacman.derection = 3;
                pacman_movment= movepacman(&map, &pacman, &score_board, &flag_pill);
                break;
            case 80:
                pacman.derection = 4;
                pacman_movment = movepacman(&map, &pacman, &score_board, &flag_pill);
                break;
            
            default:
                break;
            }   
        }
        if (score_board.time > 50 && score_board.pill_time == 0) {
            releaseTheKraken(&map,&kraken1 , &kraken2);    
        }
        if (score_board.pill_time > 0) {
            score_board.pill_time--;
            dead = moveDumKraken(&map, &kraken1, &score_board);
            if (dead == 0) {
                dead = moveDumKraken(&map, &kraken2, &score_board);
            }
        }
        else {
            kraken1.token = 'X';
            kraken2.token = 'X';
            dead = moveSmartkraken(&map, &kraken1, pacman);
            if (dead == 0) {
                dead = moveDumKraken(&map, &kraken2, &score_board);
            }
        }

        if (pacman_movment == -2) {
            killkraken(pacman, &kraken1, &kraken2,&map);
        }
        if (flag_pill) {
            startpill(&flag_pill);
            score_board.pill_time = 50;
            kraken1.token = 'Z';
            kraken2.token = 'Z';
        }

        if (dead==1) {
            printf("youve lost one life point\n");
            Sleep(2000);
            startAfterDead(&map, &pacman, &kraken1, &kraken2, &score_board,&dead);
        }
        if (dead == -1) {
            killkraken(pacman, &kraken1, &kraken2, &map);
        }

        system("cls");//refresh
        score_board.time++;
        printGameScrean(map, score_board);
        if (score_board.max_tokens == 0) {
            system("cls");//refresh
            gameflag = 0;
            printf("you win :)\n");
            printf("your score : %d\n",score_board.score);
            Sleep(2000);
        }
        if (score_board.lives <= 0) {
            system("cls");//refresh
            gameflag = 0;
            printf("you lose :(\n");
            printf("your score : %d\n", score_board.score);
            Sleep(2000);
        }

        Sleep(50);
        }
	return 0;
}
void startGame(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2, ScoreBoard *score_board) {
    pacman->location.y = 5;
    pacman->location.x = 13;
    pacman->token = '<';
    pacman->derection = 1;
    kraken1->location.y = 9;
    kraken1->location.x = 13;
    kraken1->derection = 1;
    kraken1->token = 'X';
    kraken1->underkraken = ' ';
    kraken2->location.y = 10;
    kraken2->location.x = 13;
    kraken2->token = 'X';
    kraken2->derection = 1;
    kraken2->underkraken = ' ';
    buildMap(mapgame, *pacman, *kraken1, *kraken2);
    score_board->lives = 3;
    score_board->score = 0;
    score_board->time = 0;
    score_board->max_tokens = 139;
}
void startAfterDead(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2, ScoreBoard* score_board,int * dead) {
    *dead = 0;
    mapgame->map[8][12] = '-';
    mapgame->map[8][13] = '-';
    mapgame->map[kraken1->location.y][kraken1->location.x] = kraken1->underkraken;
    mapgame->map[kraken2->location.y][kraken2->location.x] = kraken2->underkraken;
    mapgame->map[pacman->location.y][pacman->location.x] = ' ';
    pacman->location.y = 5;
    pacman->location.x = 13;
    pacman->token = '<';
    pacman->derection = 1;
    kraken1->location.y = 9;
    kraken1->location.x = 13;
    kraken1->derection = 1;
    kraken1->krakenFlag = 0;
    kraken1->token = 'X';
    kraken2->location.y = 10;
    kraken2->location.x = 13;
    kraken2->derection = 1;
    kraken2->token = 'X';
    kraken2->krakenFlag = 0;
    mapgame->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
    mapgame->map[kraken2->location.y][kraken2->location.x] = kraken2->token;
    mapgame->map[pacman->location.y][pacman->location.x] = pacman->token;
    score_board->lives --;
    score_board->time = 0;
}

void buildMap(MapGame* mapgame, Charecter pacman, Charecter kraken1, Charecter kraken2) {
    mapgame->size_x = 28;
    mapgame->size_y = 13;

    
    //empty map  V

    char string[13][28] = {
     "__________________________\n\0",
     "|Yooooooooo|  |oooooooooY|\n\0",
     "|o|-|o|--|o|  |o|--|o|-|o|\n\0",
     "|ooooo|--|o|__|o|--|ooooo|\n\0",
     "|oooooooooooooooooooooooo|\n\0",
     "|o|-|o|--|oooooo|--|o|-|o|\n\0",
     "  oooo|  |oooooo|  |oooo  \n\0",
     "|ooooo|--|oooooo|--|ooooo|\n\0",
     "|oooooooooo|--|oooooooooo|\n\0",
     "|o|-|o|--|o|  |o|--|o|-|o|\n\0",
     "|Yoooo|--|o|  |o|--|ooooY|\n\0",
     " _________________________\n\0",
     "\0"
    };
    //init characteres
    string[kraken1.location.y][kraken1.location.x] = kraken1.token;
    string[kraken2.location.y][kraken2.location.x] = kraken2.token;
    string[pacman.location.y][pacman.location.x] = pacman.token;
    //temp to oregin
    for (int i = 0; i < mapgame->size_y; i++) {
        strcpy(mapgame->map[i] , string[i]);
    }
}
void printmap(MapGame mapgame) {
    for (int i = 0; i < 13; i++) {
        printf("%s", mapgame.map[i]);
    }
}
void printGameScrean(MapGame map, ScoreBoard score_board) {
    printscore(score_board);
    printmap(map);
}
void printscore(ScoreBoard score_board) {
    printf("lives : %d     score : %d       time : %d       pill time : %d\n", score_board.lives, score_board.score, score_board.time, score_board.pill_time);
}

void ChooseDerctionDumKraken(MapGame map, Charecter *kraken1, ScoreBoard* score) {
    Location temp = nextmove(*kraken1);
    while (isDeadLock(map.map[temp.y][temp.x])) {
        changeRandomDerection(kraken1, *score);
        temp = nextmove(*kraken1);
    }
}
void changeRandomDerection(Charecter* kraken,ScoreBoard score){
    if (kraken->derection == 1) {
        kraken->derection = 4;
        return;
    }
    if (kraken->derection == 2) {
        kraken->derection = 1;
        return;
    }
    if (kraken->derection == 3) {
        kraken->derection = 2;
        return;
    }
    if (kraken->derection == 4) {
        kraken->derection = 3;
        return;
    }
}
int moveDumKraken(MapGame* map, Charecter* kraken1,ScoreBoard* score) {
    if (kraken1->krakenFlag == 1)
    {
        
        char temp;
        ChooseDerctionDumKraken(*map, kraken1, score);
        if (ispacman(map->map[nextmove(*kraken1).y][nextmove(*kraken1).x])==1 && kraken1->token=='X' ){
            return 1;
        }
        if (ispacman(map->map[nextmove(*kraken1).y][nextmove(*kraken1).x])==1  && kraken1->token == 'Z') {
            return -1;
        }
        if (kraken1->derection == 1) {
            kraken1->location.x++;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y][kraken1->location.x - 1] = temp;
        }
        if (kraken1->derection == 2) {
            kraken1->location.x--;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y][kraken1->location.x + 1] = temp;
        }
        if (kraken1->derection == 3) {
            kraken1->location.y--;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y + 1][kraken1->location.x] = temp;
        }
        if (kraken1->derection == 4) {
            kraken1->location.y++;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y - 1][kraken1->location.x] = temp;
        }
    }
    return 0;
}
int moveSmartkraken(MapGame* map, Charecter* kraken1, Charecter pacman) {
    if(kraken1->krakenFlag==1)
    {
        char temp;
        ChooseDerctionSmartKraken(*map,pacman, kraken1);
        if (ispacman(map->map[nextmove(*kraken1).y][nextmove(*kraken1).x])) {
            return 1;
        }
        if (kraken1->derection == 1) {
            kraken1->location.x++;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y][kraken1->location.x - 1] = temp;
        }
        if (kraken1->derection == 2) {
            kraken1->location.x--;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y][kraken1->location.x + 1] = temp;
        }
        if (kraken1->derection == 3) {
            kraken1->location.y--;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y+1][kraken1->location.x] = temp;
        }
        if (kraken1->derection == 4) {
            kraken1->location.y++;
            temp = map->map[kraken1->location.y][kraken1->location.x];
            kraken1->underkraken = temp;
            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
            map->map[kraken1->location.y-1][kraken1->location.x] = temp;
        }
    }
    return 0;

}

void timer() {
    int time = 100;
    printf("time: %ds\n", time);
    int i = 0;
    while (1) {

        printf("doing stuff in duration %d\n", i);
        //stuff();
        Sleep(100);

        i++;
    }
}
Location nextmove(Charecter anyCharecter) {
    Location res;
    res.x = anyCharecter.location.x;
    res.y = anyCharecter.location.y;
    if (anyCharecter.derection == 1) {
        res.x++;
        return res;
    }
    if (anyCharecter.derection == 2) {
        res.x--;
        return res;
    }
    if (anyCharecter.derection == 3) {
        res.y--;
        return res;
    }
    if (anyCharecter.derection == 4) {
        res.y++;
        return res;
    }
}
int ChooseDerctionSmartKraken(MapGame map,Charecter pacman, Charecter* kraken1) {
    Location nextlocation;

    if (pacman.location.x > kraken1->location.x) {
        kraken1->derection = 1;
        nextlocation.x = nextmove(*kraken1).x;
        nextlocation.y = nextmove(*kraken1).y;
        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
        {
            if (pacman.location.y > kraken1->location.y) {
                    kraken1->derection = 4;
                }
            else {
                kraken1->derection = 3;
            }
        }
    }
    if (pacman.location.x < kraken1->location.x) {
        kraken1->derection = 2;
        nextlocation.x = nextmove(*kraken1).x;
        nextlocation.y = nextmove(*kraken1).y;
        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
        {
            if (pacman.location.y > kraken1->location.y) {
                kraken1->derection = 4;
            }
            else {
                kraken1->derection = 3;
            }
        }
    }
    if (pacman.location.y > kraken1->location.y) {
        kraken1->derection = 4;
        nextlocation.x = nextmove(*kraken1).x;
        nextlocation.y = nextmove(*kraken1).y;
        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
        {
            if (pacman.location.x > kraken1->location.x) {
                kraken1->derection = 1;
            }
            else {
                kraken1->derection = 2;
            }
        }
    }
    if (pacman.location.y < kraken1->location.y) {
        kraken1->derection = 3;
        nextlocation.x = nextmove(*kraken1).x;
        nextlocation.y = nextmove(*kraken1).y;
        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
        {
            if (pacman.location.x > kraken1->location.x) {
                kraken1->derection = 1;
            }
            else {
                kraken1->derection = 2;
            }
        }
    }
}

int movepacman(MapGame* map, Charecter* pacman,ScoreBoard* score,int* flag_pill) {
    //movment  1 -> |2 <- |3 ^ |4 v
    Location next_move = nextmove(*pacman);
    switch (pacman->derection)
    {
    case 1:
        pacman->token = '<';
        break;
    case 2:
        pacman->token = '>';
        break;
    case 3:
        pacman->token = 'v';
        break;
    case 4:
        pacman->token = '^';
        break;
    default:
        return-1;
        break;
    }
    map->map[pacman->location.y][pacman->location.x] = pacman->token;
    if (isDeadLock(map->map[next_move.y][next_move.x])) {
        return 0;
    }
    if (isKraken(map->map[next_move.y][next_move.x])) {
        score->score += 50;
        return -2;//kill kraken

    }
    else {
        if (map->map[next_move.y][next_move.x] == 'o') {
            score->score += 10;
            score->max_tokens--;
        }
        if (map->map[next_move.y][next_move.x] == 'Y')
        {
            score->score += 30;
            *flag_pill = 1;
            score->max_tokens--;
        }
        if (next_move.x == map->size_x - 2) {
            map->map[pacman->location.y][pacman->location.x] = ' ';
            map->map[next_move.y][0] = pacman->token;
            pacman->location.x = 0;
            return 1;
        }
        if (next_move.x == -1) {
            map->map[pacman->location.y][pacman->location.x] = ' ';
            map->map[pacman->location.y][map->size_x-3] = pacman->token;
            pacman->location.x = map->size_x - 3;
            return 1;
        }
        map->map[pacman->location.y][pacman->location.x] = ' ';
        map->map[next_move.y][next_move.x] = pacman->token;
        
    }
    switch (pacman->derection)
    {
    case 1:
        pacman->location.x++;
        break;
    case 2:
        pacman->location.x--;
        break;
    case 3:
        pacman->location.y--;
        break;
    case 4:
        pacman->location.y++;
        break;
    default:
        return-1;
        break;
    }
    return 1;

}

void releaseTheKraken(MapGame* map, Charecter* kraken1, Charecter* kraken2) {
    kraken1->krakenFlag = 1;
    kraken2->krakenFlag = 1;
    map->map[8][12] = ' ';
    map->map[8][13] = ' ';
}
void killkraken(Charecter pacman, Charecter* kraken1, Charecter* kraken2,MapGame *map) {
    map->map[8][12] = '-';
    map->map[8][13] = '-';
    Location next_move = nextmove(pacman);
    if (next_move.x == kraken1->location.x && next_move.y == kraken1->location.y)
    {
        map->map[kraken1->location.y][kraken1->location.x] = ' ';
        kraken1->location.y = 9;
        kraken1->location.x = 13;
        kraken1->derection = 1;
        kraken1->krakenFlag = 0;
        kraken1->token = 'X';
        map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
    }
    if (next_move.x == kraken2->location.x && next_move.y == kraken2->location.y) {
        map->map[kraken2->location.y][kraken2->location.x] = ' ';
        kraken2->location.y = 10;
        kraken2->location.x = 13;
        kraken2->derection = 1;
        kraken2->token = 'X';
        kraken2->krakenFlag = 0;
        map->map[kraken2->location.y][kraken2->location.x] = kraken2->token;
    }
}
void startpill(int* pill_flag) {
    *pill_flag = 0;
}

int isDeadLock(char nextmovechar) {
    if (nextmovechar == '|' || nextmovechar == '_' || nextmovechar == '-' || nextmovechar == 'X'|| nextmovechar == 'Z')
        return 1;
    return 0;
}
int ispacman(char nextmovechar) {
    if (nextmovechar == 'v' || nextmovechar == '<' || nextmovechar == '>' || nextmovechar == '^')
        return 1;
    return 0;
}
int isKraken(char nextmovechar) {
    if (nextmovechar == 'Z') {
        return 1;
    }
    return 0;
}