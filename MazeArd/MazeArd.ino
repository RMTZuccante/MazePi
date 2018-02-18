#include "Matrix.h"
void setup() {
  Serial.begin(115200);
  Matrix mat;
  int arr[] = {10,20,30};
  mat._check(arr, 18, 14, 22);
}

void loop(){
}
