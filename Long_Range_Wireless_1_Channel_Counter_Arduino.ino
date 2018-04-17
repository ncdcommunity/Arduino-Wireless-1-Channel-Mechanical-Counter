///this code is written and tested for ncd.io IoT Long Range Wireless Push Notification Dry Contact Transmitter with arduino due
///sensor data structure can be found here https://ncd.io/long-range-iot-wireless-push-notification-sensor-product-manual/
/// sensor can be found here https://store.ncd.io/product/iot-long-range-wireless-push-notification-dry-contact-transmitter/

  uint8_t data[29];
  int k = 10;
  int i;
void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("ncd.io IoT Arduino Wireless Push Notification Dry Contact Transmitter");
}

void loop()
{
  
  if (Serial1.available())
  {
    data[0] = Serial1.read();
    delay(k);
   if(data[0]==0x7E)
    {
    while (!Serial1.available());
    for ( i = 1; i< 29; i++)
      {
      data[i] = Serial1.read();
      delay(1);
      }
    if(data[15]==0x7F)  /////// to check if the recive data is correct
      {
  if(data[22]==0x23)  //////// make sure the sensor type is correct
        {  
          long int count_1 = ((data[24]<<24) + (data[25]<<16) + (data[26]<<8) + (data[27])) ;
   float battery = ((data[18] * 256) + data[19]);
  float voltage = 0.00322 * battery;
  Serial.print("Sensor Number  ");
  Serial.println(data[16]);
  Serial.print("Sensor Type  ");
  Serial.println(data[22]);
  Serial.print("Firmware Version  ");
  Serial.println(data[17]);
  Serial.print("Number of counts on Channel One :");
  Serial.print(count_1);
  Serial.print("ADC value:");
  Serial.println(battery);
  Serial.print("Battery Voltage:");
  Serial.print(voltage);
  Serial.println("\n");
  if (voltage < 1)
          {
    Serial.println("Time to Replace The Battery");
          }
  
        }
      }
else
{
      for ( i = 0; i< 29; i++)
    {
      Serial.print(data[i]);
      Serial.print(" , ");
      delay(1);
    }
}
    }
  }
 
}
