int Input = A0;
int R_LED = 2;
int G_LED = 3;
int Buzzer = 4;
int fan2 = 8;
int fan1 = 9;
// VAL INTEGER
int val;
int MAX = 400;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  delay(100);
  
  pinMode(Input, INPUT);  // Sensor input pin
  pinMode(R_LED, OUTPUT);  // Red LED output pin
  pinMode(G_LED, OUTPUT);  // Green LED output pin
  pinMode(Buzzer, OUTPUT);  // Buzzer output pin
  pinMode(fan1, OUTPUT);  // Fan 1 control pin
  pinMode(fan2, OUTPUT);  // Fan 2 control pin
}

void loop() {
  val = analogRead(Input);  // Read sensor value

  if (val >= MAX) {  // If the value exceeds the threshold (indicating high pollution)
    digitalWrite(R_LED, HIGH);  // Turn on Red LED
    digitalWrite(Buzzer, HIGH);  // Activate Buzzer
    digitalWrite(fan1, HIGH);  // Turn on Fan 1
    digitalWrite(fan2, HIGH);  // Turn on Fan 2
    digitalWrite(G_LED, LOW);  // Turn off Green LED

    Serial.println("GAS LEAKING");
    sendSMS();
    delay(5000);  // Delay to prevent sending multiple SMS in a short period
  } 
  else {  // If the value is within normal range
    digitalWrite(R_LED, LOW);  // Turn off Red LED
    digitalWrite(Buzzer, LOW);  // Deactivate Buzzer
    digitalWrite(fan1, LOW);  // Turn off Fan 1
    digitalWrite(fan2, LOW);  // Turn off Fan 2
    digitalWrite(G_LED, HIGH);  // Turn on Green LED

    Serial.println("NORMAL");
  }
}

void sendSMS() {
  Serial.println("AT+CMGF=1");  // Set GSM module to Text Mode
  delay(1000);  // Wait for response
  
  Serial.println("AT+CMGS=\"+919943249595\"\r");  // Send SMS to the specified phone number
  delay(1000);  // Wait for response
  
  Serial.println("Dust particle is found, please keep safe.");
  delay(100);
  Serial.println((char)26);  // ASCII code of CTRL+Z to send the message
  delay(1000);  // Wait before completing the process
}
