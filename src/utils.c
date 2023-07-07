#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"

char *drop(char *p, char *str, char *target);

char *drop(char *dst, char *str, char *sep)
{
	int i = 0;
	char *res = (char *)malloc(STR_MAX_UTILS * sizeof(char));
	i = strlen(str);
	if(strstr(str, sep) != NULL){
		i = strlen(str) - strlen(strstr(str, sep));
	}
	strncpy(res, str, i);
	res[i] = '\0';
	if(dst != NULL){
		strcpy(dst, res);
	}
	return res;
}

void hit_any_key()
{
    fprintf(stdout, "\n\n\t\t\t- Press Enter key -\n");
    getchar();
}

int random_custom(int max)
{
	switch(max){
		case 0:
			return 0;
		default:
			return rand() % max;
	}
}

void show_debug_status(struct parameter *player, struct player_parameter *player2)
{
    fprintf(stdout, "\t\t\t\t-DEBUG MODE-\t\t\t\t%ld\n", player2->boot_cnt);
    fprintf(stdout, "\tPOW:%d SPD:%d HEL:%d INT:%d SPR:%d PRC:%d\n",player->power, player->speed, player->health, player->intelligence, player->sprit, (player->practical / 20));
    fprintf(stdout, "\tHIT:%d%% AGL:%d%% ATK:%dtimes %d DEF:%dtimes %d CRT:%d%%\n\n",player->hit, player->agility, player->numattack, player->attack, player->numdefence, player->defence, player->critical);
}

void show_title()
{
	int ret;
    ret = system("clear");
    fprintf(stdout, TITLE);
}

char *secure_fgets(char *dst, int i)
{
	int len;
	char buff[STR_MAX_UTILS];
	char *ret;
	ret = fgets(buff, STR_MAX_UTILS, stdin);
	len = strcspn(buff, "\r\n");
	if(len < i){
		i = len;
	}
	strncpy(dst, buff, i);
	dst[i] = '\0';
	return dst;
}

int strtok_custom(char *front, char *behind, char *str, char *sep)
{
	char *buff = (char *)malloc(STR_MAX_UTILS * sizeof(char));

	if(strstr(str, sep) == NULL){
		strcpy(buff, str);
		strcpy(front, buff);
		strcpy(behind, "");
		return (-1);
	} else{
		strcpy(buff, strstr(str, sep));
		drop(front, str, sep);
		strcpy(behind, &buff[strlen(sep)]);
		return 0;
	}
}
