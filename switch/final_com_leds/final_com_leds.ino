  int cmd;

void setup() {
    //Definição dos pinos para controle dos leds
  
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(30,OUTPUT);
  pinMode(32,OUTPUT);
  
  pinMode(34,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(44,OUTPUT);

  //Definição dos pinos para controle de botões
  
  pinMode(23,INPUT);
  pinMode(25,INPUT);
  pinMode(27,INPUT);
  pinMode(29,INPUT);
  pinMode(31,INPUT);
  pinMode(33,INPUT);
  
  pinMode(35,INPUT);
  pinMode(37,INPUT);
  pinMode(39,INPUT);
  pinMode(41,INPUT);
  pinMode(43,INPUT);
  pinMode(45,INPUT);

  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
     cmd =  (digitalRead(23)==1  ? 11 : digitalRead(25)==1  ? 12 :digitalRead(29)==1  ? 14 : digitalRead(31)==1  ? 15 : digitalRead(33)==1  ? 16 : digitalRead(35)==1  ? 21 : digitalRead(37)==1  ? 22 : digitalRead(39)==1  ? 23 : digitalRead(41)==1  ? 24 : digitalRead(43)==1  ? 25 : digitalRead(45)==1  ? 26 : 0 );


     Serial.println(cmd);
     delay(500);
  // put your main code here, to run repeatedly:

}
