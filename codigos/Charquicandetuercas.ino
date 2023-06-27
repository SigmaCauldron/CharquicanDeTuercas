/*  
 * Creado: Gabriel Olivares Sánches
 * Grupo: CharquicanDeTuercas
 *  Ramo: Módulo Interdisciplinario, CD2201-6 - Otoño 2023
*/

#define BLYNK_TEMPLATE_ID           "TMPL27t6ARriv"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "3irz8PybYB05jwTWcwsrb2kFBsTw6BH4"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Aqui se indica la red wifi a la que se conecta el robots
char ssid[] = "QianKun";
char pass[] = "mnodd632";

BlynkTimer timer;

Servo ESC;
Servo servoMotor;

int eje_x;
int eje_y;
int encendido;
int vel;
int sierra;
int palanca;

BLYNK_WRITE(V0){
  int value = param.asInt();
  encendido = value;
}
BLYNK_WRITE(V4){
  int value = param.asInt();
  eje_x = value;
}
BLYNK_WRITE(V5){
  int value = param.asInt();
  eje_y = value;
}
BLYNK_WRITE(V6){
  int value = param.asInt();
  vel = value;
}

BLYNK_WRITE(V1){
  int value = param.asInt();
  sierra = value;
}
BLYNK_WRITE(V8){
  int value = param.asInt();
  palanca = value;
}



BLYNK_CONNECTED(){
  //Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  //Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  //Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// Se establecen los pines asociados a cada punto de los drivers
const int motor_A_frente = D5;
const int motor_A_atras = D6;
const int motor_A = D8;
const int motor_B_frente = D1;
const int motor_B_atras = D2;
const int motor_B = D7;

const int pinPalanca = D3;
const int pinSierra = D4;

void setup() {
  //Establesco la operacion del Serial, lo cual nos permite ver por pantalla que esta haciendo el robot
  Serial.begin(115200);
  Serial.println("Iniciando...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  servoMotor.attach(D3);
  
  ESC.attach(D4);
  ESC.writeMicroseconds(1000);
  
  // Establecemos el tipo de pin que cada pins usado
  pinMode(motor_A_frente, OUTPUT);
  pinMode(motor_A_atras, OUTPUT);
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B_frente, OUTPUT);
  pinMode(motor_B_atras, OUTPUT);
  pinMode(motor_B, OUTPUT);

  pinMode(pinSierra, OUTPUT);
  pinMode(pinPalanca, OUTPUT);

  servoMotor.write(0);
  
  delay(2000);
}

int maximo = 255;
int minimo = 0;
int centro =128;

void loop() {
  Blynk.run();
  timer.run();

  if(encendido == 1){
    if(eje_x > (centro + 40)){
      giro("derecha");
    }else if(eje_x < (centro - 40)){
      giro("izquierda");
    }else if(eje_y > (centro + 40)){
      direccion("adelante");
    }else if(eje_y < (centro - 40)){
      direccion("atras");
    }else{
      detenerse();
    }

    if(palanca==1){
      servoMotor.write(45);
      delay(10);
      //Serial.println("Activando palanca");
    }else{
      servoMotor.write(0);
      delay(10);
    }

    if(sierra==1){
      ESC.write(180);
      delay(20);
      //Serial.println("Activando sierra");
    }else{
      ESC.write(0);
      delay(10);
      //Serial.println("Desactivando sierra");
    }
  }
}
