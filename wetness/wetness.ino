int humidityPin = A0;
int humidityPowerPin = 3;
int wateringPin = LED_BUILTIN;
float humidityValue = -1;
int threshold = 250;
int delayMillis = 1000;
boolean debugOutput = true;
//testeintrag
 
long measureDry = 2*60*1000; // in Millisekunden
unsigned long counterDry = 0;

long measureWet = 10*1000; 
unsigned long counterWet = 0;
long openValve = 1000; 
bool isDry = false; 

void setup()
{
  pinMode(humidityPin, OUTPUT);
  pinMode(humidityPowerPin, OUTPUT);
  digitalWrite(humidityPowerPin, LOW); 
  digitalWrite(wateringPin, LOW); 
  Serial.begin(9600);
  counterDry = millis();
  if (debugOutput)
  {
    Serial.println("Init");
  }
}

void loop()
{
  if (debugOutput)
  {
    Serial.print("Humidity: ");
    Serial.println(humidityValue);
  }
  if (millis() - counterDry > measureDry)
  {
    setIsDry();
    counterDry = millis();
  }
  
  if (isDry)
  {
    watering();
  }
  //processValue(humidityValue);
  //delay(delayMillis);
}

void watering()
{
  if (millis() - counterWet > measureWet)
  {
    setIsDry(); 
    if (isDry)
    {
      digitalWrite(wateringPin, HIGH);
      delay(openValve);
      digitalWrite(wateringPin, LOW);
      counterWet = millis();
    }
  }
}

void setIsDry()
{
  humidityValue = messen();
  isDry = (humidityValue < threshold) ? true : false; 
}

float messen()
{
  //Strom einschalten
  digitalWrite(humidityPowerPin, HIGH); 
  delay(100); 
  //messen und glätten (5 mal messen)
  float result = analogRead(humidityPin);
  //Strom ausschalten
  delay(10); 
  digitalWrite(humidityPowerPin, LOW); 
  return result; 
}

void processValue(int value)
{
  if (value < threshold)
  {
    digitalWrite(wateringPin, HIGH);
  } else
  {
    digitalWrite(wateringPin, LOW);
  }
}

