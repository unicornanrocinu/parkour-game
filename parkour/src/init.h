#ifndef _HEADERNAME_H
#define _HEADERNAME_H
#include "background_operation.h"
#endif

void init();
void game_init();
void start_plot();
void start_interface();
void setting_interface();
void input_key();
void date_init();

void init()
{
    setlocale(LC_ALL, "zh-CN");
    HideCursor();
    SetConsoleTitle("Parkour");
    srand(time(0));
    start_plot();
    start_interface();
    best_score = 0;
} // 总初始化

void game_init()
{
    system("cls");
    score = 0;
    position_x = 1;
    game_time = 0;
    state = 0;
    game_time = 0;
    fireball = false;
    start_time = INT_MAX;
    alive = true;
    magnet = false;
    memset(line_l, '|', sizeof(line_l));
    memset(line_r, '|', sizeof(line_r));
    corner_frequency = 100;
    is_corner = false;
    corner_start = false;
    corner_stop = false;
    corner_times = 0;
    memset(corner, 0, sizeof(corner));
    memset(store_line, ' ', sizeof(store_line) - 1);
    date_init();
    for (int i = 0; i < map_r; i++)
        for (int j = 0; j < map_c; j++)
            map[i][j] = ' '; // 数据初始化
    gotoxy(best_score_x, best_score_y);
    printf("BEST_SCORE:%d", best_score);
    gotoxy(best_score_x, best_score_y + 1);
    wprintf(L"Difficulty:%ls", difficulties[difficulty]);
    gotoxy(best_score_x, best_score_y + 2);
    wprintf(L"Character:%ls", character_name[character]);
    gotoxy(score_x, score_y);
    printf("SCORE:");
    gotoxy(score_x, score_y + 1);
    printf("STATE:");
    gotoxy(score_x, score_y + 2);
    printf("Fireball:"); // 游戏状态栏打印
    game_stop();
} // 游戏初始化

void start_plot()
{
    system("cls");
    gotoxy(title_x - 25, title_y);
    wprintf(L"CPL期末项目的DDL就要到了,绩点0.0的开拓者又双叒叕没有按时完成作业");
    gotoxy(title_x - 25, title_y + 1);
    wprintf(L"呢喃和平公司派出了托帕总监向开拓者催讨作业.可是,身经百战的开拓者又怎么会束手就擒...");
    gotoxy(title_x - 25, title_y + 2);
    wprintf(L"跳跃、下蹲、奔跑,开拓者们将发挥出自己的极限潜力,用实际行动证明\"规则就是用来打破的\"");
    gotoxy(title_x - 25, title_y + 3);
    wprintf(L"当然,你也可以化身托帕总监,与账账一起,将逍遥法外的开拓者捉拿归案");
    gotoxy(title_x - 25, title_y + 4);
    wprintf(L"准备好了吗？穿越这个充满挑战和惊喜的跑酷世界，向着胜利的彼岸冲刺吧！");
    gotoxy(title_x - 25, title_y + 5);
    wprintf(L"                                                               敲击SPACE进入游戏");
    char input;
    while ((input = getch()) != ' ')
        ;
}

void setting_interface()
{
    system("cls");
    char input;
    gotoxy(title_x + 3, title_y - 3);
    wprintf(L"设置");
    gotoxy(title_x, title_y - 1);
    wprintf(L"人物选择：");
    gotoxy(title_x, title_y);
    wprintf(L"1.银河棒球侠");
    gotoxy(title_x, title_y + 1);
    wprintf(L"2.托帕&账账");
    gotoxy(title_x, title_y + 3);
    wprintf(L"难度选择：");
    gotoxy(title_x, title_y + 4);
    wprintf(L"3.容易");
    gotoxy(title_x, title_y + 5);
    wprintf(L"4.标准");
    gotoxy(title_x, title_y + 6);
    wprintf(L"5.困难");
    gotoxy(title_x, title_y + 8);
    wprintf(L"你当前的人物为%ls,当前难度为%ls", character_name[character], difficulties[difficulty]);
    gotoxy(title_x, title_y + 9);
    wprintf(L"敲击空格进入游戏");
    do
    {
        input = getch();
        if (input > '0' && input < '3')
            character = input - '1';
        if (input > '2' && input < '6')
            difficulty = input - '3';
        gotoxy(title_x, title_y + 8);
        wprintf(L"你当前的人物为%ls,当前难度为%ls", character_name[character], difficulties[difficulty]);
    } while (input != ' ');
}

void start_interface()
{
    system("cls");
    gotoxy(title_x, title_y);
    wprintf(L"敲击空格键开始游戏");
    gotoxy(title_x, title_y + 1);
    wprintf(L"敲击 S 键进入设置界面");
    gotoxy(title_x, title_y + 2);
    wprintf(L"敲击 R 键回顾剧情");
    input_key();
} // 初始选择界面

void input_key()
{
    char input;
    do
    {
        input = getch();
    } while (input != ' ' && input != 'S' && input != 's' && input != 'r' && input != 'R');
    if (input == ' ')
        return;
    if (input == 's' || input == 'S')
        setting_interface();
    if (input == 'r' || input == 'R')
    {
        start_plot();
        start_interface();
    }
} // 初始选择界面的按键控制

void date_init()
{
    speed = list[difficulty].speed_set;
    barrier_frequency = list[difficulty].barrier_frequency_set;
    U_frequency = list[difficulty].U_frequency_set;
    D_frequency = list[difficulty].D_frequency_set;
    X_frequency = list[difficulty].X_frequency_set;
    score_frequency = list[difficulty].score_frequency_set;
    shield_frequency = list[difficulty].shield_frequency_set;
    fireball_frequency = list[difficulty].fireball_frequency_set;
    magnet_frequency = list[difficulty].magnet_frequency_set;
    fireball_store = list[difficulty].fireball_store_set;
} // 难度数据初始化
