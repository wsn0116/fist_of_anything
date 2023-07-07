#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "variable.h"

#include "battle.h"
#include "cmd.h"
#include "event.h"
#include "file.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    int cmd = 0;
    const char *wday[] = { "日", "月", "火", "水", "木", "金", "土" };
    char buf[BUFFER_SIZE] = "";
    struct parameter player;
    struct player_parameter player2;
    struct tm *lst = (struct tm *)malloc(sizeof(struct tm)), *lst2 = (struct tm *)malloc(sizeof(struct tm));
    time_t real_time;

    show_title();
    if (init(&player, &player2) == -1) {
        return (-1);
    }

    real_time = player2.cumulatived_time + player2.time_when_start;
    lst = localtime(&real_time);

    show_title();

    do {
        cmd = 0;

        if ((argc > 1) && ((strcmp(argv[1], "--debug") == 0) || (strcmp(argv[1], "-d") == 0))) show_debug_status(&player, &player2);
        fprintf(stdout, "\t%dXX年（ %d年目） %d月 %d日 %s曜日\n\n", ((lst->tm_year + 1900) / 100), (int)(player2.cumulatived_time / 31536000 + 1), lst->tm_mon + 1, lst->tm_mday, wday[lst->tm_wday]);
        birthday(&player, &player2, lst);
        fprintf(stdout, "\t今日は、どんな修行をさせますか？\n\n");
        fprintf(stdout, "\t1. 岩石投げ  2. ランニング  3. 水泳  4. 読書  5. 精神修養\n");
        fprintf(stdout, "\t6. 戦闘訓練  X. 必殺技の試行錯誤  8. 経絡秘孔の勉強\n");
        fprintf(stdout, "\tX. 実地訓練  10. 休息\n\n");
        fprintf(stdout, "\t97. セーブ  98. ステータスを見る  99. このへんにしておく\n\n");
        fprintf(stdout, ">> ");

        secure_fgets(buf, BUFFER_SIZE);

        if (((cmd = atoi(buf)) == 0) || (strlen(buf) == 0)) {
            fprintf(stdout, "\nそんな番号ないです。");
            hit_any_key();
            show_title();
            continue;
        }

        if (execute_cmd(&player, &player2, lst, cmd) == 1) {
            continue;
        }
        break;
    } while (1);

    if ((save_data(&player, &player2)) != -1){
        fprintf(stdout, "\nプレイデータをセーブしました。\nお疲れさまでした。\n\n");
    }

    return 0;
}
