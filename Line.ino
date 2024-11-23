//모터 드라이버 배선 http://www.makeshare.org/bbs/board.php?bo_table=motor_control&wr_id=11

// 핀 정의
#define SENSOR_1 A0
#define SENSOR_2 2
#define SENSOR_3 3
#define SENSOR_4 A3

#define MOTOR_LEFT_FORWARD 6
#define MOTOR_LEFT_BACKWARD 5
#define MOTOR_RIGHT_FORWARD 9
#define MOTOR_RIGHT_BACKWARD 10

// 속도 정의
#define SPEED 255
#define TURN_SPEED 200

// 모터 제어 함수
void motor(String side, int speed) {
  if (side == "LEFT" || side == "ALL") {
    if (speed > 0) {
      analogWrite(MOTOR_LEFT_FORWARD, speed);
      analogWrite(MOTOR_LEFT_BACKWARD, 0);
    } else {
      analogWrite(MOTOR_LEFT_FORWARD, 0);
      analogWrite(MOTOR_LEFT_BACKWARD, -speed);
    }
  }
  if (side == "RIGHT" || side == "ALL") {
    if (speed > 0) {
      analogWrite(MOTOR_RIGHT_FORWARD, speed);
      analogWrite(MOTOR_RIGHT_BACKWARD, 0);
    } else {
      analogWrite(MOTOR_RIGHT_FORWARD, 0);
      analogWrite(MOTOR_RIGHT_BACKWARD, -speed);
    }
  }
  if (side == "ALL" && speed == 0) {
    analogWrite(MOTOR_LEFT_FORWARD, 0);
    analogWrite(MOTOR_LEFT_BACKWARD, 0);
    analogWrite(MOTOR_RIGHT_FORWARD, 0);
    analogWrite(MOTOR_RIGHT_BACKWARD, 0);
  }
}

void setup() {
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);
  pinMode(SENSOR_4, INPUT);

  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // 센서 값 읽기
  int sensor1 = digitalRead(SENSOR_1);
  int sensor2 = digitalRead(SENSOR_2);
  int sensor3 = digitalRead(SENSOR_3);
  int sensor4 = digitalRead(SENSOR_4);

  // 센서 상태에 따른 모터 제어
  if (sensor2 == HIGH && sensor3 == HIGH) {
    // 직진
    motor("LEFT", SPEED);
    motor("RIGHT", SPEED);
  } else if (sensor1 == HIGH) {
    // 왼쪽으로 회전
    //motor("LEFT", -TURN_SPEED);
    //motor("RIGHT", TURN_SPEED);
  } else if (sensor4 == HIGH) {
    // 오른쪽으로 회전
    //motor("LEFT", TURN_SPEED);
    //motor("RIGHT", -TURN_SPEED);
  } else if (sensor2 == LOW && sensor3 == HIGH) {
    // 약간 오른쪽으로 조정
    motor("LEFT", SPEED);
    motor("RIGHT", SPEED / 9);
  } else if (sensor2 == HIGH && sensor3== LOW) {
    // 약간 왼쪽으로 조정
    motor("LEFT", SPEED / 9);
    motor("RIGHT", SPEED);
  } else {
    // 멈춤 (라인 이탈 시)
    motor("ALL", 0);
  }

  // 디버깅 출력
  /*
  Serial.print("S1: ");
  Serial.print(sensor1);
  Serial.print(" S2: ");
  Serial.print(sensor2);
  Serial.print(" S3: ");
  Serial.print(sensor3);
  Serial.print(" S4: ");
  Serial.println(sensor4);
*/
Serial.println(analogRead(A0));

  delay(10);
}
