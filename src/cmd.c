#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "variable.h"

#include "battle.h"
#include "file.h"
#include "utils.h"

#define CMD_THROW_STRONES 1
#define CMD_RUNNING 2
#define CMD_SWIMMING 3
#define CMD_READ_BOOKS 4
#define CMD_MENTAL_TRANING 5
#define CMD_BATTLE 6
#define CMD_SKILL_TRANING 7
#define CMD_STUDY 8
#define CMD_PVP 9
#define CMD_VACATION 10
#define CMD_SAVE_DATA 97
#define CMD_SHOW_STATUS 98
#define CMD_EXIT 99

/* 岩石投げ */
void cmd_throw_stones (struct parameter *, struct player_parameter *, struct tm *);
/* ランニング */
void cmd_running (struct parameter *, struct player_parameter *, struct tm *);
/* 水泳 */
void cmd_swimming (struct parameter *, struct player_parameter *, struct tm *);
/* 読書 */
void cmd_read_books (struct parameter *, struct player_parameter *, struct tm *);
/* 精神修養 */
void cmd_mental_traning (struct parameter *, struct player_parameter *, struct tm *);
/* 戦闘訓練 */
void cmd_battle (struct parameter *, struct player_parameter *, struct tm *);
/* 経絡秘孔の勉強 */
void cmd_study (struct parameter *, struct player_parameter *, struct tm *);
/* 休息 */
void cmd_vacation (struct parameter *, struct player_parameter *, struct tm *);
/* セーブ */
void cmd_save_data(struct parameter *, struct player_parameter *);
/* ステータスを見る */
void cmd_show_status(struct parameter *, struct player_parameter *);
/* コマンドエラー */
void cmd_error();

/* 敵 HP 回復 */
void energy_recover (struct parameter *data, int ratio);
/* 一日進める */
void increment_day (struct player_parameter *, struct tm *);
/* ファイルに状態をセーブ */
int save_data (struct parameter *, struct player_parameter *);
/* 現在の詳細なステータスを表示 */
void show_current_status (struct parameter *, struct player_parameter *);
/* 算出能力値を再計算・更新 */
void update_parameter (struct parameter *);

int execute_cmd(struct parameter *player, struct player_parameter *player2, struct tm *lst, int cmd)
{
    switch(cmd){
        case CMD_THROW_STRONES:
            cmd_throw_stones(player, player2, lst);
            return 1;
        case CMD_RUNNING:
            cmd_running(player, player2, lst);
            return 1;
        case CMD_SWIMMING:
            cmd_swimming(player, player2, lst);
            return 1;
        case CMD_READ_BOOKS:
            cmd_read_books(player, player2, lst);
            return 1;
        case CMD_MENTAL_TRANING:
            cmd_mental_traning(player, player2, lst);
            return 1;
        case CMD_BATTLE:
            cmd_battle(player, player2, lst);
            return 1;
        case CMD_STUDY:
            cmd_battle(player, player2, lst);
            return 1;
        case CMD_VACATION:
            cmd_vacation(player, player2, lst);
            return 1;
        case CMD_SAVE_DATA:
            cmd_save_data(player, player2);
            return 1;
        case CMD_SHOW_STATUS:
            cmd_show_status(player, player2);
            show_title();
            return 1;
        case CMD_EXIT:
            return 0;
        default:
            cmd_error();
            return 1;
    }
}

void cmd_throw_stones(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    for(i = 0; i < ((random_custom(GROW_MAX)) + 1 + (player->practical / 200)); i++) {
        player->power++;
    }
    if (i != 0) fprintf(stdout," 力が %d ポイント上がった。\n", i);
    if ((random_custom(100)) < 30) {
        player->health++;
        fprintf(stdout," 体力が 1 ポイント上がった。\n");
    }
    if ((random_custom(100)) < 80) {
        if (player->intelligence != 0) {
            player->intelligence--;
            fprintf(stdout," 知性が 1 ポイント下がった。\n");
        }
        if (player->sprit != 0) {
            player->sprit--;
            fprintf(stdout," 精神が 1 ポイント下がった。\n");
        }
    }
    hit_any_key();
    player->practical++;
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 4);
    show_title();
}

