#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <wchar.h>

#define not_barrier(x, y) (map[x][y] != 'U' && map[x][y] != 'D' && map[x][y] != 'X')
#define not_barrier_corner(x, y) (x >= 0 ? (corner[x][y] != 'U' && corner[x][y] != 'D' && corner[x][y] != 'X') : 1)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define SW(x, y)      \
    do                \
    {                 \
        int temp = x; \
        x = y;        \
        y = temp;     \
    } while (0)

#define map_x 50
#define map_y 8
#define map_r 7
#define map_c 3 // 地图的坐标及长度

#define corner_r 11
#define corner_c 3
#define corner_mid_r 4 // 路口的大小

int position_x;
#define postion_y 4 // 玩家坐标

#define score_x 60
#define score_y 7 // 右侧状态栏输出坐标

#define stop_x 50
#define stop_y 20 // 暂停信息输出坐标

#define best_score_x 20
#define best_score_y 6 // 左侧状态栏输出坐标

const char *states[3] = {"running  ", "jumping  ", "crouching"};
const wchar_t *difficulties[3] = {L"容易", L"标准", L"困难"};
const wchar_t *character_name[2] = {L"银河棒球侠", L"托帕&账账"};
const char obstacle[8] = {'-', '-', '-', '-', '-', '-', '-'}; // 一些文字

char line_l[7];
char line_r[7]; // 左右侧围栏

char map[map_r][map_c + 1];
char corner[corner_r][corner_c + 1]; // 路口
char store_line[4];                  // 玩家所在行信息的副本

char ch; // 键盘输入的信息

int difficulty = 1; // 难度
int character = 0;  // 人物

unsigned int score;
unsigned int best_score; // 得分
unsigned int game_time;
unsigned int start_time;        // 起跳时间
unsigned int magnet_start_time; // 磁铁开始时间

bool alive;
int state;
bool shield;
bool fireball;
bool magnet; // 道具,人物状态

int corner_frequency;
bool is_corner;    // 判断人物是否正处于路口
bool corner_start; // 判断路口开始
int corner_times;  // 判断累计通过路口数目
int corner_line;   // 判断路口在界面的输出情况
bool corner_stop;  // 转弯后有一moving time的停顿
// 路口参数

int speed; // 速度

int barrier_frequency;
int U_frequency;
int D_frequency;
int X_frequency;
int score_frequency;
int shield_frequency;
int fireball_frequency;
int magnet_frequency; // 游戏的爆率参数

int fireball_x;
int fireball_y; // 火球的坐标
int fireball_store;
int fireball_max = 3; // 火球数目及其储存上限

#define title_x 45
#define title_y 10 // 文字输出坐标

typedef struct date
{
    int speed_set;
    int barrier_frequency_set;
    int U_frequency_set;
    int D_frequency_set;
    int X_frequency_set;
    int score_frequency_set;
    int shield_frequency_set;
    int fireball_frequency_set;
    int magnet_frequency_set;
    int fireball_store_set;
} Date; // 难度结构

Date list[3] = {{50, 90, 9, 18, 22, 24, 25, 26, 27, 3}, {40, 120, 16, 32, 40, 44, 45, 46, 47, 1}, {30, 180, 28, 56, 70, 75, 76, 77, 78, 0}}; // 难度参数

void HideCursor();
void gotoxy(int x, int y);
VOID SetColor(UINT uFore, UINT uBack);
void game_stop();
void clear_map();

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
} // 隐藏光标

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
} // 光标移动

VOID SetColor(UINT uFore, UINT uBack)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, uFore + uBack * 0x10);
} // 第一个参数为字体颜色，第二个为背景颜色。

void game_stop()
{
    gotoxy(stop_x, stop_y);
    system("pause");
    gotoxy(stop_x, stop_y);
    printf("                  ");
} // 暂停逻辑

void clear_map()
{
    for (int i = map_y; i < map_y + map_r; i++)
    {
        gotoxy(map_x - 5, i);
        puts("              ");
    }
} // 清屏