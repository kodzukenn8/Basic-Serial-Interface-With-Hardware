const int LEDpins[4] = {2,3,4,5};
const int buttonPins[4] = {10,11,12,13}; 
bool ledState[4] = {LOW,LOW,LOW,LOW}; 

void setup() 
{
  Serial.begin(9600);
  //set up the pins
  for (int pin = 0; pin<=3; pin++)
    pinMode(LEDpins[pin], OUTPUT);
  for (int but = 0; but <=3; but++)
    pinMode(buttonPins[but], INPUT_PULLUP);
}

void loop() 
{
  //gets the input from the Serial Monitor
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    //checks the command
    if(command.startsWith("SET LED"))
    {
      int ledNum = command[7];
      setLED(ledNum-49);
    }
    else if (command.startsWith("SET ALL"))
    {
      if (command[9] == 78)
      {
        setAllON();
      }
      else if (command[9] == 70)
      {
        setAllOFF();
      }
    } 
    else if (command.startsWith("GET BUTTON"))
    {
      int butNum = command[10];
      getButton(butNum-49);
    }
    else if (command == "GET ALL")
      getALL();
  }

}

//function to set individual LEDS
void setLED(int pin)
{
  if (ledState[pin] == LOW)
  {
    digitalWrite(LEDpins[pin],HIGH);
    ledState[pin] = !ledState[pin];
  }
  else
  {
    digitalWrite(LEDpins[pin],LOW);
    ledState[pin] = !ledState[pin];
  }
}

//function to set all LEDs
void setAllON()
{
  for (int n = 0; n <= 3; n++)
  {
    digitalWrite(LEDpins[n], HIGH);
    ledState[n] = HIGH;
  }
}

void setAllOFF()
{
  for (int n = 0; n <= 3; n++)
  {
    digitalWrite(LEDpins[n], LOW);
    ledState[n] = LOW;
  }
}


//function to get individual button states 
void getButton(int button)
{
  int state = digitalRead(buttonPins[button]);
  Serial.print("BUTTON");
  Serial.print(button+1);
  Serial.print(":");

  if (state == 1)
    Serial.print(" Released");
  else if (state == 0)
    Serial.print(" Pressed");

  Serial.print('\n');
}

//function to get all button states
void getALL()
{
  for (int i = 0; i <= 3; i++)
  {
    int state = digitalRead(buttonPins[i]);
    Serial.print("BUTTON");
    Serial.print(i+1);
    Serial.print(":");

    if (state == 1)
      Serial.print(" Released");
    else if (state == 0)
      Serial.print(" Pressed");

    Serial.print('\n');
  }
}
