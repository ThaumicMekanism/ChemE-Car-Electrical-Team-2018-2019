#ifndef Led_h
#define Led_h

class Led {
  public:
    int pin;
    unsigned long duration;
    int numBlinks;
    long offset;
    unsigned long prevTime;
    Led(int _pin, unsigned long _duration,int _numBlinks, long _offset);
};

Led::Led(int _pin, unsigned long _duration,int _numBlinks, long _offset) {
    pin = _pin;
    duration = _duration;
    numBlinks = _numBlinks;
    offset = _offset;
    prevTime = millis();
}

#endif
