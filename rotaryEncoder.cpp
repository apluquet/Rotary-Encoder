//
//  rotaryEncoder.cpp
//

#include "rotaryEncoder.h"

using namespace std;

int guardrail = 100;
int maxTime = 50;

int last1 = 0;
int last2 = 0;

int counter1 = 0;
int counter2 = 0;

int pinClk1 = 0;
int pinClk2 = 0;

static void callback1()
{
    if (millis() - last1 > guardrail)
    {
        last1 = millis();

        int clk = digitalRead(pinClk1);
        int start = millis();
        while (millis() - start < maxTime && !clk)
        {
            clk = digitalRead(pinClk1);
        }

        if (clk)
        {
            cout << "ROTATION 1, " << counter1 << endl;
            counter1++;
        }
    }
}

static void callback2()
{
    if (millis() - last2 > guardrail)
    {
        last2 = millis();

        int clk = digitalRead(pinClk2);
        int start = millis();
        while (millis() - start < maxTime && !clk)
        {
            clk = digitalRead(pinClk2);
        }

        if (clk)
        {
            cout << "ROTATION 2, " << counter2 << endl;
            counter2++;
        }
    }
}

RotaryEncoder::RotaryEncoder(int dataPin, int clkPin, int pushPin, std::string name)
{
    static bool once = false;
    if (!once)
    {
        wiringPiSetupGpio();
        once = true;
    }

    dataPin_ = physPinToGpio(dataPin);
    clkPin_ = physPinToGpio(clkPin);
    pushPin_ = physPinToGpio(pushPin);
    name_ = name;
    setup();
}

void RotaryEncoder::setup()
{
    pinMode(dataPin_, INPUT);
    pinMode(clkPin_, INPUT);
    pinMode(pushPin_, INPUT);
    if (name_ == "1")
    {
        int err = 0;
        err = wiringPiISR(dataPin_, INT_EDGE_RISING, callback1);
        cout << "err CB1 = " << err << endl;
        pinClk1 = clkPin_;
    }
    else if (name_ == "2")
    {
        int err = 0;
        err = wiringPiISR(dataPin_, INT_EDGE_RISING, callback2);
        cout << "err CB2 = " << err << endl;
        pinClk2 = clkPin_;
    }
}
/*
int RotaryEncoder::debounce()
{
    int ret = 0;
    int reading = digitalRead(pushPin_);

    if (reading != lastPushState_)
        lastDebounceTime_ = millis();

    if ((millis() - lastDebounceTime_) >= debounceDelay_)
    {
        if (reading != currentPushState_)
        {
            currentPushState_ = reading;
            if (reading)
            {
                cout << "*clic " << name_ << " *" << endl;
                ret = 2;
            }
            else
            {
                // cout << "*clac " << name_ <<  " *" << endl;
                ret = 1;
            }
        }
    }
    lastPushState_ = reading;
    return ret;
}
*/
int main()
{
    wiringPiSetupGpio();
    RotaryEncoder A = RotaryEncoder(13, 11, 15, "1");
    RotaryEncoder B = RotaryEncoder(22, 31, 7, "2");

    cout << "You can start" << endl;
    int k = 0;
    while (1)
    {
        k++;
        delay(50);
        if (k > 1000)
        {
        }
    }
}
