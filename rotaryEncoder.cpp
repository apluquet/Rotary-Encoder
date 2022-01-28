//
//  rotaryEncoder.cpp
//

#include "rotaryEncoder.h"

using namespace std;

int _guardrail = 100;
int _maxTime = 50;

int _last1 = 0;
int _last2 = 0;

int _counter1 = 0;
int _counter2 = 0;

int _pinClk1 = 0;
int _pinClk2 = 0;

static void callback1()
{
    if (millis() - _last1 > _guardrail)
    {
        _last1 = millis();

        int clk = digitalRead(_pinClk1);
        int start = millis();
        int flag = 0;
        while (millis() - start < _maxTime && !clk)
        {
            clk = digitalRead(_pinClk1);
            flag = 1;
        }

        if (clk && flag)
        {
            _counter1--;
            cout << "ROTATION 1, " << _counter1 << endl;
        }
        else
        {
            _counter1++;
            cout << "ROTATION 1, " << _counter1 << endl;
        }
    }
}

static void callback2()
{
    if (millis() - _last2 > _guardrail)
    {
        _last2 = millis();

        int clk = digitalRead(_pinClk2);
        int start = millis();
        int flag = 0;
        while (millis() - start < _maxTime && !clk)
        {
            clk = digitalRead(_pinClk2);
            flag = 1;
        }

        if (clk && flag == 1)
        {
            _counter2--;
            cout << "ROTATION 2, " << _counter2 << endl;
        }
        else if (clk && flag == 2)
        {
            _counter2++;
            cout << "ROTATION 2, " << _counter2 << endl;
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
        _pinClk1 = clkPin_;
    }
    else if (name_ == "2")
    {
        int err = 0;
        err = wiringPiISR(dataPin_, INT_EDGE_RISING, callback2);
        cout << "err CB2 = " << err << endl;
        _pinClk2 = clkPin_;
    }
}

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
