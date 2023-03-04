// LoRa Client Node (RX).
// This is our demonstration of the device at each classroms and its operatin.
// The Server LoRa Node located at the office transmits a data packet which includes the assigned teacher's names along with respective periods.
// This LoRa Node receives that data packet and decode it in order to interpret them properly on the LCD Screen.

#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal.h>

//  Configure LCD pins
const int rs = 7, en = 8, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup(){
  
  // LCD Welcome Screen when the device is powered ON
  lcd.begin(20,4);
  lcd.setCursor(2,1);
  lcd.print("### Welcome! ###");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Waiting for Updates");
  if (!LoRa.begin(433E6)) {
    lcd.print("Failed to start LoRa!");
    while (1);
  }
 
  // Register the receive callback
  LoRa.onReceive(onReceive);
 
  // Put the module into receive mode
  LoRa.receive();
}
 
void loop() {
}
 
void onReceive(int packetSize) {
  
  // Reading the data packet
  String data = "";
  for (int i = 0; i < packetSize; i++) {
    data = data + (char)LoRa.read();
  }

  // Decoding the data packet
  String lines[8];
  int i = 0;
  int count = 0;
  String temp = "";
  
  while (i < data.length()){  
    if (data[i] == '@'){
      lines[count] = temp;
      count = count + 1;
      i = i + 1;
      temp = "";
    }
    temp = temp + data[i];
    i = i + 1; 
  }

  // Display the updated timetable on LCD Screen
  for (int x = 0; x < count; x++){
    if (x == 0){
      lcd.clear();
      lcd.setCursor(0, 0);    
      lcd.print("Good Morning " + lines[x]);  
    }
    else if (x == 1){
      continue;
    }
    else{
      lcd.setCursor(0, x-1);    
      lcd.print(lines[x]); 
    }
  }
}
