 
//String mode;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

char command;
int led = 13;
int wittySwitch = 12;  // SWITCH = Switch power (switch RPI off if on and vice verse)
int alarm = A1;        // INT = Alarm (active low)
int vOut = A2;        // Vout = RPI Power
float sensorValue;
static char displayValue[15];

unsigned long interval = 500; //default interval is 500 milliseconds

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(wittySwitch, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter S or s for switch off or any other key to see status");
  digitalWrite(led, LOW);
  digitalWrite(wittySwitch, LOW);
}

void loop()
{
  // Wait until a key is pressed
  while(Serial.available() == 0)    
  {
  }
  
  inputString = "";
  stringComplete = false;
  // Parse the string
  while (!stringComplete && (inputString.length() == 0)) 
  {
    Serial.println("reading...");
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') 
    {
      stringComplete = true;
    } 
  }
  
  Serial.println("Just read " + String(inputString));
  
  Serial.println("------------------------------------------------");
  if(inputString.equalsIgnoreCase(String("s")))
  {
    Serial.println("Flipping switch");
    digitalWrite(led, HIGH);
    digitalWrite(wittySwitch, HIGH);
    delay(interval);
    digitalWrite(led, LOW);
    digitalWrite(wittySwitch, LOW);
  }
  else
  {
    sensorValue = analogRead(alarm) * 5.0/1023;
    dtostrf(sensorValue,7, 3, displayValue);
    Serial.println("Alarm = " + String(displayValue) + " V");
    delay(1);  // Stability

    sensorValue = analogRead(vOut) * 5.0/1023;
    dtostrf(sensorValue,7, 3, displayValue);
    Serial.println("PI Voltage = " + String(displayValue) + "V");
    delay(1);  // Stability 
    
    delay(1000);
  }
  Serial.println("------------------------------------------------");
}

