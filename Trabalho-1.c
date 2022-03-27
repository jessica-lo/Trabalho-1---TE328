/*Programa que realiza a leitura de tensões, converte estes valores para resolução de 8 bits e depois para a base binária
  Para cada byte (8 bits) é reservado um conjunto de leds que permite a representação destes valores
  Três leds são utilizados para representar qual dos valores lido tem o maior módulo, sendo que cada led é respectivo a um divisor de tensão
  Todos os dados lidos são exibidos na serial
*/

/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void maioresLeituras();
void mudarPot();
void ligarLeds(int in);
//End of Auto generated function prototypes by Atmel Studio

const int leds[] = {6, 7, 8, 9, 10, 11, 12, 13};	//declara como vetor as saídas dos pinos digitais
const int ledsR[] = {5, 4, 3};						//declara como vetor as saídas dos pinos digitias
int mLeituras[] = {0, 0, 0};						//declara o vetor para armazenar a informação de qual entrada tem o maior módulo
const int button = 2;								//declara a porta do push button

int divisor[] = {A0, A1, A2};	//vetor que declara as entradas analógicas
int atual = 0;					//variável para definir o divisor de tensão lido
int input = 0;					//variável para armazenar o valor lido
int inputBin= 0;				//variável que armazena o valor em resolução 8 bits relativo a entrada
bool buttonState = false;		//declara o estado do botão como 0

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT); //declara o botão como sinal de input
  
  //declara os pinos digitais como saídas de sinal
  for(int i = 3; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
}

/*função que manipula uma array para obter a informação
  de qual(is) valor(es) tem o maior módulo, alterando o valor do vetor
  de 0 para 1
*/
void maioresLeituras(){
  int maior = 0;
  for (int i = 0; i < 3; i++){
    int leitura = analogRead(divisor[i]);
    mLeituras[i] = leitura;
    if(leitura > maior) 
      maior = leitura;
  }
  for (int i = 0; i < 3; i++){
    if(mLeituras[i] == maior) 
      mLeituras[i] = 1;
    else 
      mLeituras[i] = 0;
  }
}

/*função para alterar os potenciômetros
  e realiza um loop entre os três potenciômetros
*/
void mudarPot(){
  if(atual == 2){
    atual = 0;
  }
  else
    atual++;
}

/*função que converte o valor com resolução de 8 bits para binário
  e determina quais leds devem estar ligados para representar este valor
*/
void ligarLeds(int in){
  for(int i = 0; i <=7; i++){
    int bin = in % 2;
    if(bin == 1)
      digitalWrite(leds[i], HIGH);
    else
      digitalWrite(leds[i], LOW);
    in /= 2;
  }
}

/*função que realiza repetições
*/
void loop() {
  
//realiza a leitura do sinal do botão
  if(digitalRead(button) == 1){
     buttonState = true;
  } 
  if(buttonState == true && digitalRead(button) == 0){
     mudarPot();
     buttonState = false;
  }
  
//armazena o valor do divisor de tensão respectivo
  input = analogRead(divisor[atual]);
  
//relaciona o valor lido (10 bits) para uma variável de 8 bits
  inputBin = input/4;
  
//chamada da função ligarLeds, com entrada sendo o valor inputBin
  ligarLeds(inputBin);
  
//imprimir os dados
  Serial.print("input = ");
  Serial.print(input);
  Serial.print("\t valor em resol 8 bits= ");
  Serial.print(inputBin);
  Serial.print("\t Volts: ");
  Serial.println((5 * input) / 1024.0);
  
//se o valor do elemento do vetor for 1, o led será ligado
  maioresLeituras();
  for(int i = 0; i < 3; i++){
    if(mLeituras[i] == 1)
      digitalWrite(ledsR[i], HIGH);
    else 
      digitalWrite(ledsR[i], LOW);
  }
  
  delay(500);
}
