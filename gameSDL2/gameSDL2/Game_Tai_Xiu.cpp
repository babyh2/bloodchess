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

Game_Tai_Xiu::~Game_Tai_Xiu()
{
    // Destructor (bạn có thể thêm logic nếu cần)
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
    // Kiểm tra xem tọa độ (x, y) có nằm trong vùng của rect hay không
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

void Game_Tai_Xiu::ShowMenuTaiXiu(SDL_Renderer* screen, TTF_Font* font, bool& game_running)
{
    const int kMenu = 2;
    SDL_Rect pos_arr[kMenu] = {
        {200, 600, 0, 0},
        {200, 700, 0, 0}
    };

    TextObject textMenu[kMenu];
    const std::string menuItems[kMenu] = {"START GAME", "EXIT"};

    for (int i = 0; i < kMenu; i++)
    {
        textMenu[i].SetColor(TextObject::RED);
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }

    bool selected[kMenu] = {false, false};
    SDL_Event m_event;
    bool is_quit = false;

    while (!is_quit && game_running)
    {
        // Hiển thị menu chính
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
                game_running = false;
                is_quit = true;
            }
            else if (m_event.type == SDL_MOUSEMOTION)
            {
                int xm = m_event.motion.x;
                int ym = m_event.motion.y;
                
                // Kiểm tra xem chuột đã di chuyển vào nút nào
                for (int i = 0; i < kMenu; i++)
                {
                    bool isFocus = CheckTaiXiu(xm, ym, pos_arr[i]);
                    
                    if (isFocus && !selected[i])
                    {
                        selected[i] = true;
                        textMenu[i].SetColor(TextObject::GREEN); // Màu khi chuột di chuyển vào
                        textMenu[i].LoadText(font, menuItems[i], screen); // Cập nhật văn bản
                    }
                    else if (!isFocus && selected[i])
                    {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED); // Trở lại màu ban đầu
                        textMenu[i].LoadText(font, menuItems[i], screen);
                    }
                }
            }
            else if (m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                int xm = m_event.button.x;
                int ym = m_event.button.y;
                
                // Xử lý khi người dùng nhấp chuột vào nút
                for (int i = 0; i < kMenu; i++)
                {
                    if (selected[i])
                    {
                        if (i == 0) // START GAME
                        {
                            game_running = true;
                            return;
                        }
                        else if (i == 1) // EXIT
                        {
                            game_running = false;
                            is_quit = true;
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(screen);
    }
}

void Game_Tai_Xiu::gameThuc(SDL_Renderer* screen, TTF_Font* font, int& mark_value, bool& game_running)
{
    if (!game_running)
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
        {470, 750, 0, 0}
    };

    TextObject textMenu[kMenu];
    const std::string menuItems[kMenu] = {"TAI", "XIU", "20", "50", "100", "ALL IN", "CUOC"};

    for (int i = 0; i < kMenu; i++)
    {
        textMenu[i].SetColor(TextObject::RED);
        textMenu[i].LoadText(font, menuItems[i], screen);
        textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
        textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
    }

    bool selected[kMenu] = {false, false, false, false, false, false, false};
    SDL_Event m_event;
    bool is_quit = false;
    
    // Hiển thị điểm số
    std::string score_text = "Score: " + std::to_string(mark_value);
    TextObject score_text_object;
    score_text_object.SetColor(TextObject::WHITE);
    score_text_object.LoadText(font, score_text, screen);
    score_text_object.SetRect(850, 50);
    
    // Vòng lặp chính của màn hình game Tài Xỉu
    while (!is_quit)
    {
        LoadMenuTaiXiu(screen, "money.png");
        ShowMenu(screen, 0, 0);
        
        // Hiển thị điểm số
        score_text_object.RenderText(screen, 850, 50);
        
        for (int i = 0; i < kMenu; i++)
        {
            textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }

        while (SDL_PollEvent(&m_event))
        {
            if (m_event.type == SDL_QUIT)
            {
                is_quit = true;
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
                        textMenu[i].SetColor(TextObject::GREEN);
                        textMenu[i].LoadText(font, menuItems[i], screen);
                    }
                    else if (!isFocus && selected[i])
                    {
                        selected[i] = false;
                        textMenu[i].SetColor(TextObject::RED);
                        textMenu[i].LoadText(font, menuItems[i], screen);
                    }
                    
                    SDL_RenderPresent(screen);
                }
            }
            else if (m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                int xm = m_event.button.x;
                int ym = m_event.button.y;

                // Xử lý chọn TAI/XIU và cược
                if (selected[0])
                {
                    // Xử lý chọn TAI
                    if (selected[2])
                    {
                        taimoney = 20;
                    }
                    else if (selected[3])
                    {
                        taimoney = 50;
                    }
                    else if (selected[4])
                    {
                        taimoney = 100;
                    }
                    else if (selected[5])
                    {
                        taimoney = mark_value;
                    }
                    else
                    {
                        taimoney = 0;
                    }
                }
                else if (selected[1])
                {
                    // Xử lý chọn XIU
                    if (selected[2])
                    {
                        xiumoney = 20;
                    }
                    else if (selected[3])
                    {
                        xiumoney = 50;
                    }
                    else if (selected[4])
                    {
                        xiumoney = 100;
                    }
                    else if (selected[5])
                    {
                        xiumoney = mark_value;
                    }
                    else
                    {
                        xiumoney = 0;
                    }
                }

                if (selected[6]) // CUOC
                {
                    // Chạy game Tài Xỉu và xử lý kết quả
                    ranTaiXiu(screen,numtong, mark_value, taimoney, xiumoney, font);
                    
                    // Xử lý kết quả và điểm số
                    int sum = num[0] + num[1] + num[2];
                    if (sum <= 10) // XIU thắng
                    {
                        mark_value += xiumoney;
                        mark_value -= taimoney;
                    }
                    else // TAI thắng
                    {
                        mark_value -= xiumoney;
                        mark_value += taimoney;
                    }

                    // Kiểm tra nếu điểm số <= 0 thì thoát game
                    if (mark_value <= 0)
                    {
                        game_running = false;
                        is_quit = true;
                        break;
                    }
                }
            }
        }
        SDL_RenderPresent(screen);
    }
}
void Game_Tai_Xiu::ranTaiXiu(SDL_Renderer* renderer, int& numtong, int& mark_value, int xiumoney, int taimoney, TTF_Font* font) {
    // Tạo hạt giống cho random
    unsigned seed = time(0);
    srand(seed);
    
    int dice[3]; // Mảng chứa kết quả của 3 con xúc xắc
    
    // Tạo kết quả ngẫu nhiên cho mỗi con xúc xắc
    for (int i = 0; i < 3; i++) {
        dice[i] = rand() % 6 + 1; // Kết quả ngẫu nhiên từ 1 đến 6
        numtong += dice[i]; // Cộng kết quả vào tổng số điểm
    }

    // Tọa độ để hiển thị xúc xắc
    SDL_Rect dice_positions[3] = {
        {531, 202, 50, 50},
        {450, 332, 50, 50},
        {601, 332, 50, 50}
    };

    // Hiển thị kết quả xúc xắc
    for (int i = 0; i < 3; i++) {
        // Tạo hình chữ nhật để hiển thị xúc xắc
        SDL_Rect destRect = dice_positions[i];
        
        // Chọn màu tương ứng với kết quả xúc xắc (1-6)
        switch (dice[i]) {
            case 1:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Màu xanh lá cây
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Màu xanh dương
                break;
            case 4:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Màu vàng
                break;
            case 5:
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Màu tím
                break;
            case 6:
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Màu xanh lục
                break;
        }

        // Vẽ hình chữ nhật xúc xắc
        SDL_RenderFillRect(renderer, &destRect);
    }

    // Hiển thị kết quả xúc xắc
    SDL_RenderPresent(renderer);

    // Vẽ nút "replay" màu xanh
    SDL_Rect replay_button = {500, 500, 100, 50}; // Tọa độ và kích thước nút
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Màu xanh lá cây
    SDL_RenderFillRect(renderer, &replay_button);

    // Tạo TextObject để hiển thị chữ "replay" trên nút
    TextObject replay_text;
    replay_text.SetColor(TextObject::BLACK); // Màu đen
    replay_text.LoadText(font, "Replay", renderer); // Tải chữ "Replay"
    replay_text.RenderText(renderer, replay_button.x + 15, replay_button.y + 15); // Vị trí chữ trên nút

    // Xử lý sự kiện
    SDL_Event m_event;
    bool replay_clicked = false;
    while (!replay_clicked) {
        while (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_QUIT) {
                return;
            }
            else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                int xm = m_event.button.x;
                int ym = m_event.button.y;

                // Kiểm tra nếu nút "replay" được nhấn
                if (xm >= replay_button.x && xm <= replay_button.x + replay_button.w &&
                    ym >= replay_button.y && ym <= replay_button.y + replay_button.h) {
                    replay_clicked = true; // Nút "replay" đã được nhấn
                }
            }
        }
    }

    // Khi nút "replay" được nhấn, bắt đầu ván cược mới
    // Xóa kết quả xúc xắc
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < 3; i++) {
        SDL_RenderFillRect(renderer, &dice_positions[i]);
    }
    SDL_RenderPresent(renderer);

    // Cập nhật giá trị score (mark_value)
    // Bạn có thể điều chỉnh cập nhật score dựa trên kết quả của xúc xắc và đặt cược

    // Ví dụ: cập nhật score dựa trên kết quả tài xỉu
    if (numtong >= 11) {
        // Xử lý cược "tài"
        mark_value += taimoney;
        taimoney = 0;
    } else {
        // Xử lý cược "xỉu"
        mark_value += xiumoney;
        xiumoney = 0;
    }
    // Hiển thị score lên màn hình
    // Vẽ nút "score" màu đỏ
    SDL_Rect score_button = {50, 50, 100, 50}; // Tọa độ và kích thước nút
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
    SDL_RenderFillRect(renderer, &score_button);
    
    // Tạo TextObject để hiển thị giá trị score
    TextObject score_text;
    score_text.SetColor(TextObject::BLACK); // Màu đen
    std::string score_str = "Score: " + std::to_string(mark_value); // Tạo chuỗi giá trị score
    score_text.LoadText(font, score_str, renderer); // Tải giá trị score
    score_text.RenderText(renderer, score_button.x + 15, score_button.y + 15); // Vị trí chữ trên nút
    
    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}


