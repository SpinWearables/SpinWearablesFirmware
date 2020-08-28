// Here we define a convenient pausing function
// that waits a given number of seconds
void delay_seconds(int number_of_seconds) {
  int number_of_milliseconds = 1000 * number_of_seconds;
  delay(number_of_milliseconds);
}


// This is the setup function that will automatically run
// first when the device starts.
void setup() {
  // The next line ensures that the communication hardware
  // on our device is ready to send messages.
  // The name "Serial" is such for historical reasons
  // (it is the name for this type of communication).
  Serial.begin(9600); // The 9600 is the speed of the conection.
}

// Define a variable in which we will store a counter that goes up by one on
// each step.
int counter = 1;

// This function runs repeatedly after the setup function finishes.
void loop() {
  // Send a message to the connected computer.
  // The message will just be the value of the counter.
  Serial.println(counter);
  // Increment the value of the counter.
  counter = counter + 1;
  // Wait for a second before you start the loop function again.
  delay_seconds(1);
}
