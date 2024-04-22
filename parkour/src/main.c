#ifndef _HEADERNAME_H
#define _HEADERNAME_H
#include "background_operation.h"
#endif

#include "init.h"
#include "game.h"
#include "end.h"

int main()
{
    init(); // 初始界面加载
    do
    {

        game_init(); // 游戏初始化
        while (alive)
            game_frame();   // 游戏帧
        end();              // 结算页面
    } while (is_restart()); // 再开逻辑
}