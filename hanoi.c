#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RING_COUNT 24
//expected turns: 2 ^ RING_COUNT - 1

typedef struct ring_item{
	struct ring_item *down;
	int value;
} *ring, ring_item;

typedef struct pole_item{
	ring top;
	int size;
} *pole, pole_item;

//DECLARATION FOR A SWAP FUNCTION
void swap(pole pole1, pole pole2);

//DECLARATION FOR A SOLVED FUNCTION
int solved(pole pole3);

//DECLARATION FOR A PRINTING FUNCTION
void printPole(pole p);


int main(void)
{
	pole pole1 = (pole)malloc(sizeof(pole_item));
	pole pole2 = (pole)malloc(sizeof(pole_item));
	pole pole3 = (pole)malloc(sizeof(pole_item));

	ring tmp, last = NULL;
	for(int i = RING_COUNT; i > 0; i--)
	{
		//loop through and create new rings from RING_COUNT to 1
		tmp = (ring)malloc(sizeof(ring_item));
		tmp->value = i;
		tmp->down = last;
		last = tmp;
	}

	//set pole1 to point top to last made ring
	pole1->top = last;

	//set size defaults for beginning
	pole1->size = RING_COUNT;
	pole2->size = 0;
	pole3->size = 0;

	//loop until the final pole has all rings on it
	int turns = 0;
	int expected = pow(2, RING_COUNT) - 1;

	//print expected turns
	printf("Expected turns: %d\n\n", expected);

	while(!solved(pole3))
	{
		//DEBUGGING
		// printf("Pole 1: ");
		// printPole(pole1);
		// printf("\n\nPole 2: ");
		// printPole(pole2);
		// printf("\n\nPole 3: ");
		// printPole(pole3);
		//END DEBUGGING

		if(RING_COUNT % 2)
		{
			//ODD CASE
			
			//make the legal move between pegs A and C (in either direction)
			swap(pole1, pole3);
			turns++;
			
			//make the legal move between pegs A and B (in either direction)
			if(!solved(pole3))
			{
				swap(pole1, pole2);
				turns++;
			}
			
			//make the legal move between pegs B and C (in either direction)
			if(!solved(pole3))
			{
				swap(pole2, pole3);
				turns++;
			}
		}
		else
		{
			//EVEN CASE

			//make the legal move between pegs A and B (in either direction)
			swap(pole1, pole2);
			turns++;
			
			//make the legal move between pegs A and C (in either direction)
			if(!solved(pole3))
			{
				swap(pole1, pole3);
				turns++;
			}
			
			//make the legal move between pegs B and C (in either direction)
			if(!solved(pole3))
			{
				swap(pole2, pole3);
				turns++;
			}
		}

		//printf("\nCurrent size of pole three: %d\n", pole3->size);
	}

	//OUTPUT TURN COUNT
	printf("\nTotal turns: %d\n\n", turns);
	return 0;
}

int solved(pole pole3)
{
	return pole3->size == RING_COUNT;
}

void swap(pole pole1, pole pole2)
{
	ring tmp;
	//IF BOTH POLES ARE EMPTY
	if(pole1->top == NULL && pole2->top == NULL)
		return;

	//IF THERE IS NOTHING ON TOP OF THE FIRST POLE
	else if(pole1->top == NULL)
	{
		pole1->top = pole2->top;
		pole2->top = pole2->top->down;
		pole1->top->down = NULL;

		pole1->size++;
		pole2->size--;
	}

	//IF THERE IS NOTHING ON TOP OF THE SECOND POLE
	else if(pole2->top == NULL)
	{
		pole2->top = pole1->top;
		pole1->top = pole1->top->down;
		pole2->top->down = NULL;

		pole2->size++;
		pole1->size--;
	}

	//IF POLE1 HAS A LARGER RING ON TOP
	else if(pole1->top->value > pole2->top->value)
	{
		tmp = pole1->top;
		pole1->top = pole2->top;
		pole2->top = pole2->top->down;
		pole1->top->down = tmp;

		pole1->size++;
		pole2->size--;
	}

	//IF POLE2 HAS A LARGER RING ON TOP
	else if(pole2->top->value > pole1->top->value)
	{
		tmp = pole2->top;
		pole2->top = pole1->top;
		pole1->top = pole1->top->down;
		pole2->top->down = tmp;

		pole2->size++;
		pole1->size--;
	}

	return;
}

void printPole(pole p)
{
	ring r = p->top;
	while(r != NULL)
	{
		printf("%d - ", r->value);
		r = r->down;
	}

	return;
}