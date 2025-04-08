#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int mmenu();  // main menu
int play(int dif, int herolist[], int table[][], int m, int n);    // starting the game
void settings(int *pdif, int* pheros);  // name says it all
void help();
void maketable(int heros, int dif, int n, int m, int table[][]); // map generation and loading
void showtable(int table[][], int m, int n);

int main(void){
	int i, j, table[6][12] = {0}, herolist[4] = {0}, select, flag=0, heros=1, *pheros = &heros, count, n, m, dif=1, *pdif = &dif, check;
	n = 6; // n is the lines of the table
	m = 12;  // m is the rows of the table
	while(1){
		srand = rand(time(NULL));
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
				maketable(heros, herolist, dif, n, m, table); // map generation
				play(dif, herolist, table, m, n);
				break;
			case 2:
				help();
				break;
			case 3:
				settings(pdif, pheros);
				break;
			case 4:
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
	printf("fight the spawns of \033[95mZARGON\033[0m to advance into the next dungeon.\n");
	printf("");
}

int play(int dif, int herolist[], int table[][], int m, int n){
	int i, j, healthtable[4] ={0}, count;
	char *names[4]={0};

	showtable(table, m, n); //i hate niggers
	printf("\n\n");

	for(i=0; i<4; i++){
		switch(herolist[i]){
			case 'B':
				healthtable[i] = 8;
				break;
			case 'D' :
				healthtable[i] = 7;
				break;
			case 'E':
				healthtable[i] = 6;
				break;
			case 'W':
				healthtable[i] = 4;
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
			printf("Medium(2)\n");
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
			printf("Select with how many heros you going to play(1-4): ")
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

void maketable(int heros, int dif, int n, int m, int table[][]){
	int i, j, luckn, luckm, luckln1, luckp1, luckln2, luckp2, flag=0, mosters, health, wallcount=0;
	luckln1 = (rand() % (m-4))+2;
	luckp1 = (rand() % (n-4))+2;
	for(i=0; i<n; i++)  // adding the first horizontal wall
	{
		if(luckp1==i) // adding the first door
			continue;
		table[i][luckln1] = '#';
	}
	luckln2 = (rand() % (m-4))+2;
	while(luckln2 == luckp1){  // check if wall falls on the door of the first wall
		luck4 = (rand() % (m-4))+2;
	}
	for(i=0; i<m; i++) // adding the second vertical wall
	{
        if(table[luckln2][i]=='#') //stop when you find a wall
			break;
		table[luckln2][i] = '#';
		wallcount++; // count how many walls we got to make the door
	}
	luckp2 = (rand() % wallcount);
	table[luckln2][luckp2] = 0; //adding the door on the second wall

	for(i=0; i<3; i++);  //add the furnitures
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
	for(i=0;i<heros;i++) {  // spawning heroes
        flag =0;
		while(1){
			luckn = rand() % n;
			luckm = rand() % m;
			if(table[luckn][luckm]= '#' || table[luckn][luckm]=='@')
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
    }
    switch(dif){  // deciding number of monsters
        case 1:
            monsters = (rand() % 2) +1;
            break;
        case 2:
            monsters = (rand() % 4) +1;
            break;
        case 3:
            monsters = (rand() % 6) +1;
            break;
    }
    for(i=0;i<monsters;i++) {
        flag =0;
		while(1){
			luckn = rand() % n;
			luckm = rand() % m;
			if(table[luckn][luckm]= '#' || table[luckn][luckm]=='@')
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
		for(i=0;i<monsters;i++){
            if(table[luckn][luckm] >='0' && table[luckn][luckm] <='9'){
                flag++;
				break;
            }
        }
        if(flag){
            i--;
            continue;
        }
		switch(dif){
			case 1:
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
			case 2:
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
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			if(table[i][j] == 0){
				table[i][j] = '.';
			}
		}
	}
	return;
}

void showtable(int table[][], int m, int n){
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