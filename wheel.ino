#include <Joystick.h>

// Configure o joystick para 20 botões (0 a 19)
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 23, 0, false, false, false, false, false, false, false, false, false, false, false);

const int buttonPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15 };  // Pinos aos quais os botões estão conectados
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);

const int potentiometerTurboPin = A0;  // Pino ao qual o potenciômetro turbo está conectado
const int potentiometerBeakePin = A1;  // Pino ao qual o potenciômetro de freio está conectado
const int potentiometerABSPin = A2;    // Pino ao qual o potenciômetro de ABS está conectado
const int potentiometerTCPin = A3;     // Pino ao qual o potenciômetro de TC está conectado

int previousPotValue = 0;       // Valor anterior do potenciômetro turbo
int previousPotBrakeValue = 0;  // Valor anterior do potenciômetro de freio
int previousPotABSValue = 0;    // Valor anterior do potenciômetro de ABS
int previousPotTCValue = 0;     // Valor anterior do potenciômetro de TC
int numSteps = 10;              // Número de partes iguais (10%)
int stepSize;                   // Tamanho de cada parte em unidades do potenciômetro

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(potentiometerTurboPin, INPUT);  // Configura o pino do potenciômetro turbo como entrada
  pinMode(potentiometerBeakePin, INPUT);  // Configura o pino do potenciômetro de freio como entrada
  pinMode(potentiometerABSPin, INPUT);    // Configura o pino do potenciômetro de freio como entrada
  Joystick.begin();                       // Inicializa a emulação de joystick HID

  stepSize = 1023 / numSteps;  // Calcula o tamanho de cada parte
}

void loop() {
  int potValue = analogRead(potentiometerTurboPin);  // Lê o valor do potenciômetro turbo
  int mappedValue = potValue / stepSize;             // Mapeia o valor para o intervalo de 0 a 10
  int brakeValue = analogRead(potentiometerBeakePin);
  int brakemappedValue = brakeValue / stepSize;
  int ABSValue = analogRead(potentiometerABSPin);
  int ABSmappedValue = ABSValue / stepSize;
  int TCValue = analogRead(potentiometerTCPin);
  int TCmappedValue = TCValue / stepSize;

  // Clique nos botões
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      Joystick.setButton(i, 1);  // Define o botão como pressionado
    } else {
      Joystick.setButton(i, 0);  // Define o botão como não pressionado
    }
  }

  // Potenciômetro turbo
  if (mappedValue != previousPotValue) {
    if (mappedValue > previousPotValue) {
      // Incremento detectado
      Joystick.setButton(15, 1);  // Ativa o botão virtual 15
      delay(10);                  // Pequena pausa para evitar múltiplos incrementos rápidos
      Joystick.setButton(15, 0);  // Desativa o botão virtual 15
    } else {
      // Decremento detectado
      Joystick.setButton(16, 1);  // Ativa o botão virtual 16
      delay(10);                  // Pequena pausa para evitar múltiplos decrementos rápidos
      Joystick.setButton(16, 0);  // Desativa o botão virtual 16
    }

    // Atualiza o valor anterior para o próximo loop
    previousPotValue = mappedValue;
  }


   // Potenciômetro de freio
  if (brakemappedValue != previousPotBrakeValue) {
    if (brakemappedValue > previousPotBrakeValue) {
      // Incremento detectado
      Joystick.setButton(17, 1);  // Ativa o botão virtual 18
      delay(10);                  // Pequena pausa para evitar múltiplos incrementos rápidos
      Joystick.setButton(17, 0);  // Desativa o botão virtual 18
    } else {
      // Decremento detectado
      Joystick.setButton(18, 1);  // Ativa o botão virtual 19
      delay(10);                  // Pequena pausa para evitar múltiplos decrementos rápidos
      Joystick.setButton(18, 0);  // Desativa o botão virtual 19
    }

    // Atualiza o valor anterior para o próximo loop
    previousPotBrakeValue = brakemappedValue;
  }


  // Potenciômetro de ABS
  if (ABSmappedValue != previousPotABSValue) {
    if (ABSmappedValue > previousPotABSValue) {
      // Incremento detectado
      Joystick.setButton(19, 1);  // Ativa o botão virtual 18
      delay(10);                  // Pequena pausa para evitar múltiplos incrementos rápidos
      Joystick.setButton(19, 0);  // Desativa o botão virtual 18
    } else {
      // Decremento detectado
      Joystick.setButton(20, 1);  // Ativa o botão virtual 19
      delay(10);                  // Pequena pausa para evitar múltiplos decrementos rápidos
      Joystick.setButton(20, 0);  // Desativa o botão virtual 19
    }

    // Atualiza o valor anterior para o próximo loop
    previousPotABSValue = ABSmappedValue;
  }


   // potenciometro controle de tracao
  if (TCmappedValue != previousPotTCValue) {
    if (TCmappedValue > previousPotTCValue) {
      // Incremento detectado
      Joystick.setButton(21, 1);  // Ativa o botão virtual 18
      delay(10);                  // Pequena pausa para evitar múltiplos incrementos rápidos
      Joystick.setButton(21, 0);  // Desativa o botão virtual 18
    } else {
      // Decremento detectado
      Joystick.setButton(22, 1);  // Ativa o botão virtual 19
      delay(10);                  // Pequena pausa para evitar múltiplos decrementos rápidos
      Joystick.setButton(22, 0);  // Desativa o botão virtual 19
    }

    // Atualiza o valor anterior para o próximo loop
    previousPotTCValue = TCmappedValue;
  }

}
