#ifndef _HEADERNAME_H
#define _HEADERNAME_H
#include "background_operation.h"
#endif

void fireball_launcher();
void fireball_judge();

void fireball_launcher()
{
    if (fireball_store == 0 || fireball)
        return;
    fireball = true;
    fireball_store--;
    fireball_x = position_x;
    fireball_y = postion_y - 1;
    if (!not_barrier(postion_y - 1, position_x))
    {
        fireball = false;
        if (character)
        {
            for (int i = 0; i < 3; i++)
                if (!not_barrier(fireball_y, i))
                    map[fireball_y][i] = '$';
        }
        else
            map[postion_y - 1][position_x] = ' ';
    } // 对面前障碍的特殊判断
}

void fireball_judge()
{
    if (!not_barrier(fireball_y, fireball_x))
    {
        if (character)
        {
            for (int i = 0; i < 3; i++)
                if (!not_barrier(fireball_y, i))
                    map[fireball_y][i] = '$';
        } // 托帕人物特性
        else
            map[fireball_y][fireball_x] = ' ';
        fireball = false;
        return;
    }             // 火球与障碍为相邻格
    fireball_y--; // 火球移动
    if (fireball_y < 0)
    {
        fireball = false;
        return;
    }
    if (!not_barrier(fireball_y, fireball_x))
    {
        if (character)
        {
            for (int i = 0; i < 3; i++)
                if (!not_barrier(fireball_y, i))
                    map[fireball_y][i] = '$';
        }
        else
            map[fireball_y][fireball_x] = ' ';
        fireball = false;
        return;
    } // 火球与障碍为同格
}