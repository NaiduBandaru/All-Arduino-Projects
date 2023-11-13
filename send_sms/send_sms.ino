*    
 *   Author@ExploreEmbedded 
 *   Example to Send messages Interactively using GSM SIM800L
 *    
 *   LIBRARY CREDITS:
 *   Thanks to Cristian Steib(steibkhriz@gmail.com) for the library.
 *    
 *  
 *     
 *      PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO &gt;&gt;&gt;   SIM800L  |
 *        -----------------------------
 *            GND      &gt;&gt;&gt;   GND
 *        RX   2       &gt;&gt;&gt;   TX    
 *        TX   3       &gt;&gt;&gt;   RX
 *       RESET 8       &gt;&gt;&gt;   RST 
 *                 
 *  
*/

#include &lt;Sim800l.h&gt;
#include &lt;SoftwareSerial.h&gt; //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library
char text[161]=""; //buffer to store message
char number[11]=""; //phone number to send message
int cnt;
bool error; //to catch the response of sendSms

void setup(){
      Sim800l.begin(); // initializate the library. 
    Serial.begin(9600);
}

void loop(){

      //Read the Number
        Serial.print("\nEnter 10 digit Phone Number:");
      while(Serial.available()&lt;=0); 
      cnt = Serial.readBytesUntil('\n',number, 11);
      number[cnt] = '\0';
      Serial.println(number);

      //clear the serial input buffer so that no typed characters are pending
            
      delay(1000); //delay required before clearing the input buffer
      while(Serial.available()&gt;0) //clear buffer
      {
        Serial.read();
      }


      //Read the Message to be sent
      Serial.print("Enter Message:");
      while(Serial.available()&lt;=0); 
      cnt = Serial.readBytesUntil('\n',text, 160);
      text[cnt] = '\0';
      Serial.println(text);
      delay(1000);

      while(Serial.available()&gt;0) //clear buffer
      {
        Serial.read();
      }
  
      //Send the message and display the status
      error = Sim800l.sendSms(number,text);
      if(error)
      Serial.println("Error Sending Message");
      Serial.println("Message Sent Successfully!");

      
}

//Thanks to Cristian Steib for the SIM800l library.
