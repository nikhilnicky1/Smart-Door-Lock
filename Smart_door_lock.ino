#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <String.h>

#define solenoidPin D4

String generated_otp = "1234";
int position = 0;
String user_otp;
char key;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

int c = 0; //keypad position
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {D0,D3,D5,D6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D7,9,10}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  pinMode(solenoidPin,OUTPUT);
  digitalWrite(D4, LOW);
  setLocked(true);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);

 }

void loop() {

   
   char key = myKeypad.getKey();
 
	  if(key){
		
				Serial.print("Key Pressed : ");
        Serial.println(key);
    
		      if (key == '*' || position == 0) {
			    lcd.clear();
          lcd.setCursor(0,0);
			    position = 0;
		    	user_otp = "";
		      }
     
		    else if(key == '#' || position == 4){
			
		      	lcd.clear();
			      Serial.println(user_otp);
            Serial.println(generated_otp);
			     // position = 0;
			
			      if(generated_otp == user_otp){
               	lcd.print("Verified");
			        	setLocked(false);
			        }
			      else {
				    lcd.print("Password Wrong");
            delay(3000);
            lcd.clear();
			      }
        	user_otp = " ";   		
		    }
		    if (key == '1' || key == '2' || key =='3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9'){
		    //if (key >= '0' || key <= '9'){ 
		    	lcd.setCursor(position, 0);
		    	lcd.print("*");
		    	position++;
         	user_otp += String(key);
            			}
	}
	else if(position == 0){

		//delay(1000);
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Safeshell");
		lcd.setCursor(0,1);
		lcd.print("enter password");
					}
	
//delay(500);
		
}

void setLocked(int locked){
  if(locked) {
       Serial.print(D4);
       digitalWrite(D4,HIGH);
      }
  else{
    Serial.print(D4);
    digitalWrite(D4,LOW);
  }
}
