# Hệ Thống Quản Lý Ký Túc Xá - Phía Sinh Viên

## Tổng quan
Đây là phần sinh viên của hệ thống quản lý ký túc xá, được phát triển bởi **Bùi Quang Sanh** (102240108).

## Các chức năng đã hoàn thành

### ✅ 2.1. Quản lý thông tin cá nhân
- **2.1.1** Xem và chỉnh sửa thông tin cá nhân
- **2.1.2** Xem lịch sử hợp đồng và hóa đơn  
- **2.1.3** Xem trạng thái phòng hiện tại

### ✅ 2.2. Đăng ký phòng – đổi phòng – trả phòng
- Xem danh sách phòng trống
- Đăng ký phòng mới (tạo hợp đồng tự động)
- Kiểm tra trạng thái phòng đã đăng ký

### ✅ 2.3. Thanh toán và tra cứu
- **2.3.1** Xem hóa đơn hàng tháng (tiền phòng, điện, nước, internet)
- **2.3.2** Báo thanh toán trực tiếp
- **2.3.3** Xem lịch sử thanh toán

### ✅ 2.4. Yêu cầu dịch vụ
- **2.4.1** Gửi yêu cầu sửa chữa, bảo trì (điện, nước, internet, bảo trì phòng)

## Cấu trúc Code

### Models
- **User**: Quản lý thông tin người dùng
- **Payment**: Quản lý hóa đơn và thanh toán
- **Room**: Quản lý thông tin phòng
- **Contract**: Quản lý hợp đồng thuê phòng

### Menu System
- **MainMenu**: Menu chính (đăng nhập/đăng ký)
- **StudentMenu**: Menu dành cho sinh viên
- **AuthSystem**: Hệ thống xác thực

### Data Files
- `data/accounts.txt`: Tài khoản người dùng
- `data/information.txt`: Thông tin chi tiết sinh viên
- `data/contracts.txt`: Hợp đồng thuê phòng
- `data/payments.txt`: Hóa đơn và thanh toán
- `data/rooms.txt`: Danh sách phòng
- `data/service_requests.txt`: Yêu cầu dịch vụ

## Cách sử dụng

### Build & Run
```bash
# Build project
g++ -std=c++17 -g src/Main.cpp src/AuthSystem.cpp src/AdminMenu.cpp src/StudentMenu.cpp src/MainMenu.cpp src/models/User.cpp src/models/Room.cpp src/models/Payment.cpp -o build/out.exe -I include

# Run
./build/out.exe
```

### Test Account
- **Username**: `sanh`
- **Password**: `123456`
- **Role**: Student

### Demo Features

1. **Đăng nhập** với tài khoản test
2. **Xem thông tin cá nhân**: Menu option 1
3. **Xem hóa đơn**: Menu option 4
4. **Thanh toán**: Menu option 5 (chọn hóa đơn chưa thanh toán)
5. **Đăng ký phòng**: Menu option 7 (nếu chưa có phòng)
6. **Yêu cầu dịch vụ**: Menu option 8

## Tính năng nổi bật

### 💰 Hệ thống thanh toán hoàn chỉnh
- Hiển thị hóa đơn chi tiết (phòng, điện, nước, internet)
- Tự động tính tổng tiền
- Lưu lịch sử thanh toán

### 🏠 Quản lý phòng thông minh
- Kiểm tra phòng trống tự động
- Cập nhật số lượng người ở
- Hiển thị thông tin phòng chi tiết

### 🔧 Yêu cầu dịch vụ
- Nhiều loại yêu cầu (điện, nước, internet, bảo trì)
- Phân loại mức độ khẩn cấp
- Tracking status

### 📊 Báo cáo & Thống kê
- Lịch sử thanh toán
- Tổng tiền đã thanh toán
- Trạng thái hợp đồng

## Sample Data

### Phòng có sẵn:
- **A102**: Tòa A, tầng 1, 2 người, 1,500,000 VND/tháng (trống)
- **B101**: Tòa B, tầng 1, 1 người, 1,200,000 VND/tháng (trống)
- **C102**: Tòa C, tầng 1, 4 người, 2,000,000 VND/tháng (trống)

### Hóa đơn mẫu cho MSSV 102240108:
- **Tháng 09/2025**: 1,780,000 VND (chưa thanh toán)
- **Tháng 10/2025**: 1,795,000 VND (đã thanh toán)

## Kiến trúc & Design Patterns

- **MVC Pattern**: Tách biệt Model, View, Controller
- **File-based Database**: Sử dụng text files cho persistence
- **Object-Oriented Design**: Classes với encapsulation đầy đủ
- **Error Handling**: Validation input và file operations

## Tương lai phát triển

- [ ] Thêm chức năng đổi phòng
- [ ] Thêm chức năng trả phòng
- [ ] Payment gateway integration
- [ ] Email notifications
- [ ] Mobile app support

---
**Được phát triển bởi**: Bùi Quang Sanh - MSSV: 102240108
**Ngành**: Công nghệ thông tin
**Lớp**: 24.10A