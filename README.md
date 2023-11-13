# kalmanlike_autotuning
kalmanlike filter self tuning to the noise floor

Dreamed by BingAI

Sure, I can explain how the code works. The code implements a kalman-like auto-tuning filter, which is a technique to reduce the noise in a measurement by using a feedback loop. The code consists of three main parts: the setup, the loop, and the estimateNoise function.

- The setup part runs once when the Arduino board is powered on or reset. It does the following things:
    - It initializes the serial communication with the computer, so that the filtered value can be printed on the serial monitor.
    - It initializes the filtered value with the first reading from the analog input pin, which is defined by the PIN constant.
    - It initializes the filter gain with the initial value, which is defined by the K_INIT constant. The filter gain is a parameter that controls how much the filtered value is updated based on the measurement error. A higher filter gain means more responsiveness, but also more noise. A lower filter gain means more smoothness, but also more lag.
    - It initializes the measurement noise with a large value, which is 1023. The measurement noise is an estimate of how noisy the measurement is, and it is used to adjust the filter gain dynamically.

- The loop part runs repeatedly after the setup part. It does the following things:
    - It estimates the measurement noise using the estimateNoise function, which is explained later.
    - It reads the analog input from the pin, and stores it in a variable called z. This is the raw measurement that contains noise.
    - It calculates the measurement error, which is the difference between the raw measurement and the filtered value. The measurement error represents how much the filtered value deviates from the actual value.
    - It updates the filter gain using the measurement noise and the measurement error. The filter gain is calculated by multiplying the current filter gain by the ratio of the measurement noise and the sum of the measurement noise and the square of the measurement error. This formula ensures that the filter gain is proportional to the measurement noise and inversely proportional to the measurement error. The filter gain is also constrained between the minimum and maximum values, which are defined by the K_MIN and K_MAX constants. The idea behind this formula is that the filter gain should be higher when the measurement is noisy and lower when the measurement is accurate.
    - It updates the filtered value using the filter gain and the measurement error. The filtered value is calculated by adding the product of the filter gain and the measurement error to the previous filtered value. This formula ensures that the filtered value is corrected by a fraction of the measurement error, depending on the filter gain. The idea behind this formula is that the filtered value should be closer to the raw measurement when the filter gain is high and closer to the previous filtered value when the filter gain is low.
    - It prints the filtered value on the serial monitor, so that the user can see the result of the filtering process.
    - It waits for a short time, which is defined by the delay function. The delay function takes a parameter in milliseconds, and pauses the execution of the code for that amount of time. The delay function is used to control the sampling frequency of the measurement, which is the number of times the measurement is taken per second. A higher sampling frequency means more data, but also more noise. A lower sampling frequency means less data, but also less noise.

- The estimateNoise function is a custom function that is defined by the user. It takes no parameters and returns a float value, which is the estimate of the measurement noise. The function does the following things:
    - It declares a local variable to store the sum of squared differences, which is initialized to zero. The sum of squared differences is a measure of how much the measurement varies over time, and it is used to calculate the measurement noise.
    - It reads the first sample from the analog input pin, and stores it in a variable called prev. This is the previous measurement that is used to compare with the current measurement.
    - It loops through the remaining samples, which are defined by the N_SAMPLES constant. The N_SAMPLES constant is the number of samples to use for noise estimation, and it can be adjusted by the user. A higher number of samples means more accuracy, but also more time. A lower number of samples means less accuracy, but also less time.
        - It reads the next sample from the analog input pin, and stores it in a variable called curr. This is the current measurement that is used to compare with the previous measurement.
        - It calculates the difference between the current and previous measurements, and stores it in a variable called diff. The difference represents how much the measurement changes over time, and it is used to calculate the sum of squared differences.
        - It adds the square of the difference to the sum of squared differences, and updates the sum. The square of the difference is used to eliminate the negative values and to emphasize the large values. The sum of squared differences is used to calculate the measurement noise.
        - It updates the previous measurement with the current measurement, and prepares for the next iteration of the loop.
    - It returns the average of the sum of squared differences, which is the estimate of the measurement noise. The average is calculated by dividing the sum of squared differences by the number of samples minus one. The number of samples minus one is used to correct the bias in the estimation, and it is called the degrees of freedom. The estimate of the measurement noise is used to update the filter gain in the loop part.

I hope this explanation helps you understand how the code works. 😊
