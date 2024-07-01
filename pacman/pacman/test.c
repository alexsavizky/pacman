//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <Windows.h>
//#include <stdlib.h>
//#include <malloc.h>
//#include <time.h>
//typedef struct Location {
//    int x, y;
//}Location;
//
//typedef struct Charecter {
//    Location location;
//    int derection;
//    // 1 -> |2 <- |3 ^ |4 v   
//    char token;
//    ///*
//    ///  pacman- >/</^/V
//    /// kraken - X H
//    int krakenflag;
//}Charecter;
//typedef struct Mapgame {
//    char map[13][28];
//    Location pacman_location, kraken1_location, kraken2_location;
//    int size_x;
//    int size_y;
//} MapGame;
//typedef struct ScoreBoard {
//    int lives, score, time;
//} ScoreBoard;
//
//
//void printmap(MapGame mapgame);
//void buildMap(MapGame* mapgame, Charecter pacman, Charecter kraken1, Charecter kraken2);
//void releasetheSmartKraken(char map[][34], int i, int j, int* k, int* t);
//void printGameScrean(MapGame map, ScoreBoard score_board);
//void printscore(ScoreBoard score_board);
//int movepacman(MapGame* map, Charecter pacman, ScoreBoard* score, int* flag_pill);
//void releaseTheKraken(MapGame* map, Charecter* kraken1, Charecter* kraken2);
//Location nextmove(Charecter anycharacter);
//int moveSmartkraken(MapGame* map, Charecter* kraken1);
//int ChooseDerctionSmartKraken(MapGame map, Charecter pacman, Charecter* kraken1);
//void ChooseDerctionDumKraken(MapGame* map, Charecter* kraken1);
//void changeRandomDerection(Charecter* kraken1);
//int moveDumKraken(MapGame* map, Charecter* kraken1);
//void pacmanCaught(ScoreBoard* score_bord);
//void startGame(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2);
//void startAfterDead(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2, ScoreBoard* score_board, int* dead);
//int main() {
//    MapGame map;
//    Charecter pacman;
//    Charecter kraken1;
//    Charecter kraken2;
//    ScoreBoard score_board;
//    startGame(&map, &pacman, &kraken1, &kraken2, &score_board);
//    printmap(map);
//    int flag_pill = 0;
//    int dead = 0;
//
//    //game play 
//
//    while (1) {
//        if (_kbhit()) {
//            char a = getch();
//            switch (a) { // the real value
//            case 77://->
//                pacman.derection = 1;
//
//                if (movepacman(&map, pacman, &score_board, &flag_pill)) {
//                    pacman.location.x++;
//                }
//                break;
//            case 75://<-
//                pacman.derection = 2;
//
//                if (movepacman(&map, pacman, &score_board, &flag_pill)) {
//                    pacman.location.x--;
//                }
//
//                break;
//            case 72:
//                pacman.derection = 3;
//
//                if (movepacman(&map, pacman, &score_board, &flag_pill))
//                {
//                    pacman.location.y--;
//                }
//                break;
//            case 80:
//                pacman.derection = 4;
//                if (movepacman(&map, pacman, &score_board, &flag_pill))
//                {
//                    pacman.location.y++;
//                }
//                break;
//                //default:
//                //    system("cls");//refresh
//                //    printGameScrean(map, score_board);
//                //    score_board.time++;
//            }
//        }
//        if (score_board.time > 20) {
//            releaseTheKraken(&map, &kraken1, &kraken2);
//            //releaseDumtheKraken(map, n, m, &k, &t);    
//        }
//        if (flag_pill) {
//            kraken1.token = 'Z';
//            kraken2.token = 'Z';
//            moveDumKraken(&map, &kraken1, &score_board);
//            moveDumKraken(&map, &kraken2, &score_board);
//
//        }
//        else {
//            dead = moveDumKraken(&map, &kraken1, &score_board);
//            dead = moveSmartkraken(&map, &kraken2, pacman);
//
//        }
//        if (dead) {
//            printf("fuck you");
//            Sleep(2000);
//            startAfterDead(&map, &pacman, &kraken1, &kraken2, &score_board, &dead);
//        }
//        system("cls");//refresh
//        printGameScrean(map, score_board);
//        score_board.time++;
//        Sleep(100);
//    }
//    return 0;
//}
//void startGame(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2, ScoreBoard* score_board) {
//    pacman->location.y = 5;
//    pacman->location.x = 13;
//    pacman->token = '<';
//    pacman->derection = 1;
//    kraken1->location.y = 9;
//    kraken1->location.x = 13;
//    kraken1->derection = 1;
//    kraken1->token = 'X';
//    kraken2->location.y = 10;
//    kraken2->location.x = 13;
//    kraken2->token = 'X';
//    kraken1->derection = 1;
//    buildMap(mapgame, *pacman, *kraken1, *kraken2);
//    score_board->lives = 3;
//    score_board->score = 0;
//    score_board->time = 0;
//}
//void startAfterDead(MapGame* mapgame, Charecter* pacman, Charecter* kraken1, Charecter* kraken2, ScoreBoard* score_board, int* dead) {
//    *dead = 0;
//    //need to change
//    mapgame->map[kraken1->location.y][kraken1->location.x] = ' ';
//    mapgame->map[kraken2->location.y][kraken2->location.x] = ' ';
//    //           |
//    //that is ok V
//    mapgame->map[pacman->location.y][pacman->location.x] = ' ';
//    pacman->location.y = 5;
//    pacman->location.x = 13;
//    pacman->token = '<';
//    pacman->derection = 1;
//    kraken1->location.y = 9;
//    kraken1->location.x = 13;
//    kraken1->derection = 1;
//    kraken1->krakenflag = 0;
//    kraken1->derection = 1;
//    kraken1->token = 'X';
//    kraken2->location.y = 10;
//    kraken2->location.x = 13;
//    kraken2->token = 'X';
//    kraken2->krakenflag = 0;
//    mapgame->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//    mapgame->map[kraken2->location.y][kraken2->location.x] = kraken2->token;
//    mapgame->map[pacman->location.y][pacman->location.x] = pacman->token;
//    //buildMap(mapgame, *pacman, *kraken1, *kraken2);
//    score_board->lives--;
//    score_board->time = 0;
//}
//void buildSavedMap(MapGame* mapgame, Charecter pacman, Charecter kraken1, Charecter kraken2) {
//    mapgame->map[kraken1.location.y][kraken1.location.x] = kraken1.token;
//    mapgame->map[kraken2.location.y][kraken2.location.x] = kraken2.token;
//    mapgame->map[pacman.location.y][pacman.location.x] = pacman.token;
//}
//void buildMap(MapGame* mapgame, Charecter pacman, Charecter kraken1, Charecter kraken2) {
//    mapgame->size_x = 28;
//    mapgame->size_y = 13;
//
//
//    //empty map  V
//
//    char string[13][28] = {
//     "__________________________\n\0",
//     "|Yooooooooo|  |oooooooooY|\n\0",
//     "|o|-|o|--|o|  |o|--|o|-|o|\n\0",
//     "|ooooo|--|o|__|o|--|ooooo|\n\0",
//     "|oooooooooooooooooooooooo|\n\0",
//     "|o|-|o|--|oooooo|--|o|-|o|\n\0",
//     "  oooo|  |oooooo|  |oooo  \n\0",
//     "|ooooo|--|oooooo|--|ooooo|\n\0",
//     "|oooooooooo|--|oooooooooo|\n\0",
//     "|o|-|o|--|o|  |o|--|o|-|o|\n\0",
//     "|Yoooo|--|o|  |o|--|ooooY|\n\0",
//     " _________________________\n\0",
//     "\0"
//    };
//    //init characteres
//    string[kraken1.location.y][kraken1.location.x] = kraken1.token;
//    string[kraken2.location.y][kraken2.location.x] = kraken2.token;
//    string[pacman.location.y][pacman.location.x] = pacman.token;
//    //temp to oregin
//    for (int i = 0; i < mapgame->size_y; i++) {
//        strcpy(mapgame->map[i], string[i]);
//    }
//}
//void printmap(MapGame mapgame) {
//    for (int i = 0; i < 13; i++) {
//        printf("%s", mapgame.map[i]);
//    }
//}
//void printGameScrean(MapGame map, ScoreBoard score_board) {
//    printscore(score_board);
//    printmap(map);
//}
//void releaseTheKraken(MapGame* map, Charecter* kraken1, Charecter* kraken2) {
//    kraken1->krakenflag = 1;
//    kraken2->krakenflag = 1;
//    map->map[8][12] = ' ';
//    map->map[8][13] = ' ';
//}
//void ChooseDerctionDumKraken(MapGame map, Charecter* kraken1, ScoreBoard* score) {
//    Location temp = nextmove(*kraken1);
//    if (ispacman(map.map[temp.y][temp.x])) {
//        pacmanCaught(score);
//    }
//    while (isDeadLock(map.map[temp.y][temp.x])) {
//        changeRandomDerection(kraken1, *score);
//        temp = nextmove(*kraken1);
//    }
//}
//void changeRandomDerection(Charecter* kraken, ScoreBoard score) {
//    if (kraken->derection == 1) {
//        kraken->derection = 4;
//        return;
//    }
//    if (kraken->derection == 2) {
//        kraken->derection = 1;
//        return;
//    }
//    if (kraken->derection == 3) {
//        kraken->derection = 2;
//        return;
//    }
//    if (kraken->derection == 4) {
//        kraken->derection = 3;
//        return;
//    }
//    //int temp = (score.time % 4) + 1;
//    //if (temp == kraken->derection) {
//    //    kraken->derection = (kraken->derection+1)%4;
//    //}
//    //else{
//    //    kraken->derection = (score.time % 4) + 1;
//    //}
//}
//int moveDumKraken(MapGame* map, Charecter* kraken1, ScoreBoard* score) {
//    if (kraken1->krakenflag == 1)
//    {
//
//        char temp;
//        ChooseDerctionDumKraken(*map, kraken1, score);
//        if (ispacman(map->map[nextmove(*kraken1).y][nextmove(*kraken1).x])) {
//            return 1;
//        }
//        if (kraken1->derection == 1) {
//            kraken1->location.x++;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y][kraken1->location.x - 1] = temp;
//        }
//        if (kraken1->derection == 2) {
//            kraken1->location.x--;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y][kraken1->location.x + 1] = temp;
//        }
//        if (kraken1->derection == 3) {
//            kraken1->location.y--;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y + 1][kraken1->location.x] = temp;
//        }
//        if (kraken1->derection == 4) {
//            kraken1->location.y++;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y - 1][kraken1->location.x] = temp;
//        }
//    }
//    return 0;
//}
//int moveSmartkraken(MapGame* map, Charecter* kraken1, Charecter pacman) {
//    if (kraken1->krakenflag == 1)
//    {
//        char temp;
//        ChooseDerctionSmartKraken(*map, pacman, kraken1);
//        if (ispacman(map->map[nextmove(*kraken1).y][nextmove(*kraken1).x])) {
//            return 1;
//        }
//        if (kraken1->derection == 1) {
//            kraken1->location.x++;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y][kraken1->location.x - 1] = temp;
//        }
//        if (kraken1->derection == 2) {
//            kraken1->location.x--;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y][kraken1->location.x + 1] = temp;
//        }
//        if (kraken1->derection == 3) {
//            kraken1->location.y--;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y + 1][kraken1->location.x] = temp;
//        }
//        if (kraken1->derection == 4) {
//            kraken1->location.y++;
//            temp = map->map[kraken1->location.y][kraken1->location.x];
//            map->map[kraken1->location.y][kraken1->location.x] = kraken1->token;
//            map->map[kraken1->location.y - 1][kraken1->location.x] = temp;
//        }
//    }
//    return 0;
//
//}
//void printscore(ScoreBoard score_board) {
//    printf("lives : %d     score : %d       time : %d\n", score_board.lives, score_board.score, score_board.time);
//}
//void timer() {
//    int time = 100;
//    printf("time: %ds\n", time);
//    int i = 0;
//    while (1) {
//
//        printf("doing stuff in duration %d\n", i);
//        //stuff();
//        Sleep(100);
//
//        i++;
//    }
//}
//Location nextmove(Charecter anyCharecter) {
//    Location res;
//    res.x = anyCharecter.location.x;
//    res.y = anyCharecter.location.y;
//    if (anyCharecter.derection == 1) {
//        res.x++;
//        return res;
//    }
//    if (anyCharecter.derection == 2) {
//        res.x--;
//        return res;
//    }
//    if (anyCharecter.derection == 3) {
//        res.y--;
//        return res;
//    }
//    if (anyCharecter.derection == 4) {
//        res.y++;
//        return res;
//    }
//}
//int ChooseDerctionSmartKraken(MapGame map, Charecter pacman, Charecter* kraken1) {
//    Location nextlocation;
//
//    if (pacman.location.x > kraken1->location.x) {
//        kraken1->derection = 1;
//        nextlocation.x = nextmove(*kraken1).x;
//        nextlocation.y = nextmove(*kraken1).y;
//        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
//        {
//            if (pacman.location.y > kraken1->location.y) {
//                kraken1->derection = 4;
//            }
//            else {
//                kraken1->derection = 3;
//            }
//        }
//    }
//    if (pacman.location.x < kraken1->location.x) {
//        kraken1->derection = 2;
//        nextlocation.x = nextmove(*kraken1).x;
//        nextlocation.y = nextmove(*kraken1).y;
//        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
//        {
//            if (pacman.location.y > kraken1->location.y) {
//                kraken1->derection = 4;
//            }
//            else {
//                kraken1->derection = 3;
//            }
//        }
//    }
//    if (pacman.location.y > kraken1->location.y) {
//        kraken1->derection = 4;
//        nextlocation.x = nextmove(*kraken1).x;
//        nextlocation.y = nextmove(*kraken1).y;
//        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
//        {
//            if (pacman.location.x > kraken1->location.x) {
//                kraken1->derection = 1;
//            }
//            else {
//                kraken1->derection = 2;
//            }
//        }
//    }
//    if (pacman.location.y < kraken1->location.y) {
//        kraken1->derection = 3;
//        nextlocation.x = nextmove(*kraken1).x;
//        nextlocation.y = nextmove(*kraken1).y;
//        if (isDeadLock(map.map[nextlocation.y][nextlocation.x]))
//        {
//            if (pacman.location.x > kraken1->location.x) {
//                kraken1->derection = 1;
//            }
//            else {
//                kraken1->derection = 2;
//            }
//        }
//    }
//}
//int isDeadLock(char nextmovechar) {
//    if (nextmovechar == '|' || nextmovechar == '_' || nextmovechar == '-' || nextmovechar == 'X')
//        return 1;
//    return 0;
//}
//int ispacman(char nextmovechar) {
//    if (nextmovechar == 'V' || nextmovechar == '<' || nextmovechar == '>' || nextmovechar == '^')
//        return 1;
//    return 0;
//}
//int movepacman(MapGame* map, Charecter pacman, ScoreBoard* score, int* flag_pill) {
//    //movment  1 -> |2 <- |3 ^ |4 v
//    if (pacman.derection == 1) {
//        map->map[pacman.location.y][pacman.location.x] = '<';
//        if (map->map[pacman.location.y][pacman.location.x + 1] == '|') {
//            map->map[pacman.location.y][pacman.location.x] = '<';
//            map->map[pacman.location.y][pacman.location.x + 1] = '|';
//            return 0;
//        }
//        if (map->map[pacman.location.y][pacman.location.x + 1] == 'o') {
//            score->score += 10;
//            map->map[pacman.location.y][pacman.location.x] = ' ';
//            map->map[pacman.location.y][pacman.location.x + 1] = '<';
//            return 1;
//        }
//        if (map->map[pacman.location.y][pacman.location.x + 1] == ' ') {
//            map->map[pacman.location.y][pacman.location.x] = ' ';
//            map->map[pacman.location.y][pacman.location.x + 1] = '<';
//            return 1;
//        }
//        if (map->map[pacman.location.y][pacman.location.x + 1] == 'Y')
//        {
//            score->score += 30;
//            *flag_pill = 1;
//            map->map[pacman.location.y][pacman.location.x] = ' ';
//            map->map[pacman.location.y][pacman.location.x + 1] = '<';
//            return 1;
//        }
//
//    }
//    if (pacman.derection == 2) {
//        map->map[pacman.location.y][pacman.location.x] = '>';
//        if (map->map[pacman.location.y][pacman.location.x] == '>') {
//            if (map->map[pacman.location.y][pacman.location.x - 1] == '|') {
//                map->map[pacman.location.y][pacman.location.x] = '>';
//                map->map[pacman.location.y][pacman.location.x - 1] = '|';
//                return 0;
//            }
//            if (map->map[pacman.location.y][pacman.location.x - 1] == 'o') {
//                score->score += 10;
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y][pacman.location.x - 1] = '>';
//                return 1;
//            }
//            if (map->map[pacman.location.y][pacman.location.x - 1] == ' ') {
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y][pacman.location.x - 1] = '>';
//                return 1;
//            }
//            if (map->map[pacman.location.y][pacman.location.x - 1] == 'Y')
//            {
//                score->score += 30;
//                *flag_pill = 1;
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y][pacman.location.x - 1] = '>';
//                return 1;
//            }
//        }
//    }
//    if (pacman.derection == 3) {
//        map->map[pacman.location.y][pacman.location.x] = 'v';
//        if (map->map[pacman.location.y][pacman.location.x] == 'v') {
//            if (map->map[pacman.location.y - 1][pacman.location.x] == '|') {
//                map->map[pacman.location.y][pacman.location.x] = 'v';
//                map->map[pacman.location.y - 1][pacman.location.x] = '|';
//                return 0;
//            }
//            if (map->map[pacman.location.y - 1][pacman.location.x] == 'o') {
//                score->score += 10;
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y - 1][pacman.location.x] = 'v';
//                return 1;
//            }
//            if (map->map[pacman.location.y - 1][pacman.location.x] == '_') {
//                map->map[pacman.location.y][pacman.location.x] = 'v';
//                map->map[pacman.location.y - 1][pacman.location.x] = '_';
//                return 0;
//            }
//            if (map->map[pacman.location.y - 1][pacman.location.x] == '-') {
//                map->map[pacman.location.y][pacman.location.x] = 'v';
//                map->map[pacman.location.y - 1][pacman.location.x] = '-';
//                return 0;
//            }
//            if (map->map[pacman.location.y - 1][pacman.location.x] == ' ') {
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y - 1][pacman.location.x] = 'v';
//                return 1;
//            }
//            if (map->map[pacman.location.y - 1][pacman.location.x] == 'Y')
//            {
//                score->score += 30;
//                *flag_pill = 1;
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y - 1][pacman.location.x] = 'V';
//                return 1;
//            }
//        }
//    }
//    if (pacman.derection == 4) {
//        map->map[pacman.location.y][pacman.location.x] = '^';
//        if (map->map[pacman.location.y][pacman.location.x] == '^') {
//            if (map->map[pacman.location.y + 1][pacman.location.x] == '|') {
//                map->map[pacman.location.y][pacman.location.x] = '^';
//                map->map[pacman.location.y + 1][pacman.location.x] = '|';
//                return 0;
//            }
//            if (map->map[pacman.location.y + 1][pacman.location.x] == 'o') {
//                score->score += 10;
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y + 1][pacman.location.x] = '^';
//                return 1;
//            }
//            if (map->map[pacman.location.y + 1][pacman.location.x] == '_') {
//                map->map[pacman.location.y][pacman.location.x] = '^';
//                map->map[pacman.location.y + 1][pacman.location.x] = '_';
//                return 0;
//            }
//            if (map->map[pacman.location.y + 1][pacman.location.x] == '-') {
//                map->map[pacman.location.y][pacman.location.x] = '^';
//                map->map[pacman.location.y + 1][pacman.location.x] = '-';
//                return 0;
//            }
//            if (map->map[pacman.location.y + 1][pacman.location.x] == ' ') {
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y + 1][pacman.location.x] = '^';
//                return 1;
//            }
//            if (map->map[pacman.location.y + 1][pacman.location.x] == 'Y')
//            {
//                score->score += 30;
//                *flag_pill = 1;
//                map->map[pacman.location.y][pacman.location.x] = ' ';
//                map->map[pacman.location.y + 1][pacman.location.x - 1] = '^';
//                return 1;
//            }
//        }
//    }
//
//}
//void pacmanCaught(ScoreBoard* score_bord) {
//    score_bord->lives--;
//    score_bord->time = 0;
//    printf("__________________________\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        "_______you got caught_____\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        "__________________________\n\0",
//        " _________________________\n\0",
//        "\0");
//}