

/*
	Writen by Namyoung Lee,
	liutenant, a platoon leader of installation.
	OCT 20, 2013 
*/

#include <MsTimer2.h>

const int latchPin = 5;
const int clockPin = 12;
const int dataPin = 13;
const int ledChp[8] = {128, 64, 32, 16, 8, 4, 2, 1};

const int ledNml[] = {3, 11};
const int btNoml[] = {9, 10, 2, 4, 7, 8};
const int btInfA[] = {A0, A1};
const int btInfS[] = {A2, A3};
const int speaker = 6;

const int LEDNML = sizeof(ledNml) / sizeof(ledNml[0]);
const int BTNOML = sizeof(btNoml) / sizeof(btNoml[0]);
const int BTINFS = sizeof(btInfS) / sizeof(btInfS[0]);
const int BTINFA = sizeof(btInfA) / sizeof(btInfA[0]);
const int debounceDelay = 20; // 스위치가 안정될 때까지 기다리는 값 (ms)
const unsigned long interval = 5000; // 알람 beep음의 간격(ms)
unsigned long perTable[ BTNOML + BTINFS + BTINFA ] = {millis() - interval, millis() - interval,millis() - interval,millis() - interval,millis() - interval,millis() - interval,millis() - interval,millis() - interval,millis() - interval,millis() - interval};
boolean sdTable[ BTNOML + BTINFS + BTINFA ];
const int minHV = 250;

void setup(){
//	Serial.begin(9600);

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	// LED 핀 세팅
	for(int led = 0; led < LEDNML; led++)
		pinMode(ledNml[led], OUTPUT);
	
	// 스위치 핀 세팅
	for(int sw = 0; sw < BTNOML; sw++){
		pinMode(btNoml[sw], INPUT);
		digitalWrite(btNoml[sw], HIGH); // 내부 풀업 저항 작동
	}
	for(int sw = 0; sw < BTINFA; sw++){
		pinMode(btInfA[sw], INPUT);
		digitalWrite(btInfA[sw], HIGH); // 내부 풀업 저항 작동
	}
	for(int sw = 0; sw < BTINFS; sw++){
		pinMode(btInfS[sw], INPUT);
		digitalWrite(btInfS[sw], HIGH); // 내부 풀업 저항 작동
	}
	// Test Pin Setting
//	pinMode(13, OUTPUT);
}

