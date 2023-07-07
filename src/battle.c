#include <stdio.h>
#include <string.h>

#include "variable.h"

#include "cmd.h"
#include "utils.h"

#define CMD_ATTACK '1'
#define CMD_GUARD '2'
#define CMD_HEARING '3'
#define CMD_ESCAPE '4'

void battle_player_attack (struct parameter *player_data, struct parameter *enemy_data);
void battle_enemy_attack (struct parameter *player_data, struct parameter *enemy_data);
void battle_won (struct parameter *player_data, int turn);
void battle_lost (struct parameter *player_data);

void make_enemy(struct parameter *player_data, struct parameter *enemy_data, char *enemy_name)
{
    int i = 0;

    strcpy(enemy_data->name, enemy_name);

    enemy_data->power = player_data->power * (random_custom(12) + 1) / 10;
    enemy_data->speed = player_data->speed * (random_custom(12) + 1) / 10;
    enemy_data->health = player_data->health * (random_custom(12) + 1) / 10;
    enemy_data->intelligence = player_data->intelligence * (random_custom(12) + 1) / 10;
    enemy_data->sprit = player_data->sprit * (random_custom(12) + 1) / 10;
    enemy_data->practical = player_data->practical * (random_custom(12) + 1) / 10;

    for(i = 0; i < ((random_custom(GROW_MAX)) + 1); i++) {
        if ((random_custom(100)) == 81) enemy_data->critical_special++;
    }

    update_parameter(enemy_data);

    if (enemy_data->critical < 0) enemy_data->critical = 0;
    enemy_data->energy = enemy_data->energy_max;
}

int battle(struct parameter *player_data, struct parameter *enemy_data)
{
    int turn_cnt = 1;
    do {
        if ((random_custom(player_data->speed)) >= (random_custom(enemy_data->speed))) {
            battle_player_attack(player_data, enemy_data);
            if (enemy_data->energy <= 0) {
                battle_won(player_data, turn_cnt);
                return 0;
            }
            if (player_data->flg == 256) {
                player_data->flg = 0;
                return (-1);
            }
            battle_enemy_attack(player_data, enemy_data);
            if (player_data->energy <= 0) {
                battle_lost(player_data);
                return 0;
            }
        } else {
            fprintf(stdout, "%sに先手をとられた！\n", enemy_data->name);
            hit_any_key();
            battle_enemy_attack(player_data, enemy_data);
            if (player_data->energy <= 0) {
                battle_lost(player_data);
                return 0;
            }
            battle_player_attack(player_data, enemy_data);
            if (enemy_data->energy <= 0) {
                battle_won(player_data, turn_cnt);
                return 0;
            }
            if (player_data->flg == 256) {
                player_data->flg = 0;
                return (-1);
            }
        }
        turn_cnt++;
    } while ((player_data->energy > 0) || (enemy_data->energy > 0));
    return 0;
}

