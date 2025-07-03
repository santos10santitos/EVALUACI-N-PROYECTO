#include <Servo.h>

// ─── Sensores ──────────────────────────────────────────────
// HC‑SR04
const int trigPin = 8;
const int echoPin = 9;
// FC‑51 IR
const int sensorIR = 6;

// ─── Servos (ruedas) ───────────────────────────────────────
Servo servoFL;  // Front‑Left
Servo servoFR;  // Front‑Right
Servo servoRL;  // Rear‑Left
Servo servoRR;  // Rear‑Right

const int pinFL = 3;
const int pinFR = 5;
const int pinRL = 10;
const int pinRR = 11;

// Velocidades (ajusta si tus servos responden distinto)
const int SERVO_STOP   = 90;   // detenido
const int SERVO_FWD    = 180;  // hacia adelante
const int SERVO_REV    = 0;    // hacia atrás

// Umbrales y tiempos
const float UMBRAL_DIST  = 15.0;   // cm
const unsigned long RETROCESO_MS = 700;
const unsigned int  LOOP_DELAY   = 100; // tiempo entre ciclos (ms)

// ─── Variables internas ───────────────────────────────────
long duracion;
float distancia;

// ─── Funciones de movimiento ──────────────────────────────
void avanzar() {
  servoFL.write(SERVO_FWD);
  servoFR.write(SERVO_FWD);
  servoRL.write(SERVO_FWD);
  servoRR.write(SERVO_FWD);
}

void retroceder() {
  servoFL.write(SERVO_REV);
  servoFR.write(SERVO_REV);
  servoRL.write(SERVO_REV);
  servoRR.write(SERVO_REV);
}

void detener() {
  servoFL.write(SERVO_STOP);
  servoFR.write(SERVO_STOP);
  servoRL.write(SERVO_STOP);
  servoRR.write(SERVO_STOP);
}

// ─── Setup ────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sensorIR, INPUT);

  // Adjuntar servos
  servoFL.attach(pinFL);
  servoFR.attach(pinFR);
  servoRL.attach(pinRL);
  servoRR.attach(pinRR);

  detener();
  Serial.println("Robot listo.");
  delay(1000);
}

// ─── Loop principal ───────────────────────────────────────
void loop() {
  // ── Lectura ultrasónica ──
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion  = pulseIn(echoPin, HIGH, 25000); // 25 ms timeout (~4 m)
  distancia = duracion * 0.034 / 2.0;

  // ── Lectura infrarroja ──
  int estadoIR = digitalRead(sensorIR); // LOW = obstáculo con FC‑51

  // ── Decisión de movimiento ──
  bool obstaculoUS = (distancia > 0 && distancia < UMBRAL_DIST);
  bool obstaculoIR = (estadoIR == LOW);

  if (obstaculoUS || obstaculoIR) {
    // Obstáculo detectado → retroceder breve
    Serial.println("¡Obstáculo detectado! Retrocediendo...");
    retroceder();
    delay(RETROCESO_MS);
  } else {
    // Camino libre → avanzar
    avanzar();
  }

  // Mensajes de depuración
  Serial.print("Distancia (cm): ");
  Serial.print(distancia);
  Serial.print("  |  IR: ");
  Serial.print(estadoIR == LOW ? "OBSTÁCULO" : "libre");
  Serial.println();

  delay(LOOP_DELAY);
}
