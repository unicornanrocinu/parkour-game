#ifndef _HEADERNAME_H
#define _HEADERNAME_H
#include "background_operation.h"
#endif

void set_corner();
void corner_init();
void turn_left();
void turn_right();
void corner_show();

void set_corner()
{
    corner_line = 0;
    for (int i = 0; i < corner_r; i++)
    {
        for (int j = 0; j < corner_c; j++)
        {
            if (i >= corner_mid_r && i < corner_mid_r + 3)
                corner[i][j] = ' '; // 保证拐角处空白
            else
            {
                int r = rand() % barrier_frequency + 1;
                if (r <= U_frequency && not_barrier_corner(i - 1, j))
                    corner[i][j] = 'U';
                else if (r <= D_frequency && not_barrier_corner(i - 1, j))
                    corner[i][j] = 'D';
                else if (r <= X_frequency && not_barrier_corner(i - 1, j))
                    corner[i][j] = ' ';
                else if (r <= score_frequency)
                {
                    if (character)
                        corner[i][j] = '$';
                    else
                        corner[i][j] = 'L';
                }
                else if (r <= shield_frequency && !shield)
                    corner[i][j] = 'S';
                else if (r <= fireball_frequency && fireball_store < fireball_max)
                    corner[i][j] = 'F';
                else if (r <= magnet_frequency && !magnet)
                    corner[i][j] = 'M';
                else
                    corner[i][j] = ' ';
            }
        }
    }
}

void corner_init()
{
    is_corner = false;
    corner_start = false;
} // 路口参数初始化

void turn_left()
{
    corner_init();
    int temp = position_x;
    position_x = corner_line - 5;
    for (int i = temp, j = 0; j < map_r; i++, j++)
        strcpy(map[j], corner[i]); // 坐标变换
    memset(corner, 0, sizeof(corner));
    corner_stop = true;
    clear_map();
}

void turn_right()
{
    corner_init();
    int temp = position_x;
    position_x = 7 - corner_line;
    for (int i = temp + 8, j = 0; j < map_r; i--, j++)
        for (int k = 0, l = 2; k < 3; k++, l--)
            map[j][k] = corner[i][l]; // 坐标变换
    memset(corner, 0, sizeof(corner));
    corner_stop = true;
    clear_map();
}

void corner_show()
{
    if (corner_line <= 3) // 路口未完全出现
    {
        for (int i = 0; i < corner_line; i++)
        {
            gotoxy(map_x - 2, map_y + corner_line - i - 1);
            for (int j = 2; j < 9; j++)
                printf("%c", corner[j][i]);
        } // 路口视野
        for (int i = corner_line; i < map_r; i++)
        {
            if (i == corner_line) // 上横栏处不打印边框
            {
                gotoxy(map_x, map_y + i);
                printf("%s", map[i]);
            }
            else
            {
                gotoxy(map_x - 1, map_y + i);
                printf("%c%s%c", line_l[i], map[i], line_r[i]);
            }
        }
        gotoxy(map_x - 2, map_y + corner_line);
        putchar('-');
        putchar('-');
        gotoxy(map_x + 3, map_y + corner_line);
        putchar('-');
        putchar('-'); // 打出下横栏
    }
    else
    {
        for (int i = 0; i < corner_line - 4; i++)
        {
            gotoxy(map_x - 2, map_y + i);
            puts("         ");
        }
        gotoxy(map_x - 2, map_y + corner_line - 4);
        puts(obstacle);
        for (int i = 2; i > -1; i--)
        {
            gotoxy(map_x - 2, map_y + corner_line - i - 1);
            for (int j = 2; j < 9; j++)
                printf("%c", corner[j][i]);
        }
        for (int i = corner_line; i < map_r; i++)
        {
            gotoxy(map_x - 1, map_y + i);
            printf("%c%s%c", line_l[i], map[i], line_r[i]);
        }
        if (corner_line < 7)
        {
            gotoxy(map_x - 2, map_y + corner_line);
            putchar('-');
            putchar('-');
            gotoxy(map_x + 3, map_y + corner_line);
            putchar('-');
            putchar('-');
        }
    }
}