#include <DmxMaster.h>

float _speed2;

/*
 * mapping float
 */
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
 * Stringlight class
*/
class Stringlight {

  private:
    int _channel;
    int _maxValue = 255;
    int _minValue = 1;
    float _counter = 0;
    float _speed = 10;

  public:
    Stringlight(int channel, float startValue);
    void update();
    
};

Stringlight::Stringlight(int channel, float startValue)
{
  _channel = channel;
  _counter = startValue;
}

void Stringlight::update()
{

  float sinusCurve = sin(radians(_counter));
  float mapping = mapFloat(sinusCurve, -1, 1, _minValue, _maxValue);

  // send value to dmx
  DmxMaster.write(_channel, mapping);

  

  // update counter
  float speedval = map(_speed2,0,1024,0,100);
  _counter += speedval;

  
  
}

/*
   Arduino sketch
*/



int stringsCount = 10;
int PIstep = 360/stringsCount;

Stringlight sl1(1, PIstep*1);
Stringlight sl2(2, PIstep*2);
Stringlight sl3(3, PIstep*3);
Stringlight sl4(4, PIstep*4);
Stringlight sl5(5, PIstep*5);
Stringlight sl6(6, PIstep*6);
Stringlight sl7(7, PIstep*7);
Stringlight sl8(8, PIstep*8);
Stringlight sl9(9, PIstep*9);
Stringlight sl10(10, PIstep*10);

int value = 0;

void setup() {

  float _speed2 = 0;

  // init dmx shield
  DmxMaster.usePin(3);
  DmxMaster.maxChannel(12);

  // init serial com
  Serial.begin(9600);

}

void loop() {



  _speed2 = analogRead(A0);

  // debug
  //Serial.println( _speed2 );
  
  sl1.update();
  sl2.update();
  sl3.update();
  sl4.update();
  sl5.update();
  sl6.update();
  sl7.update();
  sl8.update();
  sl9.update();
  sl10.update();
  
  delay(100);

}
