
#include <GPxMatrix.h>

String a;
#define P_A    23
#define P_B    22
#define P_C    5
#define P_D    17
#define P_E    32
#define P_CLK  16
#define P_LAT  4
#define P_OE   15

GPxMatrix matrix(P_A, P_B, P_C, P_D, P_E, P_CLK, P_LAT, P_OE, false, 128);


void setup() {
  Serial.begin(115200);
   matrix.begin();
   matrix.setCursor(0, 0); 
 //matrix.print("hello");
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print("enter  to print in led matrix");
 a=Serial.readString();
 matrix.println(a);
 delay(5000);
}
