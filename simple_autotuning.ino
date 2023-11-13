// Define the number of samples to use for noise estimation
#define N_SAMPLES 10

// Define the initial filter gain
#define K_INIT 0.5

// Define the minimum and maximum filter gain
#define K_MIN 0.01
#define K_MAX 0.99

// Define the pin to read the analog input
#define PIN A0

// Declare global variables
float x; // The filtered value
float k; // The filter gain
float e; // The measurement error
float s; // The measurement noise

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the filtered value with the first reading
  x = analogRead(PIN);

  // Initialize the filter gain with the initial value
  k = K_INIT;

  // Initialize the measurement noise with a large value
  s = 1023;
}

void loop() {
  // Estimate the measurement noise using multiple short consecutive reads
  s = estimateNoise();

  // Read the analog input
  float z = analogRead(PIN);

  // Calculate the measurement error
  e = z - x;

  // Update the filter gain using the measurement noise
  k = constrain(k * s / (s + e * e), K_MIN, K_MAX);

  // Update the filtered value using the filter gain and the measurement error
  x = x + k * e;

  // Print the filtered value
  Serial.println(x);

  // Wait for a short time
  delay(10);
}

// A function to estimate the measurement noise using multiple short consecutive reads
float estimateNoise() {
  // Declare a local variable to store the sum of squared differences
  float ssd = 0;

  // Read the first sample
  float prev = analogRead(PIN);

  // Loop through the remaining samples
  for (int i = 1; i < N_SAMPLES; i++) {
    // Read the next sample
    float curr = analogRead(PIN);

    // Calculate the difference between the current and previous samples
    float diff = curr - prev;

    // Add the squared difference to the sum
    ssd += diff * diff;

    // Update the previous sample
    prev = curr;
  }

  // Return the average of the sum of squared differences
  return ssd / (N_SAMPLES - 1);
}
