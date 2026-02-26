/*Trường hợp 3: Hardware abstraction (ví dụ MCU vs Zynq)

Giả sử bạn có 2 nền tảng:

- STM32

- Zynq

Mỗi nền tảng có:

- SPI

- UART

- Timer

❌ Không dùng Abstract Factory

Client phải tạo từng driver cụ thể:
Nếu chuyển sang Zynq → sửa khắp nơi.*/
SPI* spi = new STM32_SPI();
UART* uart = new STM32_UART();