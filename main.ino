#include <TimerOne.h>

int signal1[] = {23, 25, 27};
int signal2[] = {46, 48, 50};
int signal3[] = {13, 12, 11};
int signal4[] = {10, 9, 8};

int redDelay = 5000;
int yellowDelay = 2000;

volatile int triggerpin1 = 31;
volatile int echopin1 = 29;
volatile int triggerpin2 = 44;
volatile int echopin2 = 42;
volatile int triggerpin3 = 7;
volatile int echopin3 = 6;
volatile int triggerpin4 = 5;
volatile int echopin4 = 4;

volatile long time;          // Variable para guardar el tiempo viajado de la onda ultrasonica
volatile int S1, S2, S3, S4; // Variables para guardar la distancia cubierta

int t = 5; // distancia bajo la cual se buscara por vehiculos

void setup()
{
    Serial.begin(115200);
    Timer1.initialize(100000);
    Timer1.attachInterrupt(softInterr);

    // Declarando los pines de los led como salidas
    for (int i = 0; i < 3; i++)
    {
        pinMode(signal1[i], OUTPUT);
        pinMode(signal2[i], OUTPUT);
        pinMode(signal3[i], OUTPUT);
        pinMode(signal4[i], OUTPUT);
    }

    // Declarando pines de los sensores ultrasonicos como entradas o salidas
    pinMode(triggerpin1, OUTPUT);
    pinMode(echopin1, INPUT);
    pinMode(triggerpin2, OUTPUT);
    pinMode(echopin2, INPUT);
    pinMode(triggerpin3, OUTPUT);
    pinMode(echopin3, INPUT);
    pinMode(triggerpin4, OUTPUT);
    pinMode(echopin4, INPUT);
}

void loop()
{
    // Si hay vehiculos en el semaforo 1
    if (S1 < t)
    {
        signal1Function();
    }

    // Si hay vehiculos en el semaforo 2
    if (S2 < t)
    {
        signal2Function();
    }

    // Si hay vehiculos en el semaforo 3
    if (S3 < t)
    {
        signal3Function();
    }

    // Si hay vehiculos en el semaforo 4
    if (S4 < t)
    {
        signal4Function();
    }
}

// Esta es la funcion de interrupcion que correra cada vez que el perdio de tiempo del timer finalize.
void softInterr()
{
    // Leyendo del primer sensor ultrasonico
    digitalWrite(triggerpin1, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin1, LOW);
    time = pulseIn(echopin1, HIGH);
    S1 = time * 0.034 / 2;

    // Leyendo del segundo sensor ultrasonico
    digitalWrite(triggerpin2, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin2, LOW);
    time = pulseIn(echopin2, HIGH);
    S2 = time * 0.034 / 2;

    // Leyendo del tercer sensor ultrasonico
    digitalWrite(triggerpin3, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin3, LOW);
    time = pulseIn(echopin3, HIGH);
    S3 = time * 0.034 / 2;

    // Leyendo del cuarto sensor ultrasonico
    digitalWrite(triggerpin4, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin4, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin4, LOW);
    time = pulseIn(echopin4, HIGH);
    S4 = time * 0.034 / 2;

    // imprime los valores de la distancia obtenida en el monitor serial para comprobar el funcionamiento
    Serial.print("S1: ");
    Serial.print(S1);
    Serial.print("  S2: ");
    Serial.print(S2);
    Serial.print("  S3: ");
    Serial.print(S3);
    Serial.print("  S4: ");
    Serial.println(S4);
}

void signal1Function()
{
    Serial.println("1");
    low();
    // apaga el led rojo y enciende el verde por 5 segundos
    digitalWrite(signal1[0], LOW);
    digitalWrite(signal1[2], HIGH);
    delay(redDelay);

    // En caso de que hayan vehiculos en otras vias:
    if (S2 < t || S3 < t || S4 < t)
    {
        // apaga el led rojo y enciende el amarillo por 2 segundos
        digitalWrite(signal1[2], LOW);
        digitalWrite(signal1[1], HIGH);
        delay(yellowDelay);
    }
}

void signal2Function()
{
    Serial.println("2");
    low();
    digitalWrite(signal2[0], LOW);
    digitalWrite(signal2[2], HIGH);
    delay(redDelay);

    if (S1 < t || S3 < t || S4 < t)
    {
        digitalWrite(signal2[2], LOW);
        digitalWrite(signal2[1], HIGH);
        delay(yellowDelay);
    }
}

void signal3Function()
{
    Serial.println("3");
    low();
    digitalWrite(signal3[0], LOW);
    digitalWrite(signal3[2], HIGH);
    delay(redDelay);

    if (S1 < t || S2 < t || S4 < t)
    {
        digitalWrite(signal3[2], LOW);
        digitalWrite(signal3[1], HIGH);
        delay(yellowDelay);
    }
}

void signal4Function()
{
    Serial.println("4");
    low();
    digitalWrite(signal4[0], LOW);
    digitalWrite(signal4[2], HIGH);
    delay(redDelay);

    if (S1 < t || S2 < t || S3 < t)
    {
        digitalWrite(signal4[2], LOW);
        digitalWrite(signal4[1], HIGH);
        delay(yellowDelay);
    }
}

// Funcion para apagar todos los diodos led excepto los rojos:
void low()
{
    for (int i = 1; i < 3; i++)
    {
        digitalWrite(signal1[i], LOW);
        digitalWrite(signal2[i], LOW);
        digitalWrite(signal3[i], LOW);
        digitalWrite(signal4[i], LOW);
    }
    for (int i = 0; i < 1; i++)
    {
        digitalWrite(signal1[i], HIGH);
        digitalWrite(signal2[i], HIGH);
        digitalWrite(signal3[i], HIGH);
        digitalWrite(signal4[i], HIGH);
    }
}