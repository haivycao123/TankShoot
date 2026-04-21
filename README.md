# TankShoot

TankShoot là game bắn súng 2D được xây dựng bằng C++ và SFML trong khuôn khổ đồ án thực hành cuối kỳ của nhóm `Nine`. Người chơi điều khiển xe tăng, tiêu diệt các đợt kẻ địch và sống sót đến khi hạ được boss cuối `AirCraft`.

README này được viết dựa trên việc phân tích source code của project và đối chiếu với nội dung chính đọc được từ báo cáo đính kèm.

## Tổng quan

- Ngôn ngữ: `C++17`
- Framework đồ họa/âm thanh: `SFML`
- Môi trường phát triển: `Visual Studio 2022`
- Kiểu game: `2D shooter / boss fight`
- Kích thước màn hình mặc định: `1280 x 720`

## Gameplay

Người chơi bắt đầu ở màn hình intro, sau đó đi qua menu chính để vào trận. Trong màn chơi, xe tăng của người chơi chỉ di chuyển theo trục ngang ở cuối màn hình, bắn đạn lên phía trên để tiêu diệt kẻ địch.

Game có nhiều loại enemy:

- `MineTrap`: bẫy mìn lao thẳng xuống, gây sát thương khi va chạm.
- `TankEnemy`: xe tăng địch di chuyển xuống và bắn đạn thường.
- `Plane`: máy bay di chuyển ngang và bắn từ phía trên.
- `ArmoredTank`: xe tăng giáp dày, nhiều máu hơn và di chuyển zig-zag.
- `AirCraft`: boss cuối với `150 HP`, có nhiều kiểu tấn công và xuất hiện sau một khoảng thời gian.

Boss `AirCraft` có 3 kiểu tấn công chính:

- Bắn đơn.
- Bắn 3 viên cùng lúc.
- Bắn laser có giai đoạn cảnh báo trước.

Khi HP boss xuống thấp, game sẽ sinh thêm quái phụ để tăng độ khó. Người chơi thắng khi boss bị tiêu diệt và thua khi HP về `0`.

## Điều khiển

- `Left` / `Right`: di chuyển sang trái / phải
- `Space` hoặc chuột trái: bắn đạn thường
- `Enter` hoặc chuột phải: dùng kỹ năng
- `Esc` hoặc nút pause trên giao diện: tạm dừng game

## Cơ chế nổi bật

- Player có `3 HP` và trạng thái bất tử tạm thời sau khi trúng đạn.
- Kỹ năng của người chơi có cooldown dài (`60s`) và có thể quét sạch phần lớn enemy thường.
- Hệ thống va chạm xử lý:
  - đạn người chơi với enemy
  - enemy với player
  - đạn địch với player
  - đạn người chơi với đạn địch
- Có hiệu ứng nổ, âm thanh bắn, âm thanh laser, âm nhạc nền và màn hình kết thúc thắng/thua.
- UI hiển thị `HP` và trạng thái `SKILL`.

## Luồng màn hình

Project được tổ chức theo mô hình state machine với các màn hình chính:

- `GSIntro`: màn hình mở đầu
- `GSMenu`: menu chính
- `GSPlay`: gameplay chính
- `GSSetting`: bật/tắt âm lượng
- `GSAbout`: thông tin nhóm thực hiện
- `GSPause`: tạm dừng
- `GSEnd`: màn hình thắng/thua

## Kiến trúc mã nguồn

```text
TankShoot/
|-- Configuration/        # Hằng số game
|-- CoreEngine/           # Application, GameStateBase, GameStateMachine
|-- GameObject/           # Player, Enemy, Bullet, Boss, Spawner...
|-- GameState/            # Các màn hình/state của game
|-- ResourceManagement/   # Texture, font, sound, UI
|-- Utility/              # Collision, button, explosion, singleton...
```

Các thành phần đáng chú ý:

- `Application`: tạo cửa sổ, chạy game loop, cập nhật và render.
- `GameStateMachine`: quản lý chuyển state.
- `ResourceManager`: nạp texture/font từ thư mục `Data/`.
- `SoundManager`: quản lý sound effect và nhạc nền.
- `Spawner`: sinh enemy ban đầu và enemy ngẫu nhiên theo thời gian.
- `CollisionManager`: xử lý toàn bộ va chạm trong gameplay.

## Tài nguyên dự án

- `Data/Texture`: ảnh giao diện, sprite player, enemy, boss, bullet...
- `Data/Sound`: hiệu ứng âm thanh
- `Data/Music`: nhạc nền
- `Data/Font`: font chữ giao diện
- `SFML/`: thư viện SFML được đặt kèm trong repo

Project hiện cũng đang chứa sẵn file build debug tại `Debug/TankShoot.exe`.

## Cách build và chạy

### Cách 1: Chạy bản đã build sẵn

Mở file:

```text
Debug/TankShoot.exe
```

Lưu ý: game cần giữ đúng cấu trúc thư mục `Data/` để nạp tài nguyên.

### Cách 2: Build bằng Visual Studio

1. Mở `TankShoot.sln` bằng `Visual Studio 2022`.
2. Chọn cấu hình build phù hợp, ưu tiên `Debug | x64`.
3. Build solution.
4. Chạy project `TankShoot`.

## Yêu cầu môi trường

- Windows
- Visual Studio 2022
- MSVC toolset `v143`
- SFML được tham chiếu trong project

Trong repo hiện đã có thư mục `SFML`, header, library và DLL cần thiết để chạy project.

## Thông tin nhóm

Theo báo cáo và màn hình `About` trong game, project được thực hiện bởi nhóm `Nine` với các thành viên:

- Cao Hai Vy
- Nguyen Lam Thao Trang
- Nguyen Cao Tri
- Nguyen Son Truong

## Gợi ý cải thiện thêm

- Chuẩn hóa đường dẫn SFML trong file `.vcxproj` để dễ build trên máy khác.
- Bổ sung ảnh chụp gameplay vào README.
- Viết thêm hướng dẫn đóng gói bản release.
- Tách rõ phần gameplay config ra file dữ liệu ngoài code.

## File chính

- Solution: `TankShoot.sln`
- Entry point: `TankShoot/TankShoot.cpp`
- Gameplay chính: `TankShoot/GameState/GSPlay.cpp`
- Cấu hình game: `TankShoot/Configuration/GameConfig.h`

