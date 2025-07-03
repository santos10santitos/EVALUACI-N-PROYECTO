// Pines del sensor ultrasónico HC-SR04
const int trigPin = 8;
const int echoPin = 9;

// Pin del sensor infrarrojo FC-51
const int sensorIR = 6;

// Variables de medición
long duracion;
float distancia;

void setup() {
  Serial.begin(9600); // Iniciar comunicación serial

  // Configurar pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sensorIR, INPUT);

  Serial.println("Sistema iniciado. Esperando sensores...");
  delay(1000);
}

void loop() {
  // Medir distancia con el sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.034 / 2;

  // Mostrar la distancia medida
  Serial.print("Distancia ultrasónica: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Evaluar resultado del sensor ultrasónico
  if (distancia < 15) {
    Serial.println("Obstáculo detectado por ultrasonido.");
  } else {
    Serial.println("No se detecta obstáculo por ultrasonido.");
  }

  // Leer estado del sensor infrarrojo
  int estadoIR = digitalRead(sensorIR);

  // Evaluar resultado del sensor infrarrojo
  if (estadoIR == LOW) {
    Serial.println("Obstáculo detectado por sensor infrarrojo.");
  } else {
    Serial.println("No se detecta obstáculo por sensor infrarrojo.");
  }

  Serial.println("-----------------------------");
  delay(3000); // Espera 1 segundo antes de la siguiente lectura
}