void loop(){

boolean btTable[ BTNOML + BTINFA + BTINFS ];
int ledPin = 0;
int chPin = 2;
int beepCtr = 0;

	// 위병소 btNoml[0] : 0 pin, ledNml[0] : 3 pin
	onPeriod(btNoml[0], btTable[0], perTable[0]); // 핀검사.   시간값 초기화
	if(0 < (millis() - perTable[0]) && (millis() - perTable[0]) < interval ){
		digitalWrite(ledNml[0], HIGH);
		sdTable[0] = HIGH;
	}else{
		digitalWrite(ledNml[0], LOW);
		sdTable[0] = LOW;
	}
	// 탄약초소 btNoml[1] : 1 pin, ledNml[1] : 11 pin
	onPeriod(btNoml[1], btTable[1], perTable[1] ); // 핀검사.   시간값 초기화
	if(0 < (millis() - perTable[1]) && (millis() - perTable[1]) < interval ){
		digitalWrite(ledNml[1], HIGH);
		sdTable[1] = HIGH;
	}else{
		digitalWrite(ledNml[1], LOW);
		sdTable[1] = LOW;
	}

	// 수색 1 btNoml[2] : 2 pin , ledNml[2] : (1)
	chPin = checkPin(btNoml[2], btTable[2]);
	if(chPin == -1)
		ledPin += ledChp[0];
	if(chPin == 0)
		perTable[2] = millis();
	if(0 < (millis() - perTable[2]) && (millis() - perTable[2]) < interval ){
		sdTable[2] = HIGH;
		beepCtr++;
		if(chPin == 2)
			beepCtr--;
	}else
		sdTable[2] = LOW;
//	if(nonPeriod(btNoml[2], btTable[2], beepCtr )){
//		selecPin += ledChp[0];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}else{
//		selecPin -= ledChp[0];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}

	// 수색 2 btNoml[3] : 4 pin, ledNml[] : (2)
	chPin = checkPin(btNoml[3], btTable[3]);
	if(chPin == -1)
		ledPin += ledChp[1];
	if(chPin == 0)
		perTable[3] = millis();
	if(0 < (millis() - perTable[3]) && (millis() - perTable[3]) < interval ){
		sdTable[3] = HIGH;
		beepCtr++;
		if(chPin == 2)
			beepCtr--;
	}else
		sdTable[3] = LOW;
//	if(nonPeriod(btNoml[3], btTable[3], beepCtr )){
//		selecPin += ledChp[1];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}else{
//		selecPin -= ledChp[1];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}


	// 본부&통신 btNoml[4] : 7 pin, ledNml[] : (4)
	chPin = checkPin(btNoml[4], btTable[4]);
	if(chPin == -1)
		ledPin += ledChp[2];
	if(chPin == 0)
		perTable[4] = millis();
	if(0 < (millis() - perTable[4]) && (millis() - perTable[4]) < interval ){
		sdTable[4] = HIGH;
		beepCtr++;
		if(chPin == 2)
			beepCtr--;
	}else
		sdTable[4] = LOW;
//		if(nonPeriod(btNoml[4], btTable[4], beepCtr )){
//		selecPin += ledChp[2];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}else{
//		selecPin -= ledChp[2];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}
	// 무기고 btNoml[5] : 8 pin, ledNml[3] : (8)
	chPin = checkPin(btNoml[5], btTable[5]);
		if(chPin == -1)
		ledPin += ledChp[3];
	if(chPin == 0)
		perTable[5] = millis();
	if(0 < (millis() - perTable[5]) && (millis() - perTable[5]) < interval ){
		sdTable[5] = HIGH;
		beepCtr++;
		if(chPin == 2)
			beepCtr--;
	}else
		sdTable[5] = LOW;
//	if(nonPeriod(btNoml[5], btTable[5], beepCtr )){
//		selecPin += ledChp[3];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}else{
//		selecPin -= ledChp[3];
//		digitalWrite(latchPin, LOW);
//		shifOut(selecPin);
//		digitalWrite(latchPin, HIGH);
//	}
	// 적외선A형 울타리1 : 16 pin, (16)
	chPin = analogRead(btInfA[0]);
	if(chPin >= minHV)
		perTable[6] = millis();
	if(0 < (millis() - perTable[6]) && (millis() - perTable[6]) < interval ){
		ledPin += ledChp[4];
		sdTable[6] = HIGH;
	}else{
		sdTable[6] = LOW;
	}

	// 적외선A형 울타리2 : 17 pin, LED : (32)
	chPin = analogRead(btInfA[1]);
	if(chPin >= minHV)
		perTable[7] = millis();
	if(0 < (millis() - perTable[7]) && (millis() - perTable[7]) < interval ){
		ledPin += ledChp[5];
		sdTable[7] = HIGH;
	}else{
		sdTable[7] = LOW;
	}

	// 적외선S형 탄약고 : (A) 0 pin (D) 14 pin, LED : (64)
	chPin = analogRead(btInfS[0]);
	if(chPin >= minHV)
		perTable[8] = millis();
	if(0 < (millis() - perTable[8]) && (millis() - perTable[8]) < interval ){
		ledPin += ledChp[6];
		sdTable[8] = HIGH;
	}else{
		sdTable[8] = LOW;
	}	
	// 적외선S형 무기고 : (A) 1 pin (D) 15 pin,  LED : (128)
	chPin = analogRead(btInfS[1]);
	if(chPin >= minHV){
		perTable[9] = millis();
	}
	if(0 < (millis() - perTable[9]) && (millis() - perTable[9]) < interval ){
		ledPin += ledChp[7];
		sdTable[9] = HIGH;
	}else{
		sdTable[9] = LOW;
	}

//	// Test Pin 
//	if(nonPeriod(7, btTable[5], beepCtr ))
//		digitalWrite(13 , HIGH);
//	else
//		digitalWrite(13 , LOW);

	// LED 출력
	digitalWrite(latchPin, LOW);
	shifOut(ledPin);
	digitalWrite(latchPin, HIGH);
	
	//사운드 출력을 위한 카운터 검사
	if(beepCtr != 0 || sdTable[0] || sdTable[1] || sdTable[6] || sdTable[7] || sdTable[8] || sdTable[9] ){ 	
		MsTimer2::set(200, beep ); // 타이머2 세팅
		MsTimer2::start();
	}else
		MsTimer2::stop();
	
	stabilieMillis();
	delay(200);
}

