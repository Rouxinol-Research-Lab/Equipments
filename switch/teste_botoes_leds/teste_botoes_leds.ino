#include <EEPROM.h>   
int ligar = B0;
int rele_ligar = B0;
int dados = B1;
int desligar = B1;
int switchh, switch1=B000000,switch2=B000000;
int cmd,bobina;
int liga_antiga = 0;
int d_bobina_antiga_2,d_bobina_antiga_1,n_bobina_antiga_1,n_bobina_antiga_2;



void setup() {
   //primeira vez na utilização desse código descomentar essas linhas
   //EEPROM.write(0, 2);
   //EEPROM.write(1, 2);
   //EEPROM.write(2, 2);
   //EEPROM.write(3, 2);
  
 Serial.begin(9600);  
  
  //DDRF = B111111;
  //DDRB = B111111; 
  //0 = B111111;

  //Definição dos pinos para o controle de relés
  
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode( 9,OUTPUT);
  pinMode( 8,OUTPUT);
  pinMode( 7,OUTPUT);
  pinMode( 6,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);

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
  
  

  
  //switch1 = EEPROM.read(0);
  //switch2 = EEPROM.read(1);

}

void loop() {
  
  if (Serial.available() > 0) {
     cmd = Serial.read();    
   }else{
        cmd =  (digitalRead(23)==1  ? 11 : digitalRead(25)==1  ? 12 :digitalRead(29)==1  ? 14 : digitalRead(31)==1  ? 15 : digitalRead(33)==1  ? 16 : digitalRead(35)==1  ? 21 : digitalRead(37)==1  ? 22 : digitalRead(39)==1  ? 23 : digitalRead(41)==1  ? 24 : digitalRead(43)==1  ? 25 : digitalRead(45)==1  ? 26 : 0 );
     
   }
   if(cmd!=0){
      programa_principal();
   }
   liga_led();
}

void programa_principal(){
     switchh = cmd/10;
     bobina = cmd%10;
     aberto();
     delay(50);
     desligar_bobina();
     delay(50);
     aberto();
     delay(50);
     escolher_bobina(bobina);
     ligar_bobina();
     delay(50);
     aterrado();
     delay(50);   
}

void escolher_bobina(int valor){
  
   switch (valor) {
   case 1:  
    dados = B111100;
    break;
   case 2:
    dados = B111001;
    break;
   case 3:
    dados = B110011;
    break;
   case 4:
    dados = B100111;
    break;
   case 5:
    dados = B001111;
    break;
   case 6:
    dados = B011110; 
  default:
    // Se nenhuma das condições for satisfeita
    break;
  }
  
}


void ligar_bobina(){
   if(bobina%2==0){
      digitalWrite(7,1);
      digitalWrite(6,0); 
     }else{
      digitalWrite(7,0);
      digitalWrite(6,1); 
     }
     
     delay(10);
     switchhh(dados);
 

}

void desligar_bobina(){
  
   if(switchh==1){
       if(EEPROM.read(1)%2==0){
        digitalWrite(7,0);
        digitalWrite(6,1); 
       }else{
        digitalWrite(7,1);
        digitalWrite(6,0); 
       } 
       passar_valores_b(EEPROM.read(0));
       passar_valores_c(B111111);
    

       
     }else{
      if(EEPROM.read(3)%2==0){
        digitalWrite(7,0);
        digitalWrite(6,1);
     }else{
        digitalWrite(7,1);
        digitalWrite(6,0);
     } 
      passar_valores_b(B111111);
      passar_valores_c(EEPROM.read(2));
     }
     delay(10);
}



void switchhh(int valor){
  if(switchh==1){
       passar_valores_b(valor);
       passar_valores_c(B111111);
       d_bobina_antiga_1 = dados;
       n_bobina_antiga_1 = bobina;
       EEPROM.update(0, d_bobina_antiga_1);
       EEPROM.update(1, n_bobina_antiga_1);
       

     }else{
       passar_valores_b(B111111);
       passar_valores_c(valor);
       d_bobina_antiga_2 = dados;   
       n_bobina_antiga_2 = bobina;  
       EEPROM.update(2, d_bobina_antiga_2);
       EEPROM.update(3, n_bobina_antiga_2); 
     }
}

void aberto(){
  passar_valores_b(B1111111);
  passar_valores_c(B1111111);
  digitalWrite(7,0);
  digitalWrite(6,0);
}

void aterrado(){
  digitalWrite(7,0);
  digitalWrite(6,0);
  passar_valores_c(B000000);
  passar_valores_b(B000000);
  
} 

void passar_valores_c(int valor){
    digitalWrite(A0, valor & (1 << 5)  ? 1 : 0);
    digitalWrite(A1, valor & (1 << 4)  ? 1 : 0);
    digitalWrite(A2, valor & (1 << 3)  ? 1 : 0);
    digitalWrite(A3, valor & (1 << 2)  ? 1 : 0);
    digitalWrite(A4, valor & (1 << 1)  ? 1 : 0);
    digitalWrite(A5, valor & (1 << 0)  ? 1 : 0);

  
}

void passar_valores_b(int valor){
    digitalWrite(13, valor & (1 << 5)  ? 1 : 0);
    digitalWrite(12, valor & (1 << 4)  ? 1 : 0);
    digitalWrite(11, valor & (1 << 3)  ? 1 : 0);
    digitalWrite(10, valor & (1 << 2)  ? 1 : 0);
    digitalWrite( 9, valor & (1 << 1)  ? 1 : 0);
    digitalWrite( 8, valor & (1 << 0)  ? 1 : 0);    
}

void liga_led(){
    digitalWrite(22, EEPROM.read(1) == 1 ? 1 : 0);
    digitalWrite(24, EEPROM.read(1) == 2 ? 1 : 0); 
    digitalWrite(26, EEPROM.read(1) == 3 ? 1 : 0);
    digitalWrite(28, EEPROM.read(1) == 4 ? 1 : 0);
    digitalWrite(30, EEPROM.read(1) == 5 ? 1 : 0); 
    digitalWrite(32, EEPROM.read(1) == 6 ? 1 : 0);
    
    digitalWrite(34, EEPROM.read(3) == 1 ? 1 : 0);
    digitalWrite(36, EEPROM.read(3) == 2 ? 1 : 0); 
    digitalWrite(38, EEPROM.read(3) == 3 ? 1 : 0);
    digitalWrite(40, EEPROM.read(3) == 4 ? 1 : 0);
    digitalWrite(42, EEPROM.read(3) == 5 ? 1 : 0); 
    digitalWrite(44, EEPROM.read(3) == 6 ? 1 : 0);
}
