#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include"game.h"

#define WIDE 	20
#define LENGTH	30

#define SPEED 	500*1000

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
				case snake:
					printf("X");
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

	pblock = &block[0];

	init_block(pblock);
	
	while(1)
	{
		print_block(block);
	}

	return	0;
}
