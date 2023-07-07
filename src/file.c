#include <stdio.h>

#include "variable.h"
#include "cmd.h"

/* ファイルから状態をロード */
int load_data(struct parameter *, struct player_parameter *);

int init(struct parameter *player, struct player_parameter *player2)
{
    FILE *fp;

    if ((fp = fopen(DATA_FILE, "r")) == NULL) {
        if (make_new_character(player, player2) == -1) {
            return (-1);
        }
    } else {
        fclose(fp);
    }

    load_data(player, player2);
    player2->boot_cnt++;

    return 0;
}

int load_data(struct parameter *data, struct player_parameter *data2)
{
    FILE *fp;

    if ((fp = fopen(DATA_FILE, "rb")) == NULL) {
        fprintf(stderr, "\nエラー ： ファイルが開けなくてロード出来ません。\n");
        return (-1);
    }
    if (fread(data, sizeof(struct parameter), 1, fp) != 1) {
        fprintf(stderr, "\nエラー ： ファイルが読み込めなくてロード出来ません。\n");
        return (-1);
    }
    if (fread (data2, sizeof(struct player_parameter), 1, fp) != 1) {
        fprintf(stderr, "\nエラー ： ファイルが読み込めなくてロード出来ません。\n");
        return (-1);
    }
    fclose (fp);
    return 0;
}

int save_data(struct parameter *data, struct player_parameter *data2)
{
    FILE *fp;

    if ((fp = fopen(DATA_FILE, "wb")) == NULL) {
        fprintf(stderr, "\nエラー ： ファイルが開けなくてセーブ出来ません。\n");
        return (-1);
    }
    if (fwrite (data, sizeof(struct parameter), 1, fp) != 1) {
        fprintf(stderr, "\nエラー ： ファイルに書き込めなくてセーブ出来ません。\n");
        return (-1);
    }
    if (fwrite (data2, sizeof(struct player_parameter), 1, fp) != 1) {
        fprintf(stderr, "\nエラー ： ファイルに書き込めなくてセーブ出来ません。\n");
        return (-1);
    }
    fclose (fp);
    return 0;
}
