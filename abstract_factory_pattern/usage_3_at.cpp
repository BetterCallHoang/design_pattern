// ===== Abstract Products =====
class SPI { public: virtual void init() = 0; };
class UART { public: virtual void init() = 0; };

// ===== Concrete Products =====
class STM32_SPI : public SPI {
public:
    void init() override { std::cout << "STM32 SPI init\n"; }
};

class STM32_UART : public UART {
public:
    void init() override { std::cout << "STM32 UART init\n"; }
};

class Zynq_SPI : public SPI {
public:
    void init() override { std::cout << "Zynq SPI init\n"; }
};

class Zynq_UART : public UART {
public:
    void init() override { std::cout << "Zynq UART init\n"; }
};

// ===== Abstract Factory =====
class HardwareFactory {
public:
    virtual SPI* createSPI() = 0;
    virtual UART* createUART() = 0;
};

// ===== Concrete Factories =====
class STM32Factory : public HardwareFactory {
public:
    SPI* createSPI() override { return new STM32_SPI(); }
    UART* createUART() override { return new STM32_UART(); }
};

class ZynqFactory : public HardwareFactory {
public:
    SPI* createSPI() override { return new Zynq_SPI(); }
    UART* createUART() override { return new Zynq_UART(); }
};

// ===== Client =====
int main() {
    HardwareFactory* factory = new ZynqFactory();

    SPI* spi = factory->createSPI();
    UART* uart = factory->createUART();

    spi->init();
    uart->init();
}