void setup() {
  // put your setup code here, to run once:
  // MOTOR 1
  pinMode(3, OUTPUT); // PWM
  pinMode(4, OUTPUT); // DIR1
  pinMode(5, OUTPUT); // DIR2

  // MOTOR 2
  pinMode(6, OUTPUT); // PWM
  pinMode(7, OUTPUT); // DIR1
  pinMode(8, OUTPUT); // DIR2

  // MOTOR 3
  pinMode(9, OUTPUT); //PWM
  pinMode(10, OUTPUT); // DIR1
  pinMode(11, OUTPUT); // DIR2

  for(int i = 3; i < 12; i++)
  {
    digitalWrite(i, LOW);
  }

  Serial.begin(9600);
  Serial.println("Type");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available())
  {
    char theChar = Serial.read();
    Serial.print("Found ");
    Serial.println(theChar);
    
    if(theChar == 'f')
    {
      analogWrite(3, 255);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    }
    else if(theChar == 'b')
    {
      analogWrite(3, 128);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    }
    else if(theChar == 'l')
    {
      analogWrite(6, 255);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
    }
    else if(theChar == 'k')
    {
      analogWrite(6, 128);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
    }
    else if(theChar == 'o')
    {
      analogWrite(9, 255);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }
    else if(theChar == 'i')
    {
      analogWrite(9, 128);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }
  }

  Serial.println(analogRead(A0));
  
}
