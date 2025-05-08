#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int mmenu(void); // main menu
int play(int dif, int **table, int *y, int *herolist, int hcount, int* healthHero); // starting the game
void settings(int *pdif, int* pheros); // name says it all
void help();
void pathfinder();
void maketable(int **table, int *n, int dif, int *herolist, int flag, int hcount); // map generation and loading
void showtable(int **table, int n);

int main(void){
	int i, j, **table, herolist[4] = {0}, healthHero[4]= {0}, select, checkhero=0, heros=2, *pheros = &heros, n, x, *y = &n;
	int dif=2, *pdif = &dif, check;
	*y = 22; // y = lines of the table
	x = 17; // x = rows of the table
	
	table = (int **)malloc(n * sizeof(int *)); // allocate memory for the dynamic 2D array
	if (table == NULL) {
		printf("Memory allocation failed\n");
		free(table);
		return 1;
	}
	
	for (i = 0; i < n; i++){
		table[i] = (int *)malloc(x * sizeof(int));
		if (table[i] == NULL){
			for (j = 0; j < i; j++) { // free allocated memory
				free(table[j]);
			}
			free(table);
			printf("Memory allocation failed\n");
			
			return 1;
		}
		for (j = 0; j < x; j++) { // set all stuff to 0
			table[i][j] = 0;//nigga you here?/???
		}
	}
	
	while(1){ 
		srand(time(NULL));
		check = mmenu(); //to do choice
		switch(check){
			case 1:
				for(i=0; i< heros; i++){  // hero selection
					checkhero=0;  // check for already existing hero
					printf("select a hero: (1-barbarian, 2-elf, 3-dwarf, 4-wizard): ");
					scanf("%d", &select);
					while(select<1||select>4)
					{
						printf("please select an avilable hero: (1-barbarian, 2-elf, 3-dwarf, 4-wizard): ");
						scanf("%d", &select);
					}
					for(j=0; j<4; j++)  //already existing hero check
					{
						if(herolist[j] == select){
							checkhero =1;
							break;
						}
					}
					if(checkhero){
                        printf("hero already selected! please select again.\n");
						i--;
						continue;
					}
					herolist[i] = select; //enter the hero
				}
				for(i=0; i<heros; i++){
					switch(herolist[i]){
						case 'B':
							healthHero[i] = 8;
							break;
						case 'D':
							healthHero[i] = 7;
							break;
						case 'E':
							healthHero[i] = 6;
							break;
						case 'W':
							healthHero[i] = 4;
							break;
						default:
							printf("Problem!");
							return 0;
					}
				}
				play(dif, table, y, herolist, heros, healthHero);
				break;
			case 2:
				help();
				break;
			case 3:
				settings(pdif, pheros);
				break;
			case 4:
			
				for (i = 0; i < n; i++) { // free allocated memory before exiting
					free(table[i]);
				}
				free(table);
				return 1;
		}
    }
}
		


