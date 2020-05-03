#include <ESP8266WiFi.h>
const char* ssid = "xxxxx";
const char* password = "xxxx";
int deng = 2;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(deng, OUTPUT);
  digitalWrite(deng, LOW);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("wifi connected");
  
  server.begin();
  Serial.println("server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n IO &#x72B6;&#x6001;: ";
  int val ;
  if (req.indexOf("/io/low") != -1){
    val = 0;
    s += (val)?"&#x9AD8;&#x7535;&#x5E73;":"&#x4F4E;&#x7535;&#x5E73;";
    s += "<br><a href='http://192.168.1.197/io/low'><input type='button' value='low'></a><a href='http://192.168.1.197/io/high'><input type='button' value='high'></a></html>\n";
    client.print(s);
    digitalWrite(deng, LOW);
    }
  else if (req.indexOf("/io/high") != -1){
    val = 1;
    s += (val)?"&#x9AD8;&#x7535;&#x5E73;":"&#x4F4E;&#x7535;&#x5E73;";
    s += "<br><a href='http://192.168.1.197/io/low'><input type='button' value='low'></a><a href='http://192.168.1.197/io/high'><input type='button' value='high'></a></html>\n";
    client.print(s);
    digitalWrite(deng, HIGH);
    }
  else{
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n IO &#x72B6;&#x6001;: Unknow <br><a href='http://192.168.1.197/io/low'><input type='button' value='low'></a><a href='http://192.168.1.197/io/high'><input type='button' value='high'></a></html>");
  }
  client.flush();
 
  delay(1);
  Serial.println("Client disonnected");

}
