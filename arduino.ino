// Pin Configurations
#define trafficRedPin 10
#define trafficYellowPin 11
#define trafficGreenPin 12
#define pedestrianGreenPin 13
#define buttonPin 8        // Push button for triggering pedestrian crossing
#define buttonIndicatorPin 9 // Button press indicator light

// 7-segment display pins (A-G): Pins 1 to 7
const int segPins[] = {1, 2, 3, 4, 5, 6, 0};

// Variables
int countdown = 9;               // Countdown starting at 9
bool buttonPressed = false;      // Flag to check button press
unsigned long previousMillis = 0; // Used for timing of the button press
bool isPedestrianCrossing = false; // Flag to check if pedestrian is crossing

void setup() {
  // Set all traffic and pedestrian LED pins as output
  DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB4); // Pins 10-12 (Traffic lights)
  DDRB |= (1 << DDB5); // Pin 13 (Pedestrian green light)
  DDRB |= (1 << DDB1); // Pin 9 (Button indicator)

  // Set button pin as input
  DDRB &= ~(1 << DDB0); // Pin 8 (Button input)
  PORTB |= (1 << PORTB0); // Enable pull-up resistor on pin 8

  // Set up 7-segment display pins as output
  DDRD |= 0x7F; // Set pins 1 to 7 (A-G) as output

  // Initial States
  PORTB &= ~(1 << PORTB2); // Traffic red OFF
  PORTB &= ~(1 << PORTB3); // Traffic yellow OFF
  PORTB |= (1 << PORTB4);  // Traffic green ON
  PORTB &= ~(1 << PORTB5); // Pedestrian green OFF
  PORTB &= ~(1 << PORTB1); // Button indicator OFF
}

void loop() {
  // Read button state
  bool buttonState = !(PINB & (1 << PINB0)); // Read button pin directly (Active LOW)

  if (buttonState && !buttonPressed && !isPedestrianCrossing) {
    buttonPressed = true;
    PORTB |= (1 << PORTB1); // Button indicator ON
    startTrafficSequence();
  }

  if (isPedestrianCrossing) {
    // Countdown logic
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) { // 1-second interval
      previousMillis = currentMillis;
      countdown--;
      update7SegmentDisplay(countdown);

      // Blink pedestrian green light
      if (countdown % 2 == 0) {
        PORTB |= (1 << PORTB5); // Pedestrian green ON
      } else {
        PORTB &= ~(1 << PORTB5); // Pedestrian green OFF
      }

      // Check if countdown is complete
      if (countdown <= 0) {
        finishPedestrianCrossing();
      }
    }
  }
}

void startTrafficSequence() {
  // Turn off traffic green and turn on traffic yellow
  PORTB &= ~(1 << PORTB4); // Traffic green OFF
  PORTB |= (1 << PORTB3);  // Traffic yellow ON
  delay(2000); // Wait for 2 seconds

  // Turn off traffic yellow and turn on traffic red
  PORTB &= ~(1 << PORTB3); // Traffic yellow OFF
  PORTB |= (1 << PORTB2);  // Traffic red ON
  delay(7000); // Wait for 7 seconds

  // Turn off pedestrian red and turn on pedestrian green
  countdown = 9; // Reset countdown to 9 seconds
  isPedestrianCrossing = true;
}

void finishPedestrianCrossing() {
  // End pedestrian crossing
  PORTB &= ~(1 << PORTB5); // Pedestrian green OFF
  PORTB &= ~(1 << PORTB2); // Traffic red OFF
  PORTB |= (1 << PORTB4);  // Traffic green ON
  isPedestrianCrossing = false;
  buttonPressed = false; // Reset button press flag
  PORTB &= ~(1 << PORTB1); // Button indicator OFF
}

void update7SegmentDisplay(int number) {
  // 7-segment display representation for numbers 0-9 (Common Cathode)
  const byte numToSegment[10] = {
    B01111110 , B00001100 , B00110111 , B00011111 , B01001101 ,
    B01011011 , B01111011 , B00001110 , B01111111 , B01011111
  };

  // Ensure the number is between 0 and 9
  if (number >= 0 && number <= 9) {
    byte segment = numToSegment[number];
    PORTD = (PORTD & 0x80) | (segment & 0x7F); // Set the lower 7 bits for the display
  }
}
