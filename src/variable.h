#include <time.h>

#define BUFFER_SIZE 255
#define DATA_FILE "fist.dat"
#define DEFAULT_NAME "ケ○シロウ"
#define GROW_MAX 3
#define STR_MAX_UTILS 32768
#define TITLE "\n何かの拳\n\n\n"
#define ZIHI 3

struct date {
    int month, day;
};

struct parameter {
    int flg;
    char name[BUFFER_SIZE];
    int power, speed, health, intelligence, sprit, practical, critical_special;
    /*	基礎能力値：力(power)、敏捷(speed)、体力(health)、知性(intelligence)、精神(sprit)、熟練度(practical)、クリティカル修正値(critical_special) */
    int hit, agility, attack, numattack, defence, numdefence, critical;
    /*	算出能力値：命中率(hit)、回避率(agility)、攻撃力(atack)、攻撃回数(numattack)、防御力(defence)、防御回数(numdefence)、クリティカル率(critical) */
    int energy, energy_max;
};

struct player_parameter {
    int age, birthday_flg, sex;
    long boot_cnt;
    float version;
    time_t cumulatived_time, time_when_start;
    struct date birthday;
};
