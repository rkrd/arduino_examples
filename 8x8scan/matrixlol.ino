#include "heart.h"

uint8_t row[8] = {2,3,4,5,6,7,8,9};
uint8_t col[8] = {13,12,11,10,15,16,17,18};

uint8_t x[][8] = 
{
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1}
};
uint8_t xx[][16] =
{
  {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1}
};
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], HIGH);
  }
//    digitalWrite(col[4], LOW);
//  digitalWrite(row[6], HIGH);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Serial.print(xx[i][j+8]);
    }
    Serial.print("\n");
  }

}

void loop() {
  static uint32_t count = 0;
  static uint32_t off = 0;
  static uint32_t ii = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++)
      digitalWrite(col[j], HIGH);
      
      
    digitalWrite(row[i], HIGH);
    for (int j = 0; j < 8; j++) {
#ifdef XX
      if (xx[i][j+off])
#else
      if (x[i][j])
#endif
        digitalWrite(col[j], LOW);
      else
        digitalWrite(col[j], HIGH);
    }
    delay(2);
    digitalWrite(row[i], LOW);
  }

  if (count++ == 10) {
    uint16_t w = sizeof(xbm_bits) / 8;
    memset(x, 0, sizeof(x));
    for (int i = 0; i < (8 - off); i++) {
      x[0][i] = xbm_bits[w * 0 + ii] & (1<<(i+off)) ? 1 : 0;
      x[1][i] = xbm_bits[w * 1 + ii] & (1<<(i+off)) ? 1 : 0;
      x[2][i] = xbm_bits[w * 2 + ii] & (1<<(i+off)) ? 1 : 0;
      x[3][i] = xbm_bits[w * 3 + ii] & (1<<(i+off)) ? 1 : 0;
      x[4][i] = xbm_bits[w * 4 + ii] & (1<<(i+off)) ? 1 : 0;
      x[5][i] = xbm_bits[w * 5 + ii] & (1<<(i+off)) ? 1 : 0;
      x[6][i] = xbm_bits[w * 6 + ii] & (1<<(i+off)) ? 1 : 0;
      x[7][i] = xbm_bits[w * 7 + ii] & (1<<(i+off)) ? 1 : 0;
    }
    for (int i = 0; i < off; i++) {
      x[0][i+(8-off)] = xbm_bits[w * 0 + ii + 1] & (1<<i) ? 1 : 0;
      x[1][i+(8-off)] = xbm_bits[w * 1 + ii + 1] & (1<<i) ? 1 : 0;
      x[2][i+(8-off)] = xbm_bits[w * 2 + ii + 1] & (1<<i) ? 1 : 0;
      x[3][i+(8-off)] = xbm_bits[w * 3 + ii + 1] & (1<<i) ? 1 : 0;
      x[4][i+(8-off)] = xbm_bits[w * 4 + ii + 1] & (1<<i) ? 1 : 0;
      x[5][i+(8-off)] = xbm_bits[w * 5 + ii + 1] & (1<<i) ? 1 : 0;
      x[6][i+(8-off)] = xbm_bits[w * 6 + ii + 1] & (1<<i) ? 1 : 0;
      x[7][i+(8-off)] = xbm_bits[w * 7 + ii + 1] & (1<<i) ? 1 : 0;
    }

    count = 0;
    off++;
    if (off == 8) {
      off = 0;
      ii = (ii+1) % (w-1);
    }
  }
}
