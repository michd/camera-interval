#define NUM_BTNS 2
#define BTN_PINS {8, 7}
#define TICK_MS 5
#define PULSE_TICKS 20
#define MIN_INTERVAL 1000

int btnPins[] = BTN_PINS;
boolean btnWasPressed[NUM_BTNS];

unsigned long lastPressTime = 0;

int led1Pin = 13;
int led2Pin = 12;
int actuatorPin = 11;

boolean led1State = false;
boolean led2State = false;

int intervalTicks = 0;
int intervalTickCount = 0;

boolean pulseActive = false;
boolean pulseLive = false;

void initButtons() {
  for(int i = 0; i < NUM_BTNS; i++) {
    pinMode(btnPins[i], INPUT);
    btnWasPressed[i] = false;
  }
}

/**
 * True if the button was just pressed (negative flank)
 */
boolean readButton(int index) {
  boolean btnIsPressed = !digitalRead(btnPins[index]);
  boolean output = false;
  
  if (btnWasPressed[index] && !btnIsPressed) {
    output = true;  
  }
  
  btnWasPressed[index] = btnIsPressed;
  return output;
}

void setup() {
  initButtons();
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(actuatorPin, OUTPUT);
  digitalWrite(led1Pin, pulseActive);
  digitalWrite(led2Pin, pulseLive);
  digitalWrite(actuatorPin, pulseActive);
}

void intervalBtnClicked() {
  unsigned long time = millis();
  
  
  if (lastPressTime > 0) {
    intervalTicks = (int)((time - lastPressTime) / TICK_MS);
    
    if (intervalTicks * TICK_MS <= MIN_INTERVAL) {
      intervalTicks = (int)(MIN_INTERVAL / TICK_MS);
    }
  }
  Serial.println(((time - lastPressTime) / TICK_MS));
  Serial.println(intervalTicks);
  lastPressTime = time;
  resetInterval();
}

void resetInterval() {
  pulseActive = false;
  intervalTickCount = 0;
}

void updatePulse() {
  if (intervalTicks == 0) {
    pulseActive = false;
    digitalWrite(led1Pin, pulseActive);
    return;
  }
  
  pulseActive = (intervalTickCount == 0);
  pulseActive = (intervalTickCount <= PULSE_TICKS);
  
  intervalTickCount++;
  if (intervalTickCount >= intervalTicks) intervalTickCount = 0;
  digitalWrite(led1Pin, pulseActive);
  digitalWrite(actuatorPin, pulseActive && pulseLive);
}

void loop() {
  if (readButton(0))
  {
    intervalBtnClicked();
  }
  
  if (readButton(1))
  {
    pulseLive = !pulseLive;
    digitalWrite(led2Pin, pulseLive);
  }
  
  updatePulse();
  delay(TICK_MS);
}


