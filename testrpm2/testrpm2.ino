const int hallPin = 5;
int hallState = 0;
bool magnet = false;
bool prevMagnet = false;
float magnetCount = 0;
unsigned long lastMagTime;
unsigned long startTime;
unsigned long endTime;
float rpm;
bool done = false; // set to true after displaying rpm once so it doesn't print continuously
int lapseTime = 20;
int numRevIgnore = 5; 

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
  if ((millis() / 1000 - lastMagTime) >= lapseTime && !done)
  {
    end(); 
    //Serial.end();
  }
  
  hallState = analogRead(hallPin);
  if (hallState <= 500) // TODO = recheck for each magnet. low when magnet present; ~1000 when magnet not present
  {
    magnet = true;
  }
  else
  {
    magnet = false;
  }

  // check if there's a change in whether or not the magnet is there, and if the magnet is there now
  if (magnet != prevMagnet && magnet)
  {
    //Serial.println("changed");
    //Serial.println(hallState);
    magnetCount++;
    if (magnetCount == numRevIgnore)
    {
      startTime = millis() / 1000;
    }
    lastMagTime = millis() / 1000;
//    Serial.println("lastMagTime");
//    Serial.println(lastMagTime);
//    Serial.println(magnetCount);
  } 
  prevMagnet = magnet; 
}

void end() // 
{
  // calculate rpm = # times magnet detecetd / total time * 60
 endTime = millis() / 1000;
// Serial.println("magnetCount");
// Serial.println(magnetCount);
// Serial.println("times");
// Serial.println(endTime);
// Serial.println(startTime);
 if (magnetCount >= numRevIgnore)
 {
//  Serial.println("magnet count");
//  Serial.println(magnetCount);
  rpm = (magnetCount - numRevIgnore) / (endTime - startTime - lapseTime) * 60;  
 }
 else
 {
  rpm = magnetCount / (endTime - startTime - lapseTime) * 60; 
 }
 
 Serial.println("RPM");
 Serial.println(rpm);
 done = true;
}


