#define M1 2
#define E1 3
#define M2 4
#define E2 5

int pins[4] = {9,10,11,12};
//int sensorRef[4] = {600,600,600,600};
int readPins[4];
bool status = false;
bool swStatus = true;

void setup() {
  // put your setup code here, to run once:
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
     if(digitalRead(readPins[0])==HIGH && digitalRead(readPins[1])==HIGH && digitalRead(readPins[2])==HIGH && digitalRead(readPins[3])==HIGH) 
    {
      goFoward();
    }else if(digitalRead(readPins[0]) ==LOW && digitalRead(readPins[1]) == LOW && digitalRead(readPins[2]) == LOW && digitalRead(readPins[3]) ==LOW){
      goFoward();
    }else if(digitalRead(readPins[0])==LOW && digitalRead(readPins[1])==LOW && digitalRead(readPins[2])==LOW){
      turn(10,60); 
    }else if(digitalRead(readPins[1])==LOW && digitalRead(readPins[2])==LOW && digitalRead(readPins[3])==LOW){
      turn(60,10);
    }
    else if(digitalRead(readPins[1]) ==LOW && digitalRead(readPins[2])==LOW)
    {
      goFoward();
    }
    else if(digitalRead(readPins[0])==LOW && digitalRead(readPins[1])==LOW)
    {
      turn(60,10);      
    }
    else if(digitalRead(readPins[2])==LOW && digitalRead(readPins[3])==LOW)
    {
      turn(10,60);
    }
    else if(digitalRead(readPins[0])==LOW)  // 맨 오른쪽 센서(A0)에 라인이 감지된 경우
    {
      turn(10,60);
    }
    else if(digitalRead(readPins[3])==LOW)  // 맨 왼쪽 센서(A5)에 라인이 감지된 경우
    {
      turn(60,10);
    }
    else if(digitalRead(readPins[1])==LOW)  // 오른쪽에서 두 번째 센서(A1)에 라인이 감지된 경우
    {
      turn(25,55); 
    }
    else if(digitalRead(readPins[2])==LOW)  // 왼쪽에서 두 번째 센서(A4)에 라인이 감지된 경우
    {
      turn(55,25);
    }
    else{
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

