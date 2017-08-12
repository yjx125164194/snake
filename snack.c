#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include"game.h"

#define WIDE 	20
#define LENGTH	30

#define SPEED 			500*1000
#define SNAKE_INIT_LENGTH	4

enum Direction
{
	up,
	down,
	right,
	left
};

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
			(*(fp + ((lfp + i)->y)))[(lfp + i)->x].content = snake_head;
		}
		else if(i == snake_length - 1)
		{
			(*(fp+((lfp + i)->y)))[(lfp + i)->x].content = snake_tail;
		}
		else
		{
			(*(fp+((lfp + i)->y)))[(lfp + i)->x].content = snake_body;
		}
		(*(fp + ((lfp + i)->y)))[(lfp + i)->x].status = true;
	}
}
void generate_ball(Location_type *ball_location)
{
	ball_location->x = rand()%LENGTH;
	ball_location->y = rand()%WIDE;
}
int shift_snake(Block_type (*fp)[LENGTH],Location_type *lfp,enum Direction Dir)
{
	Location_type tmp_head;
	Location_type tmp_tail;
	static Location_type ball_location;
	int i;
	static _Bool get_ball = false;
	static _Bool set_ball = false;

	if(!set_ball)
	{
		do
		{
			generate_ball(&ball_location);
		}	
		while((*(fp + (ball_location.y)))[ball_location.x].content != empty);
		(*(fp + (ball_location.y)))[ball_location.x].content = ball;
		(*(fp + (ball_location.y)))[ball_location.x].status = false;
		set_ball = true;
		get_ball = false;
	}

	tmp_tail = *(lfp + snake_length - 1);
	tmp_head = *lfp;

	for(i = snake_length - 2;i >= 0;i--)
	{
		*(lfp + i + 1) = *(lfp + i);
	}	
	if(Dir == up)
	{
		lfp->x = tmp_head.x;
		lfp->y = tmp_head.y - 1;
	}	
	else if(Dir == down)
	{
		lfp->x = tmp_head.x;
		lfp->y = tmp_head.y + 1;
	}	
	else if(Dir == left)
	{
		lfp->x = tmp_head.x - 1;
		lfp->y = tmp_head.y;
	}	
	else if(Dir == right)
	{
		lfp->x = tmp_head.x + 1;
		lfp->y = tmp_head.y;
	}	
	if(lfp->x == ball_location.x && lfp->y == ball_location.y)
	{
		get_ball = true;
		set_ball = false;
		snake_length++;
	}
	if(!get_ball)
	{
		(*(fp + (tmp_tail.y)))[tmp_tail.x].content = empty;
		(*(fp + (tmp_tail.y)))[tmp_tail.x].status = false;
	}
	if((*(fp + (lfp->y)))[lfp->x].status)
	{
		return 1;
	}
	put_snake_into_block(fp,lfp);
	return 0;
}
void print_block(Block_type (*fp)[LENGTH])
{
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
	usleep(SPEED);
}

int main(int argc,char **argv)
{
	Block_type block[WIDE][LENGTH];
	Block_type (*pblock)[LENGTH];
	Location_type *snake;
	enum Direction direction = down;	

	snake = (Location_type *)malloc(sizeof(Location_type) * (WIDE-1) * (LENGTH-1));
	pblock = &block[0];

	srand((unsigned int)time(0));

	init_block(pblock);
	init_snake(snake);
	put_snake_into_block(pblock,snake);

	while(1)
	{
    		if(kbhit())
    		{
      			switch(sh_getch())
      			{
        			case '8':
          				if(direction == right || direction == left)
					{
						direction = up;
					}
          				break;
       				case '4':
          				if(direction == up || direction == down)
          				{
						direction = left;
					}
          				break;
        			case '6':
          				if(direction == up || direction == down)
          				{
						direction = right;
					}
          				break;
        			case '5':
          				if(direction == right || direction == left)
          				{
						direction = down;
					}
          				break;
        			case 'q':
					free(snake);
          				exit(0);
       				default:break;
     			 }			
   		}			
    		setbuf(stdin,NULL);
		if(shift_snake(pblock,snake,direction))
		{
			break;
		}
		print_block(pblock);
		
	}
	printf("you are dead!point is %d\n",snake_length - SNAKE_INIT_LENGTH);
	free(snake);
	return	0;
}