int mmenu(void){
	int choice;
	printf ("\033c"); // clears the screen
    for (int i = 0; i < 11; i++){
        printf("\n");
    }
    for (int i =0; i <=25; i++){
        printf("\r                                  ["); // to \r gia reset
        for (int j = 0; j<25; j++){
            if (j < i) {
                printf("\033[1;32m#\033[0m");
            } else {
                printf(" ");
            }
        }
        printf("] %2d%%", (i*100/25));

		if (i >= 17) { // + humor
			printf("             \033[3mNothing actually loads lol.\033[0m");
		}

        for(int k = 0; k < 200000000; k++);
    }
	
	printf("\n");
    printf("\t\t   ___________________________________________________\n");
    printf("\t\t / \\   \033[1;32m_   _                _____                 _\033[0m   \\\n");
	printf("            />___L_|\033[1;32m  | | | |              |  _  |               | |   \033[0m|_____  \n");
	printf("   [\033[1;32m########\033[0m\033[1;35m[]\033[0m_____|\033[1;32m  | |_| | ___ _ __ ___ | | | |_   _  ___  ___| |_  \033[0m|_____|>\n");
	printf("            \\>\t \\_|\033[1;32m  |  _  |/ _ \\ '__/ _ \\| | | | | | |/ _ \\/ __| __|\033[0m |\n");
    printf("\t\t   |\033[1;32m  | | | |  __/ | | (_) \\ \\/' / |_| |  __/\\__ \\ |_  \033[0m|\n");
    printf("\t\t   |\033[1;32m  \\_| |_/\\___|_|  \\___/ \\_/\\_\\__,_|\\___||___/\\__|  \033[0m|\n");
    printf("\t\t   |   ________________________________________________|___\n");
    printf("\t\t   |  /                                                   /\n");
    printf("\t\t   \\_/___________________________________________________/\n\n");

    printf("\n");
    printf("\t\t\t\t    \033[1mWelcome to HeroQuest!\033[0m\n\n");
    printf("\t\t\t\t     \033[1;37m---- MAIN MENU ----\033[0m\n\n");

    printf("\t\t\t\t\tPlay\033[1;32m      [1]\033[0m\n");
	printf("\t\t\t\t\tHelp\033[1;32m      [2]\033[0m\n");
	printf("\t\t\t\t\tSettings\033[1;32m  [3]\033[0m\n");
	printf("\t\t\t\t\tQuit\033[1;32m      [4]\033[0m\n\n");

    for(int i = 0; i < 1000000000; i++);

	printf("\t\t\t\t   \033[3;37mEnter your choice [1-4]: \033[0m\n\n");
	scanf("%d", &choice);
	printf("\n");
	while(choice > 4 || choice < 1){
		printf("\033[3;37mPlease give a number in range of [1-4]: \033[0m ");
		scanf("%d", &choice);
		printf("\n");
	}
	return choice;
}



void help(){
	printf ("\033c"); // clears the screen
	printf("\n\t\t\033[1mINSTRUCTIONS\033[0m\n\n");
    printf("\033[4mHow to play:\033[0m \n\n");
    printf("\033[3;92mHeroQuest\033[0m is a game of dungeons with monsters that you have to slay\n");
    printf("You select with which heros you want to play (or all of them) and\n");
    printf("fight the spawns of \033[1;95mZARGON\033[0m to advance into the next dungeon.\n\n");
    
    printf("\033[4mCommands:\033[0m\n\n");
    
    printf("\033[3;92m Hero Movement:\033[0m\n");
    printf("  Format: \033[95m[B|D|E|W]>[U|D|L|R][Steps]...\033[0m\n");
    printf("  Example: \033[95mB>L3U2\033[0m - Barbarian moves 3 left, then 2 up\n");
    printf("  Heroes have different movement steps: Barbarian (8), Dwarf (6), Elf (8), Wizard (4)\n\n");
    

    printf("\033[3;92m Hero Attack:\033[0m\n");
    printf("  Format: \033[95m[B|D|E|W]>A*[CellCoords]\033[0m\n");
    printf("  Example: \033[95mD>A*E2\033[0m - Dwarf attacks monster at position E2\n");
    printf("  \033[90m- Barbarian: Can attack adjacent enemies (orthogonal)\033[0m\n");
    printf("  \033[90m- Dwarf: Can attack adjacent enemies (orthogonal + diagonal)\033[0m\n");
    printf("  \033[90m- Elf: Can attack non-adjacent enemies in same row/column (if line of sight)\033[0m\n");
    printf("  \033[90m- Wizard: Can attack any enemy in same row/column (ignoring obstacles)\033[0m\n\n");

    printf("\033[3;92m Other Commands:\033[0m\n");
    printf("  \033[95mX\033[0m - End youre turn (monsters will move)\n");
    printf("  \033[95mQ\033[0m - Quit game\n\n");
    
    printf("\033[4mTips:\033[0m\n");
    printf(" Each hero can move once and attack once per turn, in any order\n");
    printf(" Use your heroes' special abilities strategically\n");
    printf(" Monsters will try to reach and attack your heroes during their turn\n");
}



