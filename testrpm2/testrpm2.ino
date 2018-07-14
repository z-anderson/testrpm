const int hallPin = 5;
int hallState = 0;
bool magnet = false;
bool prevMagnet = false;
int magnetCount = 0;
unsigned long lastMagTime;
unsigned long startTime;
unsigned long endTime;
float rpm;
bool done = false; // set to true after displaying rpm once so it doesn't print continuously
int lapseTime = 20;
int numRevIgnore = 5; 
//int numRevPrint = 3;
int secondsPrint = 5;
bool printedCurrent = false;

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
    magnetCount++;
    if (magnetCount == numRevIgnore)
    {
      startTime = millis() / 1000;
    }
    lastMagTime = millis() / 1000;
  } 

    if (millis() % (secondsPrint * 1000) == 0) // print current rpm every 15 seconds 
    {
      Serial.println((int)(millis() / 1000));
      printrpm(0);
      printedCurrent = true;
    }
    else
    {
      printedCurrent = false;
    }

  prevMagnet = magnet; 
}

void printrpm(int printLapseTime)
{
  // calculate rpm = # times magnet detecetd / total time * 60
 endTime = millis() / 1000;
 Serial.println("times");
 Serial.println(endTime);
 Serial.println(startTime);
 Serial.println("magnetCount");
 Serial.println(magnetCount);
 if (magnetCount >= numRevIgnore)
 {
  rpm = (1.0* magnetCount - numRevIgnore) / (endTime - startTime - printLapseTime) * 60.0;  
 }
 else
 {
  rpm = (1.0 * magnetCount) / (endTime - startTime - lapseTime) * 60.0; 
 }
 Serial.println("RPM");
 Serial.println(rpm);
 
}

void end() // 
{
 printrpm(lapseTime);
 done = true;
 Serial.println("done!");
}


