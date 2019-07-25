double pulPin = 2;
/*releated to step  */
double dirPin = 3;
/*releated to direction*/
double enablePin = 4;
double oneDegreeBefore = 0;
double Degree = 0;
double blank = 0;
double ImpulseDelay = 50000;
double OneDegreeBefore = 0;
double impulseDegree = 0.12;
double Lswitch1 = 5;
double Lswitch2 = 6;
double microStep = 16;
void setup() {
  Serial.begin(9600);
  pinMode(dirPin, OUTPUT);
  pinMode(pulPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(Lswitch1, INPUT);
  pinMode(Lswitch2, INPUT);
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH);
}

void loop() {
  while (Serial.available() > 0) {
    OneDegreeBefore = Degree;
    Degree = Serial.parseInt();
    blank = Serial.parseInt();
    Serial.println(Degree);
    stepper();
  }
}
void stepperZerodegre() {
  boolean ent1 = false;
  boolean ent2 = false;
  while (!((ent1 == true) and (ent2 == true))) {
    ent1 = entSchalter1();
    ent2 = entScahlter2();
    Impulse();
  }
  Degree = 0;
}

boolean entSchalter1() {

  if (digitalRead(Lswitch1) == 1) {
    return true;
  }
  else {
    return false;
  }
}

boolean entScahlter2() {
  if (digitalRead(Lswitch1) == 1) {
    return true;
  }
  else {
    return false;
  }
}


void stepper() {
  int MovementDegree;
  int i = 0;
  Serial.print("Degree");
  Serial.println(Degree);
  Serial.print("OneDegreeBefore");
  Serial.println(OneDegreeBefore);
  MovementDegree = OneDegreeBefore - Degree;
  i = calculateStep(MovementDegree);
  Serial.println("step");
  Serial.println(i);
  if (MovementDegree < 0) {
    digitalWrite(dirPin, LOW);
    for (int x = 0; x <= i; x++) {
      Serial.println(x);
      Impulse();
    }
  }
  else if (MovementDegree > 0) {
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x <= i; x++) {
      Serial.println(x);
      Impulse();
    }
  }
  Serial.println("stop");


}
int calculateStep(int MovementDegree) {

  int i = abs(MovementDegree / impulseDegree ) * microStep;
  Serial.print("1.");
  Serial.println(MovementDegree);
  Serial.print("2.");
  Serial.println(impulseDegree);
  Serial.print("3.");
  Serial.println(microStep);
  return i;
}

void Impulse() {

  digitalWrite(pulPin, HIGH);
  delayMicroseconds(ImpulseDelay);
  digitalWrite(pulPin, LOW);

}
