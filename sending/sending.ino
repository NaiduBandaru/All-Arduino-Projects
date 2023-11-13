#include <SoftwareSerial.h>
SoftwareSerial sgsm(2, 3);

void setup()
{
  sgsm.begin(9600);
}

void loop()
{
  if(sgsm.available()) {  // check if message is available
    String message = sgsm.readString();  // read the message
    
    if(message.startsWith("LOC")) {  // check if message starts with "LOC:"
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      
      sgsm.print("AT+CMGS=\"+919985172319\"\r");
      delay(1000);
      
      sgsm.print("Location:");
      delay(1000);
      
      sgsm.write(0x1A);
      delay(10000);
    }
  }
}
