const int hallPin = 5;
int hallState = 0;
bool magnet = false;
bool prevMagnet = false;
float magnetCount = 0;
unsigned long lastMagTime;
unsigned long startTime;
unsigned long endTime;
float rpm;
bool done = false; // reset to true in end()
int numRevIgnore = 5; // * making an assumption that we will hit this

//TODO = discount for 10 (or whatever) magnet detections
// to let it get up to speed 

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
  
  if ((millis() / 1000 - lastMagTime) >= 20 && !done)
  {
    //Serial.println("done:");
    Serial.println(done);
//    Serial.println("end time");
//    Serial.println(millis() / 1000);
    end(); 
    //Serial.end();
  }
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
    Serial.println("changed");
    //Serial.println(hallState);
    magnetCount++;
    if (magnetCount == numRevIgnore)
    {
      startTime = millis() / 1000;
    }
    lastMagTime = millis() / 1000;
//    Serial.println("lastMagTime");
//    Serial.println(lastMagTime);
      Serial.println(magnetCount);
  } 
  prevMagnet = magnet; 
}

void end() // 
{
 endTime = millis() / 1000; // / 60;
 //Serial.println(time);
// Serial.println("magnetCount");
// Serial.println(magnetCount);
 Serial.println("times");
 Serial.println(endTime);
 Serial.println(startTime);
// Serial.println(startTime / 60);
 if (magnetCount >= numRevIgnore)
 {
  Serial.println("magnet count");
  Serial.println(magnetCount);
  rpm = (magnetCount - numRevIgnore) / (endTime - startTime - 20) * 60;  // 20 = gap time
 }
 else
 {
  rpm = rpm = magnetCount / (endTime - startTime - 20) * 60; // 20 = gap time
 }
 
 Serial.println("RPM");
 Serial.println(rpm);
 done = true;
}


