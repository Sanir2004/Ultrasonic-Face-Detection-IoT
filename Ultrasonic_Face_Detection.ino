// Define pin connections
const int trigPin = 2;
const int echoPin = 3;
const int LEDlampRed = 4;
const int LEDlampYellow = 5;
const int LEDlampGreen = 6;
const int buzzer = 7;

// Variables for ultrasonic sensor and distance calculation
long durationInDigit, distanceInCM;
bool faceDetected = false;

void setup() {
    Serial.begin(9600); // Initialize Serial Monitor for debugging and communication

    // Set pin modes
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LEDlampRed, OUTPUT);
    pinMode(LEDlampYellow, OUTPUT);
    pinMode(LEDlampGreen, OUTPUT);
    pinMode(buzzer, OUTPUT);

    // Ensure LEDs and buzzer are off initially
    digitalWrite(LEDlampRed, LOW);
    digitalWrite(LEDlampYellow, LOW);
    digitalWrite(LEDlampGreen, LOW);
    noTone(buzzer);
}

void loop() {
    // Check for face detection input from Serial
    if (Serial.available() > 0) {
        char input = Serial.read();
        if (input == '1') {
            faceDetected = true; // Face detected
        } else if (input == '0') {
            faceDetected = false; // No face detected
        }
    }

    if (faceDetected) {
        // Disable lights and buzzer if a face is detected
        digitalWrite(LEDlampRed, LOW);
        digitalWrite(LEDlampYellow, LOW);
        digitalWrite(LEDlampGreen, LOW);
        noTone(buzzer);
    } else {
        // Normal operation when no face is detected
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        // Read pulse duration
        durationInDigit = pulseIn(echoPin, HIGH);

        // Calculate distance in cm
        distanceInCM = (durationInDigit * 0.034) / 2;

        // Filter out invalid readings
        if (distanceInCM <= 0 || distanceInCM > 400) {
            distanceInCM = 400; // Treat as no object in range
        }

        // Control LEDs and buzzer based on distance
        if (distanceInCM > 50) {
            digitalWrite(LEDlampGreen, LOW);
            digitalWrite(LEDlampYellow, LOW);
            digitalWrite(LEDlampRed, LOW);
            noTone(buzzer);
        } else if (distanceInCM <= 50 && distanceInCM > 30) {
            digitalWrite(LEDlampGreen, HIGH);
            digitalWrite(LEDlampYellow, LOW);
            digitalWrite(LEDlampRed, LOW);
            noTone(buzzer);
        } else if (distanceInCM <= 30 && distanceInCM > 10) {
            digitalWrite(LEDlampGreen, HIGH);
            digitalWrite(LEDlampYellow, HIGH);
            digitalWrite(LEDlampRed, LOW);
            tone(buzzer, 700);
        } else {
            digitalWrite(LEDlampGreen, HIGH);
            digitalWrite(LEDlampYellow, HIGH);
            digitalWrite(LEDlampRed, HIGH);
            tone(buzzer, 1000);
            delay(300);
            digitalWrite(LEDlampRed, LOW);
            delay(300);
        }
    }

    // Debugging: Print distance and face detection status to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distanceInCM);
    Serial.print(" cm, Face Detected: ");
    Serial.println(faceDetected ? "Yes" : "No");

    delay(100); // Small delay to stabilize sensor readings
}
