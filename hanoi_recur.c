//RECURSIVE VERSION OF HANOI SOLVER

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RING_COUNT 24
//expected turns: 2 ^ RING_COUNT - 1

//CREATE STRUCTURE FOR RING
typedef struct ring_item{
	struct ring_item *down;
	int value;
} *ring, ring_item;

//CREAT STRUCTURE FOR POLE
typedef struct pole_item{
	ring top;
	int size;
} *pole, pole_item;

//CREATE GLOBAL THAT CAN BE USED BY RECUSIVE CALL
int TOTAL_MOVES = 0;

//DECLARATION FOR A MOVE FUNCTION
void move(int n, pole src, pole dest, pole aux);

//DECLARATION FOR A PRINTING FUNCTION
void printPole(pole p);

//DECLARATION FOR POLE INIT BASED ON RING_COUNT
ring init_pole(int r);


int main(void)
{
	pole pole1 = (pole)malloc(sizeof(pole_item));
	pole pole2 = (pole)malloc(sizeof(pole_item));
	pole pole3 = (pole)malloc(sizeof(pole_item));

	//set pole1 to point top to last made ring
	pole1->top = init_pole(RING_COUNT);

	//set size defaults for beginning
	pole1->size = RING_COUNT;
	pole2->size = 0;
	pole3->size = 0;

	//loop until the final pole has all rings on it
	int expected = pow(2, RING_COUNT) - 1;

	//print expected turns
	printf("Expected turns: %d\n\n", expected);

	//CALL MOVE(pole1, pole3, pole2) to start recursion
	move(RING_COUNT, pole1, pole3, pole2);

	//OUTPUT TURN COUNT
	printf("\nTotal turns: %d\n\n", TOTAL_MOVES);
	return 0;
}

//FUNCTION TO CREATE A STACK OF RINGS FROM RING_COUNT TO 1 TO HAVE POLE1 POINT TO
ring init_pole(int r)
{
	ring tmp, last = NULL;
	for(int i = r; i > 0; i--)
	{
		//loop through and create new rings from RING_COUNT to 1
		tmp = (ring)malloc(sizeof(ring_item));
		tmp->value = i;
		tmp->down = last;
		last = tmp;
	}

	return last;
}

//RECURSIVE FUNCTION TO MOVE N RINGS FROM SRC TO DEST USING AUX AS MIDDLE GROUND
void move(int n, pole src, pole dest, pole aux)
{
	if(n > 0)
	{
		//INCRIMENT THE TOTAL MOVES GLOBAL
		TOTAL_MOVES++;
		//NOW DO THE RECURSIVE CALLS

		//FIRST MOVE ALL ON TOP OF N TO THE AUX TO FREE N DISK
		move(n-1, src, aux, dest);

		//NOW MOVE NTH DISC TO DEST
		if(src->top != NULL)
		{
			//SWAP TOP OF SRC TO TOP OF DEST
			ring tmp = src->top;
			src->top = tmp->down;
			tmp->down = dest->top;
			dest->top = tmp;
		}

		//MOVE THE REMAINING DISKS TO THE DEST USING SRC AS THE AUX NOW
		move(n-1, aux, dest, src);
	}
}