void stabilieMillis() {
	for(int i = 0; i < 6; i++) {
		if((perTable[i] -  1000) < millis() && millis() < perTable[i])
			perTable[i] = millis() - interval;
	}
}

int checkPin(int pin, boolean &pSt) // 일정 시간을 두는 스위치
{
    boolean state;
    boolean previousState;

    previousState = digitalRead(pin); // 스위치의 상태를 저장
    for(int counter=0; counter < debounceDelay; counter++)
    {
        delay(1);   // 1밀리초 동안 대기
        state = digitalRead(pin); //핀을 읽음
        if(state != previousState)
        {
            counter = 0; //상태가 변경되면 카운터를 재설정한다.
            previousState = state; //그리고 현재 상태를 저장한다.
        }
    }
    //스위치가 디바운스 기간보다 긴 시간 동안 안정된 상태를 유지하게 되면 여기에 도달하게 된다.
	// 스피커 카운트와 이전 상태값 저장 디바운스값 리턴
	if(state == LOW ) {
		if (pSt == LOW ) {
			pSt = LOW;
			return 2;
		}else {
			pSt = LOW;
			return 1;
		}
	}else {
		if(pSt == HIGH ){
			pSt = HIGH;
			return -1;
		}else {
			pSt = HIGH;
			return 0;
		}
	}
}

void onPeriod(int pin, boolean &pSt, unsigned long &time) // 일정 시간을 두는 스위치
{
    boolean state;
    boolean previousState;

    previousState = digitalRead(pin); // 스위치의 상태를 저장
    for(int counter=0; counter < debounceDelay; counter++)
    {
        delay(1);   // 1밀리초 동안 대기
        state = digitalRead(pin); //핀을 읽음
        if(state != previousState)
        {
            counter = 0; //상태가 변경되면 카운터를 재설정한다.
            previousState = state; //그리고 현재 상태를 저장한다.
        }
    }
    //스위치가 디바운스 기간보다 긴 시간 동안 안정된 상태를 유지하게 되면 여기에 도달하게 된다.
	// 스피커 카운트와 이전 상태값 저장 디바운스값 리턴
	if(state == LOW ) {
		if (pSt == LOW ) {
			pSt = LOW;
		}else {
			pSt = LOW;
		}
	}else {
		if(pSt == HIGH ){
			pSt = HIGH;
		}else {
			time = millis(); 
			pSt = HIGH;
		}
	}
}

void shifOut(byte dataOut ){
	boolean pinState;

	digitalWrite(dataPin, LOW);
	digitalWrite(clockPin, LOW);

	for(int i = 0; i <= 7; i++){
		digitalWrite(clockPin, LOW);
		if(dataOut & (1<<i)){
			pinState = HIGH;
		}else{
			pinState = LOW;
		}
		digitalWrite(dataPin, pinState);
		digitalWrite(clockPin, HIGH);
	}
	digitalWrite(clockPin, LOW);
}

// 비프음을 출력
void beep() {
	if(sdTable[0] || sdTable[1] ) {
		int period = 1000000L / 2000;
		int pulse = period / 2;
		for(long i = 0; i < 477 * 1000L; i += period ){
			digitalWrite(speaker, HIGH);
			delayMicroseconds(pulse);
			digitalWrite(speaker, LOW);
			delayMicroseconds(pulse);
		}
	}else if(sdTable[2] || sdTable[3] || sdTable[4] || sdTable[5]) {
		int	period = 1000000L / 1460;
		int	pulse = period /2;
			for(long i = 0; i < 174 * 1000L; i += period ){
			digitalWrite(speaker, HIGH);
			delayMicroseconds(pulse);
			digitalWrite(speaker, LOW);
			delayMicroseconds(pulse);
		}
	}
	tone(speaker, 1360, 170);
}




