
#include <Wire.h>
#include <MPU6050_light.h>
#include <Ultrasonic.h>
#include <QTRSensors.h>
#include <FastLED.h>
#include <LiquidCrystal.h>

MPU6050 mpu(Wire);

//const int rs = 31, en = 33, d4 = 35, d5 = 37, d6 = 39, d7 = 41;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const PROGMEM uint8_t ENB = 6; // right
const PROGMEM uint8_t IN4 = 8; // right
const PROGMEM uint8_t IN3 = 7; // righT

const PROGMEM uint8_t IN2 = 9; // left
const PROGMEM uint8_t IN1 = 10; // left
const PROGMEM uint8_t ENA = 11; // left


const PROGMEM uint8_t button = A3;
const PROGMEM uint8_t potKp = A2;
const PROGMEM uint8_t potKd = A1;

Ultrasonic ultrasonicF(2,3); // trig echo
 Ultrasonic ultrasonicR(22, 23); // trig echo
 Ultrasonic ultrasonicL(4,5); // trig echo

const PROGMEM uint8_t LED_PIN = 44;
const PROGMEM uint8_t NUM_LEDS = 5;

const uint8_t SensorCount = 12;                                                             // number of sensors
static const uint8_t analog_pins[] = {A15,A14,A13,A12,A11,A10,A9,A8,A7,A6,A5,A4};// PINS

// ********************************************* IMPORTANT PATH STRING : *************************************************************************
const int defaultTime = 300;

//                           B 3    s
const int pathDistances[] = {0,0, 10000}; // ENIG DEV 1
const char path[] = "B1s";

//                              B D W  B  E  C   R  p o V L  V  L  C   C  C  C  C
// const int pathDistances[] = {0,0,20,60,0,250,10,0,210,10,0,100,0,100,20,20,80,70}; // WORKING 1ere reele
// const char path[] = "BDWBECRpoVLVLCCCCC";

// R= RIGHT    ;     L left : B  mode black  ;    W mode WHITE
// F forward  ;     S stop  ; C conditions like distance based ones
// EXEMPLE "BRLWLRLRFBCLFCWRRRs"
// **********************************************************************************************************************

// ********************************************* Variables: Dont touch! *************************************************************************

// Led Variables
static uint8_t PathColorSettings[SensorCount];
uint8_t hue = 0;
long ledactiontime = 0;
CRGB leds[NUM_LEDS];
boolean updateLedsInSensorsFn = true;

// Sensors Variables
static uint16_t lastIntDsensors[SensorCount];
int distanceL, distanceR, distanceF;
QTRSensors qtr;
uint16_t sensors[SensorCount];
char Dsensors[SensorCount]; // Dsensors : W B , IntDsensors => 1=LINE, 0=Background,
static uint16_t IntDsensors[SensorCount];
double lastIntDsensorstimes[SensorCount];
uint16_t position;

// RunRobot Variables
int pathTimes[sizeof(pathDistances) / sizeof(pathDistances[0])];
int conditionsCounter = 0;
char Prevc = 0, mode = 'S', currentLineColor;
double Taction = 0;
int pathSteps = 0;
boolean isPathTimesArrayCorrect = true;
boolean isPathArrayCorrect = true;
boolean RUNROBOT = false;
boolean enableSpeedManager = false;
int defaultManualSpeed = 1;
int SpeedManager_LowSpeed = 1;
int SpeedManager_HighSpeed = 3;

// Mouvement Variables
int lastLeftSpeed = 0;
int lastRightSpeed = 0;
boolean BLOCKMOVEMENT = false;

// Line Follow
int prev_i = 0, prev_error = 0;                        // Line Follow Integral
double LineFwNewTime = 0, LineFwPrevTime = 0;          // Line follow
OfflineDirection offD = OfflineDirection::AUTO;        // Line follow
WhichLineToFollow direction = WhichLineToFollow::AUTO; // Line follow
int SetPoint = 5500;                                   // (SensorCount-1)*1000/2=(SensorCount-1)*500

// Gyro Variables
double initialAngle = 0;
double GyroAngle = 0;
const PROGMEM double GyroOffset = 10000;
