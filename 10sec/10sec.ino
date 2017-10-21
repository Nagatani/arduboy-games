#include <Arduboy2.h>
#define DEBUG_MODE 0  //1: DEBUG (Show Time & FrameCount)
Arduboy2 ab;

boolean start_flag; // ゲーム開始管理フラグ
boolean stop_flag;  // タイマーストップ・ゲーム終了を管理するフラグ

long fc;      // フレームカウンタ
double sec;   // 秒
double msec;  // ミリ秒

void setup() {
  ab.begin();
  ab.setFrameRate(60);
  reset_game();
}

void loop() {
  // お約束
  if (!(ab.nextFrame())) return;
  // ボタン処理の暴発を防ぐためのおまじない
  ab.pollButtons();

  if (!start_flag) {
    // ゲーム開始前
    if( ab.justPressed(A_BUTTON) ) {  // justPressed使わないと暴発する
      // ゲームスタート
      start_flag = true;
    }
    return;
  }
  if (start_flag && stop_flag) {
    // ゲーム開始後からタイマーストップの状態
    if( ab.justPressed(A_BUTTON) ) {
      // 最初から
      reset_game();
    }
    return;
  }
  
  ab.clear();

  // フレームカウント開始
  fc += 1;
  // 秒数の計算
  sec = (double)fc / 60;
  msec = (double)fc * 1000 / 60;
  
  ab.setCursor(0, 0);
  ab.print("Now, let's count 10s!");
  ab.setCursor(0, 8);
  ab.print("press [A] perfectly!");

  // デバッグモードの場合はフレームカウントとミリ秒を表示
  if (DEBUG_MODE == 1) {
    ab.setCursor(0, 48);
    ab.print(msec);
    ab.setCursor(0, 56);
    ab.print(fc);
  }
  // タイマーストップを監視
  if (ab.justPressed(A_BUTTON)) {
    stop_timer();
  }

  // 諸々画面表示
  ab.display();
}

// タイマーストップ
void stop_timer() {
  stop_flag = true;
  
  ab.setCursor(0, 24);
  ab.print("Result:");
  ab.setCursor(44, 24);
  ab.print(sec);
  ab.setCursor(44, 32);
  double dif;
  dif = abs(msec - 10000);
  if (dif <= 10) {
    ab.print("Perfect!!1");
  } else if (dif <= 50) {
    ab.print("Great!!");
  } else if (dif <= 100) {
    ab.print("Nice!");
  } else if (dif < 200) {
    ab.print("fmm...");
  } else {
    ab.print("oh...");
  }
  ab.setCursor(24, 56);
  ab.print("Restart with A");
}

// ゲームリセット
void reset_game() {
  ab.clear();
  fc = 0;
  msec = 0.0;
  stop_flag = false;
  start_flag = false;
  show_startscreen();
}
// 起動画面
void show_startscreen() {
  ab.clear();
  ab.setCursor(32, 24);
  ab.print("10sec Game");
  ab.setCursor(24, 40);
  ab.print("Start with A");
  ab.setCursor(16, 48);
  ab.print("and Stop with A");
  ab.setCursor(24, 56);
  ab.print("after 10 sec");
  ab.display();
}


