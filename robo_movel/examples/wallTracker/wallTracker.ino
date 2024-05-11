#include <robo_movel.h>

void setup() {
  setupConfig(115200);
  delay(3000);
}

void loop() {
  wallTracker();
}

