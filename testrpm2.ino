const int hallPin = 5;
int hallState = 0;
bool magnet = false;
bool prevMagnet = false;
float magnetCount = 0;
unsigned long lastMagTime;
unsigned long startTime;
unsigned long endTime;
float rpm;

void setup()
{
  Serial.begin(9600);
  pinMode(hallPin, INPUT); 
  Serial.print("SETUP\n");
  startTime = millis() / 1000;
  lastMagTime = millis() / 1000;  
}

void loop()
{
  // millis() is a very large number, and lastmagtime is initliazed to zero 
  
  if ((millis() / 1000 - lastMagTime) >= 20)
  {
//    Serial.println("end time");
//    Serial.println(millis() / 1000);
    end(); 
    Serial.end();
  }
  //Serial.print("test\n");
  hallState = analogRead(hallPin);

  if (hallState <= 500)
  {
    magnet = true;
  }
  else
  {
    magnet = false;
  }
  

  if (magnet != prevMagnet && magnet)
  {
    //Serial.println("changed");
    //Serial.println(hallState);
    magnetCount++;
    lastMagTime = millis() / 1000;
//    Serial.println("lastMagTime");
//    Serial.println(lastMagTime);
//    Serial.println(magnetCount);
  } 
  prevMagnet = magnet; 
}

void end() // 
{
 endTime = millis() / 1000; // / 60;
 //Serial.println(time);
// Serial.println("magnetCount");
// Serial.println(magnetCount);
// Serial.println("times");
// Serial.println(endTime);
// Serial.println(startTime / 60);
 rpm = magnetCount / (endTime - startTime - 20) * 60; // / 60); // 20 = gap time
 Serial.println("RPM");
 Serial.println(rpm);
}


