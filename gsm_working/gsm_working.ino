#include <SoftwareSerial.h>
SoftwareSerial sgsm(2, 3);
void setup()
{
  sgsm.begin(9600);
}
void loop()
{
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      /*Replace XXXXXXXXXX to 10 digit mobile number &
        ZZ to 2 digit country code*/
      sgsm.print("AT+CMGS=\"+919985172319\"\r");
      delay(1000);
      //The text of the message to be sent.
      sgsm.print("Location:");
      delay(1000);
      sgsm.write(0x1A);
      delay(10000);
  }
