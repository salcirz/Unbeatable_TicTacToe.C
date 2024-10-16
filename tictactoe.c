#include <stdio.h>
#include <stdbool.h>

/* 
 * General Methods: Print Board, Check Winner, Place Winner, Block, placerandom
 *
 * User goes first: Place Defense, checkcorners, checkcenters
 * 
 * User goes Second: placemove
 */


// set the board to all -1 
int nums[9]= {-1,-1,-1,-1,-1,-1,-1,-1,-1};

// double array of all possible win combinations based on index  
int wincombinations[8][3]= {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};



//function to print the board 
void printboard(){

	//for the length of the board
	for(int i = 0 ; i<9; i++){
		
		//either print O,X, or " " based on whats in that space
		if(nums[i] == 1){
		
			printf("O");
		
		}else if(nums[i]==0) {
		
			printf("X");
		}else{
			printf(" ");
		}
		
		//every three print a straigt line
		if(i%3== 2&& i<7){
			printf("\n-----\n");

		//otherwise print a wall
		}else if(i<8){
		
			printf("|");
		}
	
	}
	//at the end print a blank line
	printf("\n\n");


}

//helper method to check if the corner indexes are empty
bool checkcorners(){

	//if corners are all negative one then theyre empty
	if(nums[0]==-1 && nums[2]==-1 && nums[6]==-1&& nums[8]==-1){
		return true;
	
	}else{
	
		return false;
	
	}

}


//helper method to check if the center spots are taken, all besides the true middle
bool checkcenters(){

	if(nums[1]==-1 && nums[3]==-1 && nums[5]==-1&&nums[7]==-1){
	
		return true;
	
	}else{
	
		return false;
	}

}


//checks if there is a winner at any point
bool winner(){
	
	//checks all possible combinations and if they are all equal and not -1 then theres a winner
	if(nums[0] == nums[1] && nums[1] ==  nums[2] && nums[0]!= -1){
		return true;	
	}
	if(nums[3]== nums[4] && nums[4]== nums[5]&& nums[3]!=-1){
		return true;
	}
	if(nums[6]==nums[7]&& nums[7]==nums[8]&& nums[6]!=-1){
		return true;
	}
	if(nums[0]== nums[3]&& nums[3]== nums[6]&& nums[0]!=-1){
		return true;
	}
	if(nums[1]== nums[4] && nums[4]== nums[7]&& nums[1]!=-1){
		return true;
	}
	if(nums[2]== nums[5]&& nums[5]== nums[8]&& nums[2]!=-1){
		return true; 
	}
	if(nums[0]== nums[4] && nums[4]== nums[8]&&nums[0]!=-1){
		return true;	
	}
	if(nums[2]== nums[4]&& nums[4]== nums[6]&& nums[2]!=-1){
		return true;
	}
	
	return false; 

}


// helper method to place the first open spot 
void placerandom(){

	//for the whole board
	for(int i = 0; i<8;i++){
	
		//if the spot is blank place an x there 
		if(nums[i]==-1){
		
			nums[i]=0;
			return;
		
		}
	
	}

}

//place defense function used when going second. its based on where the user goes which is place holder 
void placedefense(int placeholder){


	//if they go middle then go top corner 
	if(placeholder== 4){
	
		nums[0]=0;
	
	}else{
		//otherwise we go middle
		nums[4]=0;
	}



}

//place move is used when we go first and now its our second turn, and its based on where they go which is placeholder  
void placemove(int placeholder){

	//if they go in the bottom right corner or the tiles above and to the left of it we go middle
	if(placeholder == 5|| placeholder == 7|| placeholder == 8){
		nums[4]=0;
	
	//otherwise if they go directly next to me (im 0) 
	}else if(placeholder == 1|| placeholder==3){
	
		//we go in the corner opposite of them 
		nums[6/placeholder]=0;

	// otherwise if they go the two other corners we go bottom right 
	}else if(placeholder==2 || placeholder==6){
		
		nums[8]=0;
	}else{
	
		//and otherwise we go bottom right
		nums[8]=0;
	}


	




}


//method to check if we are threatened to lose and if we are we place it 
bool placeblock(){

	//declare the current spot where checking its index and two booleans
	int spot;
	int index; 
	bool brake = false;
	bool foundspot;


	//for the length of the double array, or all possible win conditions
	for(int i = 0; i<8; i++){

	
		//we check all three spots for each combination
		for(int j =0;j<3;j++){
			foundspot = false;
	
			//if we find a spot then we set it and save its index 
			if(nums[wincombinations[i][j]]==-1){

				
  				spot = wincombinations[i][j];
				index =j;
				foundspot = true;
				break;	
							
			}

		}

		//we saved found spot so we can just continue if there isint one 
		if(!foundspot){
			continue;
		}


		//set the brake to false so we know that we didnt break yet, if we end up breaking that means that spot we
		//found it was not possible to win there for the other player so we broke
		brake = false;

		//for the other spots 
		for(int k=0; k<3; k++){
			//if the spot is the one we found keep going 
			if(k == index){
				continue;
			}
			
			//if the next win combination spot is empty or my spot then we cant win and break is true
			if(nums[wincombinations[i][k]] == -1|| nums[wincombinations[i][k]] == 0){
				brake = true;
				break; 
			}

		}

		//if we didnt end up breaking then the other player has two positions in that win combination with one open spot
		//which we now take and return true 
		if(brake == false){

			nums[spot] = 0;
			
			return true;			
		}
	
	}
	//if there was no block then we return false 
	return false; 

}


