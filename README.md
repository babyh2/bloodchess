# Blood Chess - BabyH2
- link preview game : [youtube](https://youtu.be/lQVQ9EjT5JM?si=PuJfXUm7alVitVLs)
# Cài đặt 
- Bản chạy được ngay : tải Blood_Chess.rar và giải nén từ [release](https://github.com/babyh2/bloodchess/releases/tag/release)
- Bản chạy trên IDE hoặc textEditor : clone repo hoặc code -> Download ZIP

# Nguồn
Các hình ảnh trong game tự thiết kế hoặc tìm ngẫu nhiên trên google nguồn chủ yếu :
- hình ảnh : [canva](https://www.canva.com)
- font : google

# Giới thiệu Game 
Lấy cảm hứng từ giải mê cung và vượt chướng ngại vật.
Điểm đặc biệt:
- Cấc item đa dạng và random nên không thể đoán trước được để vượt qua như nào.
- Bản đồ game có nhiều ngõ cụt và đầm lầy gây ức chế cho người chơi.
- Bom thì trừ rất nhiều máu còn hồi phục thì không đáng là bao nhiêu người chơi cần có năng lực tư duy và quan trọng là năng lựuc may mắn thì mới thắng được game
- Người chơi cũng phải chú ý đến điểm số để mua nhân vật (nhân vật có từng kĩ năng riêng biệt)
- Nhân vật mặc định thì không có kĩ năng gì

# Bắt đầu game 
- Menu : có 5 sự lựa chọn :
  + START_GAME : bắt đầu vào game và chơi
  <div style="text-align: center;">
 ![game](https://github.com/babyh2/bloodchess/blob/main/gameSDL2/Debug/photo/menuchinh.png?raw=true)


  + RULES OF THE GAME : hiển thị hướng dẫn game
  ![huongdan](https://github.com/babyh2/bloodchess/blob/main/gameSDL2/Debug/photo/RULES_OF_THE_GAME.png?raw=true)
  </div>

  + SHOPGAME :
  ![shop](https://github.com/babyh2/bloodchess/blob/main/gameSDL2/Debug/photo/shop.png?raw=true)


  + HIGHSCORE:
     ![menu](https://github.com/babyh2/bloodchess/blob/main/gameSDL2/Debug/photo/HighScore.png?raw=true)

  + EXIT : thoát game
  + WIN GAME :
   ![menu](https://github.com/babyh2/bloodchess/blob/main/gameSDL2/Debug/photo/win.png?raw=true)


  + THUA GAME :
   ![menu](https://github.com/babyh2/bloodchess/blob/main/gameSDL2/Debug/photo/loss.png?raw=true)

# Source code 
- folder font : chứa font chữ
- folder photo, img , map : chứa hình ảnh nhân vật, màn hình , menu và bản đồ
- gameSDL2.cpp : chứa hàm main
  + Hàm init() : khỏi tạo shop khi mua thất bại
  + hàm close() : hàm giải phóng và đưa các con trỏ về NULL
- BaseObject.cpp
  + hàm LoadImg : lấy dữ liệu tấm ảnh từ đường dẫn và load nó lên
  + hàm render : vẽ tấm ảnh lên màn hình
  + hàm free : giải phóng con trỏ đưa về mặc định ban đầu
- TextObject.cpp
  + hàm LoadText : lấy dữ liệu chữ , chuyển nó thành hình ảnh rồi load lên
  + hàm RenderText : vẽ chữu lên màn hình
  + hàm SetColor : tạo các màu cho chữ
  + hàm GetSize ; lấy dữ liệu kích thước tấm ảnh
- MainObject.cpp
  + hàm setPos : tạo dựng vị trí cho nhân vật
  + LoadImg : lấy dữ liệu hình ảnh nhân vật từ file và load nó lên
  + Show : đưa hình ảnh nhân vật ra màn hình
  + HandelInputAction : một trong những hàm xử lí di chuyển thiết lập việc di chuyển trái phải trên dưới
  + DoPlayer : thiết lập việc di chuyển và tốc độ di chuyển của nhân vật
  + CenterEntityOnMap : thiết lập việc map di chuyển theo nhân vật
  + CheckToMap : hàm check va chạm của nhân vật với tường
  + CheckVaCham, checktaodoc, checktaixiu, checkhoiphuc, checkbom, checksieuhoiphuc : check va chạm giữa nhân vật với các item trong bản đồ
- GameMap.cpp
  + LoadMap : đọc toàn bộ thông tin của file map
  + LoadTiles : lấy dữ liệu từ mảng chứa thông tin map và sắp xếp hình ảnh tương ứng
  + DrawMap : vẽ hình ảnh của các chi tiết của bản đồ lên màn hình
  + hàm GetMap : lấy dữ liệu của bản đồ game
  + Hàm Setmap : chỉ định bản đồ
  + KhoiPhucMap : tạo lập lạ map như cũ sau mỗi lượt chơi
  + random_vatcan : tạo ngẫu nhiên các item trong game 
- Menu.cpp:
  + LoadMenu : Load hình ảnh của menu và gán vào project
  + hàm show : đưa hình ảnh lên màn hình
  + CheckFocus : xử lý vị trí của chuột
  + ShowMenu : thiết lập menu chính của game
  + menuMuaBan : thiết lập menu shop của game
  + hàm MenuWin : thiết lập menu khi người chơi dành chiến thắng
  + hàm MenuLoss : thiết lập menu khi người chơi thua cuộc
  + hàm menuHighScore : thiết lập menu hiển thị khi người chơi muốn xem highscore
  + hàm menuRules : thiết lập menu hiển thị hướng dẫn người chơi chơi game
- Commonfunc.h : định nghĩa các biến hàm, cấu trúc cần thiết cho game

  
