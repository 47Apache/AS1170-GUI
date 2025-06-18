#include <Wire.h>
#include <SD.h>  // Include the SD library
#include <HardwareSerial.h>

#define _slaveaddress 0x30  // 7-bit I2C address
#define SDA_PIN 12
#define SCL_PIN 13
#define CLOCK_SPEED 400000  // 400 kHz
#define CONTROL 0x6
#define PWM_INDICATOR_REGISTER 0x9
#define CURRENT_SET_LED1_REGISTER 0x1
#define CURRENT_SET_LED2_REGISTER 0x2
#define FLASH_TIMER_REGISTER 0x5
#define STROBE_SIGNALING_REGISTER 0x7

// Define a structure to hold register information
struct Register {
  String name;
  int address;
  int defaultValue;
  String fields[8];
};

Register registers[10];  // Array to hold register objects
int numRegisters = 0;    // Number of registers loaded



// Define a function to read a register
int readRegister(Register reg, int bit = -1) {
  Wire.beginTransmission(_slaveaddress);  // START, SLAVEADDR
  Wire.write(reg.address);                // Register address
  Wire.endTransmission(false);            // Repeated START
  Wire.requestFrom(_slaveaddress, 1);
  byte content = Wire.read();

  // If a specific bit is not specified, read the whole register
  if (bit == -1) {
    return content;
  } else {
    // If a specific bit is specified, read only that bit
    return bitRead(content, bit);
  }
}


int writeRegister(Register* reg, int value) {
  Wire.beginTransmission(_slaveaddress);  // START, SLAVEADDR
  Wire.write(reg->address);               // Register address
  byte newContent = value;                // Use bitwise OR to keep old bits and change only the specified bits
  Wire.write(newContent);
  Wire.endTransmission();  // STOP
  return newContent;
}

// Define a function to load registers from a CSV file
int loadRegisters(String filename, Register regs[]) {
  // Open the file
  File file = SD.open(filename);

  // Read the file line by line and create Register objects
  // Add the Register objects to an array

  // Close the file
  file.close();

  // Return the number of Register objects loaded
  return numRegisters;
}

void printRegisterValue(String name, int address, int startBit, int endBit, String label) {
  static byte prevValue = 0;           // Store the previous value
  static unsigned long lastCheck = 0;  // Store the last time the register was checked
  Register reg;
  reg.name = name;
  reg.address = address;
  byte value = readRegister(reg);  // Read the whole byte

  Serial.print(name);
  Serial.print(" (");
  Serial.print(label);
  Serial.print("): ");
  Serial.println(value, BIN);  // Print the whole byte in binary

  // Get the current time
  unsigned long now = millis();

  // Only check the value of the register once a second has passed
  if (now - lastCheck >= 1000) {
    // If the register is a "Fault" register and the value has changed, print the new value and update prevValue
    if (name.startsWith("Fault") && value != prevValue) {
      Serial.print(name);
      Serial.print(" (");
      Serial.print(label);
      Serial.print("): ");
      Serial.println(value, BIN);  // Print the whole byte in binary
      prevValue = value;           // Update the stored value
    }
  }
}
void pollserial(void) {
  // Check incoming serial chars

  while (1) {
    int ch = Serial.read();

    if (ch == -1) break;
  }
}

void setup() {

  Wire.begin(SDA_PIN, SCL_PIN, CLOCK_SPEED);  // Initialize I2C bus with SDA on pin 6, SCL on pin 11 and preferred frequency
  Serial.begin(115200);


  Register reg;


  // Load registers from the CSV file
  numRegisters = loadRegisters("field_map.csv", registers);

  // Read the register at address 0

  printRegisterValue("PWM and Indicator", 0x9, 0, 1, "incl_pwm");
  printRegisterValue("Current set LED1", 0x1, 0, 7, "led current 1");
  printRegisterValue("Current set LED2", 0x2, 0, 7, "led current 2");
  printRegisterValue("Flash timer", 0x5, 0, 7, "flash timeout");
  printRegisterValue("Strobe signaling", 0x7, 7, 7, "strobe on");
  printRegisterValue("Strobe signaling", 0x7, 6, 6, "strobe type");
  printRegisterValue("Control", 0x6, 0, 1, "mode setting");
  printRegisterValue("Control", 0x6, 3, 3, "out_on");
  printRegisterValue("Control", 0x6, 4, 4, "autostrobe");
  printRegisterValue("Fault", 0x8, 0, 0, "fault uvlo");
  printRegisterValue("Fault", 0x8, 4, 4, "fault");
  printRegisterValue("Fault", 0x8, 5, 5, "fault overtempt");
  printRegisterValue("Fault", 0x8, 6, 6, "led short");
  printRegisterValue("Fault", 0x8, 7, 7, "fault ovp");
  printRegisterValue("Fixed ID", 0x0, 3, 7, "fixed id");
  pollserial();
}

void loop() {


  Register reg;

  // Check if data is available to read
  if (Serial.available()) {
    // Read the entire line
    String line = Serial.readStringUntil('\n');


    // Split the line into parts
    int commaIndex1 = line.indexOf(',');
    int commaIndex2 = line.indexOf(',', commaIndex1 + 1);
    int commaIndex3 = line.indexOf(',', commaIndex2 + 1);

    // Parse the command, register address, value, and bit
    String command = line.substring(0, commaIndex1);
    int address = line.substring(commaIndex1 + 1, commaIndex2).toInt();
    int value = line.substring(commaIndex2 + 1, commaIndex3).toInt();


    command.trim();  // Remove any trailing whitespace

    // Check if the command is the reset command
    if (command == "reset") {
      ESP.restart();  // Perform a software reset
      pollserial();
    }

    else if (command == "read") {
      printRegisterValue("PWM and Indicator", 0x9, 0, 1, "incl_pwm");
      printRegisterValue("Current set LED1", 0x1, 0, 7, "led current 1");
      printRegisterValue("Current set LED2", 0x2, 0, 7, "led current 2");
      printRegisterValue("Flash timer", 0x5, 0, 7, "flash timeout");
      printRegisterValue("Strobe signaling", 0x7, 7, 7, "strobe on");
      printRegisterValue("Control", 0x6, 0, 1, "mode setting");
      printRegisterValue("Fault", 0x8, 0, 0, "fault uvlo");
      printRegisterValue("Fault", 0x8, 4, 4, "fault");
      printRegisterValue("Fault", 0x8, 5, 5, "fault overtempt");
      printRegisterValue("Fault", 0x8, 6, 6, "led short");
      printRegisterValue("Fault", 0x8, 7, 7, "fault ovp");
      printRegisterValue("Fixed ID", 0x0, 3, 7, "fixed id");

    }


    // Check if the command is "write"
    else if (command == "write") {
      Register reg;
      reg.address = address;
      writeRegister(&reg, value);
      delay(0.1);


      pollserial();
    }
  }
  pollserial();
}
