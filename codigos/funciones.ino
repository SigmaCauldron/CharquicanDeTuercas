void mover_A(String direccion){
  if(direccion=="adelante"){
    digitalWrite(motor_A_frente, HIGH);
    digitalWrite(motor_A_atras, LOW);
  }else if(direccion=="atras"){
    digitalWrite(motor_A_frente, LOW);
    digitalWrite(motor_A_atras, HIGH);
  }
  analogWrite(motor_A, 4*vel);
  Serial.println(vel);
}

void detener_A(){
  digitalWrite(motor_A, LOW);
}

void mover_B(String direccion){
  if(direccion=="adelante"){
    digitalWrite(motor_B_frente, HIGH);
    digitalWrite(motor_B_atras, LOW);
  }else if(direccion=="atras"){
    digitalWrite(motor_B_frente, LOW);
    digitalWrite(motor_B_atras, HIGH);
  }
  analogWrite(motor_B, 4*vel);
}

void detener_B(){
  digitalWrite(motor_B, LOW);
}

void giro(String direccion){
  if(direccion=="derecha"){
    mover_A("atras");
    mover_B("adelante");
    Serial.println("Moviendo hacia la derecha");
  }else if(direccion=="izquierda"){
    mover_A("adelante");
    mover_B("atras");
    Serial.println("Moviendo hacia la izquierda");
  }
  detenerse();
}

void direccion(String direccion){
  if(direccion=="adelante"){
    mover_A("adelante");
    mover_B("adelante");
    Serial.println("Moviendo hacia adelante");
  }else if(direccion=="atras"){
    mover_A("atras");
    mover_B("atras");
    Serial.println("Moviendo hacia atras");
  }
  detenerse();
}

void detenerse(){
  detener_A();
  detener_B();
}
