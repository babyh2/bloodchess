# Word Puzzle Feature - Build & Run Guide

## Overview
Đã thêm **Word Puzzle Mini-Game** vào Blood Chess. Khi va chạm với các item (poison, heal, bomb, super-heal), thay vì trực tiếp trừ/cộng máu, game sẽ hiện màn hình đoán từ.

## Gameplay Logic

### Khi Va Chạm với Item
1. Random chọn 1 từ từ `wordsEn.txt` (109,584 từ)
2. Hiện màn hình puzzle với số ô trống = số ký tự của từ
3. Timer countdown: **5 giây × số ký tự** của từ
4. **Gợi ý**: Mỗi 5 giây, hiện 1 ký tự ngẫu nhiên (điểm giảm 1)
5. Player gõ chữ và nhấn Enter để submit

### Scoring
- **Điểm tối đa**: = số ký tự của từ
- **Mỗi gợi ý** (5s): điểm giảm 1
- **Đúng**: Cộng điểm còn lại vào `mark_value`
- **Sai/Hết giờ**: Trừ `word.length() × 5` điểm

### Example
- Từ: `"apple"` (5 ký tự)
- Timer: 25 giây (5×5)
- Điểm ban đầu: 5
- Nếu trả lời sau 12 giây (2 gợi ý): +3 điểm
- Nếu hết giờ: -25 điểm (5×5)

## New Files Added

```
gameSDL2/gameSDL2/
├── PuzzleScreen.h           # Puzzle UI & logic
├── PuzzleScreen.cpp
├── ResourceManager_extra.cpp # Load wordsEn.txt
└── wordsEn.txt              # 109,584 English words
```

## Code Changes

### 1. ResourceManager
- Thêm `std::vector<std::string> words_`
- Method `LoadWordsList()` - load từ file
- Method `GetRandomWord()` - random 1 từ

### 2. PuzzleScreen
- `RunPuzzle(word)` - hiện UI và xử lý input
- Timer countdown (5s/ký tự)
- Auto-reveal hint mỗi 5s
- Keyboard input & validation

### 3. Main Loop (gameSDL2.cpp)
Thay đổi từ:
```cpp
if (p_player.checktaodoc(map_data, BLANK_TAODOC, MOI_TAO_DOC)) {
    mark_value -= 10;  // ❌ Trừ điểm trực tiếp
}
```

Thành:
```cpp
if (p_player.checktaodoc(map_data, BLANK_TAODOC, MOI_TAO_DOC)) {
    std::string word = resManager.GetRandomWord();
    PuzzleResult pr = puzzle.RunPuzzle(word);
    if (pr.solved) {
        mark_value += pr.awardedPoints;  // ✅ Cộng điểm nếu đúng
    } else {
        mark_value -= word.length() * 5;  // ❌ Trừ điểm nếu sai
    }
}
```

## Build Instructions

### Option 1: Visual Studio (Khuyến Nghị)
```
1. Mở gameSDL2.sln
2. Build Solution (F7)
3. Run (F5)
```

### Option 2: Command Line (Developer PowerShell)
```powershell
cd "C:\BaiTap\bloodchess\bloodchess\gameSDL2"

# Find MSBuild
$vs = 'C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe'
$inst = & $vs -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
$msbuild = Join-Path $inst 'MSBuild\Current\Bin\MSBuild.exe'

# Build
& $msbuild gameSDL2.sln /p:Configuration=Release /p:Platform=Win32

# Run
cd Release
.\gameSDL2.exe
```

### Option 3: Automated Script
```powershell
cd "C:\BaiTap\bloodchess\bloodchess"
.\build.ps1 -CopyDLLs
cd gameSDL2\Release
.\gameSDL2.exe
```

## Controls

### During Puzzle
- **Type letters**: Nhập chữ (chỉ a-z)
- **Backspace**: Xóa ký tự
- **Enter**: Submit đáp án
- **ESC**: Hủy (tính là thua)

### Normal Game
- **↑ ↓ ← →**: Di chuyển
- **ESC**: Menu

## Technical Details

### Puzzle UI Layout
```
┌────────────────────────────────────┐
│ Time left: 15s    Points: 3        │  ← Header
│                                    │
│        Guess the Word              │  ← Title
│                                    │
│     ┌───┬───┬───┬───┬───┐         │  ← Input boxes
│     │ a │ p │   │   │   │         │
│     └───┴───┴───┴───┴───┘         │
│                                    │
│  Type and press ENTER to submit   │  ← Hint
└────────────────────────────────────┘
```

### Timer Logic
- Start timer = `word.length() * 5 * 1000` ms
- Every 5 seconds: reveal 1 random hidden letter
- Points decrease by 1 for each reveal
- If time runs out: player loses

### Word Selection
- Random from 109,584 words in `wordsEn.txt`
- Uses `SDL_GetTicks()` for seed
- Case-insensitive matching

## Troubleshooting

### "wordsEn.txt not found"
```
Ensure wordsEn.txt is in the same folder as gameSDL2.exe
Copy from: gameSDL2\gameSDL2\wordsEn.txt
To: gameSDL2\Release\wordsEn.txt
```

### Build Errors
If you see "PuzzleScreen.h not found":
```
1. Right-click project → Add → Existing Item
2. Add PuzzleScreen.h, PuzzleScreen.cpp, ResourceManager_extra.cpp
3. Rebuild
```

### Words Not Loading
Check Output window for:
```
Warning: words list not loaded
```
Make sure `wordsEn.txt` is in working directory.

## Future Enhancements (Optional)

- [ ] Add difficulty levels (word length filter)
- [ ] Show definition after correct answer
- [ ] Multiplayer word battle
- [ ] Leaderboard for fastest solves
- [ ] Custom word lists

## Performance

- Words loaded **once** at startup (fast)
- Puzzle UI renders at 60 FPS
- No lag during gameplay
- Memory efficient (vector of strings)

---

**Chúc bạn chơi game vui vẻ!** 🎮📝
