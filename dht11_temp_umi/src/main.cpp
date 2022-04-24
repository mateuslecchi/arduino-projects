#include <Arduino.h>
#include "DHT.h"

const int t_vermelho = 2;
const int t_amarelo = 3;
const int t_verde = 4;
const int u_vermelho = 5;
const int u_amarelo = 6;
const int u_verde = 7;
const int led_padrao = 13;
const int pino_dht = 9;
float temperatura; // variável para armazenar o valor de temperatura
float umidade; // variável para armazenar o valor de umidade
DHT dht(pino_dht, DHT11); // define o pino e o tipo de DHT

int contador = 0;

void setup() {
  // Inicia e configura a Serial
  Serial.begin(9600); // 9600bps

  dht.begin(); // inicializa o sensor DHT

  pinMode(t_vermelho, OUTPUT);
  pinMode(t_amarelo, OUTPUT);
  pinMode(t_verde, OUTPUT);
  pinMode(u_vermelho, OUTPUT);
  pinMode(u_amarelo, OUTPUT);
  pinMode(u_verde, OUTPUT);
  pinMode(led_padrao, OUTPUT);
}

void loop() {
  // Aguarda alguns segundos entre uma leitura e outra
  delay(2000); // 2 segundos (Datasheet)

  // A leitura da temperatura ou umidade pode levar 250ms
  // O atraso do sensor pode chegar a 2 segundos
  temperatura = dht.readTemperature(); // lê a temperatura em Celsius
  umidade = dht.readHumidity(); // lê a umidade

  // Se ocorreu alguma falha durante a leitura
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do Sensor DHT!");
  }
  else { // Se não

    if (temperatura <= 25)
    {
      digitalWrite(t_verde, HIGH);
      digitalWrite(t_amarelo, LOW);
      digitalWrite(t_vermelho, LOW);
    }

    if(temperatura > 25 && temperatura <= 30)
    {
      digitalWrite(t_verde, LOW);
      digitalWrite(t_amarelo, HIGH);
      digitalWrite(t_vermelho, LOW);
    }

    if(temperatura > 30)
    {
      digitalWrite(t_verde, LOW);
      digitalWrite(t_amarelo, LOW);
      digitalWrite(t_vermelho, HIGH);
    }

    if (umidade <= 40)
    {
      digitalWrite(u_verde, LOW);
      digitalWrite(u_amarelo, LOW);
      digitalWrite(u_vermelho, HIGH);
    }

    if(umidade > 40 && umidade <= 70)
    {
      digitalWrite(u_verde, LOW);
      digitalWrite(u_amarelo, HIGH);
      digitalWrite(u_vermelho, LOW);
    }

    if(umidade > 70)
    {
      digitalWrite(u_verde, HIGH);
      digitalWrite(u_amarelo, LOW);
      digitalWrite(u_vermelho, LOW);
    }


    // Imprime o valor de temperatura  
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" *C ");
    
    Serial.print("\t"); // tabulação
  
    // Imprime o valor de umidade
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %\t"); 

    // Imprime o valor de umidade
    Serial.print("Contador: ");
    Serial.print(contador++);
    Serial.print("\t"); 
    
    Serial.println(); // nova linha

    digitalWrite(led_padrao, HIGH);
    delay(25);
    digitalWrite(led_padrao, LOW);
  }
}