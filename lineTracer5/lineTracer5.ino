#define M1 2
#define E1 3
#define M2 4
#define E2 5

int pins[4] = {9,10,11,12};
bool readPins[4];
//int sensorRef[4] = {600,600,600,600};
bool status = false;
bool swStatus = true;

void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<6;++i) pinMode(i,OUTPUT);
  for(int i=0;i<4;++i) pinMode(pins[i],INPUT);
  Serial.begin(9600);
  pinMode(8,INPUT);
  digitalWrite(M2,HIGH);
  digitalWrite(M1,LOW);
}

void loop() {
  for(int i=0;i<4;++i){
    readPins[i] = digitalRead(pins[i]);
  }
  if(digitalRead(8) == LOW && swStatus == true){
    status = !status;
    swStatus = false;
  }else if(digitalRead(8) == HIGH && swStatus == false){
    swStatus = true;
  }
  if(status){
    if(readPins[0] ==LOW && readPins[1] == LOW && readPins[2] == LOW && readPins[3] ==LOW){
      goFoward();
      Serial.println("1111");
    }
    else if(readPins[0]==LOW && readPins[1]==LOW || readPins[2] ==LOW)
    {
      Serial.println("1110");
      turn(80,20);      
    }
    else if(readPins[2]==LOW && readPins[3]==LOW || readPins[1] ==LOW)
    {
      Serial.println("0111");
      turn(20,80);
    }
     else if(readPins[1] ==LOW && readPins[2]==LOW)
    {
      Serial.println("0110");
      goFoward();
    }
    else if(readPins[0]==LOW)  // 맨 오른쪽 센서(A0)에 라인이 감지된 경우
    {
      Serial.println("1000");
      turn(20,80);
    }
    else if(readPins[3]==LOW)  // 맨 왼쪽 센서(A5)에 라인이 감지된 경우
    {
      Serial.println("0001");
      turn(80,20);
    }
    else if(readPins[1]==LOW)  // 오른쪽에서 두 번째 센서(A1)에 라인이 감지된 경우
    {
      Serial.println("0100");
      turn(30,80); 
    }
    else if(readPins[2]==LOW)  // 왼쪽에서 두 번째 센서(A4)에 라인이 감지된 경우
    {
      Serial.println("0010");
      turn(80,30);
    }
    else{
      Serial.println("0000");
      goFoward();
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
    analogWrite(E1,120);
    analogWrite(E2,120);
}
void turn(int l,int r){
    analogWrite(E1,l);
    analogWrite(E2,r);
}

