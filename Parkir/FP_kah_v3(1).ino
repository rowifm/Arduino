#include <SPI.h>
#include <Ethernet.h>

int sensorpin0 =A0;
int sensorpin1 =A1;
int sensorpin2 =A2;
int sensorvalue0 = 0;
int sensorvalue1 = 0;
int sensorvalue2 = 0;
//int ledpin = 11;
//int ledBright;



int sensorPin = 5; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures

 byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10,126,12,65);
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
EthernetServer server(80);
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 

      while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

    Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
// int reading = analogRead(sensorPin);  
EthernetClient client = server.available();


sensorvalue0 = analogRead(sensorpin0);
Serial.print("Analog 1 Read = ");
Serial.println(sensorvalue0);
sensorvalue1 = analogRead(sensorpin1);
Serial.print("Analog 2 Read = ");
Serial.println(sensorvalue1);
sensorvalue2 = analogRead(sensorpin2);
Serial.print("Analog 3 Read = ");
Serial.println(sensorvalue2);

String jawaban1;
String jawaban2;
String jawaban3;
          if(sensorvalue0>=100){
          jawaban1 = "<td class=\"p1\">P1 Tersedia</th>";
           }else{ 
           jawaban1 = "<td class=\"p2\">P1 Tidak Tersedia</th>";    
            } 
          
          if(sensorvalue1>=100){
          jawaban2 = "<td class=\"p1\">P2 Tersedia</th>";
            }else{
          jawaban2 ="<td class=\"p2\">P2 Tidak Tersedia</th>";    
              }
          
           if(sensorvalue2>=100){
          jawaban3 = "<td class=\"p1\">P3 Tersedia</th>";
           }else{ 
           jawaban3 = "<td class=\"p2\">P3 Tidak Tersedia</th>";    
            } 
             
 if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 2");  // refresh the page automatically every 2 sec
          client.println();
           client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>");
            client.println("Sistem Parkir JSI | Bukan TI | Bayar Coy");
            client.println("</title>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1><center>Peta Parkir JSI</center></h1>");
        
        
            client.println("<style type=\"text/css\">");
            client.println(".tg  {border-collapse:collapse;border-spacing:0;}");
            client.println(".tg td{font-family:Arial, sans-serif;font-size:14px;padding:20px 20px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}");
            client.println(".tg .p1{background-color:#00ff00;color:#000000;vertical-align:center}");
            client.println(".tg .p2{background-color:#ff0000;vertical-align:center} ");
            client.println(".tg .jalan{background-color:#cccccc;vertical-align:center}");
            client.println("</style>");
        
        
            client.println("<table class=\"tg\" style=\"undefined;table-layout: fixed; width: 774px\">");
            client.println("<colgroup>");
            client.println("<col style=\"width: 350px\">");
            client.println("<col style=\"width: 70px\">");
            client.println("<col style=\"width: 350px\">");
            client.println("</colgroup>");            
            client.println("<tr>");
            client.println(jawaban1); 
            client.println("<td class=\"jalan\" rowspan=\"3\"></th>");
            client.println("</tr>");
            client.println("<tr>");
            client.println(jawaban2);
            client.println("</tr>");
            client.println("<tr>");
            client.println(jawaban3);
            client.println("</tr>");
            client.println("</table>");
        
        
            client.println("</body>");
            client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
 

 delay(1000);                                     //waiting a second
}
