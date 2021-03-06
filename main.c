#include <os.h>
#include <stdlib.h>
#include <time.h>
#include "n2DLib.h"
#include "pieces.h"
#include "sprites.h"

#define GRID_W 10
#define GRID_H 23
#define GRID_Y 10
#define GRID_X 105
#define GRID_SPAWN 3

#define TIMER 0x900D0000
unsigned timer_ctl_bkp[2], timer_load_bkp[2];


//#define DEBUG


void draw_tilemap(const unsigned map[])
{
	unsigned x, y;
	unsigned tile;

	for (y = GRID_SPAWN; y < GRID_H; y++)
	for (x = 0; x < GRID_W; x++)
	{
		tile = map[y * GRID_W + x];
		drawSprite(color[tile],  x * 11 ,(y - GRID_SPAWN) * 11 );
	}
}

void piece_draw(unsigned piece, unsigned orientation, unsigned x, unsigned y)
{
	unsigned i, j;
	unsigned tile;

	for (j = 0; j < 4; j++)
	for (i = 0; i < 4; i++)
	{
		tile = pieces[piece][orientation][i + j * 4];
		if (tile > 0 && (y + j) >= GRID_SPAWN)
			drawSprite(color[tile],  (x + i) * 11, (y + j - GRID_SPAWN) * 11  );
	}	
}

unsigned piece_merge(unsigned piece, unsigned orientation, unsigned x, unsigned y, unsigned map[])
{
	unsigned i, j;
	unsigned tile;

	for (j = 3; j < 4; j--)
	for (i = 0; i < 4; i++)
	{
		tile = pieces[piece][orientation][i + j * 4];
		if (tile > 0 && (x + i) < GRID_W && (y + j) < GRID_H)
		{
			map[(x + i) + (y + j) * GRID_W] = tile;
			if ((y + j) < 2)
				return 1;
		}
#ifdef DEBUG
		else if (tile > 0)
		{
			printf("Invalid write to map : %u, %u, %u, %u\n", tile, orientation, x + i, y + j);
		}
#endif
	}
	return 0;
}

unsigned piece_collide(unsigned piece, unsigned orientation, unsigned x, unsigned y, unsigned map[])
{
	unsigned i, j;
	unsigned tile;

	for (j = 0; j < 4; j++)
	for (i = 0; i < 4; i++)
	{
		tile = pieces[piece][orientation][i + j * 4];
		if (tile > 0)
		{
			if (map[(x + i) + (y + j) * GRID_W])
				return 1;

			if ((x + i) >= GRID_W || (y + j) >= GRID_H)
				return 1;
		}
	}
	return 0;
}

unsigned key_left()
{
	return isKeyPressed(KEY_NSPIRE_LEFT) || isKeyPressed(KEY_NSPIRE_4);
}

unsigned key_right()
{
	return isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_6);
}

unsigned key_up()
{
	return isKeyPressed(KEY_NSPIRE_UP) || isKeyPressed(KEY_NSPIRE_8);
}

unsigned key_down()
{
	return isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_5) || isKeyPressed(KEY_NSPIRE_2);
}


int bag_piece( int bag[7], int *bag_cnt )
{
	
	int i, z = 1;
	if(*bag_cnt == 0)
	{
		for(i = 0; i < 7; i++)
		 bag[i] = i;
		*bag_cnt = 7;
	}
	
	do
	{
		i = rand() % 7;
		if(bag[i] != -1)
		{
			bag[i] = -1;
			z = 0;
		} 
	} while(z) ;
	*bag_cnt = *bag_cnt - 1;
	return i;
}
	