void battle_player_attack(struct parameter *player_data, struct parameter *enemy_data)
{
    int hit_times = 0, damage = 0, num_attack = 0, num_defence = 0, i = 0;
    char temp[BUFFER_SIZE] = "";

    if (player_data->flg == 300) {
        player_data->defence = player_data->defence - (player_data->defence / 3);
    } else if (player_data->flg == 4649) {
        player_data->defence = player_data->defence * 4;
    }
    player_data->flg = 0;

    do {
        show_title();
        fprintf(stdout, "\n");
        fprintf(stdout, "%s - HP : %d / %d\n\n", player_data->name, player_data->energy, player_data->energy_max);
        fprintf(stdout, "行動を選択してください。\n");
        fprintf(stdout, "1. 攻撃  2. 防御  3. 瞑想  4. 戦略的撤退\n\n");
        fprintf(stdout, ">> ");
        secure_fgets(temp, BUFFER_SIZE);
        fprintf(stdout, "\n");

        switch (temp[0]) {
            case CMD_ATTACK:
                if ((random_custom(100)) > player_data->critical) {
                    if ((random_custom(player_data->hit)) >= (random_custom(enemy_data->agility))) {
                        num_attack = random_custom(player_data->numattack - 1) + 1;
                        num_defence = random_custom(enemy_data->numdefence);
                        if (num_attack < num_defence) num_defence = num_attack;
                        fprintf(stdout, "%sの %d 回攻撃！", player_data->name, num_attack);
                        if (num_defence <= 0){
                            fprintf(stdout, "%sは防御出来なかった！\n", enemy_data->name);
                        } else {
                             fprintf(stdout, "%sが %d 回防御！\n", enemy_data->name, num_defence);
                        }
                        hit_times = num_attack - num_defence;
                        if (hit_times > 0){
                            fprintf(stdout, "%d 回ヒット ", hit_times);
                        }
                        damage = (player_data->attack / 2 + (random_custom(player_data->attack / 2))) * 5 * hit_times;
                        if (damage > 0){
                            fprintf(stdout, "%d ダメージ！！\n", damage);
                            hit_any_key();
                        } else {
                            fprintf(stdout, "ダメージは与えられなかった。\n");
                            hit_any_key();
                            damage = 0;
                        }
                    } else {
                        fprintf(stdout, "回避されてしまった！ ダメージが与えられない！！\n");
                        hit_any_key();
                    }
                } else {
                    damage = player_data->numattack * 5 * player_data->attack + (random_custom(player_data->attack));
                    fprintf(stdout, "クリティカル！\n");
                    fprintf(stdout, "%d 回ヒット %d ダメージ！！\n", player_data->numattack, damage);
                    hit_any_key();
                }
                enemy_data->energy = enemy_data->energy - damage;
                break;
            case CMD_GUARD:
                fprintf(stdout, "%sは身を守っている。\n", player_data->name);
                hit_any_key();
                player_data->defence = player_data->defence + (player_data->defence / 2);
                player_data->flg = 300;
                break;
            case CMD_HEARING:
                fprintf(stdout, "%sは静かに瞑想をした。\n", player_data->name);
                hit_any_key();
                energy_recover(player_data, 8);
                break;
            case CMD_ESCAPE:
                if ( (random_custom(player_data->speed)) >= (random_custom(enemy_data->speed)) ) {
                    fprintf(stdout, "%sは戦略的撤退に成功した。\n", player_data->name);
                    hit_any_key();
                    player_data->flg = 256;
                } else {
                    fprintf(stdout, "%sは戦略的撤退に失敗した。\n", player_data->name);
                    player_data->defence = player_data->defence / 4;
                    player_data->flg = 4649;
                    hit_any_key();
                }
                break;
            default:
                continue;
        }
        break;
    } while (1);
}

void battle_enemy_attack(struct parameter *player_data, struct parameter *enemy_data)
{
    int hit_times = 0, damage = 0, num_attack = 0, num_defence = 0, i = 0;
    show_title();
    fprintf(stdout, "%sの攻撃！\n\n", enemy_data->name);
    if ((random_custom(100)) > enemy_data->critical) {
        if ((random_custom(enemy_data->hit)) >= (random_custom(player_data->agility))) {
            num_attack = random_custom(enemy_data->numattack - 1) + 1;
            num_defence = random_custom(player_data->numdefence);
            if (num_attack < num_defence) num_defence = num_attack;
            fprintf(stdout, "%sの %d 回攻撃！", enemy_data->name, num_attack);
            if (num_defence <= 0) {
                fprintf(stdout, "%sは防御出来なかった！\n", player_data->name);
            } else {
                 fprintf(stdout, "%sが %d 回防御！\n", player_data->name, num_defence);
            }
            hit_times = num_attack - num_defence;
            if (hit_times > 0) {
                fprintf(stdout, "%d 回ヒット ", hit_times);
            }
            damage = (enemy_data->attack / 2 + (random_custom(enemy_data->attack / 2))) * 5 * hit_times;
            if (damage > 0) {
                fprintf(stdout, "%d ダメージ！！\n", damage);
                hit_any_key();
            } else {
                fprintf(stdout, "ダメージには至らなかった。\n");
                hit_any_key();
                damage = 0;
            }
        } else {
            fprintf(stdout, "攻撃を回避した。\n");
            hit_any_key();
        }
    } else {
        damage = enemy_data->numattack * 2 * enemy_data->attack + (random_custom(enemy_data->attack));
        fprintf(stdout, "クリティカル！\n");
        fprintf(stdout, "%d 回ヒット %d ダメージ！！\n", enemy_data->numattack, damage);
        hit_any_key();
    }
    player_data->energy = player_data->energy - damage;
}

void battle_won(struct parameter *player_data, int turn) 
{
    int i = 0;

    show_title();
    fprintf(stdout, "\n勝利！！\n\n");
    fprintf(stdout, "かかったターン数： %d ターン\n\n", turn);
    for(i=0; i<((random_custom(GROW_MAX))*2+1); i++){
        player_data->practical++;
    }
    if ( i != 0 ) fprintf(stdout,"熟練度が少し上がった。\n");
    hit_any_key();
}

void battle_lost(struct parameter *player_data)
{
    show_title();
    fprintf(stdout, "\n敗北・・・。\n");
    hit_any_key();
    player_data->energy = 1;
}
