//TODO: Replace random life with spaceships
/* 
 * Created By: Keeyan Nejad @KNejad
 * Creation Date: 2016/10/11
 * Description: Game of life game where you have to protect block 5 E. Each turn you get to change the value of 1 block
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define gridSize  32

int block[gridSize][gridSize] = {};

//creates a random number between min_num and max_num (Inclusive)
int random_number(int min_num, int max_num)
{
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1; // this is done to include max_num in output.
	}else{
		low_num=max_num+1;// this is done to include max_num in output.
		hi_num=min_num;
	}
	srand(time(NULL));
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}



// Initialises the grid to all 0 except for the 4*4 block in the center
void createGrid(){
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			block[i][j] = 0;
		}
	}
	block[gridSize/2][gridSize/2] = 1;
	block[gridSize/2][gridSize/2+1] = 1;
	block[gridSize/2+1][gridSize/2+1] = 1;
	block[gridSize/2+1][gridSize/2] = 1;
}

//prints the grid to the screen
void printGrid(){
	printf("   ");
	for(int x = 0; x<gridSize; x++){
		printf("%-3d", x);
	}
	printf("\n");
	for(int y = 0; y < gridSize; y++){
		printf("%-3d", y);
		for(int x = 0; x<gridSize; x++){	
			if(block[x][y]){
				printf("%-3c", '*');
			}
			else{
				printf("%-3c", ' ');
			}

		}
		printf("\n");
	}

}

//asks the user to alter a block on the grid
int alterGrid(){

	int inx;
	int iny;

	printf("Coordinates to Change: ");
	scanf("%d%d", &inx,&iny);

	//cleara the buffer
	while ((getchar()) != '\n'); 
	if(inx<=31 && inx>=0 && iny<=31 && iny>=0){
		block[inx][iny] = !block[inx][iny];
	}else{
		printf("Incorrect Option. Try Again\n");
		alterGrid();
	}


}


//Processes all the blocks 
void processBlocks(){
	int newBlock[gridSize][gridSize] = {};
	for(int y = 0; y <gridSize; y++){
		int neigbours = 0;
		for(int x = 0; x<gridSize; x++){	
			neigbours = block[x-1][y-1] + block[x][y-1] + block[x+1][y-1] + 
				block[x-1][y] + block[x+1][y]+ 
				block[x-1][y+1] + block[x][y+1]+ block[x+1][y+1];
			if(block[x][y]){
				if(neigbours<2){
					newBlock[x][y] = 0;
				}else
					if(neigbours == 2 || neigbours == 3){
						newBlock[x][y] = 1;
					}else
					{
						newBlock[x][y] = 0;
					}
			}
			//if block is dead and it has exactly 3 neibours it revives
			else if(neigbours==3){
				newBlock[x][y] = 1;
			}
		}
	}
	for(int y = 0; y <gridSize; y++){
		for(int x = 0; x<gridSize; x++){	
			block[x][y] = newBlock[x][y];
		}
	}

}

//Create some blocks near each other at the top of the screen
void createLife(int x_min, int x_max, int y_min, int y_max){
	//create a random number between 0 and gridSize - 5 
	int x = random_number(x_min,x_max);
	int xplus = x +4;

	int initialy = random_number(y_min,y_max);
	int y = initialy;
	int yplus = y + 4;
	for(x; x<xplus;x++){
		y = initialy;
		for(y; y<yplus;y++){		
			if(x>=0 && x<=31 && y>=0 && y<=31){
				//randomly sets blocks in a 4*4 grid to either 0 or 1
				block[x][y] = rand() % 2;
			}
		}
	}	
}
int allAlive(){
	if(
			block[gridSize/2][gridSize/2] == 1 && 
			block[gridSize/2][gridSize/2+1] == 1 && 
			block[gridSize/2+1][gridSize/2+1] == 1 && 
			block[gridSize/2+1][gridSize/2] == 1
	  ){
		return 1;
	}else{
		return 0;
	}
}

void main() {
	int score = 0;
	int alive = 1;
	createGrid();
	while(alive){
		//creates life in all four sides
		createLife(0,gridSize,0,4);
		createLife(0,4,0,gridSize-4);
		createLife(gridSize-8,gridSize-4,0,gridSize-4);
		createLife(0,gridSize-4,gridSize-8,gridSize-4);
		printGrid();
		if(!allAlive()){
			alive = 0;
			break;
		}
		alterGrid();
		if(!allAlive()){
			alive = 0;
			break;
		}
		processBlocks();
		score++;
	}
	printf("Game Over! Score: %d\n", score);
}
