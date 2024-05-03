#include <FastLED.h>

// Configuration des LED
#define NUM_LEDS 300
#define LED_PIN 5
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define BRIGHTNESS 255

// Pin pour le bouton
#define BUTTON_PIN 4 // GPIO4

CRGB leds[NUM_LEDS];
bool boutonPresse = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW && !boutonPresse) {
    boutonPresse = true;
    remplirBandeaudeLEDs();
    delay(5000); // Attendre 5 secondes
    eteindreToutesLesLEDs();
    boutonPresse = false;
  }
}

void remplirBandeaudeLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    int indexLED = random(NUM_LEDS);
    while (leds[indexLED] != CRGB::Black) {
      indexLED = random(NUM_LEDS);
    }
    leds[indexLED] = CHSV(random(256), 255, 255); // Utilise CHSV pour générer des couleurs plus vives
    FastLED.show();
    delay(30);
  }
}

void eteindreToutesLesLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
  }
}
