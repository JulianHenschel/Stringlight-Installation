#include <DmxMaster.h>

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
    int _minValue = 0;
    int _direction = 1;
    float _counter = 0;
    float _speed = 0.25;

  public:
    Stringlight(int channel, float startValue);
    void update();
    void setValue(int brightness);

};

Stringlight::Stringlight(int channel, float startValue)
{
  _channel = channel;
  _counter = startValue;
}

void Stringlight::update()
{

  float sinusCurve = sin(radians(_counter));
  int mapping = mapFloat(sinusCurve, -1, 1, 0, 255);

  // send value to dmx
  setValue(mapping);

  // debug
  //Serial.println( mapping );

  // update counter
  _counter += _speed;
  
}

void Stringlight::setValue(int brightness)
{
  DmxMaster.write(_channel, brightness);
}

/*
   Arduino sketch
*/
Stringlight sl1(1, 0);
Stringlight sl2(2, 10);

void setup() {

  // init dmx shield
  DmxMaster.usePin(3);
  DmxMaster.maxChannel(4);

  // init serial com
  Serial.begin(9600);

}

void loop() {

  sl1.update();
  sl2.update();

  delay(50);

}
