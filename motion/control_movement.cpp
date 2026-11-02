
#include <iostream>
#include <chrono>
#include <thread>
#include <lgpio.h>

// BCM GPIO 번호
const int motorPin1 = 5;
const int motorPin2 = 6;
const int enablePin = 18;

// 원래 Arduino PWM 200/255에 해당
const double motorSpeed = 200.0 / 255.0 * 100.0;
const int pwmFrequency = 1000;

int main()
{
    // GPIO 칩 열기 (Raspberry Pi 4 기준)
    int h = lgGpiochipOpen(0);

    if (h < 0) {
        std::cerr << "GPIO 초기화 실패\n";
        return 1;
    }

    // GPIO 출력 설정 및 LOW 초기화
    int result = 0;
    result |= lgGpioClaimOutput(h, 0, motorPin1, 0);
    result |= lgGpioClaimOutput(h, 0, motorPin2, 0);
    result |= lgGpioClaimOutput(h, 0, enablePin, 0);

    if (result < 0) {
        std::cerr << "GPIO 출력 설정 실패\n";
        lgGpiochipClose(h);
        return 1;
    }

    // 1. 전진
    std::cout << "Motor Forward\n";

    lgGpioWrite(h, motorPin1, 1);
    lgGpioWrite(h, motorPin2, 0);

    int pwmResult = lgTxPwm(
        h, enablePin, pwmFrequency,
        motorSpeed, 0, 0
    );

    if (pwmResult < 0) {
        std::cerr << "PWM 시작 실패\n";
    } else {
        std::this_thread::sleep_for(
            std::chrono::seconds(3)
        );
    }

    // 2. 정지
    std::cout << "Motor Stop\n";

    lgTxPwm(h, enablePin, 0, 0, 0, 0);
    lgGpioWrite(h, motorPin1, 0);
    lgGpioWrite(h, motorPin2, 0);

    std::this_thread::sleep_for(
        std::chrono::seconds(5)
    );

    // GPIO 자원 해제
    lgGpiochipClose(h);

    return pwmResult < 0 ? 1 : 0;
}
