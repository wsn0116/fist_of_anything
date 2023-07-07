#include <time.h>

/* 敵 HP 回復 */
void energy_recover (struct parameter *data, int ratio);
/* コマンド実行 */
int execute_cmd (struct parameter *, struct player_parameter *, struct tm *lst, int cmd);
/* キャラメイク関数 */
int make_new_character (struct parameter *, struct player_parameter *);
/* 算出能力値を再計算・更新 */
void update_parameter (struct parameter *);
