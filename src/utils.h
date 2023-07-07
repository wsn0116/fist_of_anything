/* 乱数発生器 */
int random_custom(int max);
/* セキュアな fgets */
char *secure_fgets(char *str, int i);
/* 使いやすい strtok */
int strtok_custom(char *front, char *behind, char *str, char *sep);

/* デバッグ表示 */
void show_debug_status(struct parameter *, struct player_parameter *);
/* 画面を消去し、タイトルを表示 */
void show_title(void);
/* 何かキーが押されるのを待つ */
void hit_any_key(void);
