# HIGH STRIKER

Báo cáo môn học Hệ Nhúng - IT4210

## GIỚI THIỆU

__Đề bài__: Xây dựng phần cứng và phần mềm mô phỏng trò chơi High Striker. Hệ thống cho phép đo lực tối đa mà người dùng tác động lên cảm biến, hiển thị qua cột LED và hiển thị trên màn hình. Lưu và hiển thị giá trị kỷ lục.\
Đo lực: dùng load cell. Chú ý cần đo đủ nhanh.\
Hiển thị: LED bar nằm dọc + màn hình trên kit STM32.

__Sản phẩm:__
1. Hiển thị điểm hiện tại người chơi
2. Lưu trữ điểm cao nhất
3. Reset lượt chơi bằng nút bấm user button
4. Giao diện đồ họa đẹp mắt
5. Hiển thị lên màn hình Your Score và Best Score và hiệu ứng khi chơi
- Ảnh chụp minh họa:\
  ![Ảnh minh họa](https://github.com/phandungnc/High_Striker_Lavie/blob/main/anh%20minh%20hoa.jpg)

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

__Mô tả các thành phần phần cứng__

- STM32F429ZIT6: bo mạch điều khiển chính, xử lý logic, giao tiếp phần cứng
- HX711: khuếch đại tín hiệu từ loadcell, chuyển sang tín hiệu số gửi vào vi điều khiển
- Loadcell: cảm biến lực khi có tác động
- Dây nối: Kết nối giữa các thiết bị
__Mô tả các thành phần phần mềm__

- STM32CubeIDE: viết và quản lý code, hỗ trợ build, debug, nạp code vào MCU
- TouchGFX: Thiết kế giao diện, hiệu ứng, hiển thị điểm, gen code tự động
- Firmware C/C++: xử lý giá trị đọc từ HX711, tính toán điểm và hiển thị lên màn hình
### ĐẶC TẢ HÀM

- Hàm đọc dữ liệu từ HX711
  ```C
     /**
      *  @param  GPIOx_SCK Loại chân 
      *  @param  SCK_Pin Số thứ tự chân
      *  @param  GPIOx_DOUT Loại chân
      *  @param  DOUT_Pin Số thứ tự chân
      */
     int32_t HX711_ReadData(GPIO_TypeDef* GPIOx_SCK, uint16_t SCK_Pin, GPIO_TypeDef* GPIOx_DOUT, uint16_t DOUT_Pin)
  ```
- Hàm cập nhật điểm hiện tại
  ```C
     /**
      *  @param  value Giá trị điểm
      */
     update_score_from_sensor(int value)
  ```
- Hàm cập nhật điểm cao nhất
  ```C
     /**
      *  @param  value Giá trị điểm
      */
     update_highScore_from_sensor(int value)
  ```
- Hàm xử lý bật, tắt hiệu ứng giao diện
   ```C
     /**
      *  
      */
     void Screen1View::handleTickEvent()
  ```
-  Hàm quản lý hiển thị điểm và hiệu ứng lên màn hình
   ```C
     /**
      *  
      */
     void Model::tick()
  ```
### KẾT QUẢ
Link demo: https://www.youtube.com/shorts/O6ix2_2aoTM
