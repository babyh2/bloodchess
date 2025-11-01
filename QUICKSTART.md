# QUICK START GUIDE - Blood Chess

## 🚀 Cách Nhanh Nhất Để Chạy Game

### Option 1: PowerShell Build Script (KHUYẾN NGHỊ)
```powershell
# Mở PowerShell trong folder bloodchess
cd C:\BaiTap\bloodchess\bloodchess

# Build và copy DLLs tự động
.\build.ps1 -CopyDLLs

# Chạy game
cd gameSDL2\Release
.\gameSDL2.exe
```

### Option 2: Visual Studio (Dễ Nhất)
```
1. Double-click: gameSDL2\gameSDL2.sln
2. Nhấn F5
```

### Option 3: Command Line Build
```powershell
cd C:\BaiTap\bloodchess\bloodchess\gameSDL2
msbuild gameSDL2.sln /p:Configuration=Release
cd Release
.\gameSDL2.exe
```

## ⚡ Nếu Gặp Lỗi

### "SDL2.dll not found"
```powershell
# Copy DLLs
copy LibSdl2\Dll\X86\*.dll gameSDL2\Release\
```

### "Failed to load resources"
```
Đảm bảo có các file trong folder Release:
- Dreams.ttf
- dennham.jpg
- menuchinh.png, shop.png, win.png, loss.png
- Folder img/ với player sprites
- Folder map/ với tile images
```

### Game lag/slow
```
1. Build Release (không phải Debug)
2. Đóng các chương trình khác
3. Check FRAME_PER_SECOND = 60 trong Commonfunc.h
```

## 🎮 Điều Khiển Game

```
↑ ↓ ← →    : Di chuyển
ESC        : Menu / Skip message
Mouse      : Click menu
```

## 📖 Tài Liệu Chi Tiết

- **OPTIMIZATION_GUIDE.md**: Tất cả thay đổi tối ưu hóa
- **README.md**: Hướng dẫn đầy đủ
- Inline code comments: Giải thích logic

## ✅ Các Cải Tiến Chính

✅ FPS: 20 → **60** (+240%)  
✅ Player speed: 1 → **2** (responsive hơn)  
✅ Resource loading: Tối ưu, zero lag  
✅ Memory leaks: Fixed  
✅ Code quality: Refactored, cleaner  

---

**Chúc bạn chơi game vui vẻ!** 🎮