//if we can win then we place the winner
void placewinner(){

	//for the whole board if the spot is empty we take it
	for(int i=0; i<9;i ++){
	
		if(nums[i]==-1){
			
			nums[i]= 0;
			
	
		}else{
			continue;
		}
		//if that means we win then we break and take it
		if(winner()){
			
			break;
		}else{

		//other wise reset that spot and continue 
		nums[i]=-1;
		}
	}



}


void main(){


	//ask the player if they want to go first or second
	int firstORsecond= -1;

	//while its not a valid # we keep asking
	while(firstORsecond!=1 && firstORsecond!=2){
	
		printf("Go first or second (1/2): ");
		scanf("%d",&firstORsecond);

	
	}

	//if they want to go second
	if(firstORsecond==2){

		//this is the first turn 
        	int turn =1;                                                                                                                         
		int placeholder;

		// we ask them where they want to go second 
        	printf("enter which spot you would like to choose\n1|2|3\n-----\n4|5|6\n-----\n7|8|9\n \n");
		
		//we take top left corner 
		nums[0]= 0;

		//print the board
        	printboard();



		// if theres no winner and the board is not full or turn is not 5
		while(!winner() && turn!=5){
	
			//we ask them for their turn 
			printf("your turn: ");
			scanf("%d", &placeholder);
			printf("\n");

			//we subtract 1 to get the index not value 
			placeholder = placeholder-1;
	
			//while that spot is taken or null choose another 
			while(nums[placeholder]==0 || nums[placeholder] ==1){
			
				printf("\nthat spot is taken, choose another: ");
				scanf("%d", &placeholder);
				printf("\n");
				placeholder = placeholder-1;

			}





			//set their spot and incriment the turn 
			nums[placeholder]=1;
			turn = turn +1;
		

			//if they placed and there is a winner then they win (redundant code because they cant win :) )
			if(winner()){
		
				printf("you win! \n");
				break;
			}








			//if we can win then win
			placewinner();

			//then we place winner and print board
			if(winner()){
				printboard();
				printf("you lose \n");
				break;

			// otherwise if we cant win and have to block then block
			}else if(placeblock()){
			
				printboard();
		

			//if its round two then we can place our strategic move 
			}else if (turn==2){
		

				placemove(placeholder);
				printboard();


			//otherwise if its round 3 and they didnt go middle we go middle
			}else if (turn==3&& nums[4]==-1){
				nums[4] =0 ;
				printboard();
			
			//otherwise place first open spot 
			}else{
				
		 		placerandom();
				printboard();
			}
		
		}


		//if its the last turn and no winner then its a draw 
		if(turn == 5 && !winner()){

			printf("draw\n");
      

		}

	//if they want to go first then run this code
	}else{


		//turn is 0 ask what spot they want and print board 
		int turn = 0;
		printf("enter which spot you would like to choose\n1|2|3\n-----\n4|5|6\n-----\n7|8|9\n \n");
                printboard();


		//if theres no winner and the turn is not 5
		while(!winner()&& turn!=5){
		

			// ask their turn
			int secondholder;
			printf("your turn: ");
			scanf("%d",&secondholder);
			printf("\n");
			secondholder=secondholder-1;
			
			
			//if its not a valid turn ask again 
                        while(nums[secondholder]==0 || nums[secondholder] ==1){

                                printf("\nthat spot is taken, choose another: ");
                                scanf("%d", &secondholder);
				printf("\n");
                                secondholder = secondholder-1;

                        }	

			//set their spot to one and increment turn
			nums[secondholder]=1;
			turn =turn +1;

			//if its the last turn then break 
			if(turn == 5){
				break;
			}


			//if we can win then win 
			placewinner();

			//print winner if there is one 
			if(winner()){
				printboard();
				printf("you lose\n");
				break;
			
			// if its the first turn then we place our initial defense based on their move (secondholder)
			}else if (turn==1){
				
				placedefense(secondholder);
				printboard();

			//otherwise if we can block then bloack 
			}else if(placeblock()){
				
				printboard();


			// if its my second turn and they didnt go in one of the center spots and they went center and 
			// theres no block
			}else if(turn == 2 && checkcenters() && nums[4]==1){

				//then we go index 2 or top right corner 
			        nums[2]=0;
				printboard();

			// if its second turn, they didnt go in middle or any centers, then computer goes in 1 index 
			}else if(turn == 2 &&checkcenters() && nums[4]==0){
				nums[1]=0;
				printboard();
			
			//if its the second turn and nobody went in a corner spot, then we go in either 8 or 2 
			//depending on if the 1 spot is taken or not
			}else if(turn == 2 && !checkcenters() && checkcorners()){
			
				if(nums[1]== -1){
					nums[8]=0;
					printboard();
				}else{
					nums[2]= 0;
					printboard();  
				}
							
			// else if its turn two and they went a center and a corner 
			}else if(turn == 2 && !checkcenters() && !checkcorners()){
				
				//were starting at the first open center spot and going every two
				for(int i = 1; i<9; i+=2){

					//if they took that spot and its either one or five index
					//then we go the next center spot or i+2
					if(nums[i]== 1 && (i==1||i==5)){
						nums[i+2]=0;
						printboard();
					
					//otherwise if they took that spot and its a 3 or 7 index
					//then we go in the previous center spot
					}else if(nums[i]==1&&(i==3||i==7)){
						nums[i-2]=0;
						printboard();
					
					
					}

				}
			
			
			}else{
			
				//otherwise we place a random spot 
				placerandom();
				printboard();
			
			}
			
		
		
		}

		//if its turn 5 and no winner then print board and draw
		if(turn==5 && !winner()){
		
			printboard();
			printf("draw\n");
		
		}
		
		
	

       }

}                                                     

//good luck 
