//
//    FILE: AS5600_position.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AS5600
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.


#include "AS5600.h"

//  select right class.
//  AS5600 as5600;   //  use default Wire
AS5600L as5600;   //  use default Wire


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  Wire.begin(1, 0, 400000);//arg1: sda, arg2: scl, arg3:clock

  // as5600.begin(4);  //  set direction pin.
  // as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.
  Serial.print("set before");
  Serial.println(as5600.getAddress());

  as5600.setAddress(0x36);  //  AS5600L only
  Serial.print("after setting");
  Serial.println(as5600.getAddress());

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
  while(!as5600.isConnected());


  delay(1000);
}


void loop()
{
  static uint32_t lastTime = 0;

  //  set initial position
  as5600.getCumulativePosition();

  //  update every 100 ms
  //  should be enough up to ~200 RPM
  if (millis() - lastTime >= 100)
  {
    lastTime = millis();
    Serial.print(as5600.getCumulativePosition());
    Serial.print("\t");
    Serial.println(as5600.getRevolutions());
  }

  //  just to show how reset can be used
  if (as5600.getRevolutions() >= 10)
  {
    as5600.resetPosition();
  }
}


//  -- END OF FILE --

