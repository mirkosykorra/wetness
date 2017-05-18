int humidityPin = A0;
int humidityPowerPin = 3;
int wateringPin = LED_BUILTIN;
float humidityValue = -1;
int threshold = 250;
int delayMillis = 1000;
boolean debugOutput = true; 

void setup()
{
  pinMode(humidityPin, OUTPUT);
  pinMode(humidityPowerPin, OUTPUT);
  digitalWrite(humidityPowerPin, LOW); 
  digitalWrite(wateringPin, LOW); 
  Serial.begin(9600);
  if (debugOutput)
    Serial.println("Init");
}

void loop()
{
  humidityValue = messen();
  
  if (debugOutput)
  {
    Serial.print("Humidity: ");
    Serial.println(humidityValue);
  }
  processValue(humidityValue);
  delay(delayMillis);
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

