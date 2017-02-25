// skeleton code for ECE 2036 thermostat lab
// code must be added by students
#include "mbed.h"
#include "TMP36.h"
#include "SDFileSystem.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "Speaker.h"
// must add your new class code to the project file Shiftbrite.h
#include "Shiftbrite.h"
PwmOut led_red(p24);
PwmOut led_green(p25);
PwmOut led_blue(p26);
// use class to setup temperature sensor pins
TMP36 myTMP36(p15);  //Analog in

// use class to setup microSD card filesystem
SDFileSystem sd(p5, p6, p7, p8, "sd");

// use class to setup the  Color LCD
uLCD_4DGL uLCD(p9, p10, p11); // create a global uLCD object

// use class to setup pushbuttons pins
PinDetect pb1(p22);
PinDetect pb2(p23);
PinDetect pb3(p5);
PinDetect pb4(p6);


// use class to setup speaker pin
Speaker mySpeaker(p21); //PWM out

// use class to setup Shiftbrite pins
//Shiftbrite myShiftbrite(p9, p10, p11, p12, p13);// ei li di n/c ci

// use class to setup Mbed's four on-board LEDs
DigitalOut myLED1(LED1);
DigitalOut myLED2(LED2);
DigitalOut myLED3(LED3);
DigitalOut myLED4(LED4);



//also setting any unused analog input pins to digital outputs reduces A/D noise a bit
//see http://mbed.org/users/chris/notebook/Getting-best-ADC-performance/
DigitalOut P16(p18);
DigitalOut P17(p19);
DigitalOut P18(p20);
DigitalOut P19(p30);
DigitalOut P20(p16);

// Global variables used in callbacks and main program
// C variables in interrupt routines should use volatile keyword
int volatile heat_setting_day = 75; // heat to temp
int volatile cool_setting_day = 65;// cool to temp
int volatile heat_setting_night = 80;
int volatile cool_setting_night = 70;
bool volatile check = false;
bool volatile var1 = false;
bool volatile var2 = false;
bool volatile var3 = false;
bool volatile inCel = false;
float current_temp;
int mode = 0; // heat or cool mode
void pb1_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    var1 = true;
    if (!check) {
        heat_setting_day++;
        cool_setting_day++;
    } else {
        heat_setting_night++;
        cool_setting_night++;
    }
}
// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
        var2 = true;
        if (!check) {
            heat_setting_day--;
            cool_setting_day--;
        } else {
            heat_setting_night--;
            cool_setting_night--;
        }
}
// Callback routine is interrupt activated by a debounced pb3 hit
void pb3_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    mode = ((mode+1)%3);
    var3 = true;
}
// Callback routine is interrupt activated by a debounced pb4 hit
void pb4_hit_callback (void)
{
    // CODE HERE WILL RUN WHEN INTERUPT IS GENERATED
    if (inCel) {
        heat_setting_day = (9.0*heat_setting_day)/5.0 + 32.0; // heat to temp
        cool_setting_day = (9.0*cool_setting_day)/5.0 + 32.0;// cool to temp
        heat_setting_night = (9.0*heat_setting_night)/5.0 + 32.0;
        cool_setting_night = (9.0*cool_setting_night)/5.0 + 32.0;
        inCel = false;
    } else {
        heat_setting_day = ((heat_setting_day - 32)*5.0)/9.0; // heat to temp
        cool_setting_day = ((cool_setting_day - 32)*5.0)/9.0;// cool to temp
        heat_setting_night = ((heat_setting_night - 32)*5.0)/9.0;
        cool_setting_night = ((cool_setting_night - 32)*5.0)/9.0;
        inCel = true;
    }

}
void RGB_Light(int r, int g, int b) {
    led_red = r;
    led_green= g;
    led_blue = b;
}


