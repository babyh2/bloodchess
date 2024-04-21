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


void Game_Tai_Xiu::PlayTaiXiuGame(SDL_Renderer* screen, TTF_Font* font, int& mark_value, bool& game_running)
{
	if (!game_running)
	{
		return;
	}

	const int kMenu = 9;
	SDL_Rect pos_arr[kMenu] = {
		{202, 370, 0, 0}, // TAI position
		{820, 370, 0, 0}, // XIU position
		{85, 650, 0, 0}, // 20 bet amount position
		{345, 650, 0, 0}, // 50 bet amount position
		{605, 650, 0, 0}, // 100 bet amount position
		{865, 650, 0, 0}, // ALL IN bet amount position
		{470, 750, 0, 0}, // CUOC (bet) position
		{500, 500, 100, 50}, // Replay button position
		{700, 500, 100, 50} // Exit button position
	};

	TextObject textMenu[kMenu];
	const std::string menuItems[kMenu] = { "TAI", "XIU", "20", "50", "100", "ALL IN", "CUOC", "Replay", "Exit" };

	int taimoney = 0, xiumoney = 0; // Các giá trị cược ban đầu cho TAI và XIU
	bool selected[kMenu] = { false, false, false, false, false, false, false, false, false };
	SDL_Event m_event;
	bool is_quit = false;
	bool tai = false, xiu = false;
	int dice[3]; // Mảng chứa kết quả của 3 con xúc xắc
	int sum = 0; // Tổng điểm của 3 con xúc xắc

	TextObject result_text;
	result_text.SetColor(TextObject::WHITE);

	// TextObject cho hiển thị điểm số
	std::string score_text = "Score: " + std::to_string(mark_value);
	TextObject score_text_object;
	score_text_object.SetColor(TextObject::RED); // Đổi màu chữ sang đỏ
	score_text_object.LoadText(font, score_text, screen);
	score_text_object.SetRect(850, 50);

	while (!is_quit)
	{
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
				}
			}
			else if (m_event.type == SDL_MOUSEBUTTONDOWN)
			{
				int xm = m_event.button.x;
				int ym = m_event.button.y;

				// Xử lý lựa chọn TAI/XIU và cược
				if (selected[0]) {
					tai = true;
					xiu = false;
				}
				if (selected[1]) {
					tai = false;
					xiu = true;
				}

				if (tai)
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

					mark_value -= taimoney; // Trừ số tiền đã cược
				}
				else if (xiu)
				{
					// Xử lý chọn XIU
					int cuoc = 0;
					if (selected[2])
					{
						xiumoney += 20;
						cuoc = 20;
					}
					else if (selected[3])
					{
						xiumoney += 50;
						cuoc = 50;
					}
					else if (selected[4])
					{
						xiumoney += 100;
						cuoc = 100;
					}
					else if (selected[5])
					{
						xiumoney = mark_value;
						cuoc = 20;
					}
					else
					{
						xiumoney = 0;
					}

					mark_value -= cuoc; // Trừ số tiền đã cược
				}

				// Kiểm tra khi nút "CUOC" được nhấn
				if (selected[6])
				{
					// Tạo kết quả ngẫu nhiên cho mỗi con xúc xắc
					for (int i = 0; i < 3; i++)
					{
						dice[i] = rand() % 6 + 1; // Kết quả ngẫu nhiên từ 1 đến 6
						sum += dice[i]; // Cộng kết quả vào tổng số điểm
					}

					// Hiển thị hình ảnh xúc xắc lên màn hình
					std::string dice_images[3] = {
						"img/t" + std::to_string(dice[0]) + ".png",
						"img/t" + std::to_string(dice[1]) + ".png",
						"img/t" + std::to_string(dice[2]) + ".png"
					};

					SDL_Rect dice_positions[3] = {
						{531, 202, 90, 90},
						{450, 332, 90, 90},
						{601, 332, 90, 90}
					};

					for (int i = 0; i < 3; i++)
					{
						SDL_Surface* img_surface = IMG_Load(dice_images[i].c_str());
						SDL_Texture* img_texture = SDL_CreateTextureFromSurface(screen, img_surface);
						SDL_FreeSurface(img_surface);

						SDL_RenderCopy(screen, img_texture, nullptr, &dice_positions[i]);
						SDL_DestroyTexture(img_texture);
					}

					// Xử lý kết quả và cập nhật điểm số
					if (sum > 10)
					{
						// TAI thắng
						mark_value += taimoney;
						mark_value -= xiumoney;
						result_text.LoadText(font, "Result: TAI wins!", screen);
					}
					else
					{
						// XIU thắng
						mark_value += xiumoney;
						mark_value -= taimoney;
						result_text.LoadText(font, "Result: XIU wins!", screen);
					}

					if(mark_value <= 0) is_quit = true;

					// Hiển thị kết quả lên màn hình
					result_text.RenderText(screen, 470, 150);

					// Hiển thị điểm số (score) đã cập nhật
					score_text = "Score: " + std::to_string(mark_value);
					score_text_object.LoadText(font, score_text, screen);
					score_text_object.RenderText(screen, 850, 50);

					// Hiển thị nút replay và exit
					SDL_SetRenderDrawColor(screen, 0, 255, 0, 255); // Màu xanh lá cây cho nút replay
					SDL_RenderFillRect(screen, &pos_arr[7]);

					SDL_SetRenderDrawColor(screen, 255, 0, 0, 255); // Màu đỏ cho nút exit
					SDL_RenderFillRect(screen, &pos_arr[8]);

					TextObject replay_text, exit_text;
					replay_text.SetColor(TextObject::WHITE);
					replay_text.LoadText(font, "Replay", screen);
					replay_text.RenderText(screen, pos_arr[7].x + 20, pos_arr[7].y + 15);

					exit_text.SetColor(TextObject::WHITE);
					exit_text.LoadText(font, "Exit", screen);
					exit_text.RenderText(screen, pos_arr[8].x +
						30, pos_arr[8].y + 15);

					SDL_RenderPresent(screen);

					bool decision_made = false;
					SDL_Event event;
					while (!decision_made)
					{
						while (SDL_PollEvent(&event))
						{
							if (event.type == SDL_MOUSEBUTTONDOWN)
							{
								int mouse_x = event.button.x;
								int mouse_y = event.button.y;

								// Kiểm tra sự kiện nhấp chuột lên nút replay hoặc exit
								if (mouse_x >= pos_arr[7].x && mouse_x <= pos_arr[7].x + pos_arr[7].w &&
									mouse_y >= pos_arr[7].y && mouse_y <= pos_arr[7].y + pos_arr[7].h)
								{
									// Chọn replay
									decision_made = true;
									break;
								}
								else if (mouse_x >= pos_arr[8].x && mouse_x <= pos_arr[8].x + pos_arr[8].w &&
									mouse_y >= pos_arr[8].y && mouse_y <= pos_arr[8].y + pos_arr[8].h)
								{
									// Chọn exit
									decision_made = true;
									game_running = false;
									is_quit = true; // Thoát khỏi vòng lặp
									break;
								}
							}
						}
					}
				}
				
			}
		}

		SDL_RenderClear(screen);
		LoadMenuTaiXiu(screen, "money.png");
		ShowMenu(screen, 0, 0);

		// Hiển thị điểm số
		score_text_object.RenderText(screen, 850, 50);

		for (int i = 0; i < kMenu; i++)
		{
			textMenu[i].SetColor(selected[i] ? TextObject::GREEN : TextObject::RED);
			textMenu[i].LoadText(font, menuItems[i], screen);
			textMenu[i].SetRect(pos_arr[i].x, pos_arr[i].y);
			textMenu[i].GetSize(pos_arr[i].w, pos_arr[i].h);
			textMenu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
		}

		// Hiển thị số tiền đã cược cho TAI và XIU
		TextObject tai_bet_text, xiu_bet_text;
		tai_bet_text.SetColor(TextObject::WHITE);
		xiu_bet_text.SetColor(TextObject::WHITE);
		tai_bet_text.LoadText(font, "TAI bet: " + std::to_string(taimoney), screen);
		xiu_bet_text.LoadText(font, "XIU bet: " + std::to_string(xiumoney), screen);
		tai_bet_text.RenderText(screen, 202, 400);
		xiu_bet_text.RenderText(screen, 820, 400);

		SDL_RenderPresent(screen);
	}
}

