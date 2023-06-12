#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4
#define LED_BLUE 5
#define UNKNOWN -1

#define BUTTON_GREEN 8
#define BUTTON_YELLOW 9
#define BUTTON_RED 10
#define BUTTON_BLUE 11

#define SECOND 1000
#define HALF_SECOND 500

#define POTENCIOMETER 0

#define LEDS_LENGTH 4

int ledSteps[LEDS_LENGTH];
int currentStepProgram = 0;
int ledsCountResponse = 0;

enum statesProgram {
  READY,
  ANSWERING,
  WINNER,
  LOSER,
};

void setup() {
  Serial.begin(9600);
  setPorts();
  initApp();
}

void loop() {
  switch (currentStep()) {
    case READY:
      Serial.println("PRONTO");
      startGame();
      break;
    case ANSWERING:
      Serial.println("RESPONDENDO");
      userAnswering();
      break;
    case WINNER:
      Serial.println("VENCEDOR");
      blinkWin();
      break;
    case LOSER:
      Serial.println("PERDEDOR");
      blinkGameOver();
      break;
  }
}

void setPorts() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
}

void initApp() {
  randomSeed(analogRead(POTENCIOMETER));

  for (int i = 0; i < LEDS_LENGTH; i++) {
    ledSteps[i] = random(LED_GREEN, LED_BLUE + 1);
  }
}

int currentStep() {
  if (currentStepProgram <= LEDS_LENGTH) {
    if (currentStepProgram == ledsCountResponse) {
      return READY;
    }
    return ANSWERING;
  } else if (currentStepProgram == LEDS_LENGTH + 1) {
    return WINNER;
  } else {
    return LOSER;
  }
}

void startGame() {
  currentStepProgram++;
  ledsCountResponse = 0;

  if (currentStepProgram <= LEDS_LENGTH) {
    for (int i = 0; i < currentStepProgram; i++) {
      blinkLed(ledSteps[i]);
    }
  }
}

void userAnswering() {
  int response = checkButtonPressed();

  if (response == UNKNOWN) {
    return;
  }

  if (response == ledSteps[ledsCountResponse]) {
    ledsCountResponse++;
  } else {
    currentStepProgram = LEDS_LENGTH + 2;
  }
}

int blinkLed(int port) {
  digitalWrite(port, HIGH);
  delay(SECOND);
  digitalWrite(port, LOW);
  delay(HALF_SECOND);

  return port;
}

int checkButtonPressed() {
  if (digitalRead(BUTTON_GREEN) == LOW) {
    return blinkLed(LED_GREEN);
  }
  if (digitalRead(BUTTON_YELLOW) == LOW) {
    return blinkLed(LED_YELLOW);
  }
  if (digitalRead(BUTTON_RED) == LOW) {
    return blinkLed(LED_RED);
  }
  if (digitalRead(BUTTON_BLUE) == LOW) {
    return blinkLed(LED_BLUE);
  }

  return UNKNOWN;
}

void blinkWin() {
  blinkLed(LED_GREEN);
  blinkLed(LED_YELLOW);
  blinkLed(LED_RED);
  blinkLed(LED_BLUE);
  delay(HALF_SECOND);
}

void blinkGameOver() {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  delay(SECOND);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(HALF_SECOND);
}