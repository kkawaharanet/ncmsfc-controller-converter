#include <XInput.h>

#include <Wire.h>

#define BUTTON_COUNT 8
#define INPUT_A 1
#define INPUT_B 0
#define INPUT_X 3
#define INPUT_Y 2
#define INPUT_L 4
#define INPUT_R 5
#define INPUT_SELECT 6
#define INPUT_START 7
#define INPUT_LEFT 8
#define INPUT_UP 9
#define INPUT_RIGHT 10
#define INPUT_DOWN 11
#define INPUT_COUNT 12

bool InputCurrent[INPUT_COUNT];
bool InputBefore[INPUT_COUNT];

void setup()
{
    // Initialize memory
    memset(InputCurrent, 0, sizeof(InputCurrent));
    memset(InputBefore, 0, sizeof(InputBefore));

    // Initialize XInput
    XInput.begin();

    // Initialize I2C
    i2cInitialize();

    bool input[INPUT_COUNT];
    i2cGetInput(input);
}

void loop()
{
    i2cGetInput(InputCurrent);
    updateJoystickNormal(InputCurrent, InputBefore);
    memcpy(InputBefore, InputCurrent, sizeof(InputBefore));
}

void i2cInitialize()
{
    // put your setup code here, to run once:
    // Begin I2C as a master
    Wire.begin();

    // Disable encryption 1
    Wire.beginTransmission(0x52);
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission();
    delay(1);

    // Disable encryption 2
    Wire.beginTransmission(0x52);
    Wire.write(0xFB);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(1);

    // Overwrite device ID
    Wire.beginTransmission(0x52);
    Wire.write(0xFE);
    Wire.write(0x03);
    Wire.endTransmission();
    delay(1);

    // Prepare to read
    Wire.beginTransmission(0x52);
    Wire.write(0xFA);
    Wire.endTransmission();
    delay(1);

    // Read
    Wire.requestFrom(0x52, 6);
    while (Wire.available())
    {
        // It returns value, but it is unused
        Wire.read();
    }
}

void i2cGetInput(bool *input)
{
    // Prepare to read
    Wire.beginTransmission(0x52);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(1);

    // Read
    unsigned int i = 0;
    unsigned char buffer[32];
    Wire.requestFrom(0x52, 21);
    while (Wire.available())
    {
        buffer[i++] = Wire.read();
    }

    // Buttons
    input[INPUT_A] = (buffer[7] & 0b00010000) == 0;
    input[INPUT_B] = (buffer[7] & 0b01000000) == 0;
    input[INPUT_X] = (buffer[7] & 0b00001000) == 0;
    input[INPUT_Y] = (buffer[7] & 0b00100000) == 0;
    input[INPUT_L] = (buffer[6] & 0b00100000) == 0;
    input[INPUT_R] = (buffer[6] & 0b00000010) == 0;
    input[INPUT_SELECT] = (buffer[6] & 0b00010000) == 0;
    input[INPUT_START] = (buffer[6] & 0b00000100) == 0;
    input[INPUT_LEFT] = (buffer[7] & 0b00000010) == 0;
    input[INPUT_UP] = (buffer[7] & 0b00000001) == 0;
    input[INPUT_RIGHT] = (buffer[6] & 0b10000000) == 0;
    input[INPUT_DOWN] = (buffer[6] & 0b01000000) == 0;
}

void updateJoystickNormal(bool *current, bool *before)
{
    // A
    if (current[INPUT_A])
    {
        XInput.press(BUTTON_B);
    }
    else
    {
        XInput.release(BUTTON_B);
    }

    // B
    if (current[INPUT_B])
    {
        XInput.press(BUTTON_A);
    }
    else
    {
        XInput.release(BUTTON_A);
    }

    // X
    if (current[INPUT_X])
    {
        XInput.press(BUTTON_Y);
    }
    else
    {
        XInput.release(BUTTON_Y);
    }

    // Y
    if (current[INPUT_Y])
    {
        XInput.press(BUTTON_X);
    }
    else
    {
        XInput.release(BUTTON_X);
    }

    // L
    if (current[INPUT_L])
    {
        XInput.press(BUTTON_LB);
    }
    else
    {
        XInput.release(BUTTON_LB);
    }

    // R
    if (current[INPUT_R])
    {
        XInput.press(BUTTON_RB);
    }
    else
    {
        XInput.release(BUTTON_RB);
    }

    // SELECT
    if (current[INPUT_SELECT])
    {
        XInput.press(BUTTON_BACK);
    }
    else
    {
        XInput.release(BUTTON_BACK);
    }

    // START
    if (current[INPUT_START])
    {
        XInput.press(BUTTON_START);
    }
    else
    {
        XInput.release(BUTTON_START);
    }

    // D-pad
    if (current[INPUT_LEFT])
    {
        XInput.press(DPAD_LEFT);
        XInput.release(DPAD_RIGHT);
    }
    else if (current[INPUT_RIGHT])
    {
        XInput.release(DPAD_LEFT);
        XInput.press(DPAD_RIGHT);
    }
    else
    {
        XInput.release(DPAD_LEFT);
        XInput.release(DPAD_RIGHT);
    }
    if (current[INPUT_UP])
    {
        XInput.press(DPAD_UP);
        XInput.release(DPAD_DOWN);
    }
    else if (current[INPUT_DOWN])
    {
        XInput.release(DPAD_UP);
        XInput.press(DPAD_DOWN);
    }
    else
    {
        XInput.release(DPAD_UP);
        XInput.release(DPAD_DOWN);
    }
}