void cmd_running(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    for(i = 0; i < ((random_custom(GROW_MAX)) + 1 + (player->practical / 200)); i++) {
        player->speed++;
    }
    if (i != 0) fprintf(stdout," 敏捷が %d ポイント上がった。\n", i);
    if ((random_custom(100)) < 30) {
        player->health++;
        fprintf(stdout," 体力が 1 ポイント上がった。\n");
    }
    if ((random_custom(100)) < 80) {
        if (player->intelligence != 0) {
            player->intelligence--;
            fprintf(stdout," 知性が 1 ポイント下がった。\n");
        }
    }
    hit_any_key();
    player->practical++;
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 4);
    show_title();
}

void cmd_swimming(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    for(i = 0; i < ((random_custom(GROW_MAX)) + 1 + (player->practical / 200)); i++) {
        player->health++;
    }
    if (i != 0) fprintf(stdout," 体力が %d ポイント上がった。\n", i);
    if ((random_custom(100)) < 30) {
        player->power++;
        fprintf(stdout," 力が 1 ポイント上がった。\n");
    }
    if ((random_custom(100)) < 80) {
        if ( player->intelligence != 0 ){
            player->intelligence--;
            fprintf(stdout," 知性が 1 ポイント下がった。\n");
        }
    }
    hit_any_key();
    player->practical++;
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 4);
    show_title();
}

void cmd_read_books(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    for(i = 0; i < ((random_custom(GROW_MAX)) + 1 + (player->practical / 200)); i++) {
        player->intelligence++;
    }
    if (i != 0) fprintf(stdout," 知性が %d ポイント上がった。\n", i);
    if ((random_custom(100)) < 80) {
        if (player->power != 0) {
            player->power--;
            fprintf(stdout," 力が 1 ポイント下がった。\n");
        }
        if (player->speed != 0) {
            player->speed--;
            fprintf(stdout," 敏捷が 1 ポイント下がった。\n");
        }
        if (player->health != 0) {
            player->health--;
            fprintf(stdout," 体力が 1 ポイント下がった。\n");
        }
    }
    hit_any_key();
    if ((random_custom(100)) < 30) player->practical++;
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 4);
    show_title();
}

void cmd_mental_traning(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    for(i = 0; i < ((random_custom(GROW_MAX)) + 1 + (player->practical / 200)); i++) {
        player->sprit++;
    }
    if (i != 0) fprintf(stdout," 精神が %d ポイント上がった。\n", i);
    if ((random_custom(100)) < 80) {
        if (player->power != 0) {
            player->power--;
            fprintf(stdout," 力が 1 ポイント下がった。\n");
        }
        if (player->speed != 0) {
            player->speed--;
            fprintf(stdout," 敏捷が 1 ポイント下がった。\n");
        }
        if (player->health != 0) {
            player->health--;
            fprintf(stdout," 体力が 1 ポイント下がった。\n");
        }
    }
    hit_any_key();
    if ((random_custom(100)) < 30) player->practical++;
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 4);
    show_title();
}

void cmd_battle(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    struct parameter enemy;

    fprintf(stdout, "\n");
    if ( (random_custom(100)) < 70 ){
        fprintf(stdout, "別の継承者候補「よろしくお願いします！」\n");
        hit_any_key();
        make_enemy(player, &enemy, "別の継承者候補");
        battle(player, &enemy);
        update_parameter(player);
        increment_day(player2, lst);
    } else {
        fprintf(stdout, "今、訓練相手が居ないので訓練出来ません。\n");
        hit_any_key();
    }
    show_title();
}

void cmd_study(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    if ((random_custom(100)) < 5){
        player->critical_special++;
        fprintf(stdout," クリティカル率が少し上がった。\n");
        for (i = 0; i < ((random_custom(GROW_MAX)) * 2 + 1); i++) {
            player->practical++;
        }
        if (i != 0) {
            fprintf(stdout,"熟練度が少し上がった。\n");
        } else {
            player->practical++;
        }
    }
    if ((random_custom(100)) < 30) {
        if (player->power != 0) {
            player->power--;
            fprintf(stdout," 力が 1 ポイント下がった。\n");
        }
        if (player->speed != 0) {
            player->speed--;
            fprintf(stdout," 敏捷が 1 ポイント下がった。\n");
        }
        if (player->health != 0) {
            player->health--;
            fprintf(stdout," 体力が 1 ポイント下がった。\n");
        }
    }
    hit_any_key();
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 4);
    show_title();
}