int play(int dif, int **table, int *y, int *herolist, int hcount, int *healthHero){
	int i, j, k, x=17, lose=1, wincount=0, moveLength1=0, moveLength2=0, steps=1, enoughMoves=1, minicount=1, direction = 0;
	char move[20] = {0};
	maketable(table, y, dif, herolist, 0, hcount);
	while(lose){ //flag if player loses, game ends
		wincount++; //posa stages nikise
		minicount =1; //hrisimopoihte san flag gia tin arhikopoisi ton steps ana round
		for(k=0; k<hcount; k++){
			enoughMoves = 1;
			while(steps>0 && enoughMoves){ //ean ta vimata tou iroa teliosoun h den thelei na hrisimopoihsi alla
				showtable(table, y);
				printf("\033[4mHealth:\033[0m\n");
				for(i=0; i<hcount; i++){
					printf("%c:%d ", herolist[i], healthHero[i]);
				}
				printf("\n");
				if(wincount == 1){ //nice message to welcome you into the first stage
					printf("Welcome To Your First Dungeon! Let The Fun Begin...\n");
				}
				printf("\033[4mThis is the Dungeon no.%d\033[0m\n", wincount);
				printf("What is your move?:\n");
				fgets(move, 20, stdin);
				if(move[0] == 'n' || move[0] == 'N'){
					enoughMoves = 0;
					continue;
				}
				//ELENHEI TA PANTA
				while(1){ //elenhos gia sosti kinisi
					if(move[0] != 'b' || move[0] != 'B' ||move[0] != 'w' ||move[0] != 'W' || move[0] != 'e' || move[0] != 'E' || move[0] != 'd' || move[0] != 'D'){
						printf("That move is invalid. Please type again:\n");
						fgets(move, 20, stdin);
					}
					else if(move[1] != '>'){
						printf("That move is invalid. Please type again:\n");
						fgets(move, 20, stdin);
					}
					else if(move[2] != 'u' || move[2] != 'U' ||move[2] != 'd' ||move[2] != 'D' || move[2] != 'l' || move[2] != 'L' || move[2] != 'r' || move[2] != 'R' || move[2] != 'a' || move[2] != 'A'){
						printf("That move is invalid. Please type again:\n");
						fgets(move, 20, stdin);
					}
					else if((move[2] != 'a' || move[2] != 'A') && move[3] != '*'){
						printf("That move is invalid. Please type again:\n");
						fgets(move, 20, stdin);
					}
					else if(move[3] != '*' && (move[4] != 'u' || move[4] != 'U' ||move[4] != 'd' ||move[4] != 'D' || move[4] != 'l' || move[4] != 'L' || move[4] != 'r' || move[4] != 'R')){
						printf("That move is invalid. Please type again:\n");
						fgets(move, 20, stdin);
					}
					else{
						break;
					}
				}
				while(1){ //elenhos ean o iroas pou epelexe uparhei
					int existCheck=0;
					for(j=0; j<hcount; j++){
						if(herolist[j] == move[0]){
							existCheck=1;
							break;
						}
					}
					if(existCheck){
						break;
					}
					printf("That move is invalid. Please type again:\n");
					fgets(move, 20, stdin);
				}
				if(minicount){ //only for the first time he choose
					switch(move[0]){ //how many moves they got
						case 'b':
						case 'B':
							steps =8;
							break;
						case 'e':
						case 'E':
							steps = 12;
							break;
						case 'd':
						case 'D':
							steps = 6;
							break;
						case 'w':
						case 'W':
							steps = 10;
							break;
					}
				}
				if((move[2] == 'u' || move[2] == 'U' ||move[2] == 'd' ||move[2] == 'D' || move[2] == 'l' || move[2] == 'L' || move[2] == 'r' || move[2] == 'R') && !(move[5] >= '1' && move[5] <= 'z')){ //move only to one direction
					moveLength1 = move[3]*10+move[4];
					if(steps<moveLength1){
						printf("That move is invalid. Please type again:\n");
						fgets(move, 20, stdin);
					}
					switch(move[2]){	//elenhos gia empodia
						case 'u':
						case 'U':
							for(i=0; i<moveLength1; i++){ 
								
							}
							break;
						case 'd':
						case 'D':
							direction = 2;
							break;
						case 'l':
						case 'L':
							direction = 3;
							break;
						case 'r':
						case 'R':
							direction = 4;
							break;
						default:
							printf("problemmmmm\n");
							return 0;
					}
				}
			}
		}
	}	
}


