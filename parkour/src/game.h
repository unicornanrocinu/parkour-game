#ifndef _HEADERNAME_H
#define _HEADERNAME_H
#include "background_operation.h"
#endif

#include "fireball.h"
#include "corner.h"

void show();
void time_go();
bool is_valid_X(int x);
void set_newline();
void is_shield();
void judge();
void moving();
void user();
void game_frame();

void game_frame()
{
    user();    // 用户输入
    show();    // 屏幕输出
    time_go(); // 模拟游戏时间的流逝
    moving();  // 模拟人物运动
    show();    // 屏幕输出
    judge();   // 判断碰撞
    Sleep(5);
}

void user()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == 'w' || input == 'W')
        {
            if (!state)
            {
                state = 1;
                start_time = game_time;
            }
        }
        else if (input == 's' || input == 'S')
        {
            if (!state)
            {
                state = 2;
                start_time = game_time;
            }
        }
        else if (input == 'a' || input == 'A')
        {
            if (position_x > 0)
                position_x--;
        }
        else if (input == 'd' || input == 'D')
        {
            if (position_x < map_c - 1)
                position_x++;
        }
        else if (input == 'f' || input == 'F')
            fireball_launcher();
        else if (input == ' ')
            game_stop(); // 暂停
        else if ((input == 'E' || input == 'e') && is_corner)
            turn_right();
        else if ((input == 'Q' || input == 'q') && is_corner)
            turn_left(); // 转弯
    }
}

void show()
{
    if (corner_start)
        corner_show(); // 路口特殊输出
    else
    {
        for (int i = 0; i < map_r; i++)
        {
            gotoxy(map_x - 1, map_y + i);
            printf("%c%s%c", line_l[i], map[i], line_r[i]);
        } // 正常输出
    }
    if (fireball)
    {
        gotoxy(fireball_x + map_x, fireball_y + map_y);
        putchar('o');
    } // 火球输出
    gotoxy(position_x + map_x, postion_y + map_y);
    putchar('*'); // 玩家输出
    gotoxy(score_x + 6, score_y);
    printf("%d", score);
    gotoxy(score_x + 6, score_y + 1);
    printf("%s", states[state]);
    gotoxy(score_x + 9, score_y + 2);
    for (int i = 0; i < fireball_store; i++)
        printf("o ");
    for (int i = fireball_store; i < fireball_max; i++)
        printf("  ");
    if (shield)
    {
        gotoxy(score_x, score_y + 3);
        printf("Shield");
    }
    else
    {
        gotoxy(score_x, score_y + 3);
        printf("      ");
    }
    if (magnet)
    {
        gotoxy(score_x, score_y + 4);
        printf("Magnet");
    }
    else
    {
        gotoxy(score_x, score_y + 4);
        printf("      ");
    } // 面板输出
}

void time_go()
{
    game_time++;
    if (game_time - start_time == (int)(1.5 * speed))
        state = 0; // 1.5个moving_time后状态回位
    if (magnet && game_time - magnet_start_time == 20 * speed)
        magnet = false;
    if (corner_times < score / corner_frequency) // 路口生成判断
    {
        corner_start = true;
        corner_times = score / corner_frequency;
        set_corner();
    }
    speed = (int)(list[difficulty].speed_set * MAX((1 - (score / 20) / 100), 0.5)); // 速度变化
}

void set_newline()
{
    for (int i = 0; i < map_c; i++)
        map[0][i] = ' ';
    for (int i = 0; i < map_c; i++)
    {
        int r = rand() % barrier_frequency + 1;
        if (r <= U_frequency && not_barrier(1, i))
            map[0][i] = 'U'; // 保证前一行的对应格子无障碍
        else if (r <= D_frequency && not_barrier(1, i))
            map[0][i] = 'D';
        else if (r <= X_frequency && not_barrier(1, i) && is_valid_X(i))
            map[0][i] = 'X';
        else if (r <= X_frequency && !magnet)
            map[0][i] = ' '; // 磁铁生效时金币爆率上升
        else if (r <= score_frequency)
        {
            if (character)
                map[0][i] = '$';
            else
                map[0][i] = 'L';
        }
        else if (r <= shield_frequency && !shield)
            map[0][i] = 'S';
        else if (r <= fireball_frequency && fireball_store < fireball_max)
            map[0][i] = 'F';
        else if (r <= magnet_frequency && !magnet)
            map[0][i] = 'M';
        else
            map[0][i] = ' ';
    }
}

