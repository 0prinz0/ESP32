/*******************************************************************
 *  this is a basic example how to program a Telegram Bot          *
 *  using TelegramBOT library on ESP8266                           *
 *                                                                 *
 *  Open a conversation with the bot, it will echo your messages   *
 *  https://web.telegram.org/#/im?p=@EchoBot_bot                   *                                                                 
 *                                                                 *
 *  written by Giacarlo Bacchio                                    *
 *******************************************************************/


#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>



// Initialize Wifi connection to the router
char ssid[] = "HannahsJugendherberge"; // your network SSID (name)
char pass[] = "8UydQpyF1Vnk"; // your network key

char serverAddress[] = "192.168.0.68"; // server address
int port = 8080; // server port


WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;
String response;
int statusCode = 0;

void connect(){
Serial.println(" ");

  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid); // print the network name (SSID);
  WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network:
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
  }
  Serial.println(" ");

  // print the SSID of the network you're attached to:
  Serial.println("##################");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println("##################");
}

 double getSensorData(){

  return 0.00;
}

void setup() {
  Serial.begin(9600);
  connect();
}

void loop() {
   double sensorValue = getSensorData();
  
  client.beginRequest();
  String subAdress = "/Rest/status?id=5&value=";

  client.get(subAdress+sensorValue);
  client.sendBasicAuth("prinz","test");
  client.endRequest();


  // read the status code and body of the response
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println("Sleep for 1 min");
  ESP.deepSleep(3600e6);
  
}