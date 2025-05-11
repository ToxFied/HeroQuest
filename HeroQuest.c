#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int combat(int flag);
int mmenu(void); // main menu
int play(int dif, int **table, int *y, int hero_pos[][2], int *herolist, int hcount, int* healthHero); // starting the game
void settings(int *pdif, int* pheros); // name says it all
void help();
int pathfinder(int **table, int pos_i, int pos_j, int flag, int dest_i, int dest_j);
void maketable(int **table, int *n, int hero_pos[][2], int dif, int *herolist, int flag, int hcount); // map generation and loading
void showtable(int **table, int n);
int moveMon(int **table, int *y, int move[][2], int pos_i, int pos_j, int **heroOnRoomPos);


int main(void){
	int i, j, **table, herolist[4] = {0}, healthHero[4]= {0}, select, checkhero=0, heros=2, *pheros = &heros, n, x, *y = &n;
	int dif=2, hero_pos[4][2], *pdif = &dif, check, tempSelect;
	*y = 22; // y = lines of the table
	x = 17; // x = rows of the table
	
	table = (int **)malloc(*y *sizeof(int *));
	if (table == NULL) {
		printf("Memory allocation failed\n");
		free(table);
		return 1;
	}
	
	for (i = 0; i < *y; i++){
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
			table[i][j] = 0;
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
					int tempSelect = 0;
					switch (select) {
						case 1:
							tempSelect = 'B';
							break;
						case 2:
							tempSelect = 'E';
							break;
						case 3:
							tempSelect = 'D';
							break;
						case 4:
							tempSelect = 'W';
							break;
					}
					for(j=0; j<i; j++)  //already existing hero check
					{
						if(herolist[j] == tempSelect){
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
					switch(select){
						case 1:
							herolist[i] = 'B';
							break;
						case 2:
							herolist[i] = 'E';
							break;
						case 3:
							herolist[i] = 'D';
							break;
						case 4:
							herolist[i] = 'W';
							break;
					}
				}
				for(i=0; i<heros; i++){
					switch(herolist[i]){
						case 'B':
							healthHero[i] = 8; //Barbarian
							break;
						case 'D':
							healthHero[i] = 7; //Dwarf
							break;
						case 'E':
							healthHero[i] = 6; //Elf
							break;
						case 'W':
							healthHero[i] = 4; //Wizard
							break;
						default:
							printf("Problem!");
							return 0;
					}
				}
				i = play(dif, table, &n, hero_pos, herolist, *pheros, healthHero);
				break;
			case 2:
				help();
				break;
			case 3:
				settings(pdif, pheros);
				break;
			case 4:
			
				for (i = 0; i < *y; i++) { // free allocated memory before exiting
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
    }
	printf ("\033c"); // clears the screen
    for(int k = 0; k < 200000000; k++);
	
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
    printf("  \033[90m- Elf: Can attack non-adjacent enemies in same row/column (if in line of sight)\033[0m\n");
    printf("  \033[90m- Wizard: Can attack any enemy in same row/column (ignoring obstacles)\033[0m\n\n");

    printf("\033[3;92m Other Commands:\033[0m\n");
    printf("  \033[95mX\033[0m - End your turn (monsters will move)\n");
    printf("  \033[95mQ\033[0m - Quit game\n\n");
    
    printf("\033[4mTips:\033[0m\n");
    printf(" Each hero can move once and attack once per turn, in any order\n");
    printf(" Use your heroes' special abilities strategically\n");
    printf(" Monsters will try to reach and attack your heroes during their turn\n");

	printf("\n\n\033[4mPress enter to continue.\033[0m\n");
	getchar(); // To consume the newline from previous input
	getchar(); // To wait for user to press Enter
	return;
}



int play(int dif, int **table, int *y, int hero_pos[][2], int *herolist, int hcount, int *healthHero){
	int i, j, k, x=17, lose=1, wincount=0, animationSteps[13][2] = {0}, moveLength1=0, currentHero=0, attacking=0, MoveStrLength=0, moving=0, temp=0, countFlag=0, ai=0;
	int continueFlag=0, moveLength2=0, flag=0, steps=1, enoughMoves=1, minicount=1, direction1 = 0, piece_i=0, piece_j=0, correctMove=1, checked =0, damage, advance =0;
	int totallength=0, flagforl2=0, flagforl1 =0, direction2=0, new_piece_i=0, new_piece_j=0, final_piece_i=0, final_piece_j=0, animationStepsLength=0, mcount=0, telepathy=0, mx, my;
	char move[13] = {0};
	maketable(table, y, hero_pos, dif, herolist, 0, hcount);
	while(lose){ //flag if player loses, game ends
		wincount++; //posa stages nikise
		minicount =1; //hrisimopoihte san flag gia tin arhikopoisi ton steps ana round
		for(i=0;i<x*(*y);i++){
			mcount++;
		}
		advance = 0;
		while(!advance){
			for(k=0; k<hcount; k++){
				enoughMoves = 1;
				while(steps>0 && enoughMoves && !advance){ //ean ta vhmata tou iroa teliosoun h den thelei na hrisimopoihsi alla
					showtable(table, *y);
					printf("\033[4mHealth:\033[0m\n");
					for(i=0; i<hcount; i++){
						printf("%c:%d ", herolist[i], healthHero[i]);
					}
					printf("\n");
					if(wincount == 1){ //nice message to welcome you into the first stage
						printf("Welcome To Your First Dungeon! Let The Fun Begin...\n");
						printf("If you want to take the easy way out, press q/Q.\n");
					}
					printf("\033[4mThis is the Dungeon no.%d\033[0m\n", wincount);
					//ELENHEI TA PANTA
					correctMove = 1;
					while(correctMove){
						checked=0;
						countFlag=0;
						continueFlag=0;
						attacking=0;
						totallength = 0;
						moveLength1 =0;
						moveLength2 =0;
						direction1=0;
						direction2=0;
						new_piece_i=0;
						new_piece_j=0;
						final_piece_i=0;
						final_piece_j=0;
						flagforl2=0;
						flagforl1 =0;
						telepathy = 0;
						
						printf("What is your move? (if you dont want to make more moves press x/X):\n");
						fgets(move, 20, stdin);
						
						if(move[0] == 'x' || move[0] == 'X'){ //elenhos gia to an o paihtis thelei na kanei alles kiniseis
							enoughMoves = 0;
						}

						if(move[0] == 'q' || move[0] == 'Q'){ //elenhos gia to an o paihtis thelei na termatisei to paixnidi
							return 0;
						}
						
						MoveStrLength=strlen(move);
						if(enoughMoves == 0){
							break;
						}
						while(1){ //elenhos ean o iroas pou epelexe uparhei

							int existCheck=0;
							for(j=0; j<hcount; j++){
								if(herolist[j] == move[0]){
									currentHero = herolist[j];
									existCheck=1;
									break;
								}
							}
							if(existCheck){
								break;
							}
							continueFlag =1;
						}
						if(continueFlag){
							continue;
						}
						if(move[1] != '>'){ //elenhos  gia >
							continue;
						}
						if(move[2] == 'a' || move[2] == 'A'){ //elenhos an kanei attack kai gia *
							attacking =1;
							if(move[3] != '*'){
								attacking =0;
								continue;
							}
						}

						if(move[0] == 'm' || move[2] == 'M') { //elenhos gia na spawnarei/eksafanisei mosnster kai gia *
							attacking =0;
							telepathy =1;
						}
						//elenhos ean kanei kinisi meta tis epilogis tou iroa
						if(move[2] != 'a' && move[2] != 'A' && move[2] != 'u' && move[2] != 'U' && move[2] != 'd' &&  move[2] != 'D' && move[2] != 'l' && move[2] != 'L' &&  move[2] != 'r' &&  move[2] != 'R' && move[0] != 'm' && move[0] != 'M'){
							continue;
						}

						
						if(minicount){ //only for the first time he choose for position and how many moves they got
							switch(move[0]){ //
								case 'b':
								case 'B':
									for(i=0;i<6;i++){
										for(j=0;j<9;j++){
											if(table[i][j] == 'B'){
												piece_i = i;
												piece_j = j;
											}
										}
									}
									steps =8;
									break;
								case 'e':
								case 'E':
									for(i=0;i<6;i++){
										for(j=0;j<9;j++){
											if(table[i][j] == 'E'){
												piece_i = i;
												piece_j = j;
											}
										}
									}
									steps = 12;
									break;
								case 'd':
								case 'D':
									for(i=0;i<6;i++){
										for(j=0;j<9;j++){
											if(table[i][j] == 'D'){
												piece_i = i;
												piece_j = j;
											}
										}
									}
									steps = 6;
									break;
								case 'w':
								case 'W':
									for(i=0;i<6;i++){
										for(j=0;j<9;j++){
											if(table[i][j] == 'W'){
												piece_i = i;
												piece_j = j;
											}
										}
									}
									steps = 10;
									break;
							}
						}
						for(i=2;i<MoveStrLength-3;i++){ //vriskei to totallength
							if(move[i] == 'u' && move[2] != 'U' && move[2] != 'd' &&  move[2] != 'D' && move[2] != 'l' && move[2] != 'L' &&  move[2] != 'r' &&  move[2] != 'R'){
								if(countFlag==1){ //o elenhos diplis kinisis
									continueFlag=1;
									break;
								}
								if(checked){ //o hristis prospathise na kanei kai trito move se ena command
									continueFlag=1;
									break;
								}
								if(moving){ //ean valei kai deftero direction
									if(temp == 'u' || temp == 'U' || temp == 'd' || temp == 'D'){ //ean hrisimopoiei dio katefthinsis ston idio axona
										if(move[i] == 'u' || move[i] == 'U' || move[i] == 'd' || move[i] == 'D'){
											continueFlag = 1;
											break;
										}
										checked=1;
										direction2 = move[i];
									}
									else{
										if(move[i] == 'l' || move[i] == 'L' || move[i] == 'r' || move[i] == 'R'){
											continueFlag = 1;
											break;
										}
										checked = 1;
										direction2 = move[i];
									}
								}
								moving =1; //flag gia na xeroume pou na arhisoume na metrame
								temp = move[i]; //perno tin kinisi pou ekane
								countFlag = 1; //gia ton elehno an vazei 2 kinisis tin mia meta apo tin allh
								direction1 = move[i];
								continue;
							}
							if(moving){
								if(checked){ //h defteri katefthinsi
									if(flagforl2){//gia to deftero digit
										moveLength2 = moveLength2*10 + (move[i] -'0');
										continue;
									}
									moveLength2 = move[i] = '0';
									flagforl2 = 1;
								}
								else{ //h proti katefthinsi
									if(flagforl1){//gia to deftero digit
										moveLength1 = moveLength1*10 + (move[i] -'0');
										continue;
									}
									moveLength1 = move[i] - '0';
									flagforl1 = 1;
								}
							}
						}
						if(continueFlag){
							continue;
						}
						totallength = moveLength1 + moveLength2;
						if(steps < totallength){ //ean o hristis zitise parapano vimata apo oti mporei o hroas na kanei
							continue;
						}
						for(i=0; i<=moveLength1; i++){//checks for obsticles on first direction
							switch(direction1){//checkarei gia empodia sto proto direction
								case 'u':
								case 'U':
									if((table[piece_i-i][piece_j] >= 'A' && table[piece_i-i][piece_j] <= 'z') || table[piece_i-i][piece_j]=='#' || table[piece_i-i][piece_j] == '@'){
										continueFlag=1;
										break;
									}
									else if(!attacking && table[piece_i-i][piece_j] >= '1' && table[piece_i-i][piece_j] <= '9'){
										continueFlag = 1;
										break;
									}
									else if(i != moveLength1-1 && attacking && table[piece_i-i][piece_j] >= '1' && table[piece_i-i][piece_j] <= '9'){
										continueFlag = 1;
										break;
									}
									if(attacking && i == moveLength1 && (table[new_piece_i-i][new_piece_j] <= '1' || table[new_piece_i-i][new_piece_j] >= '9')){
										continueFlag =1;
										break;
									}
									new_piece_i = piece_i - i;
									new_piece_j = piece_j;
									final_piece_i = new_piece_i - i;
									final_piece_j = new_piece_j;
									break;
								case 'd':
								case 'D':
									if((table[piece_i+i][piece_j] >= 'A' && table[piece_i+i][piece_j] <= 'z') || table[piece_i+i][piece_j]=='#' || table[piece_i+i][piece_j] == '@')
									{
										continueFlag=1;
										break;
									}
									else if(!attacking && table[piece_i+i][piece_j] >= '1' && table[piece_i+i][piece_j] <= '9'){
										continueFlag = 1;
										break;
									}
									else if(i != moveLength1-1 && attacking && (table[piece_i+i][piece_j] >= '1' && table[piece_i+i][piece_j] <= '9')){
										continueFlag = 1;
										break;
									}
									if(attacking && i == moveLength1 && (table[new_piece_i+i][new_piece_j] <= '1' || table[new_piece_i+i][new_piece_j] >= '9')){
										continueFlag =1;
										break;
									}
									new_piece_i = piece_i + i;
									new_piece_j = piece_j;
									final_piece_i = new_piece_i + i;
									final_piece_j = new_piece_j;
									break;
								case 'l':
								case 'L':
									if((table[piece_i][piece_j-i] >= 'A' && table[piece_i][piece_j-i] <= 'z') || table[piece_i][piece_j-i]=='#' || table[piece_i][piece_j-i] == '@')
									{
										continueFlag=1;
										break;
									}
									else if(!attacking && table[piece_i][piece_j-i] >= '1' && table[piece_i][piece_j-i] <= '9'){
										continueFlag = 1;
										break;
									}
									else if(i != moveLength1-1 && attacking && (table[piece_i][piece_j-i] >= '1' && table[piece_i][piece_j-i] <= '9')){
										continueFlag = 1;
										break;
									}
									if(attacking && i == moveLength1 && (table[new_piece_i][new_piece_j-i] <= '1' || table[new_piece_i][new_piece_j-i] >= '9')){
										continueFlag =1;
										break;
									}
									new_piece_i = piece_i;
									new_piece_j = piece_j - i;
									final_piece_i = new_piece_i;
									final_piece_j = new_piece_j - i;
									break;
								case 'r':
								case 'R':
									if((table[piece_i][piece_j+i] >= 'A' && table[piece_i][piece_j+i] <= 'z') || table[piece_i][piece_j+i]=='#' || table[piece_i][piece_j+i] == '@')
									{
										continueFlag=1;
										break;
									}
									else if(!attacking && table[piece_i][piece_j+i] >= '1' && table[piece_i][piece_j+i] <= '9'){
										continueFlag = 1;
										break;
									}
									else if(i != moveLength1-1 && attacking && (table[piece_i][piece_j+i] >= '1' && table[piece_i][piece_j+i] <= '9')){
										continueFlag = 1;
										break;
									}
									if(attacking && i == moveLength1 && (table[new_piece_i][new_piece_j+i] <= '1' || table[new_piece_i][new_piece_j+i] >= '9')){
										continueFlag =1;
										break;
									}
									new_piece_i = piece_i;
									new_piece_j = piece_j + i;
									final_piece_i = new_piece_i;
									final_piece_j = new_piece_j + i;
									break;
								default:
									// no problems
									break;
								
							}
							if(continueFlag){
								break;
							}
						}
						if(continueFlag){
							continue;
						}
						if(checked){// if existed, checks obsticles for second direction
							for(i=0; i<moveLength2; i++){
								switch(direction2){
									case 'u':
									case 'U':
										if((table[new_piece_i-i][new_piece_j] >= 'A' && table[new_piece_i-i][new_piece_j] <= 'z') || table[new_piece_i-i][new_piece_j]=='#' || table[new_piece_i-i][new_piece_j] == '@')
										{
											continueFlag=1;
											break;
										}
										else if(!attacking && table[new_piece_i-i][new_piece_j] >= '1' && table[new_piece_i-i][new_piece_j] <= '9'){
											continueFlag = 1;
											break;
										}
										else if(i != moveLength2-1 && attacking && currentHero != 'E' && currentHero != 'W' && table[new_piece_i-i][new_piece_j] >= '1' && table[new_piece_i-i][new_piece_j] <= '9'){
											continueFlag = 1;
											break;
										}
										else if(attacking && i == moveLength2 && (table[new_piece_i-i][new_piece_j] <= '1' || table[new_piece_i-i][new_piece_j] >= '9')){
											continueFlag = 1;
											break;
										}
										final_piece_i = new_piece_i - i;
										final_piece_j = new_piece_j;
										break;
									case 'd':
									case 'D':
										if((table[new_piece_i+i][new_piece_j] >= 'A' && table[new_piece_i+i][new_piece_j] <= 'z') || table[new_piece_i+i][new_piece_j]=='#' || table[new_piece_i+i][new_piece_j] == '@')
										{
											continueFlag=1;
											break;
										}
										else if(!attacking && table[new_piece_i+i][new_piece_j] >= '1' && table[new_piece_i+i][new_piece_j] <= '9'){
											continueFlag = 1;
											break;
										}
										else if(i != moveLength2-1 && attacking && (table[new_piece_i+i][new_piece_j] >= '1' && table[new_piece_i+i][new_piece_j] <= '9')){
											continueFlag = 1;
											break;
										}
										else if(attacking && i == moveLength2 && (table[new_piece_i+i][new_piece_j] <= '1' || table[new_piece_i+i][new_piece_j] >= '9')){
											continueFlag = 1;
											break;
										}
										final_piece_i = new_piece_i + i;
										final_piece_j = new_piece_j;
										break;
									case 'l':
									case 'L':
										if((table[new_piece_i][new_piece_j-i] >= 'A' && table[new_piece_i][new_piece_j-i] <= 'z') || table[new_piece_i][new_piece_j-i]=='#' || table[new_piece_i][new_piece_j-i] == '@')
										{
											continueFlag=1;
											break;
										}
										else if(!attacking && table[new_piece_i][new_piece_j-i] >= '1' && table[new_piece_i][new_piece_j-i] <= '9'){
											continueFlag = 1;
											break;
										}
										else if(i != moveLength2-1 && attacking && (table[new_piece_i][new_piece_j-i] >= '1' && table[new_piece_i][new_piece_j-i] <= '9')){
											continueFlag = 1;
											break;
										}
										else if(attacking && i == moveLength2 && (table[new_piece_i][new_piece_j-i] <= '1' || table[new_piece_i][new_piece_j-i] >= '9')){
											continueFlag = 1;
											break;
										}
										final_piece_i = new_piece_i;
										final_piece_j = new_piece_j - i;
										break;
									case 'r':
									case 'R':
										if((table[new_piece_i][new_piece_j+i] >= 'A' && table[new_piece_i][new_piece_j+i] <= 'z') || table[new_piece_i][new_piece_j+i]=='#' || table[new_piece_i][new_piece_j+i] == '@')
										{
											continueFlag=1;
											break;
										}
										else if(!attacking && table[new_piece_i][new_piece_j+i] >= '1' && table[new_piece_i][new_piece_j+i] <= '9'){
											continueFlag = 1;
											break;
										}
										else if(i != moveLength1-1 && attacking && currentHero != 'E' && currentHero != 'W' && (table[new_piece_i][new_piece_j+i] >= '1' && table[new_piece_i][new_piece_j+i] <= '9')){
											continueFlag = 1;
											break;
										}
										else if(attacking && i == moveLength2 && (table[new_piece_i][new_piece_j+i] <= '1' || table[new_piece_i][new_piece_j+i] >= '9')){
											continueFlag = 1;
											break;
										}
										else if(currentHero == 'E' && attacking){
											for(j=0; j<*y; j++){
												if(table[new_piece_i][new_piece_j] == '#' || table[new_piece_i][new_piece_j] == '#'|| (table[new_piece_i ][new_piece_j] >= 'A' && table[new_piece_i ][new_piece_j] <= 'Z')){
													flag++;
													break;
												}
											}
											break;
										}
										else if(currentHero == 'W' && attacking){
											for(i=0; i<*y; i++){
												if(table[new_piece_i][new_piece_j] == '#'){
													continueFlag = 1;
													break;
												}
											}
											break;
										}
										final_piece_i = new_piece_i;
										final_piece_j = new_piece_j + i;
										break;
									default:
										// no problems
										break;
								}	
								if(continueFlag){
									break;
								}
							}
						}
						if(continueFlag){
							continue;
						}
						//250+ lines worth of checks
						//outdid yourself man -anesths
						steps-=totallength;
					}
					if(!enoughMoves){
						continue;
					}
					for(i=0;i<moveLength1;i++){
						switch(direction1){
							case 'u':
							case 'U':
								animationSteps[i][0] = piece_i-i;
								animationSteps[i][1] = piece_i;
							break;
							case 'd':
							case 'D':
								animationSteps[i][0] = piece_i+i;
								animationSteps[i][1] = piece_i;
								break;
							case 'l':
							case 'L':
								animationSteps[i][0] = piece_i;
								animationSteps[i][1] = piece_i-i;
								break;
							case 'r':
							case 'R':
								animationSteps[i][0] = piece_i;
								animationSteps[i][1] = piece_i+i;
								break;
						}
					}
					if(checked){ //if sec direction exists
						for(j=i;j<moveLength2+i;j++){ // animation table fill
							switch(direction1){
								case 'u':
								case 'U':
									animationSteps[j][0] = animationSteps[j-1][0]-1;
									animationSteps[j][1] = animationSteps[j-1][1];
								break;
								case 'd':
								case 'D':
									animationSteps[i][0] = animationSteps[j-1][0]+1;
									animationSteps[i][1] = animationSteps[j-1][1];
									break;
								case 'l':
								case 'L':
									animationSteps[j][0] = animationSteps[j-1][0];
									animationSteps[j][1] = animationSteps[j-1][1]-1;
									break;
								case 'r':
								case 'R':
									animationSteps[j][0] = animationSteps[j-1][0];
									animationSteps[j][1] = animationSteps[j-1][1]+1;
									break;
							}
						}
					}

					if(telepathy) {
						// Spawn or remove monster
						if(move[3] != '*'){ // syntax check
							printf("Invalid syntax. (Use: m>x*y).\n");
							continue;
						}
						mx = move[2]; //declare x coord as mx
						my = move[4]; //declare y coord as my
						if(table[mx][my] == '.'){
							//table[mx][my] = ; // lathos, switch gia diff kai rand gia health
							mcount++;
						}
						else if(table[mx][my] >= '1' && table[mx][my] <= '9'){
							table[mx][my] = '.';
							mcount--;
						}
						else{
							printf("Invalid move. You cannot spawn or remove a monster here.\n");
							continue;
						}
					}
					for(i=0; i<13; i++){//counts how many moves on animation table are
						if(animationSteps[i][0] == 0){
							break;
						}
					}
					animationStepsLength = i;
					if(attacking){//elenhos an kanei attack etsi oste na stamatisi mia thesi prin
						animationStepsLength--;
					}
					//arhizei to animation
					table[piece_i][piece_j] = '.';
					table[animationSteps[0][0]][animationSteps[0][1]] = currentHero;
					printf ("\033c"); // clears the screen
					showtable(table, *y);
					for(i=0;i<1000000000;i++);
					for(i=1;i<animationStepsLength;i++){
						table[animationSteps[i-1][0]][animationSteps[i-1][1]] = '.';
						table[animationSteps[i][0]][animationSteps[i][1]] = currentHero;
						printf ("\033c"); // clears the screen
						showtable(table, *y);
						for(i=0;i<1000000000;i++);
					}
					if(attacking){
						damage = combat(0);//damage
						//critical
						if(rand() % 10 == 1){
							damage*=2;
						}
						table[final_piece_i][final_piece_j] = table[final_piece_i][final_piece_j] - '0' - damage;
						if(table[final_piece_i][final_piece_j] <= 0){
							printf("Monster was slain\n");
							mcount--;
							table[final_piece_i][final_piece_j] = '.';
						}
						else{
							table[final_piece_i][final_piece_j] = table[final_piece_i][final_piece_j] + '0';
						}
					}
					if(mcount==0){
						printf("Well played Warrior, you advance through the next level!");
						advance = 1;
					}
				}
				if(advance){
					break;
				}
			}
			for(i=0; i<*y; i++){
				for(j=0;j<x;j++){
					if(table[i][j] >= '1' && table[i][j] <= '9'){
						ai = moveMon(table, y, animationSteps, i, j, hero_pos);
					}
				}
			}
		}	
		maketable(table, y, hero_pos, dif, herolist, 1, hcount);
	}
	return 10;
}



void settings(int *pdif, int *pheros){
	int choice;
	printf ("\033c"); // clears the screen
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

			while(*pdif > 3 || *pdif<1){
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



void maketable(int **table, int *n, int hero_pos[][2], int dif, int *herolist, int flag, int hcount){
	int i, j, k=0, m=17, ishashtag, luckm =0, luckn=0, mcount=0, monster_max=0, health=0;
	if (flag){
		//kane realloc edw. EDIT: Den kserw an doulevei swsta. test it
		int tempn = *n;

		table = (int **)realloc(table, (*n) *sizeof(int *));

		if (table == NULL){
			printf("Reallocation failed.");
		}

		for (i = tempn; i<*n; i++){
			table[i]=(int *)malloc(m * sizeof(int));
			if (table[i] == NULL){
				printf("Allocation failed.");
			}
			//for (j = 0; j <m; j++) {
			//	table[i][j] = ' ';
			//}
		}
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
			hero_pos[j][0] = luckn;
			hero_pos[j][1] = luckm;
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
                health = 3*dif -rand()%3;
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


int combat(int flag){
	int i, j, move, defended, attack=0, sum=0;
	defended = 0;
	attack = 0;
	if(!flag){ //player is attacking
		for(i=0; i<3; i++){
			move = rand() % 6;
			if(move <= 2 && move >= 0){
				attack++;
			}
			else{
				continue;
			}
		}
		for(i=0;i<2;i++){
			move = rand() % 6;
			if(move == 0){
				defended++;
			}
			else{
				continue;
			}
		}
	}
	else if(flag){ //monster is attacking
		for(i=0;i<2;i++){
			move = rand() % 6;
			if(move <= 2 && move >= 0){
				attack++;
			}
			else{
				continue;
			}
		}
		for(i=0;i<3;i++){
			move = rand() % 6;
			if(move <= 1 && move >= 0){
				defended++;
			}
			else{
				continue;
			}
		}
	}
	sum= attack-defended;
	if(sum<0){
		sum = 0;
	}
	return sum;
}


int moveMon(int **table, int *y, int move[][2], int pos_i, int pos_j, int **heroOnRoomPos) {
    int i, j, min, temp;
    int heroOnRoom = 0;
    int k=((pos_i-11)/10)+1; // Room number
    int upperWall = 11 +((k-1)*10);
    int whichRoom=0;
    int checking_i=3;
    int checking_j=3;
    int attack =0;
    // Finds a hero 
    // on the left room and saves the position

    if(pos_j >= 1 && pos_j <= 5){ // left room
        whichRoom = 1;
    }
    else if(pos_j >= 7 && pos_j <= 9) { // mid room
        whichRoom = 2;
    }
    else if(pos_j>=11 && pos_j<=15){ // right room
        whichRoom = 3;
    }
    else if(pos_i <= 6){ // spawn room
        whichRoom = 4;
    }
    else{ //debuging room
        printf("\033[1;95m We got a problem! Room wasn't detected. \033[0;0m\n");    
        return 0;
    }
    if(whichRoom == 1){ // left room
        for (i=0; i<9; i++){
            for (j=0; j<5; j++){
                if (table[upperWall+1+i][j+1] >= 'A' && table[upperWall+1+i][j+1] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+upperWall+1;
                    heroOnRoomPos[heroOnRoom][j] = j+1;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    else if(whichRoom == 2){ // mid room
        for (i=0; i<*y-8; i++){
            for (j=0; j<3; j++){
                if (table[7+i][j+7] >= 'A' && table[7+i][j+7] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+7;
                    heroOnRoomPos[heroOnRoom][j] = j+7;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    else if(whichRoom == 3){ // right room
        for (i=0; i<9; i++){
            for (j=0; j<5; j++){
                if (table[upperWall+1+i][j+11] >= 'A' && table[upperWall+1+i][j+11] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+upperWall+1;
                    heroOnRoomPos[heroOnRoom][j] = j+11;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    else if(whichRoom == 4){  // spawn room
        for (i=0; i<6; i++){
            for (j=0; j<9; j++){
                if (table[1+i][j+4] >= 'A' && table[1+i][j+4] <= 'Z') {
                    heroOnRoomPos[heroOnRoom][i] = i+1;
                    heroOnRoomPos[heroOnRoom][j] = j+4;
                    heroOnRoom++;
                    break;
                }
            }
        }
    }
    if (heroOnRoom) { 
        min = (heroOnRoomPos[0][0] + heroOnRoomPos[0][1]) - (pos_i + pos_j); // Arxikopoiei to min
    }

    if(heroOnRoom >1){
        for (i=1; i<heroOnRoom; i++){
            temp = (heroOnRoomPos[i][0] + heroOnRoomPos[i][1]) - (pos_i + pos_j);
            if (temp < min){
                min = temp;
                i--;
            }
        }
    }
    if(heroOnRoom){
        int count1 =1;
        int count2 =0;
        int MoveCountI = 0;
        int MoveCountJ = 0;
        int step =0;
        while(step<10){ // should add a check for error code
            while(step < 10 && (checking_i != -1 || checking_i != 0) && checking_i!= -2){
                if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -1){
                    if(checking_j == -1){
                        MoveCountJ++;
                        move[count1][0] = pos_i + MoveCountI;
                        move[count1][1] = pos_j + MoveCountJ;
                        step++;
                        count2=count1;
                        count1++;
                        checking_j = 5;
                        continue;
                    }
                    checking_i = -1; // Blocked
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -2){
                    checking_i = -2; // Error
                    checking_j = -2; // Error
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 0){
                    checking_i = 0; // No movement needed
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 1){
                    MoveCountI++;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 1, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 2){
                    MoveCountI--;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
            }
            while(step < 10 && (checking_j != -1 || checking_j != 0) && checking_j!= -2){
                if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -1){
                    if(checking_i == -1){
                        MoveCountJ++;
                        move[count1][0] = pos_i + MoveCountI;
                        move[count1][1] = pos_j + MoveCountJ;
                        step++;
                        count2=count1;
                        count1++;
                        checking_i = 0;
                        continue;
                    }
                    checking_j = -1; // Blocked
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == -2){
                    checking_i = -2; // Error
                    checking_j = -2; // Error
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 0){
                    checking_j = 0; // No movement needed
                    continue;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 1){
                    MoveCountJ++;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
                else if(pathfinder(table, move[count2][0], move[count2][1], 0, heroOnRoomPos[i][0], heroOnRoomPos[i][1]) == 2){
                    MoveCountJ--;
                    move[count1][0] = pos_i + MoveCountI;
                    move[count1][1] = pos_j + MoveCountJ;
                    step++;
                    count2=count1;
                    count1++;
                }
            }
            if(checking_i == -2 || checking_j == -2)
            {
                printf("there was a problem in pathfinder\n");
                return 0;
            }
            else if(checking_i ==0 && checking_j == 0){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
}    

int pathfinder(int **table, int pos_i, int pos_j, int flag, int dest_i, int dest_j){
    
    if (flag){
        if (pos_i < dest_i){
            if ((table[pos_i + 1][pos_j] >= '1' && table[pos_i + 1][pos_j] <= 'Z' ) || table[pos_i + 1][pos_j] == '#') {
                return -1; // Blocked
            } else {
                return 1; // Move down
            }
        } else if (pos_i > dest_i){
            if ((table[pos_i - 1][pos_j] >= '1' && table[pos_i - 1][pos_j] <= 'Z' ) || table[pos_i - 1][pos_j] == '#') {
                return -1; // Blocked
            } else {
                return 2; // Move up
            }

        } else {
            return 0; // No movement needed
        }
    } else {
        if (pos_j < dest_j){
            if ((table[pos_i][pos_j + 1] >= '1' && table[pos_i][pos_j + 1] <= 'Z' ) || table[pos_i][pos_j + 1] == '#') {
                return -1; // Blocked
            } else {
                return 1; // Move right
            }
        } else if (pos_j > dest_j){
            if ((table[pos_i][pos_j - 1] >= '1' && table[pos_i][pos_j - 1] <= 'Z' ) || table[pos_i][pos_j - 1] == '#') {
                return -1; // Blocked
            } else {
                return 2; // Move left
            }
        } else {
            return 0; // No movement needed
        }
    }
    printf("\033[1;95m We got a problem! Pathfinding failed. \033[0;0m\n");
    return -2; // Error case
}