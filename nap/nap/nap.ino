#include "programer.h"
#include "upload.h"
void setup() {
  Serial.begin(115200); /* Initialize serial for status msgs */

  while (!Serial)
    ;
  delay(100);
  setupProg();
  setupUpload();
}

void loop(void) {
 loopUpload();
}