void cmd_vacation(struct parameter *player, struct player_parameter *player2, struct tm *lst)
{
    int i;

    fprintf(stdout, "\n");
    fprintf(stdout, "一日ゆっくり休んだため、HP がたくさん回復した。\n");
    if ( (random_custom(100)) < 30 ){
        for(i = 0; i < ((random_custom(GROW_MAX)) + 1 + (player->practical / 200)); i++) {
            if ( player->power != 0 ) player->power--;
            if ( player->speed != 0 ) player->speed--;
            if ( player->health != 0 ) player->health--;
        }
        fprintf(stdout, "力、敏捷、体力が %d ポイント下がった。\n", i);
    }
    hit_any_key();
    update_parameter(player);
    increment_day(player2, lst);
    energy_recover(player, 1);
    show_title();
}

void cmd_save_data(struct parameter *player, struct player_parameter *player2)
{
    if ( (save_data(player, player2)) != -1 ){
        fprintf(stdout, "\n%sさんのプレイデータをセーブしました。", player->name);
    }
    hit_any_key();
    show_title();
}

void cmd_show_status(struct parameter *player, struct player_parameter *player2)
{
    show_title();
    show_current_status(player, player2);
    hit_any_key();
}

void cmd_error()
{
    fprintf(stdout, "\nそんな番号ないです。");
    hit_any_key();
    show_title();
}

void energy_recover(struct parameter *data, int ratio)
{
    if (ratio < 1) ratio = 1;
    data->energy = data->energy + (data->energy_max / ratio) + data->health;
    if (data->energy > data->energy_max) data->energy = data->energy_max;
}

void increment_day(struct player_parameter *data2, struct tm *lst)
{
    time_t real_time;

    data2->birthday_flg = 0;
    data2->cumulatived_time = data2->cumulatived_time + 86400;
    real_time = data2->cumulatived_time + data2->time_when_start;
    lst = localtime(&real_time);
}

int make_new_character(struct parameter *data, struct player_parameter *data2)
{
    int cnt = 0;
    char front[3] = "", behind[3] = "";
    char temp[BUFFER_SIZE] = "";
    FILE *fp;

    do {
        fprintf(stderr, "データファイルがないけど、どうしますか？\n");
        fprintf(stdout, "1. 新規作成する\t2. そんなハズない\n>> ");
        secure_fgets(temp, BUFFER_SIZE);
        switch (temp[0]){
            case '1':
                cnt++;
                break;
            case '2':
                fprintf(stderr, "\nそんなこと言われても困ります。\n\n");
                return(-1);
            default :
                fprintf(stderr, "\nちゃんと入力しないとダメです。\n\n");
                break;
        }
    } while ( cnt == 0 );

    cnt = 0;
    show_title();

    do {
        fprintf(stdout, "主人公の名前を入力してください。 >> ");
        secure_fgets(data->name, BUFFER_SIZE);
        if ((strcmp(data->name, "")) == 0){
            if (cnt < ZIHI - 1) {
                fprintf(stderr, "ちゃんと入力しないとダメです。\n\n");
            } else {
                fprintf(stderr, "決める気がないなら勝手に決めますよ。\n");
            }
            cnt++;
        }
    } while ((strcmp(data->name, "")) == 0 && cnt < ZIHI);
    if ((strcmp(data->name, "")) == 0) {
        strcpy(data->name, DEFAULT_NAME);
    }

    do {
        fprintf(stdout, "\n%sの年齢を「半角英数で」入力してください。 >> ", data->name);
        secure_fgets(temp, BUFFER_SIZE);
        if ((data2->age = atoi(temp)) == 0){
            fprintf(stderr, "ちゃんと入力しないとダメです。\n");
        } else if (data2->age >= 128 || data2->age <= 14) {
            fprintf(stderr, "15 歳以上、128 歳未満じゃないとダメです。\n");
        }
    } while (data2->age >= 128 || data2->age <= 14);

    temp[0] = '\x00';

    do {
        fprintf(stdout, "\n%sの誕生日を「月／日」の形式で「半角英数で」入力してください。\n例えば、1月16日なら 1/16 って感じです。 >> ", data->name);
        secure_fgets(temp, BUFFER_SIZE);
        strtok_custom(front, behind, temp, "/");
        data2->birthday_flg = 0;
        data2->birthday.month = atoi(front);
        data2->birthday.day = atoi(behind);
        if ((data2->birthday.month == 0) || (data2->birthday.day == 0)) {
            fprintf(stderr, "ちゃんと入力しないとダメです。\n");
        } else if (data2->birthday.month > 12 || data2->birthday.day > 31) {
            fprintf(stderr, "そんな組み合わせはダメです。\n");
        }
    } while (data2->birthday.month == 0 || data2->birthday.day == 0);

    do {
        fprintf(stdout, "\n%sの性別を「半角英数で」入力してください。\n男なら 1。女なら 0 です。 >> ", data->name);
        secure_fgets(temp, BUFFER_SIZE);
        if ((data2->sex = atoi(strncpy(temp, temp, 1))) == 0 || (strlen(temp)) == 0) {
            fprintf(stderr, "ちゃんと入力しないとダメです。\n");
        }
    } while (data2->sex > 2 || data2->sex < 0 || (strlen(temp)) == 0);

    data->power = 10;
    data->speed = 10;
    data->health = 10;
    data->intelligence = 10;
    data->sprit = 10;
    data->practical = 0;
    data->critical_special = 0;
    update_parameter(data);

    data->energy = data->energy_max;
    data->flg = 0;
    data2->boot_cnt = 0;
    data2->version = 0.0;

    data2->cumulatived_time = 0;
    data2->time_when_start = time(NULL);

    if ((fp = fopen(DATA_FILE, "wb")) == NULL) {
        fprintf(stderr, "\nエラー ： ファイルが作れないです。\n");
        return (-1);
    }

    if (fwrite (data, sizeof(struct parameter), 1, fp) != 1) {
        fprintf(stderr, "\nエラー ： ファイルに書き込めないです。\n");
        return (-1);
    }

    if (fwrite (data2, sizeof(struct player_parameter), 1, fp) != 1) {
        fprintf(stderr, "\nエラー ： ファイルに書き込めないです。\n");
        return (-1);
    }

    fclose (fp);

    fprintf(stdout, "\nプレイヤーデータの作成が完了しました。\n");
    hit_any_key();

    return 0;

}

