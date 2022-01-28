//
//  .-. . . .-.   .-. . . .-. .-. .
//   |  |-| |-    `-. |\| |-|  |  |
//   '  ' ` `-'   `-' ' ` ` ' `-' `-'
//
//  rotaryEncoder.cpp
//
//  - The Snail -
//
//

#include "rotaryEncoder.h"
#include "snailGlView.h"

using namespace std;
using namespace snail;

int _guardrail = 100;
int _debounce = 150;

int _last1 = 0;
int _last2 = 0;

int _lastClic = 0;

// int _counter1 = 0;
// int _counter2 = 0;

int _clockwise1 = 0;
int _clockwise2 = 0;

static void callbackData1()
{
    if (_clockwise1 == 1 && millis() - _last1 < _guardrail)
        return;

    if (millis() - _last1 > _guardrail)
    {
        _last1 = millis();
        _clockwise1 = -1;
        // _counter1 --;
        GlView::getInstance()->update("r1", -1);
    }
}

static void callbackClk1()
{
    if (_clockwise1 == -1 && millis() - _last1 < _guardrail)
        return;

    if (millis() - _last1 > _guardrail)
    {
        _last1 = millis();
        _clockwise1 = 1;
        // _counter1 ++;
        GlView::getInstance()->update("r1", +1);
    }
}

static void callbackData2()
{
    if (_clockwise2 == 1 && millis() - _last1 > _guardrail)
        return;

    if (!_clockwise2 && millis() - _last2 < _guardrail)
    {
        _last2 = millis();
        _clockwise2 = -1;
        // _counter2 --;
        GlView::getInstance()->update("r2", -1);
    }
}

static void callbackClk2()
{
    if (_clockwise2 == -1 && millis() - _last1 < _guardrail)
        return;
        
    if (_clockwise2 && millis() - _last2 > _guardrail)
    {
        _last2 = millis();
        _clockwise2 = +1;
        // _counter2 ++;
        GlView::getInstance()->update("r2", +1);
    }
}

static void callbackClic()
{
    if (millis() - _lastClic > _debounce)
    {
        _lastClic = millis();
        GlView::getInstance()->update("r2", 0);
        // cout << "clic" << endl;
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
        err = wiringPiISR(dataPin_, INT_EDGE_RISING, callbackData1);
        cout << "err CB1 = " << err << endl;
        err = wiringPiISR(clkPin_, INT_EDGE_RISING, callbackClk1);
        cout << "err CB1 = " << err << endl;
    }
    else if (name_ == "2")
    {
        int err = 0;
        err = wiringPiISR(dataPin_, INT_EDGE_RISING, callbackData2);
        cout << "err CB2 = " << err << endl;
        err = wiringPiISR(clkPin_, INT_EDGE_RISING, callbackClk2);
        cout << "err CB1 = " << err << endl;
        err = wiringPiISR(pushPin_, INT_EDGE_RISING, callbackClic);
        cout << "err CB-clic = " << err << endl;
    }
}
