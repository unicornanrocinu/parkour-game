#ifndef _HEADERNAME_H
#define _HEADERNAME_H
#include "background_operation.h"
#endif

void end_interface();
void get_RE();
bool is_restart();
void end();
void end_plot();

void end()
{
    end_plot();
    end_interface();
    get_RE();
}

void end_plot()
{
    system("cls");
    if (score < 1000)
    {

        SetColor(4, 0);
        if (character)
        {
            gotoxy(title_x - 15, title_y - 1);
            wprintf(L"托帕万万没有想到这次的对手尽然如此难缠,一不留神间就跟丢了目标,");
            gotoxy(title_x - 15, title_y);
            wprintf(L"账账垂头丧气地伏在脚边,托帕决心下次一定要让开拓者好看.");
        }
        else
        {
            gotoxy(title_x - 15, title_y - 1);
            wprintf(L"尽管开拓者试图打破规则, 但最终还是为规则所束缚");
            gotoxy(title_x - 15, title_y);
            wprintf(L"托帕总监催讨作业的声音越来越近, 开拓者们只能望着远方的列车失落地停下了脚步");
            gotoxy(title_x - 15, title_y + 1);
            wprintf(L"等待他的是又一次的挂科.或许努力学习才是唯一出路 ? 下次一定");
        }
    }
    else if (score < 2000)
    {
        SetColor(9, 0);
        if (character)
        {
            gotoxy(title_x - 15, title_y - 1);
            wprintf(L"托帕追逐开拓者一路,终于在对方在雅利洛 - vi翻找垃圾桶时捉住了对方,");
            gotoxy(title_x - 15, title_y);
            wprintf(L"惊叹于对方除学习外的决心毅力, 托帕决定再给开拓者一个机会.");
        }
        else
        {
            gotoxy(title_x - 15, title_y - 1);
            wprintf(L"最终托帕总监还是捉到了在正在翻找垃圾桶的开拓者.");
            gotoxy(title_x - 15, title_y);
            wprintf(L"虽然没有按时完成作业, 但他证明了自己的潜力.托帕总监大发慈悲地延长了ddl, 赞美托帕, 托门.");
        }
    }
    else
    {
        SetColor(2, 0);
        if (character)
        {
            gotoxy(title_x - 15, title_y - 1);
            wprintf(L"托帕轻而易举地将开拓者捉回了呢喃和平公司仙林分公司,");
            gotoxy(title_x - 15, title_y);
            wprintf(L"在那里, 他将与野生在逃扑满一起度过三年时光.");
        }
        else
        {
            gotoxy(title_x - 15, title_y - 1);
            wprintf(L"托帕总监与账账紧追不舍,但开拓者展现出了惊人的技巧和智慧.");
            gotoxy(title_x - 15, title_y);
            wprintf(L"最终, 他成功逃脱了追捕, 彻底摆脱了作业的束缚, 打破了规则.从此, 银河棒球侠的名号响彻呢喃.");
        }
    }
    gotoxy(title_x - 15, title_y + 2);
    wprintf(L"                            敲击SPACE跳出剧情");
    char input;
    while ((input = getch()) != ' ')
        ;
} // 触发结局事件

void end_interface()
{
    system("cls");
    SetColor(7, 0);
    gotoxy(title_x, title_y);
    best_score = MAX(score, best_score);
    wprintf(L"你的成绩是：%d", score);
    gotoxy(title_x, title_y + 1);
    wprintf(L"敲击 R 键再来一把");
    gotoxy(title_x, title_y + 2);
    wprintf(L"敲击 E 键退出游戏");
    gotoxy(title_x, title_y + 3);
    wprintf(L"敲击 T 键打开设置面板");
}

void get_RE()
{
    do
    {
        ch = getch();
        if (ch == 'T' || ch == 't')
            setting_interface();
        end_interface();
    } while (ch != 'R' && ch != 'E' && ch != 'r' && ch != 'e');
} // 接受输入

bool is_restart()
{
    if (ch == 'R' || ch == 'r')
        return true;
    system("cls");
    gotoxy(title_x, title_y);
    wprintf(L"你确定要退出吗?");
    gotoxy(title_x, title_y + 1);
    wprintf(L"不玩了(Y)/再来一把(N)");
    do
    {
        ch = getch();
        if (ch == 'Y' || ch == 'y')
            return false;
        if (ch == 'N' || ch == 'n')
            return true;
    } while (1);
} // 判断是否重开
