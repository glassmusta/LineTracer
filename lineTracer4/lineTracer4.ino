#define M1 2
#define E1 3
#define M2 4
#define E2 5

int pins[4] = {A0,A1,A2,A3};
int sensorRef[4] = {600,600,600,600};
int readPins[4];
int runState = 0;
bool status = false;
bool swStatus = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=2;i<6;++i) pinMode(i,OUTPUT);
  for(int i=0;i<4;++i) pinMode(pins[i],INPUT);
  pinMode(8,INPUT);
  digitalWrite(M2,HIGH);
  digitalWrite(M1,LOW);
}

void loop() {
  for(int i=0;i<4;++i){
    readPins[i] = analogRead(pins[i]);
  }

  if(digitalRead(8) == LOW && swStatus == true){
    status = !status;
    swStatus = false;
  }else if(digitalRead(8) == HIGH && swStatus == false){
    swStatus = true;
  }
  if(status){
     if(readPins[0]>sensorRef[0] && readPins[1]>sensorRef[1] && readPins[2]>sensorRef[2] && readPins[3]>sensorRef[3]) 
    {
      goFoward();
    }else
    if(readPins[0] < sensorRef[0])  // 맨 오른쪽 센서(A0)에 라인이 감지된 경우
    {
      turn(10,60);
    }
    else if(readPins[3] < sensorRef[3])  // 맨 왼쪽 센서(A5)에 라인이 감지된 경우
    {
      turn(60,10);
    }
    else if(readPins[1] < sensorRef[1])  // 오른쪽에서 두 번째 센서(A1)에 라인이 감지된 경우
    {
      turn(25,55); 
    }
    else if(readPins[2] < sensorRef[2])  // 왼쪽에서 두 번째 센서(A4)에 라인이 감지된 경우
    {
      turn(55,25);
    }
    else if(readPins[1]<sensorRef[1] && readPins[2]<sensorRef[2])
    {
      goFoward();
    }
    else if(readPins[0]<sensorRef[0] && readPins[1]<sensorRef[1])
    {
      turn(60,10);      
    }
    else if(readPins[2]<sensorRef[2] && readPins[3]<sensorRef[3])
    {
      turn(10,60);
    }else if(readPins[0]<sensorRef[0] && readPins[1]<sensorRef[1] && readPins[2]<sensorRef[2]){
      turn(10,60); 
    }else if(readPins[1]<sensorRef[1] && readPins[2]<sensorRef[2] && readPins[3]<sensorRef[3]){
      turn(60,10);
    }else{
      setup();
    }
  }else if(status == false){
    Stop();
  }
  //알고리즘 끝
  delay(20);
   
  }

void Stop(){
    digitalWrite(E2,LOW);
    digitalWrite(E1,LOW);
}
void goFoward(){
    analogWrite(E1,80);
    analogWrite(E2,80);
}
void turn(int l,int r){
    analogWrite(E1,l);
    analogWrite(E2,r);
}