void draw_debug(int s, int m)
{
	int txtx = 0, txty = 0;// text displaying ints
	txtx = 150;
	txty = 10;
	drawDecimal(&txtx, &txty, (s / 10) ,0,65335);
	txtx = 150;
	txty = 20;
	drawDecimal(&txtx, &txty, s, 0,65335);
	txtx = 150;
	txty = 30;
	drawDecimal(&txtx, &txty, m, 0, 65335);
}
int main(void)
{
	timer_init(0);//initialize timer #0
	timer_init(1);//initialize timer #1
//initialize ALL the things vvv


	srand(time(NULL)); // RNG seed
	unsigned i, j; // Loop indices, also can be used for free outside loops

	unsigned x = 3, y = 0; //set initial x and y values for piece

	int cleared_lines, turn_score, clearing_value;  //initialize scoring parameters
	int score = 0, multiplier = 10, current_level = 1; //same
	int pause = -1; //game is not paused on start

	int base_score = 2; //
	
	
	int bag[7]; //bag can hold 7 pieces
	int bag_cnt = 0; //bag is set to empty state at load

	unsigned cur_piece = bag_piece( bag, &bag_cnt ), rot = 0;  //initialize first piece. Must change this so it chooses from L/J

	unsigned speed = 16384, key_delay = 8192; //



	unsigned map[GRID_H * GRID_W];	
	for (i = 0; i < GRID_H * GRID_W; i++) map[i] = 0; // Map init. Might be able to replace this with a memset( ??
	

	initBuffering();
	clearBufferW();

	timer_load(1, speed);

	while (! isKeyPressed(KEY_NSPIRE_ESC))
	{
		draw_tilemap(map);
		
		//reset turn score to zero
		turn_score = 0;
		
		if (isKeyPressed(KEY_NSPIRE_VAR))
		{
			pause = pause*-1;
			if(pause == 1)
				i = timer_read(1);
			while(isKeyPressed(KEY_NSPIRE_VAR))
			if(pause == -1)
				timer_load(1,i);
		}
		if (pause == 1)
			continue;
		
		if (key_up() || key_right() || key_left() || key_down() || isKeyPressed(KEY_NSPIRE_PLUS))
		{
			if (timer_read(0) == 0)
			{
				if (key_up() && ! piece_collide(cur_piece, (rot + 1) % 4, x, y, map))
					rot = (rot + 1) % 4;

				if (key_right() && ! piece_collide(cur_piece, rot, x + 1, y, map))
					x++;

				if (key_left() && ! piece_collide(cur_piece, rot, x - 1, y, map))
					x--;

				if (key_down() && ! piece_collide(cur_piece, rot, x, y + 1, map))
				{
					timer_load(1, speed);
					y++;
				}

				if (isKeyPressed(KEY_NSPIRE_PLUS))
					cur_piece = bag_piece( bag, &bag_cnt);

				timer_load(0, key_delay);
				key_delay = 1024;
			}
		}
		else
		{
			key_delay = 8192;
			timer_load(0, 0);
		}

		piece_draw(cur_piece, rot, x, y);
		draw_debug(score, multiplier);
		//
		updateScreen();

		if (timer_read(1) == 0)
		{
			if (! piece_collide(cur_piece, rot, x, y + 1, map))
			{
				y++;
			}
			else
			{
				if (piece_merge(cur_piece, rot, x, y, map)) //Game over
				{
#ifdef DEBUG
					printf("THE GAME\n");
#endif
					deinitBuffering();
					timer_restore(0);
					timer_restore(1);
					return 0;
				}
				x = 3; y = 0;
				rot = 0;
				cur_piece = bag_piece( bag, &bag_cnt); //get a new piece from the bag
#ifdef DEBUG
				printf("Spawn : %u, %u\n", cur_piece, rot);
#endif

				cleared_lines = 0;  //set line counter to zero
				clearing_value = 0; //set clearing value to zero
				for (i = GRID_H - 1; i < GRID_H; i--) //loop over grid height
				{
					unsigned k = 0;
					for (j = 0; j < GRID_W; j++)  //loop over grid width
					{
						if (map[j + i * GRID_W] > 0)
							k++;
					}
					
					if (k == GRID_W)  //SCORE!!!!!1!!
					{
						cleared_lines++;
						clearing_value = clearing_value + cleared_lines;
						for (j = 0; j < GRID_W; j++)
							map[j + i * GRID_W] = 0;

						for (j = i; j > 0; j--)
						for (k = 0; k < GRID_W; k++)
							map[k + j * GRID_W] = map[k + (j - 1) * GRID_W];

						for (j = 0; j < GRID_W; j++)
							map[j] = 0;

						i++;
					}
				}
				turn_score = turn_score + (clearing_value * base_score);

				if(cleared_lines){ //check if combos are made, add moar scoar!
					base_score = base_score + (((current_level - 1)/3)+1);
					if(cleared_lines == 4) multiplier = multiplier + 2;
					//if(grid_clear) multiplier = multiplier + 5;  have not yet implemented the check for this
				}
				else
				{
					base_score = current_level * 2;
				}
				score = score + (multiplier * turn_score);

				
			}
			timer_load(1, speed);
		}
	}

	deinitBuffering();
	timer_restore(0);
	timer_restore(1);
	return 0;
}

