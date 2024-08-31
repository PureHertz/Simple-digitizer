const int n_ave = 100;  // 移動平均回数
const int in = 10;  // アナログインプット端子

int cnt = 0;  // 移動平均用のカウント値
float temp[n_ave];  // 移動平均用の配列
float v_ave;  // 読み取り電圧値の移動平均 


void setup() {
  analogReadResolution(12);
  Serial.begin(19200);
}


void loop() {
  // --- 移動平均 ---
  if (cnt == n_ave) {
    cnt = 0;
  }
  temp[cnt] = analogRead(in);
  v_ave = 0.0;
  for (int i=0; i<n_ave; i++) {
    v_ave += temp[i];
  }
  v_ave = v_ave/n_ave * (3.3/4095.0);
  cnt += 1;
  
  // --- コマンドの処理 ---
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    
    // --- FETCH ---
    if ((cmd == "FETC?")||(cmd == "FETCh?")) {
      Serial.println(v_ave, 4);
    }
    else {
      Serial.println("");
    }
  }
}