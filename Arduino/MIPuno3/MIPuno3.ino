
//All methods
/*
 * ParseHeader
 */

//Including libraries
#include <SPI.h>
#include <Ethernet.h>

//Declaring pins
//Ethernet shield at pins 10 through 13

//Declaring some variables
IPAddress ip(192, 168, 1, 3);
char buffer[100];  
String httpHeader;        
int arg = 0;
int val = 0; 

//Declaring some hardware
EthernetServer server(80);

//Declaring some arrays
byte mac[] = 
{ 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED 
};  

void setup() 
{
  Serial.begin(9600);
  Serial.println("Arduino UNO 3 Start");

  DDRD = 0xFC;     
  DDRB = 0x3F;

  //Setting up some hardware
  Ethernet.begin(mac, ip);
  server.begin();
   
  Serial.print("Server is at "); 
  Serial.println(Ethernet.localIP());
}


void loop() 
{
  Serial.println("-------------------------------------------------");
  Serial.println();
  Serial.println("Restart loop");
  Serial.println();
  
  EthernetClient client = server.available(); 

  if (client) 
  {
    Serial.println("New client connected");
    
    boolean currentLineIsBlank = true;
    
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
     
        if (httpHeader.length() < maxLength) 
        {
          httpHeader += c;
        }
        
        if (c == '\n' && currentLineIsBlank) 
        {
          httpHeader.replace(" HTTP/1.1", ";");          
          httpHeader.trim();                             
          Serial.println(httpHeader);                         
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");   
          client.println("Refresh: 3");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<HTML>");
          client.println("<HEAD><TITLE>Hoogen-hooft</TITLE></HEAD>");
          client.println("<STYLE> body{width:1280px;font-family:verdana;background-color:LightBlue;} ");
          client.println("</STYLE>");
          client.println("<BODY>");
          client.println("<H4 style='color:Black'>Hoogen-hooft</H4>"); 
          client.println("<P style='font-size:80%; color:Black'>");
          
          for (int i = 0; i <= 5; i++) 
          {
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); 
            client.println(buffer); 
            client.println("<br>");
          }
          
          client.println("</P>");

          if(sensorValuex > 600)
          {
            client.println("<P style='color:Red'>"); 
            client.print(sensorPinx);
            client.print(": ");
            client.print(sensorValuex);
            client.println("</P>");
          }

          else
          {
            client.println("<P style='color:White'>"); 
            client.print(sensorPinx);
            client.print(": ");
            client.print(sensorValuex);
            client.println("</P>");
          }

          if(sensorValuey > 600)
          {
            client.println("<P style='color:Red'>"); 
            client.print(sensorPiny);
            client.print(": ");
            client.print(sensorValuey);
            client.println("</P>");
          }

          else
          {
            client.println("<P style='color:White'>"); 
            client.print(sensorPiny);
            client.print(": ");
            client.print(sensorValuey);
            client.println("</P>");
          }
  
          client.println("<P>");
          
          if (ParseHeader(httpHeader, arg, val)) 
          {
              Serial.println(httpHeader);
              Serial.println(arg);
              Serial.println(val);
              
              digitalWrite(arg, val);
              
              client.print("Pin ");
              client.print(arg); 
              client.print(" = "); 
              client.println(val);
          }
          
          else 
          {
            client.println("No IO-pins to control");
          }
          
          client.println("</P>");
          
          client.println("</BODY>");
          client.println("</HTML>");
          break;
        }
        
        if (c == '\n') \
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r') 
        {
          currentLineIsBlank = false;
        }
      }
    }
    
    delay(1);
    client.stop();
    httpHeader = "";
    
    Serial.println("Client disconnected");
  }
}

bool ParseHeader(String header, int &a, int &v)
{
  String astring = header.substring(14, 15);
  String vstring = header.substring(16, 17);

  Serial.println(astring);
  Serial.println(vstring);
  
  a = astring.toInt();
  v = vstring.toInt();
  
  if((a == 8 || a == 9) && (v == 0 || v == 1))
  {
    return true;
  }

  else
  {
    return false;
  }
}


