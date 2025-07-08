# HIGH STRIKER

Báo cáo môn học Hệ Nhúng - IT4210

## GIỚI THIỆU

__Đề bài__: Xây dựng phần cứng và phần mềm mô phỏng trò chơi High Striker. Hệ thống cho phép đo lực tối đa mà người dùng tác động lên cảm biến, hiển thị qua cột LED và hiển thị trên màn hình. Lưu và hiển thị giá trị kỷ lục.
Đo lực: dùng load cell. Chú ý cần đo đủ nhanh.
Hiển thị: LED bar nằm dọc + màn hình trên kit STM32.

__Sản phẩm:__
1. Hiển thị điểm hiện tại người chơi
2. Lưu trữ điểm cao nhất
3. Reset lượt chơi bằng nút bấm user button
4. Giao diện đồ họa đẹp mắt
5. Hiển thị lên màn hình Your Score và Best Score và hiệu ứng khi chơi
- Ảnh chụp minh họa:\
  ![Ảnh minh họa](https://soict.hust.edu.vn/wp-content/uploads/logo-soict-hust-1-1024x416.png)

## TÁC GIẢ

- Tên nhóm: Lavie
- Thành viên trong nhóm
  |STT|Họ tên|MSSV|Công việc|
  |--:|--|--|--|
  |1|Trần Đình Đạt|20225279|Xử lý truyền qua UART|
  |2|Phan Đức Dũng|20225294|Thiết kế giao diện và xử lý hiển thị|
  |3|Nguyễn Kiến Quốc|20225153|Xử lý điểm hiện tại, điểm cao nhất|

## MÔI TRƯỜNG HOẠT ĐỘNG

- STM32F429ZIT6
- Cảm biến lực load cell
- HX711 đọc tín hiệu từ cảm biến lực

## SƠ ĐỒ SCHEMATIC

![image](https://github.com/user-attachments/assets/f15f7379-09bf-472a-b0d9-4de6d32a6ec0)

### TÍCH HỢP HỆ THỐNG

- Mô tả các thành phần phần cứng 
- Mô tả các thành phần phần mềm

### ĐẶC TẢ HÀM

- Giải thích một số hàm quan trọng: ý nghĩa của hàm, tham số vào, ra

  ```C
     /**
      *  Hàm tính ...
      *  @param  x  Tham số
      *  @param  y  Tham số
      */
     void abc(int x, int y = 2);
  ```
  
### KẾT QUẢ

- Các ảnh chụp với caption giải thích.
- Hoặc video sản phẩm
