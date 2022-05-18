#include <iostream>
#include <unistd.h>
#include <thread>
#include <ctime>
#include <stdlib.h>
#include <pca9685.h>

int main(){
    setvbuf(stdout, NULL,_IONBF,0);
    pca9685::init();
    pca9685::set_servo_motor(0, 0.5);
    pca9685::destroy();
}