void settings(int *pdif, int *pheros){
	int choice;
    while(1){
		printf("\n\n\t\t\t\t     \033[1;37m---- SETTINGS ----\033[0m\n\n");
		printf("\n\t\t\t\t      Difficulty\033[1;32m  [1]\033[0m\n");
		printf("\t\t\t\t      Heros\033[1;32m       [2]\033[0m\n");
		printf("\t\t\t\t      Exit\033[1;32m        [3]\033[0m\n");
	
		for(int i = 0; i < 1000000000; i++); //san sleep
	
		printf("\n\n\t\t\t\t   \033[3;37mEnter your choice [1-4]: \033[0m\n\n");
		scanf("%d", &choice);
		printf("\n");
		while(choice > 3 || choice<1){
			printf("\033[3;37mPlease give a number in range of [1-3]:\033[0m ");
			scanf("%d", &choice);
			printf("\n");
		}
		if(choice == 3){
			return;
		}
		else if(choice == 1){
			printf("Child's Play      [1]\033[0m\n");
			printf("Medium            [2]\033[0m\n"); // default
			printf("\033[1;31mHurt me plenty!   [3]\033[0m\n");
			scanf("%d", pdif);
			printf("\n");

			for(int i = 0; i < 1000000000; i++);

			while(*pdif > 3 || pdif<1){
			printf("\033[3;37mPlease give a number in range of [1-4]:\033[0m ");
				scanf("%d", pdif);
				printf("\n");
			}
		}
		else if(choice ==2){
			printf("Select the number of heros \033[3m(you are going to play with)\033[0m (1-4): "); // default: 2
			scanf("%d", pheros);
			printf("\n");
			while(*pheros<1 || *pheros > 4){
				printf("\033[3;37mPlease give a number in range of [1-4]:\033[0m ");
				scanf("%d", pheros);
				printf("\n");
			}
		}
	}
}



