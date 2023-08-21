/* RFID Based Smart Traffic Signal for Ambulance
   by Aakaar Lab
*/

int yellow_led=12,red_led=13,green_led=11,count=0,countp;


char* rfid_id[]={"270021BEBE06","270021BCFE44"};//Replace your RFID tags here 
char* names[]={"Ambulance-1","Ambulance-1"};
int presence[2];

void setup() 
{   
Serial.begin(9600);
pinMode(yellow_led,OUTPUT);
pinMode(red_led,OUTPUT);
pinMode(green_led,OUTPUT);
}

void loop() 
{
  int i;
  char response[12];
  int ch;
  delay(200);
  signalchange();
  if(Serial.available()>0)
    {
        i=0;
        do
        {
            while(Serial.available()<=0);
            response[i]=Serial.read();
            Serial.print(response[i]);
            i++;
        }while(i<12);
        response[i]='\0';
        if(strcmp(response,rfid_id[0])==0)//User1 rfid received
        {
          digitalWrite(red_led,LOW);
          digitalWrite(green_led,HIGH);
        }
        else if(strcmp(response,rfid_id[1])==0)//User2 rfid received
        {
          digitalWrite(red_led,LOW);
          digitalWrite(green_led,HIGH);
        }
        delay(5000);
        
    }
   if(countp==1)
   {count++; }
   if(countp==0)
   {count--; }
     
  
}
void signalchange()
{
 if(count==0)
  { 
    digitalWrite(green_led,LOW);
    digitalWrite(yellow_led,HIGH);
    delay(1000);
    digitalWrite(yellow_led,LOW);
    digitalWrite(red_led,HIGH);
    
    countp=1;
  }
  else if(count==50)
  { digitalWrite(red_led,LOW);
    digitalWrite(yellow_led,HIGH);
    delay(1000);
    digitalWrite(yellow_led,LOW);
    digitalWrite(green_led,HIGH);
    countp=0;
}
}

uint8_t getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  Serial.println(F("Scanned PICC's UID:"));
  for ( uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
  }
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}
