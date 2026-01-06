const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int BUTTON_PIN = 2; // 模組 IN 接 D2

int moodPoint = 10; // 初始中性
unsigned long lastPressTime = 0;
unsigned long lastDecayTime = 0;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT); // 模組內已經有電阻
  lastPressTime = millis();
  lastDecayTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // 讀取按鈕
  if (digitalRead(BUTTON_PIN) == LOW) { // 按下
    if (currentTime - lastPressTime > 200) { // 防彈跳
      moodPoint++;
      if (moodPoint > 20) moodPoint = 20;
      lastPressTime = currentTime;
      lastDecayTime = currentTime;
    }
  }

  // 沒按壓 5 秒後開始減分
  if (currentTime - lastPressTime > 5000) {
    if (currentTime - lastDecayTime > 1000) {
      moodPoint--;
      if (moodPoint < 0) moodPoint = 0;
      lastDecayTime = currentTime;
    }
  }

  // 計算 RGB 顏色
  int r, g, b;
  if (moodPoint <= 10) {
    r = map(moodPoint, 0, 10, 255, 0);
    g = map(moodPoint, 0, 10, 0, 255);
    b = 0;
  } else {
    r = 0;
    g = map(moodPoint, 10, 20, 255, 0);
    b = map(moodPoint, 10, 20, 0, 255);
  }

  // 共陽 LED 需要反轉亮度
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}
