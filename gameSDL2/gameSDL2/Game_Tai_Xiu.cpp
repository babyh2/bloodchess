#include "stdafx.h"
#include "Game_Tai_Xiu.h"

Game_Tai_Xiu::Game_Tai_Xiu()
{
    for (int i = 0; i < 3; i++)
    {
        num[i] = 0;
    }
    numtong = 0;
    menu_width_ = 0;
    menu_height_ = 0;
    taimoney = 0;
    xiumoney = 0;
}

bool Game_Tai_Xiu::LoadMenuTaiXiu(SDL_Renderer* screen, std::string path)
{
    // Load ảnh của menu và gán vào p_object
    bool ret = LoadImg(path, screen);
    if (ret)
    {
        // Gán kích thước của menu
        menu_width_ = rect_.w;
        menu_height_ = rect_.h;
    }
    return ret;
}

void Game_Tai_Xiu::ShowMenu(SDL_Renderer* screen, int x, int y)
{
    SDL_Rect renderQuad = {x, y, menu_width_, menu_height_};
    SDL_RenderCopy(screen, p_object, NULL, &renderQuad);
}

bool Game_Tai_Xiu::CheckTaiXiu(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Game_Tai_Xiu::ShowMenuTaiXiu(SDL_Renderer* screen, TTF_Font* font)
{
    const int kMenu = 2;
    SDL_Rect pos_arr[kMenu] = {
        {200, 600, 0, 0},
        {200, 700, 0, 0},
    };

    TextObject textMenu[kMenu];
    const std::string menuItems[kMenu] = {"START GAME", "EXIT"};

    for (int i = 0; i < kMenu; i++)
    {
        textMenu[i].SetColor(TextObject::RED); // Màu mặc định là màu đỏ
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }

    bool selected[kMenu] = {false, false};

    SDL_Event m_event;

    bool is_quit = false;

    while (!is_quit)
    {
        LoadMenuTaiXiu(screen, "aiduaemvedemnay.png");
        ShowMenu(screen, 0, 0);
        for (int i = 0; i < kMenu; i++)
        {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }

        while (SDL_PollEvent(&m_event))
        {
            if (m_event.type == SDL_QUIT)
            {
                return false;
            }
            else if (m_event.type == SDL_MOUSEMOTION)
            {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra di chuyển chuột vào mục menu
                for (int i = 0; i < kMenu; i++)
                {
                    bool isFocus = CheckTaiXiu(xm, ym, pos_arr[i]);
                    
                    // Kiểm tra trạng thái trước đó và thay đổi màu sắc nếu cần
                    if (isFocus && !selected[i])
                    {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::GREEN); // Đổi sang màu vàng khi con trỏ chuột đến
                        textMenu[i].LoadText(font, menuItems[i], screen); // Cập nhật văn bản
                    }
                    else if (!isFocus && selected[i])
                    {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu đỏ khi con trỏ chuột rời khỏi
                        textMenu[i].LoadText(font, menuItems[i], screen); // Cập nhật văn bản
                    }
                }
            }
            else if (m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                
                // Kiểm tra chọn mục menu
                if (selected[0])
                {
                    return true;
                }
                else if (selected[1])
                {
                    return false; // Thoát trò chơi
                }
            }
        }
    }

    return false;
}

