#include <stdio.h>
#include <time.h>

#include "variable.h"

#include "cmd.h"
#include "utils.h"

void birthday(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    if ((player2->birthday.month == lst->tm_mon + 1) && (player2->birthday.day == lst->tm_mday) && player2->birthday_flg == 0) {
        player2->birthday_flg++;
        player2->age++;
        fprintf(stdout, "\t%sさんは、%d歳の誕生日を迎えました。\n\n", player->name, player2->age);
        if (player2->age < 20) {
            for(i = 0; i < ((random_custom(GROW_MAX)) + 1); i++){
                player->power++;
                player->speed++;
                player->health++;
                player->intelligence++;
                player->sprit++;
            }
        } else if (player2->age >= 40) {
            for(i = 0; i < ((random_custom(GROW_MAX)) + 1); i++){
                player->power--;
                player->speed--;
                player->health--;
                player->intelligence--;
                player->sprit--;
            }
        } else if (player2->age >= 80){
            if ( (random_custom(100)) < (player2->age/2) ){
                /* @TODO: 老衰による死亡処理 */
            }
        }
    }
}