bool is_valid_X(int x)
{
    int list_x = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i == x)
        {
            list_x++;
            continue;
        }
        for (int j = 0; j < 3; j++)
        {
            if (map[j][i] == 'X')
            {
                list_x++;
                break;
            }
        }
    }
    return list_x == 3 ? false : true;
} // 3行内只有2行有X,保证通行

void is_shield()
{

    if (shield)
    {
        map[postion_y][position_x] = ' ';
        shield = false;
    }
    else
        alive = false;
    return;
} // 护盾效果实现

void judge()
{
    if (magnet) // 磁铁效果实现
    {
        for (int i = 0; i < 3; i++)
        {
            if (store_line[i] == '$')
            {
                store_line[i] = ' ';
                map[postion_y][i] = ' ';
                score += 5;
            }
            if (store_line[i] == 'L')
            {
                store_line[i] = ' ';
                map[postion_y][i] = ' ';
                score += 5;
                int r = rand() % 100;
                if (r < 5)
                    score += 5;
                else if (r < 7)
                    score += 10;
                else if (r < 8)
                    score += 15;
                else if (r < 9)
                    shield = true;
                else if (r < 10)
                {
                    if (fireball_store < fireball_max)
                        fireball_store++;
                }
                else if (r < 11)
                {
                    magnet = true;
                    magnet_start_time = game_time;
                }
            }
        }
    }
    if (store_line[position_x] == ' ')
        return;
    else if (store_line[position_x] == 'X')
    {
        store_line[position_x] = ' ';
        is_shield();
    }
    else if (store_line[position_x] == 'U')
    {
        store_line[position_x] = ' ';
        if (state == 1)
            return;
        else
            is_shield();
    }
    else if (store_line[position_x] == 'D')
    {
        store_line[position_x] = ' ';
        if (state == 2)
            return;
        else
            is_shield();
    }
    else if (store_line[position_x] == '-')
    {
        alive = 0;
        return;
    }
    else if (store_line[position_x] == '$')
    {
        store_line[position_x] = ' ';
        map[postion_y][position_x] = ' ';
        score += 5;
        return;
    }
    else if (store_line[position_x] == 'S')
    {
        store_line[position_x] = ' ';
        map[postion_y][position_x] = ' ';
        shield = true;
        return;
    }
    else if (store_line[position_x] == 'F')
    {
        store_line[position_x] = ' ';
        map[postion_y][position_x] = ' ';
        if (fireball_store < fireball_max)
            fireball_store++;
        return;
    }
    else if (store_line[position_x] == 'M')
    {
        store_line[position_x] = ' ';
        map[postion_y][position_x] = ' ';
        if (!magnet)
        {
            magnet = true;
            magnet_start_time = game_time;
        }
        return;
    }
    else if (store_line[position_x] == 'L') // 开拓者特性
    {
        store_line[position_x] = ' ';
        map[postion_y][position_x] = ' ';
        score += 5;
        int r = rand() % 100;
        if (r < 5)
            score += 5;
        else if (r < 7)
            score += 10;
        else if (r < 8)
            score += 15;
        else if (r < 9)
            shield = true;
        else if (r < 10)
        {
            if (fireball_store < fireball_max)
                fireball_store++;
        }
        else if (r < 11)
        {
            magnet = true;
            magnet_start_time = game_time;
        }
        return;
    }
}

void moving()
{
    if (game_time % speed)
        return;
    if (corner_stop)
    {
        corner_stop = false;
        return;
    } // 转弯后暂停1次
    if (corner_start)
    {
        corner_line++;
        for (int i = map_r - 1; i > corner_line - 1; i--)
        {
            memcpy(map[i], map[i - 1], map_c * sizeof(char));
            line_l[i] = line_l[i - 1];
            line_r[i] = line_r[i - 1];
        }
        if (corner_line > 4)
            is_corner = true;
    } // 路口特殊生成
    else
    {
        for (int i = map_r - 1; i > 0; i--)
        {
            memcpy(map[i], map[i - 1], map_c * sizeof(char));
            line_l[i] = line_l[i - 1];
            line_r[i] = line_r[i - 1];
        }
        line_l[0] = '|';
        line_r[0] = '|';
        set_newline();
    } // 正常地图移动
    if (corner_start && corner_line > 4 && corner_line < 8)
    {
        memset(store_line, ' ', sizeof(store_line) - 1);
    }
    else if (corner_start && corner_line > 7)
        memset(store_line, '-', sizeof(store_line) - 1); // 路口特殊玩家所在行复制
    else
        strcpy(store_line, map[postion_y]);
    if (fireball)
        fireball_judge(); // 火球判断
    score++;
}
