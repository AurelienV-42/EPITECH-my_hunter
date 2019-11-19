/*
** EPITECH PROJECT, 2017
** Aurélien Vandaële <aurelien.vandaele@epitech.eu>
** File description:
** my_hunter
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "my.h"

void my_put_help(void)
{
	my_putstr("This game is a reproduction of my_hunter game ");
	my_putstr("which was a game on the NES ");
	my_putstr("but with some new features like the background");
	my_putstr(" or the spaceship\n");
	my_putstr("To win you should kill the spaceship !\n");
	my_putstr("Hit = 100 Points\n");
	my_putstr("Score <= 1000 points, you\'re bad\n");
	my_putstr("Score >= 1000 2500 <= , you\'re like all people\n");
	my_putstr("Score >= 2500, you\'re a god\n");
}

int my_hunter(void)
{
	sfVideoMode mode = {1280, 769, 4};
	sfRenderWindow* window;
	sfTexture* texture;
	sfTexture* duck;
	sfSprite* sprite;
	sfSprite* sprite_duck;
	sfEvent event;
	sfIntRect rect = {0, 0, 58, 110};
	sfClock *clock_duck = sfClock_create();
	sfTime time_duck;
	float sec_duck;
	sfVector2f pos_duck;
	int score = 0;
	int speed = 0;
	int end_game = 3;

	pos_duck.y = rand() % 700;
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (window == NULL)
		return 84;
	texture = sfTexture_createFromFile("space.png", NULL);
        duck = sfTexture_createFromFile("spritesheetspace.png", NULL);
	if (texture == NULL)
		return 84;
	sprite = sfSprite_create();
	sprite_duck = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setTexture(sprite_duck, duck, sfTrue);
	sfRenderWindow_setFramerateLimit(window, 60);
	while (sfRenderWindow_isOpen(window))
	{
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue || end_game <= 0)
				sfRenderWindow_close(window);
		}		
		if (sfMouse_isButtonPressed(sfMouseLeft) == 1)
			if (sfMouse_getPosition(sfMouseLeft).x >= pos_duck.x &&
			    sfMouse_getPosition(sfMouseLeft).x <= (pos_duck.x + 58) &&
			    sfMouse_getPosition(sfMouseLeft).y >= pos_duck.y &&
			    sfMouse_getPosition(sfMouseLeft).y <= (pos_duck.y + 110)) {
				pos_duck.y = rand()%700;
				pos_duck.x = 0;
				score += 100;
				my_putstr("Well Played ! Hit it again ! + 100 Points\n");
				speed += 3;
			}		
		time_duck = sfClock_getElapsedTime(clock_duck);
		sec_duck = time_duck.microseconds / 1000000.0;
		if (sec_duck > 0.1) {
			rect.left += 58;
			pos_duck.x += 20 + speed;
			if (pos_duck.x >= 1280) {
				end_game--;
				my_putstr("Oh sorry, you're bad\n");
				pos_duck.y = rand()%700;
				pos_duck.x = 0;
			}
			sfSprite_setPosition (sprite_duck, pos_duck);
			sfClock_restart(clock_duck);
		}
		if (rect.left == 58 * 7)
			rect.left = 0;
		sfRenderWindow_clear(window, sfBlack);
		sfSprite_setTextureRect(sprite_duck, rect);
		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfRenderWindow_drawSprite(window, sprite_duck, NULL);
		sfRenderWindow_display(window);
	}
	my_putstr("Your score is : ");
	my_putnbr(score);
	my_putchar('\n');
	if (score < 1000)
		my_putstr("You're so bad...\n");
	if (score >= 1000 && score <= 2500)
		my_putstr("Hmm... Not bad\n");
	if (score > 2500)
		my_putstr("Oh my god, I thank it wasn't possible...\n");
	sfClock_destroy(clock_duck);
	sfSprite_destroy(sprite);
	sfSprite_destroy(sprite_duck);
	sfTexture_destroy(texture);
	sfTexture_destroy(duck);
	sfRenderWindow_destroy(window);
	return (0);
}

int main(int ac, char **av)
{
	int i = 0;

	if (ac >= 2) {
		if (av[1][0] == '-' && av[1][1] == 'h') {
			my_put_help();
			return (0);
		}
		return (84);
	}
	i = my_hunter();
	return (i);
}