void Game_Tai_Xiu::gameThuc(SDL_Renderer* screen, TTF_Font* font, int& mark_value)
{
    if (!ShowMenuTaiXiu(screen, font))
    {
        return;
    }

    const int kMenu = 7;
    SDL_Rect pos_arr[kMenu] = {
        {202, 370, 0, 0},
        {820, 370, 0, 0},
        {85, 650, 0, 0},
        {345, 650, 0, 0},
        {605, 650, 0, 0},
        {865, 650, 0, 0},
        {470, 750, 0, 0},
    };

    TextObject textMenu[kMenu];
    const std::string menuItems[kMenu] = {"TAI", "XIU", "20", "50", "100", "ALL IN", "CUOC"};

    for (int i = 0; i < kMenu; i++)
    {
        textMenu[i].SetColor(TextObject::RED); // Màu mặc định là màu đỏ
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }

    bool selected[kMenu] = {false, false, false, false, false, false, false};
    SDL_Event m_event;

    while (true)
    {
        LoadMenuTaiXiu(screen, "money.png");
        ShowMenu(screen, 0, 0);
        for (int i = 0; i < kMenu; i++)
        {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }

        while (SDL_PollEvent(&m_event))
        {
            if (m_event.type == SDL_QUIT)
            {
                return;
            }
            else if (m_event.type == SDL_MOUSEMOTION)
            {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                for (int i = 0; i < kMenu; i++)
                {
                    bool isFocus = CheckTaiXiu(xm, ym, pos_arr[i]);
                    
                    if (isFocus && !selected[i])
                    {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::GREEN); // Đổi sang màu vàng khi con trỏ chuột đến
                        textMenu[i].LoadText(font, menuItems[i], screen); // Cập nhật văn bản
                    }
                    else if (!isFocus && selected[i])
                    {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu đỏ khi con trỏ chuột rời khỏi
                        textMenu[i].LoadText(font, menuItems[i], screen); // Cập nhật văn bản
                    }
                }
            }
            else if (m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                int xm = m_event.button.x;
                int ym = m_event.button.y;

                if (selected[0])
                {
                    // Xử lý chọn TAI
                    if (selected[2])
                    {
                        taimoney += 20;
                    }
                    else if (selected[3])
                    {
                        taimoney += 50;
                    }
                    else if (selected[4])
                    {
                        taimoney += 100;
                    }
                    else if (selected[5])
                    {
                        taimoney += mark_value;
                    }
                    mark_value -= taimoney;
                }
                else if (selected[1])
                {
                    // Xử lý chọn XIU
                    if (selected[2])
                    {
                        xiumoney += 20;
                    }
                    else if (selected[3])
                    {
                        xiumoney += 50;
                    }
                    else if (selected[4])
                    {
                        xiumoney += 100;
                    }
                    else if (selected[5])
                    {
                        xiumoney += mark_value;
                    }
                    mark_value -= xiumoney;
                }
                else if (selected[6])
                {
                    // Xử lý chọn CUOC
                    logicgame(screen,mark_value);
                }
            }
        }
    }
}

void Game_Tai_Xiu::logicgame(SDL_Renderer* screen, int& mark_value)
{
    unsigned seed = time(0);
    srand(seed);
    for (int i = 0; i < 3; i++)
    {
        num[i] = rand() % 6 + 1;
        numtong += num[i];
    }
    int xc1, yc1;

    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            xc1 = 531;
            yc1 = 202;
            break;
        case 1:
            xc1 = 450;
            yc1 = 332;
            break;
        case 2:
            xc1 = 601;
            yc1 = 332;
            break;
        }

        switch (num[i])
        {
        case 1:
            LoadMenuTaiXiu(screen, "img/t1.png");
            ShowMenu(screen, xc1, yc1);
            break;
        case 2:
            LoadMenuTaiXiu(screen, "img/t2.png");
            ShowMenu(screen, xc1, yc1);
            break;
        case 3:
            LoadMenuTaiXiu(screen, "img/t3.png");
            ShowMenu(screen, xc1, yc1);
            break;
        case 4:
            LoadMenuTaiXiu(screen, "img/t4.png");
            ShowMenu(screen, xc1, yc1);
            break;
        case 5:
            LoadMenuTaiXiu(screen, "img/t5.png");
            ShowMenu(screen, xc1, yc1);
            break;
        case 6:
            LoadMenuTaiXiu(screen, "img/t6.png");
            ShowMenu(screen, xc1, yc1);
            break;
        default:
            break;
        }
    }

    if (xiumoney > 0)
    {
        if (numtong <= 10)
        {
            mark_value += xiumoney;
            xiumoney = 0;
        }
        else
        {
            mark_value += taimoney;
            taimoney = 0;
        }
    }
    numtong = 0;
}
