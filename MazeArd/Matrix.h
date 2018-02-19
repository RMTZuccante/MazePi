#ifndef MATRIX_H
#define MATRIX
#include <Arduino.h>

#define FRONT 0
#define RIGHT 1
#define LEFT 2
#define BACK 3

class Matrix {
  public:
    static String readLine() {
      while (!Serial.available());
      String s;
      char c = Serial.read();
      do {
        s += c;
        while (!Serial.available());
        c = Serial.read();
      } while (c != '\n');
      return s;
    }

    Matrix() {}

    bool init() {
      int c = 0;
      String m;
      do {
        if (c > 10) {
          return 0;
        }
        m = readLine();
        Serial.println(m);
        m = readLine();
        c++;
      } while (m != "ok");
      return 1;
    }

    void check(int dist[], int temperatureL, int temperatureR, int color) {
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

    void getInfo(bool* arr) {
      Serial.println("getinfo");
      String s = readLine();
      arr[0] = s[0] - '0';
      arr[1] = s[2]  - '0';
    }

    void move(bool forward) {
      Serial.print("move ");
      Serial.println(forward ? "forth" : "back");
    }

    int getDir() {
      Serial.println("getdir");
      return readLine().toInt();
    }

    void backToStart() {
      Serial.println("tostart");
    }
    
    bool end() {
      Serial.println("end");
      return readLine()[0] - '0';
    }

    void die() {
      Serial.println("stop");
    }
  private:
};
#endif
