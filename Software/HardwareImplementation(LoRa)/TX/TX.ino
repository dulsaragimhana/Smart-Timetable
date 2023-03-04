#include <SPI.h>
#include <LoRa.h>

String generate_packet(String Class, int Periods, String Payload[8]);
 
void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Getting ready to send Data");
    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
  
  Serial.println("");
  delay(1000);

  // The updated timetable for the class 10-B (Consider an example class room 10-B)
  String Class = "10-B";
  int Periods = 2;      // Number of free periods
  String Payload[Periods] = {"P2:Mr.K.C.Rathnasiri", "P7:Mrs.P.D.Sandamali"};     // Assigned teachers for those periods along with the period

  // Generating the datapacket to transmit
  String packet = "";
  packet = generate_packet(Class, Periods, Payload);
  Serial.println(packet);
  
  // Sending the packet
  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
 
}
 
void loop() 
{
}

// Method for encoding the updated timetable for transmittion
String generate_packet(String Class, int Periods, String Payload[8]){
  String EOL = "@";   // to identify End Of Lines                                
  String packet =  Class + EOL + String(Periods) + EOL;
  for (int i = 0; i < Periods; i++){
    packet = packet + Payload[i] + EOL;
  }
  return packet;
}
