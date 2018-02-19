#include "Matrix.h"
Matrix mat;
bool info[2];

#define Victim info[1]
#define Black info[0]

void setup() {
  Serial.begin(115200);
  mat.init();
  int arr[] = {10,20,30};
  mat.check(arr, 18, 14, 22);
  mat.move(1);
  mat.move(0);
  Serial.println(mat.end());
}

void loop(){  
  mat.getInfo(info);
  Serial.print(Victim);
  Serial.print(' ');
  Serial.println(Black);
  Serial.println(mat.getDir());
}
