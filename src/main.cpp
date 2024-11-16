#include <Arduino.h>
#include <SimpleFOC.h>
#include <SimpleFOCDrivers.h>
//PA6
#define LED_PIN 7
// put function declarations here:
//int myFunction(int, int);
//InlineCurrentSense()
int i=0;
//Encoder(pin_A,pin_B,ppr)
  Encoder sensor =Encoder(2,3,2048);
  //BLDCDriver3PWM::BLDCDriver3PWM(int phA, int phB, int phC, int en1, int en2, int en3){
  BLDCDriver3PWM driver =BLDCDriver3PWM(9,5,6);
  LowsideCurrentSense current_sense= LowsideCurrentSense(0.01,50,A0,A1,A2);
  //Channel A,B call back
  void doA(){
    sensor.handleA();
    }
  void doB()
    {
    sensor.handleB();
    }

// BLDCMotor( int pp , float R)
// - pp            - pole pair number
// - R             - motor phase resistance
// - KV            - motor kv rating (rmp/v)
// - L             - motor phase inductance

BLDCMotor motor=BLDCMotor(11,9.75);

Commander command =Commander(Serial);
void onMotor(char* cmd)
{
  command.motor(&motor,cmd);
}
void setup() {
  // put your setup code here, to run once:
 // int result = myFunction(2, 3);
                          /*-------------------------init sensor----------------------*/
 sensor.init();//Khoi tao encoder
 sensor.enableInterrupts(doA,doB); //cho phep interrupts o hai channel A &B
                            /*----------------init driver------------*/
//pwm prequency
driver.pwm_frequency=20000;
//Max DC voltage allow define...
driver.voltage_limit=12;
//khoi tao driver
driver.init();
//Link current sense with driver
current_sense.linkDriver(&driver);
//init current sense
current_sense.init();

/*-----------------------------------------------init motor------------------------------- */
//link motor & sensor
motor.linkSensor(&sensor);
//link motor & driver
motor.linkDriver(&driver);
//link motor & current sense
motor.linkCurrentSense(&current_sense);
//set control loop type to  be used
motor.controller=MotionControlType::angle;
//velocity PI controller parameters

motor.PID_velocity.P=0.2f;
motor.PID_velocity.I=20;
motor.PID_velocity.D=0;
//default voltage_power_supply
motor.voltage_limit=6;
//default value is 300 volts per sec => 0.3 V per millisecond

motor.PID_velocity.output_ramp=1000;
//Low pass filter for time constant
motor.LPF_velocity.Tf=0.01f;
//angle P controller
motor.P_angle.P=20;
motor.velocity_limit=20;

motor.init();
//aligning voltage[V]
motor.voltage_sensor_align=3;

//start FOC
motor.initFOC();

//monitoring
Serial.begin(115200);
motor.useMonitoring(Serial);
//define the motor id
command.add('A',onMotor,"motor");




pinMode(LED_PIN,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Function FOC
  motor.loopFOC();

  i++;
  digitalWrite(LED_PIN,HIGH);
  delay(1000);
  digitalWrite(LED_PIN,LOW);
    delay(1000);

    motor.monitor();
}

// put function definitions here:
