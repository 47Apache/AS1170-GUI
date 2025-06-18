# Release Notes

## Changes Introduced

### 1. Dynamic Configuration of STROBE_PIN (Pin 13)
- **Function Introduced:** The logic to configure `STROBE_PIN` dynamically was added inside the `setup()` function.
- **Condition Implemented in `setup()`:**
  ```cpp
  pinMode(STROBE_PIN, INPUT_PULLUP); // Ensure initial read is reliable
  delay(10); // Small delay for stability
  
  if (digitalRead(STROBE_PIN) == LOW) {
      pinMode(STROBE_PIN, INPUT);
      pinMode(pwmPin, OUTPUT);
      digitalWrite(pwmPin, HIGH); // Enable VCSEL load board
  } else {
      pinMode(STROBE_PIN, OUTPUT);
  }
  ```
- **Behavior:**
  - If `STROBE_PIN` reads **LOW**, it is configured as an **input** (VCSEL load board detected), and `pwmPin` is set to **HIGH**.
  - If `STROBE_PIN` reads **HIGH**, it is configured as an **output** (IRED board detected).

### 2. PWM Pin (Pin 5) Behavior Adjustment
- When a VCSEL load board is detected (**STROBE_PIN is LOW**):
  - `pwmPin` (Pin 5) is set as an **output**.
  - `pwmPin` is set to **HIGH** using `digitalWrite(pwmPin, HIGH);` to activate the VCSEL load board.

### Summary
These changes ensure that the correct board type is detected and configured dynamically, improving flexibility and preventing potential misconfiguration of the STROBE and PWM pins.

