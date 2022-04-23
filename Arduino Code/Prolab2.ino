#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs=2,en=3,d4=4,d5=5,d6=6,d7=7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const byte pir_pin=29;
const byte flame_pin=30;
const byte yesil_pin=12;
const byte kirmizi_pin=13;
const byte lamp_pin=11;
const byte buzzer_pin=10;
const byte satir_pin=4;
const byte sutun_pin=3;
const String password="1907";
String user_password="";
char eleman[satir_pin][sutun_pin]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};

byte satir_pinleri[]={25,26,27,28};
byte sutun_pinleri[]={24,23,22};

Keypad keypad1=Keypad(makeKeymap(eleman),satir_pinleri,sutun_pinleri,satir_pin,sutun_pin);

void Keypad_Function(){
  
  char karakter=keypad1.getKey();

  if(karakter){

    if(karakter=='#'){

        

        if(user_password==password){

          digitalWrite(yesil_pin,HIGH);
          digitalWrite(kirmizi_pin,LOW);
          
        }
        else{
          digitalWrite(kirmizi_pin,HIGH);
          digitalWrite(yesil_pin,LOW);
        }

        user_password="";
    }
    else if(karakter=='*'){

      user_password="";

      digitalWrite(yesil_pin,LOW);
      digitalWrite(kirmizi_pin,LOW);
    }
    else{
 
    user_password+=karakter;
    } 
  } 
}
void Pir_Function(){

int kontrol=digitalRead(pir_pin);

if(kontrol==HIGH){
digitalWrite(lamp_pin,HIGH);  
}
else{
digitalWrite(lamp_pin,LOW);
}
}
void Flame_Function(){

int kontrol2=digitalRead(flame_pin);

if(kontrol2==HIGH){

 digitalWrite(buzzer_pin,HIGH);

}
else{
digitalWrite(buzzer_pin,LOW);
}
}
void Derece_Function(){


int value=analogRead(A1);

float celcius=(value/1024.0)*2560.0;
celcius=celcius/10.0;

if(celcius<20){
lcd.setCursor(0,0);
lcd.print("Sicaklik Dustu. ");
lcd.setCursor(0,1);
lcd.print("Sicaklik:");
lcd.print(celcius);
lcd.print("*C");
}
else if(celcius>30){
  lcd.setCursor(0,0);
  lcd.print("Sicaklikyukseldi");
  lcd.setCursor(0,1);
  lcd.print("Sicaklik:");
  lcd.print(celcius);
  lcd.print("*C");
}
else{
lcd.setCursor(0,0);
lcd.print("Sicaklik:");
lcd.print(celcius);
lcd.print("*C");
lcd.setCursor(0,1);
lcd.print("                                       ");
  
}
}


void setup() {
Serial.begin(9600);
lcd.begin(16,2);
analogReference(INTERNAL2V56);
pinMode(yesil_pin,OUTPUT);
pinMode(kirmizi_pin,OUTPUT);
pinMode(lamp_pin,OUTPUT);
pinMode(buzzer_pin,OUTPUT);

}

void loop() {
Derece_Function();
Keypad_Function();
Pir_Function();
Flame_Function();

}
