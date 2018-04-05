#define Trig 8

#define Echo 9

const int inA1 = 5;// IN2 pin 5
const int inA2 = 7;// IN1 pin 7
const int enA = 6;

const int inB1 = 2; // IN4 pin 2
const int inB2 = 4; // IN3 pin 4
const int enB = 3;

const int powerDC = 255;//мощность ШИМ
const int DelayUltrasonicSensor = 1000; // задержка измерения датчиком расстояния


void setup() {
// датчик ультразвуковой
    pinMode(Trig, OUTPUT); // выход
    pinMode(Echo, INPUT); // вход


    pinMode(inA1, OUTPUT);// выход на L298n передние колеса
    pinMode(inA2, OUTPUT);// выход на L298n передние колеса
    pinMode( enA , OUTPUT);// выход на L298n передние колеса

    pinMode(inB1, OUTPUT);// выход на L298n задние колеса
    pinMode(inB2, OUTPUT); // выход на L298n задние колеса
    pinMode( enB , OUTPUT);// выход на L298n задние колеса

    analogWrite(enB, powerDC);
    analogWrite(enA, powerDC);

}

unsigned int impulseTime = 0;
unsigned int distance_sm = 0;

void loop() {

    distance_sm = getDistance();

// если расстояние более 40 сантиметров просто еду вперед
    if (distance_sm >= 60)
    {
// delay(1000);
        stopTurn();
        forvardMove();
    } else {
        if (distance_sm >= 20)
        {
// delay(1000);
// если расстояние более 20 сантиметров но менее 40;
//пытаюсь объехать:
            turnLeft();
            forvardMove();

        } else {
// delay(1000);
// выключаю поворт...
            stopTurn();
// если расстояние менее 20 сантиметров полный назад

            bacwardMove();

        }
    }
}

//измеряем растояние датчиком ульразвука
int getDistance() {

    impulseTime = 0;
// включаю датчик
    digitalWrite(Trig, HIGH);
//ждем
    delayMicroseconds(DelayUltrasonicSensor);
//выключаю датчик
    digitalWrite(Trig, LOW);

// замеряем длину импульса
    impulseTime = pulseIn(Echo, HIGH);
// ответ возвращаю в сантиметрах
    return impulseTime / 58;
}

void forvardMove() {
    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
}

void bacwardMove() {
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
}

void turnLeft() {
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
}


void turnRight() {
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
}

void stopTurn() {
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, LOW);
}

