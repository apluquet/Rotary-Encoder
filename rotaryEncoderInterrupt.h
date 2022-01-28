//
//  .-. . . .-.   .-. . . .-. .-. .
//   |  |-| |-    `-. |\| |-|  |  |
//   '  ' ` `-'   `-' ' ` ` ' `-' `-'
//
//  rotaryEncoder.h
//
//  - The Snail -
//
//

#ifndef _SNAIL_ROTARY_ENCODER_H_
#define _SNAIL_ROTARY_ENCODER_H_

#include <wiringPi.h>
#include <iostream>
#include "controller.h"

class RotaryEncoder : public snail::Observable
{
public:
    RotaryEncoder(int dataPin, int clkPin, int pushPin, std::string name);

    void setup();
    int  status() const { return direction_;};
    void clearStatus() {direction_ = 0;}

    int lastDataState_ = 0;
    int currentDataState_ = 0;
    int counter_ = 0;

    int lastPushState_ = 0;
    int currentPushState_ = 0;

    int dataPin_;
    int clkPin_;
    int pushPin_;

    std::string name_;

    unsigned long lastDebounceTime_ = 0;
    unsigned long debounceDelay_ = 50;
    int direction_;
};

#endif // _SNAIL_ROTARY_ENCODER_H_