int main()
{
    // Use internal pullups for the three pushbuttons
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb3_hit_callback);
    pb4.attach_deasserted(&pb4_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    pb3.setSampleFrequency();
    pb4.setSampleFrequency();
    // pushbuttons now setup and running


    enum ThermState { Heat_off = 0, Heat_on, Cool_off, Cool_on, off };
    ThermState state = Heat_off;
    uLCD.baudrate(7000000);
    // State machine code below will need changes and additions
    set_time(82780);
    while (1) {
        uLCD.cls();
        time_t seconds = time(NULL);
        uLCD.locate(1,2);
        uLCD.printf("Time: %s \r", ctime(&seconds));
        tm* now = localtime(&seconds);
        check = ((now->tm_hour == 23) || (now->tm_hour >= 0 && now->tm_hour < 6));
        current_temp = myTMP36.read();
        if (inCel) {
            current_temp = ((current_temp - 32)*5.0)/9.0;
        }
        uLCD.color(WHITE);
        uLCD.text_width(1.3); //2X size text
        uLCD.text_height(1.3);
        uLCD.locate(5, 6);
        uLCD.printf(" Inside\n   Temperature:");
        uLCD.locate(5, 5);
        if (mode == 0) {
            if (var3) {
                mySpeaker.PlayNote(800.0,0.1,0.8);
            }
            var3 = false;
            RGB_Light(0,1,0);
            state = off;
            myLED1 = 0;
            myLED2 = 0;
            myLED3 = 0;
            myLED4 = 0;
            uLCD.background_color(0x78AB46);
            uLCD.textbackground_color(0x78AB46);
            uLCD.locate(1, 1);
            uLCD.text_width(1.5); //2X size text
            uLCD.text_height(1.5);
            uLCD.printf("Mode: OFF");
            uLCD.text_width(1.3); //2X size text
            uLCD.text_height(1.3);
            uLCD.locate(5, 6);
            uLCD.printf(" Inside\n   Temperature:");
            uLCD.locate(5, 10);
            uLCD.circle(62, 70, 45, WHITE);
            uLCD.text_width(2); //2X size text
            uLCD.text_height(2);
            uLCD.printf(" %2.0f", current_temp);
        } else if (mode==2 & !check) {
            if (var3) {
                mySpeaker.PlayNote(950.0,0.1,0.8);
            }
            var3 = false;
            myLED2 = 1;
            myLED1 = 0;
            uLCD.locate(17,11);
            uLCD.printf("$");
            switch (state) {
                case Cool_off:
                    RGB_Light(0,0,0);
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", cool_setting_day);
                    uLCD.textbackground_color(BLACK);
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: COOLING OFF");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(BLACK);
                    myLED3 = 0;
                    if (current_temp > cool_setting_day + 1) {
                        mySpeaker.PlayNote(550.0,0.5,0.8);
                        state = Cool_on;
                    }
                    break;
                case Cool_on:
                    RGB_Light(0,0,1);
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", cool_setting_day);
                    myLED3 = 1;
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: COOLING");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(0x7ec0ee);
                    uLCD.textbackground_color(0x7ec0ee);
                    if (current_temp < cool_setting_day - 1) {
                        mySpeaker.PlayNote(350.0,0.5,0.8);
                        state = Cool_off;
                    }
                    break;
                default:
                    state = Cool_off;
                    myLED4 = 0;
            }
        } else if (mode==1 & !check) {
            if (var3) {
                mySpeaker.PlayNote(250.0,0.1,0.8);
            }
            var3 = false;
            myLED1 = 1;
            myLED2 = 0;
            uLCD.locate(17,11);
            uLCD.printf("$");
            switch (state) {
                case Heat_off:
                    RGB_Light(0,0,0);
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", heat_setting_day);
                    uLCD.textbackground_color(BLACK);
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: HEATING OFF");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(BLACK);
                    myLED4 = 0;
                    if (current_temp < heat_setting_day - 1) {
                        mySpeaker.PlayNote(700.0,0.5,0.8);
                        state = Heat_on;
                    }
                    break;
                case Heat_on:
                    uLCD.background_color(0xFF8000);
                    uLCD.textbackground_color(0xFF8000);
                    RGB_Light(1,0,0);
                    myLED4 = 1;
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", heat_setting_day);
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: HEATING");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    if (current_temp >= heat_setting_day + 1) {
                        mySpeaker.PlayNote(830.0,0.5,0.8);
                        state = Heat_off;
                    }
                    break;
                default:
                    state = Heat_off;
                    myLED3 = 0;
            }
        } else if (mode==2 & check) {
            if (var3) {
                mySpeaker.PlayNote(950.0,0.1,0.8);
            }
            var3 = false;
            myLED2 = 1;
            myLED1 = 0;
            uLCD.locate(17,11);
            uLCD.printf("*");
            switch (state) {
                case Cool_off:
                    RGB_Light(0,0,0);
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", cool_setting_night);
                    uLCD.textbackground_color(BLACK);
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: COOLING OFF");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(BLACK);
                    myLED3 = 0;
                    if (current_temp > cool_setting_night + 1) {
                        mySpeaker.PlayNote(550.0,0.5,0.8);
                        state = Cool_on;
                    }
                    break;
                case Cool_on:
                    RGB_Light(0,0,1);
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", cool_setting_night);
                    myLED3 = 1;
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: COOLING");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(0x7ec0ee);
                    uLCD.textbackground_color(0x7ec0ee);
                    if (current_temp < cool_setting_night - 1) {
                        mySpeaker.PlayNote(350.0,0.5,0.8);
                        state = Cool_off;
                    }
                    break;
                default:
                    state = Cool_off;
                    myLED4 = 0;
            }
        } else {
            if (var3) {
                mySpeaker.PlayNote(250.0,0.1,0.8);
            }
            var3 = false;
            myLED1 = 1;
            myLED2 = 0;
            uLCD.locate(17,11);
            uLCD.printf("*");
            switch (state) {
                case Heat_off:
                    RGB_Light(0,0,0);
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", heat_setting_night);
                    uLCD.textbackground_color(BLACK);
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: HEATING OFF");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(BLACK);
                    myLED4 = 0;
                    if (current_temp < heat_setting_night - 1) {
                        mySpeaker.PlayNote(700.0,0.5,0.8);
                        state = Heat_on;
                    }
                    break;
                case Heat_on:
                    RGB_Light(1,0,0);
                    myLED4 = 1;
                    uLCD.locate(5, 8);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Set To: %d", heat_setting_night);
                    uLCD.locate(1, 1);
                    uLCD.text_width(1.5); //2X size text
                    uLCD.text_height(1.5);
                    uLCD.printf("Mode: HEATING");
                    uLCD.locate(5, 10);
                    uLCD.circle(62, 70, 45, WHITE);
                    uLCD.text_width(2); //2X size text
                    uLCD.text_height(2);
                    uLCD.printf(" %2.0f", current_temp);
                    uLCD.background_color(0xFF8000);
                    uLCD.textbackground_color(0xFF8000);
                    if (current_temp >= heat_setting_night + 1) {
                        mySpeaker.PlayNote(830.0,0.5,0.8);
                        state = Heat_off;
                    }
                    break;
                default:
                    state = Heat_off;
                    myLED3 = 0;
            }
        }
        if (var1) {
            mySpeaker.PlayNote(400.0,0.1,0.8);
            var1 = false;
        }
        if (var2) {
            mySpeaker.PlayNote(600.0,0.1,0.8);
            var2 = false;
        }
        wait(0.33);
        // heartbeat LED - common debug tool
        // blinks as long as code is running and not locked up
        //myLED1=!myLED1;

    }
}