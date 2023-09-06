# Task_6_2

# Every Step Matter

---

### Description

The objective of this task is to interface with the encoder and calculate the cut-off frequency required to design a low-pass filter for the encoder.

### Code

- ********************Functions********************
    
    encoder_PinA
    
    ```arduino
    // checks whether the encoder is rotating clockwise or counter-clockwise
    // and increment or decrement the cycles count upon that.
    **if (digitalRead(PIN_A) == digitalRead(PIN_B))
        counter--;
    else
        counter++;**
    ```
    
    encoder_PinB
    
    ```arduino
    // checks whether the encoder is rotating clockwise or counter-clockwise
    // and increment or decremenet the cycles count upon that.
    **if (digitalRead(PIN_A) == digitalRead(PIN_B))
        counter++;
    else
        counter--;**
    ```
    

### Low-Pass Filter

The filter to be designed for this encoder will need to have a minimum cut-off frequency of 215 Hz.

**********************Explanation**********************

> **Given the following values:**
> 
> 
> Resolution = 540 pulse per revolution,
> 
> Vmax = 0.5 m/s
> radius of the wheel = 0.2 m
> 

> **Calculations:**
> 
> 
> periodic time (T) = 2 * *pi **r / Vmax = 2.513 sec
> rotations per second (f) = 1/ T = 0.3978 = 0.4 Hz
> pulses per second (fc) = 215 pulses
> 

Therefore, we will be needing a minimum cut-off frequency of 215 Hz, 250 recommended.