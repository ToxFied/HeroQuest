#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int mmenu(); // main menu
int play(int dif, int herolist[], int **table, int m, int n); // starting the game
void settings(int *pdif, int* pheros); // name says it all
void help();
void maketable(int heros, int **heroes_pos, int ***monsters_pos, int herolist[], int dif, int n, int m, int **table); // map generation and loading
void showtable(int **table, int m, int n);

int main(void){
	int i, j, **table, herolist[4] = {0}, select, flag=0, heros=2, *pheros = &heros, count, n, m, dif=2, *pdif = &dif, check, heroes_pos[4][2] = {0}, monsters_pos[6][2][1] = {0};
	n = 6; // n = lines of the table
	m = 12; // m = rows of the table
	
	table = (int **)malloc(n * sizeof(int *)); // allocate memory for the dynamic 2D array
	if (table == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}
	
	for (i = 0; i < n; i++){
		table[i] = (int *)malloc(m * sizeof(int));
		if (table[i] == NULL){
			for (j = 0; j < i; j++) { // free previously allocated memory
				free(table[j]);
			}
			free(table);
			printf("Memory allocation failed\n");
			
			return 1;
		}
		for (j = 0; j < m; j++) { // set all elements to 0
			table[i][j] = 0;
		}
	}
	
	while(1){ 
		srand(time(NULL));
		check = mmenu();
		switch(check){
			case 1:
				for(i=0; i< heros; i++){  // hero selection
					flag=0;  // check for already existing hero
					printf("select a hero: (1-barbarian, 2-elf, 3-dwarf, 4-wizard): ");
					scanf("%d", &select);
					while(select<1||select>4)
					{
						printf("please select an avilable hero: (1-barbarian, 2-elf, 3-dwarf, 4-wizard): ");
						scanf("%d", &select);
					}
					for(j=0; j<4; j++)  //already existing hero check
					{
						if(herolist[j] == select)
							flag =1;
							break;
					}
					if(flag)
					{
                        printf("hero already selected! please select again.\n");
						i--;
						continue;
					}
					herolist[i] = select; //enter the hero
				}
				maketable(heros, heroes_pos, monsters_pos, herolist, dif, n, m, table); // map generation
				play(dif, herolist, table, m, n);
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
				
int mmenu()
{
	int choice;
	printf("\n\n");
	printf("\t\t\tWELCOME TO HEROQUEST\n\n");
	printf("\tPlay(1)\n");
	printf("\tHelp(2)\n");
	printf("\tSettings(3)\n");
	printf("\tQuit(4)\n");
	printf("\nGive one of the 3 numbers above to start!: ");
	scanf("%d", &choice);
	printf("\n");
	while(choice > 4 || choice < 1){
		printf("please give a number in range of (1-4): ");
		scanf("%d", &choice);
		printf("\n");
	}
	return choice;
}
void help(){
	system("clear");
	printf("\n\t\t\033[1mNSTRUCTIONS\033[0m\n\n");
	printf("\033[4mHow to play:\033[0m \n\n");
	printf("\033[3;92mHeroQuest\033[0m is a game of dungeons with monsters that you have to slay\n");
	printf("You select with which heros you want to play (or all of them) and\n");
	printf("fight the spawns of \033[95mZARGON\033[0m to advance into the next dungeon.\n\n");
}

int play(int dif, int herolist[], int **table, int m, int n){
	int i, j, healthtable[4] ={0}, count;
	char *names[4]={0};

	showtable(table, m, n);
	printf("\n\n");

	for(i=0; i<4; i++){
		switch(herolist[i]){
			case 'B':
				healthtable[i] = 8; // barbarian
				break;
			case 'D' :
				healthtable[i] = 7; // dwarf
				break;
			case 'E':
				healthtable[i] = 6; // elf
				break;
			case 'W':
				healthtable[i] = 4; // wizard
				break;
		}
	}

    for(i=0; i<4;i++){
        if(!(herolist[i] == 0)){ // count the number of heroes
            count++;
        }
    }

    for(i=0; i<4; i++){ 
		switch(herolist[i]){
			case 'B':
				names[i] = "Barbarian";
				break;
			case 'D' :
				names[i] = "Dwarf";
				break;
			case 'E':
				names[i] = "Elf";
				break;
			case 'W':
				names[i] = "Wizard";
				break;
		}
    }

	for(i=0;i<count; i++){ 
		printf("%s: \033[92;1m%dHP\033[0m \n", names[i], healthtable[i]);  // prints the health of each selected hero
	}
	printf("\n");

	

}

void settings(int *pdif, int *pheros){
	int choice;
    while(1){
		printf("\n\n\t\033[1mSettings\033[0m:\n\n\n");
		printf("\tSelect difficulty(1) \t\t Heros(2)\t\t Exit the settings(3)\n\n");
		printf("\nSelect: ");
		scanf("%d", &choice);
		printf("\n");
		while(choice > 3 || choice<1){
			printf("Please give an available choice from the above(1-3): ");
			scanf("%d", &choice);
			printf("\n");
		}
		if(choice == 3){
			return;
		}
		else if(choice == 1){
			printf("Child's Play(1)\n");
			printf("Medium(2)\n"); // default
			printf("Hurt me plenty!(3)\n");
			printf("\nSelect a difficulty!: ");
			scanf("%d", pdif);
			printf("\n");
			while(*pdif > 3 || pdif<1){
				printf("Please give an available choice from the above(1-3): ");
				scanf("%d", pdif);
				printf("\n");
			}
		}
		else if(choice==2){
			printf("Select with how many heros you going to play(1-4): "); // default: 2
			scanf("%d", pheros);
			printf("\n");
			while(*pheros<1 || *pheros > 4){
				printf("please givean available number of heros(1-4) ");
				scanf("%d", pheros);
				printf("\n");
			}
		}
	}
}

void maketable(int heros, int **heroes_pos, int ***monsters_pos, int herolist[], int dif, int n, int m, int **table){
	int i, j, luckn, luckm, wall1, door1, wall2, door2, flag=0, monsters, health, wallcount=0;
	wall1 = (rand() % (m-4))+2;
	door1 = (rand() % (n-4))+2;
	for(i=0; i<n; i++)  // adding the first horizontal wall
	{
		if(door1==i) // adding the first door
			continue;
		table[i][wall1] = '#'; 
	}
	wall2 = (rand() % (m-4))+2;
	while(wall2 == door1){  // check if wall falls on the door of the first wall
		wall2 = (rand() % (m-4))+2;
	}
	for(i=0; i<m; i++) // adding the second vertical wall
	{
        if(table[wall2][i]=='#') //stop when you find a wall
			break;
		table[wall2][i] = '#';
		wallcount++; // count the number of cells that a wall occupies in order to input a door
	}
	door2 = (rand() % wallcount);
	table[wall2][door2] = 0; // adding the door on the second wall

	for(i=0; i<3; i++);  // add the furniture
	{
		while(1){
			luckn = rand() % n;
			luckm = rand() % m;
			if(table[luckn][luckm]=='#') 
			{
				continue;
			}
			else
			{
				break;
			}
        }
		table[luckn][luckm] = '@'; 
	}

	for(i=0;i<heros;i++){  // spawning heroes
        flag = 0;
		while(1){
			luckn = rand() % n;
			luckm = rand() % m;
			if(table[luckn][luckm] = '#' || table[luckn][luckm] == '@')
			{
				continue;
			}
			else
			{
				break;
			}
	    }
        for(i=0;i<heros;i++){
            if(table[luckn][luckm] == herolist[i]){
                flag++;
            }
        }
        if(flag){
            i--;
            continue;
        }

		heroes_pos[i][0] = luckn; // heroes position of x
		heroes_pos[i][1] = luckm; // heroes position of y
	}
    switch(dif){  // deciding number of monsters
        case 1:
            monsters = (rand() % 2) +1; // Child's Play
            break;
        case 2:
            monsters = (rand() % 4) +1; // Medium
            break;
        case 3:
            monsters = (rand() % 6) +1; // Hurt me plenty	
            break;
    }
    for(i=0;i<monsters;i++) { // spawning monsters
        flag = 0;
		while(1){ // Infinite loop to find a free spot for a monster
			luckn = rand() % n; 
			luckm = rand() % m;
			if(table[luckn][luckm]=='#' || table[luckn][luckm]=='@')
			{
				continue;
			}
			else
			{
				break;
			}
	    }
        for(i=0;i<heros;i++){ 
            if(table[luckn][luckm] == herolist[i]){
                flag++;
				break;
            }
        }
        if(flag){
            i--;
            continue;
        }
		for(i=0;i<monsters;i++){ // check if the spot is already taken by a monster or a hero
            if(table[luckn][luckm] >='0' && table[luckn][luckm] <='9'){
                flag++;
				break;
            }
        }
        if(flag){
            i--;
            continue;
        }

		monsters_pos[i][0][0] = luckn; // monsters position of x
		monsters_pos[i][1][0] = luckm; // monsters position of y

		switch(dif){
			case 1: // Child's Play
				health = (rand() % 3) +1;
				switch(health){
					case 1:
						health = '1';
						break;
					case 2:
						health = '2';
						break;
					case 3:
						health = '3';
						break;
				}
			case 2: // Medium
				health = (rand() % 3) +4;
				switch(health){
					case 4:
						health = '4';
						break;
					case 5:
						health = '5';
						break;
					case 6:
						health = '6';
						break;
				}
			case 3:
				health = (rand() % 3) +7;
				switch(health){
					case 7:
						health = '7';
						break;
					case 8:
						health = '8';
						break;
					case 9:
						health = '9';
						break;
				}
		}
		table[luckn][luckm] = health;
    }
	for(i=0; i<n; i++){ // filling the table with '.'
		for(j=0; j<m; j++){
			if(table[i][j] == 0){
				table[i][j] = '.';
			}
		}
	}
	return;
}

void showtable(int **table, int m, int n){
	int i, j, k;
	system("clear");
	printf("\n    \033[4m "); 
    
    for(k=0; k<m-1; k++){
        printf("%c ", 'A' +k);
    }
    printf("%c", 'A' + k);
    printf("\033[0m\n");
    
    for(k=0; k<n; k++){ 
        printf(" %d %c", k+1, 222); // left border
        for( i = 0; i < m; i++) {
            printf(" %c", table[k][i]);
        }
        printf("\n");
    }
	return;
}