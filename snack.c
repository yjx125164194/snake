#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include"game.h"

#define WIDE 	20
#define LENGTH	30

#define SPEED 			500*1000
#define SNAKE_INIT_LENGTH	4

int snake_length = SNAKE_INIT_LENGTH;

void init_block(Block_type (*fp)[LENGTH])
{
	int i,j;
	
	for(i = 0;i < WIDE;i++)
	{
		for(j = 0;j < LENGTH;j++)
		{			
			if(i == WIDE - 1 || j == LENGTH - 1 || i == 0 || j == 0)
			{
				(*(fp+i))[j].content = wall;
				(*(fp+i))[j].status = true;
			}
			else
			{	
				(*(fp+i))[j].content = empty;
				(*(fp+i))[j].status = false;
			}
		}
	}
}
void init_snake(Location_type *fp)
{
	int i;
	for(i = 0;i < SNAKE_INIT_LENGTH;i++)
	{
		(fp+i)->x = (LENGTH/2);
		(fp+i)->y = (WIDE/2) - i;
	}
}
void put_snake_into_block(Block_type(*fp)[LENGTH],Location_type *lfp)
{
	int i;
	for(i = 0;i < snake_length;i++)
	{	
		if(!i)
		{
			(*(fp+((lfp+i)->y)))[(lfp+i)->x].content = snake_head;
		}
		else if(i == snake_length - 1)
		{
			(*(fp+((lfp+i)->y)))[(lfp+i)->x].content = snake_tail;
		}
		else
		{
			(*(fp+((lfp+i)->y)))[(lfp+i)->x].content = snake_body;
		}
	}
}
void print_block(Block_type (*fp)[LENGTH])
{
	usleep(SPEED);
	system("clear");

	int i,j;
	for(i = 0;i < WIDE;i++)
	{
		for(j = 0;j < LENGTH;j++)
		{
			switch((*(fp+i))[j].content)
			{
				case empty:
					printf(" ");
					break;
				case wall:
					printf("@");
					break;
				case snake_head:
					printf("Q");
					break;
				case snake_body:
					printf("X");
					break;
				case snake_tail:
					printf("x");
					break;
				case ball:
					printf("O");
					break;
				default:break;
			}
		}
		printf("\n");
	}
}

int main(int argc,char **argv)
{
	Block_type block[WIDE][LENGTH];
	Block_type (*pblock)[LENGTH];
	Location_type *snake;
	
	snake = (Location_type *)malloc(sizeof(Location_type) * (WIDE-1) * (LENGTH-1));
	pblock = &block[0];

	srand((unsigned int)time(0));

	init_block(pblock);
	init_snake(snake);
	put_snake_into_block(pblock,snake);

	while(1)
	{
		print_block(block);
	}
	
	free(snake);
	return	0;
}