void maketable(int **table, int *n, int dif, int *herolist, int flag, int hcount){
	int i, j, k=0, m=17, ishashtag, luckm =0, luckn=0, mcount=0, hcount=0, monster_max=0, health=0;
	if (flag){
		//kane realloc edw
		int tempn = *n;

		table = (int **)realloc(*table, (*n) *sizeof(int *));

		if (table == NULL){
			printf("Reallocation failed.");
		}

		for (i = tempn; i<*n; i++)(
			table[i]=(int *)malloc(m * sizeof(int));
			if (table[i] == NULL){
				printf("Allocation failed.");
			}
	
		)
	}
	int level = ((*n=11)/10)+1; //hero count
	// build standard room
    for(i = 0; i < *n; i++) {
        for(j = 0; j < m; j++) {
            table[i][j] = ' '; // fill all with space
            if(i == 0 && j >= 3 && j <= 13) {
                table[i][j] = '#'; //top
            }
            else if(i > 0 && i < 7 && (j == 3 || j == 13)) {
                table[i][j] = '#'; // left and right
            }
            else if(i == 7 && ((j > 2 && j < 7) || (j > 9 && j < 14))) {
                table[i][j] = '#'; //midle
            }
            else if(i > 7 && i < 11 && (j == 6 || j == 10)) { 
                table[i][j] = '#'; //bottom
            }
        }
    }

    k = 11;
    for(int l = 0; l < level ; l++){
        for(i = k; i < k+10; i++){
            for(j=0; j<m; j++){
                table[i][j] = ' ';
                if(i == k && (j<7 || j>9)){
                    table[i][j] = '#';
                }
                else if(i > 11 && i < k+10){
                    if((j == 0 || j == m - 1)){
                        table[i][j] = '#';
                    }
                    if(((j == 6 || j == 10) && !(k+5 == i))){
                        table[i][j] = '#';
                    }
                }
            }
        }
        k+=10;
    }
    for(j=0;j<m;j++){ // bottom wall
        table[i][j] = '#';
    }
    // filling the floor
    for (i = 1; i < 12; i++) {
        ishashtag = 0;
        for (j = 0; j < m; j++) {
            if (table[i][j] == '#' && ishashtag == 0) {
                ishashtag = 1;
                continue;      
            }
            if (table[i][j] == '#' && ishashtag == 1) {
                ishashtag = 0;
                continue;
            }
            if (ishashtag == 1 && table[i][j] != '#'){
                table[i][j] = '.';
            }
        }
    }
    
    k=11;

    //O PALIATZIS
    for(i=0; i<level; i++){
        for (j=0; j<2; j++) {
            luckm = (rand() % 5)+1;
            luckn = (rand() % 9)+1;
            // printf("%d %d\n", luckn, luckm); // Debugging line
            if(table[k+luckn][luckm] == '@'){
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 5){
                j--;
                continue;
            }
            else{
                table[luckn+k][luckm] = '@';
            }
        }
        k+=10;
 }
    k=11;
    for(i=0; i<level; i++){
        for (j=0; j<2; j++) {
            luckm = (rand() % 5)+11;
            luckn = (rand() % 9)+1;
            // printf("%d %d\n", luckn, luckm); // Debugging line
            
            if(table[k+luckn][luckm] == '@'){   // Kanei check to @, heroes, mcount
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 11){
                j--;
                continue;
            }
            else{
                table[k+luckn][luckm] = '@';
            }
        }
        k+=10;
    }
    
    // HEROES
    for(j=0; j<hcount; j++){
        luckm = (rand() % 9)+4;
        luckn = (rand() % 6)+1;
        if(table[luckn][luckm] != '.'){
            j--;
            continue;
        }
        else{
            table[luckn][luckm] = herolist[j];
        }
    }
    k=11;
    
    //LEFT MONSTERS
    monster_max = 2*dif;
    for(i=0; i<level; i++){
        mcount = (rand() % monster_max) + 1;
        for (j=0; j<mcount; j++) {
            luckm = (rand() % 5)+1;
            luckn = (rand() % 9)+1;
            
            if(table[k+luckn][luckm] >= '1' && table[k+luckn][luckm] <= 'Z' ){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 5){ // Door case
                j--;
                continue;
            }
            else if((k+luckn == k+1 && luckm == 1) || (k+luckn == k+9 && luckm == 1) ||            // Corner cases for left side
                    (k+luckn == k+1 && luckm == 5) || (k+luckn == k+9 && luckm == 5)){
                j--;
                continue;
            }
            else{
                health = 3*dif-rand()%3;
                table[k+luckn][luckm] = health + '0';
            }
        }
        k+=10;
    }
    k=11;
	
    //RIGHT MONSTERS
    monster_max = 2*dif;
    for(i=0; i<level; i++){
        mcount = (rand() % monster_max) + 1;
        for (j=0; j<mcount; j++) {
            luckm = (rand() % 5)+11;
            luckn = (rand() % 9)+1;
            
            if(table[k+luckn][luckm] >= '1' && table[k+luckn][luckm] <= 'Z' ){   // Kanei check to @, heroes, monsters
                j--;
                continue;
            }
            else if(luckn+k == k+5 && luckm == 11){
                j--;
                continue;
            }
            else if((k+luckn == k+1 && luckm == 11) || (k+luckn == k+9 && luckm == 11) || 
                (k+luckn == k+1 && luckm == 15) || (k+luckn == k+9 && luckm == 15)) { // Corner cases for right side
                    j--;
                    continue;
            }
            else{
                health = 3*dif-rand()%3;
                table[k+luckn][luckm] = health + '0';
            }
        }
        k+=10;
    }
	return;
}



void showtable(int **table, int n){
	int m = 17, i, j, k;
	for(i = 1; i<4; i++){ 
        table[7][6+i] = '.';
    }

    for (i = 12; i < n; i++) {
        for (j = 1; j < m; j++) {
            if(table[i][j] != '#' && table[i][j] != '@' && (table[i][j] <= '1' || table[i][j] >= 'Z')) {
                table[i][j] = '.';
            }
        }
    }
	printf("\n     \033[4m "); 

    for(k=0; k<m-1; k++){
        printf("%c ", 'A' +k);
    }
    printf("%c |", 'A' + k);
    printf("\033[0m\n");
    printf(" %.3d |", 1);
    printf("\n");
    
    for(k=0; k<n; k++){ 
        printf(" %.3d |", k+2);
        for( i = 0; i < m; i++) {
            printf("%c ", table[k][i]);
        }
        printf("\n");
    }
	return;
}