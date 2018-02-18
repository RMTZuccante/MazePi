#ifndef MATRIX_H
#define MATRIX
#include <Arduino.h>
class Matrix {
  public:
    static String readLine() {      
      while(!Serial.available());
      String s;
      char c = Serial.read();
      do {
        s += c;
        while(!Serial.available());
        c = Serial.read();
      } while (c != '\n');
      return s;
    }
    
    Matrix(){
      String m;
      do {
        m = readLine();
        Serial.println(m);
        m = readLine();
      } while(m != "ok");
    }
    
    void _check(int dist[], int temperatureL, int temperatureR, int color){
      Serial.print("check ");
      Serial.print(dist[0]);
      Serial.print(' ');
      Serial.print(dist[1]);
      Serial.print(' ');
      Serial.print(dist[2]);
      Serial.print(' ');
      Serial.print(temperatureL);
      Serial.print(' ');
      Serial.print(temperatureR);
      Serial.print(' ');
      Serial.println(color);    
    }
  private:
};
#endif
