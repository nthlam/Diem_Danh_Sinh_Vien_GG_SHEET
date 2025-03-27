# Hệ Thống Điểm Danh RFID với ESP32

## Giới thiệu
Đây là dự án sử dụng **ESP32**, **RFID RC522** và **Google Sheets API** để xây dựng hệ thống điểm danh sinh viên tự động.
[Video Demo](https://youtu.be/OQ0Rh2ILLfk?si=pBxmc4a9zhQPHQav)
![Image](https://github.com/user-attachments/assets/ae2872ec-c935-4463-be16-a7300f4cbb5e)
## Chức năng chính
- Quét thẻ RFID để nhận diện sinh viên.
- Gửi dữ liệu điểm danh lên **Google Sheets**.
- Chuyển đổi trạng thái **Vào/Ra** bằng nút nhấn.
- Hiển thị trạng thái bằng đèn LED và âm thanh buzzer.

## Phần cứng yêu cầu
- **ESP32**
- **Module RFID RC522**
- **Buzzer, LED, nút nhấn**
- **Kết nối WiFi**

## Cách sử dụng
### 1. Kết nối phần cứng
Sơ đồ kết nối (ESP32 - RFID):

- SS_PIN -> GPIO16 
- RST_PIN -> GPIO17 
- Buzzer -> GPIO5 
- LED (check) -> GPIO4 
- Button -> GPIO15

### 2. Cấu hình WiFi & Google Sheets
- **Chỉnh sửa WiFi**:
  ```cpp
  const char* ssid = "Tên_WiFi";
  const char* password = "Mật_Khẩu";
### 3. Cài đặt thư viện (Arduino)
- MFRC522 (RFID)
- WiFi (ESP32)
- HTTPClient (Gửi request)

### 4.  Nạp code vào ESP32



