//
//  rotaryEncoder.cpp
//

#include "rotaryEncoder.h"

using namespace std;

static int _t1 = 0;
static int _turning1 = 0;
static int _t2 = 0;
static int _turning2 = 0;
static unsigned long _debounceDelay_ = 50;

static void data1_callback()
{
	if (!_turning1)
	{	
		_turning1 = -1;
		_t1 = millis();
		return;
	}
	//clock before!
	if ( millis() - _t1 > _debounceDelay_ )
	{
		//GlView::getInstance()->update("r1", -1);
        cout << "turning 1 left" << endl;
		_turning1 = 0;
		_t1 = 0;
		
	}
}

static void clock1_callback()
{
	if (!_turning1)
	{	
		_turning1 = 1;
		_t1 = millis();
		return;
	}
	//data before!
	if ( millis() - _t1 > _debounceDelay_ )
	{
		//GlView::getInstance()->update("r1", 1);
        cout << "turning 1 right" << endl;
		_turning1 = 0;
		_t1 = 0;
	}
}

static void data2_callback()
{
	if (!_turning2)
	{	
		_turning2 = -1;
		_t2 = millis();
		return;
	}
	//clock before!
	if ( millis() - _t2 > _debounceDelay_ )
	{
        //GlView::getInstance()->update("r2", -1);
        cout << "turning 2 left" << endl;
		_turning2 = 0;
		_t2 = 0;
	}
}

static void clock2_callback()
{
	if (!_turning2)
	{	
		_turning2 = 1;
		_t2 = millis();
		return;
	}
	//data before!
	if ( millis() - _t2 > _debounceDelay_ )
	{
		//GlView::getInstance()->update("r2", 1);
        cout << "turning 2 right" << endl;
		_turning2 = 0;
		_t2 = 0;
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
    if ( name_ == "1" )
    {
    	int err = 0;
    	err = wiringPiISR(dataPin_,INT_EDGE_RISING,data1_callback); 
    	cout << err << endl;
    	err = wiringPiISR(clkPin_,INT_EDGE_RISING,clock1_callback);
    	cout << err << endl; 
    }
    else if ( name_ == "2" )
    {
    	int err = 0;
    	err = wiringPiISR(dataPin_,INT_EDGE_RISING,data2_callback); 
    	cout << err << endl;
    	err = wiringPiISR(clkPin_,INT_EDGE_RISING,clock2_callback); 
    	cout << err << endl;
    }
}

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
/*
void RotaryEncoder::rotate()
{
    if (lastDataState_ == 0 && currentDataState_ == 1)
    {
        counter_--;
        cout << "counter " << name_ << " = " << counter_ << endl;
        direction_ = -1;
    }

    if (lastDataState_ == 1 && currentDataState_ == 0)
    {
        counter_++;
        cout << "counter " << name_ << " = " << counter_ << endl;
        direction_ = 1;
    }
}*/

int main()
{
    wiringPiSetupGpio();
    RotaryEncoder A = RotaryEncoder(13, 11, 15, "A");
    RotaryEncoder B = RotaryEncoder(22, 31, 7, "B");

    A.setup();
    B.setup();

    cout << "You can start" << endl;

    while (1)
    {}
}

