#define pin1 10
#define pin2 9
#define pin3 8
#define pin4 7

void moveFrente(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}

void moveRe(){
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}

void direita(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);

  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

void esquerda(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);

  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}

void parar(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);

  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