void show_current_status(struct parameter *data, struct player_parameter *data2)
{
    char sex[7] = "";

    if (data2->sex == 0) {
        strcpy(sex, "女");
    } else if (data2->sex == 1) {
        strcpy(sex, "男");
    } else {
        strcpy(sex, "不詳");	
    }

    fprintf(stdout, "\tステータス\n\n");
    fprintf(stdout, "\t%s\t性別：%s\n\t年齢： %d 歳\t誕生日： %d 月 %d 日\n\n", data->name, sex, data2->age, data2->birthday.month, data2->birthday.day);
    fprintf(stdout, "\tHP ： %d / %d\n\n", data->energy, data->energy_max);
    fprintf(stdout, "\t 力 ： %d\t命中率： %d%%\n", data->power, data->hit);
    fprintf(stdout, "\t敏捷： %d\t回避率： %d%%\n", data->speed, data->agility);
    fprintf(stdout, "\t体力： %d\t攻撃力： %d 回 %d\n", data->health, data->numattack, data->attack);
    fprintf(stdout, "\t知性： %d\t防御力： %d 回 %d\n", data->intelligence, data->numdefence, data->defence);
    fprintf(stdout, "\t精神： %d\tクリティカル率： %d%%\n\n", data->sprit, data->critical);
    fprintf(stdout, "\t熟練度： %d\n", (data->practical / 20));
    fprintf(stdout, "\n");
}

void update_parameter(struct parameter *data)
{
    data->energy_max = ((data->power + data->speed + data->health + data->intelligence + data->sprit) / 5 * 12) + data->practical / 20;
    /* HP ＝（（力＋敏捷＋体力＋知性＋精神）÷５×１２）＋熟練度÷２０ */

    data->hit = 70 + data->practical / 18;							/* 命中率＝７０＋熟練度÷１８ */
    data->agility = 70 + (data->practical+data->speed) / 20;		/* 回避率＝７０＋（熟練度＋敏捷）÷２０ */
    data->attack = data->power;										/* 攻撃力＝力そのまま */
    data->numattack = (data->hit + data->speed) / 32;				/* 攻撃回数＝（敏捷＋命中率）÷３２ */
    data->defence = (data->speed + data->health) / 2;				/* 防御力＝（敏捷＋体力）÷２  */
    data->numdefence = (data->health + data->agility) / 32;			/* 防御回数＝（体力＋回避率）÷３２ */
    data->critical = (data->hit + data->agility) / 40 + (data->intelligence + data->sprit) / 40 + data->critical_special;
    /* クリティカル率＝（命中率＋回避率）÷４０＋（知力＋精神）÷４０＋クリティカル修正値 */
}
