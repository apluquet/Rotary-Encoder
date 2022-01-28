//
//  rotaryEncoder.h
//

#include <wiringPi.h>
#include <iostream>

class RotaryEncoder
{
public:
    RotaryEncoder(int dataPin, int clkPin, int pushPin, std::string name);

    void setup();
    int debounce();
    //void rotate();
    //void update();
    int  status() const { return direction_;};
    void clearStatus() {direction_ = 0;}

    int lastDataState_ = 0;
    int currentDataState_ = 0;
    int counter_ = 0;

    int lastPushState_ = 0;
    int currentPushState_ = 0;

    int dataPin_; // 11
    int clkPin_;  // 13
    int pushPin_; // 15

    std::string name_;

    unsigned long lastDebounceTime_ = 0;
    unsigned long debounceDelay_ = 50;
    int direction_;
};
