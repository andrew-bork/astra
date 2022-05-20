#include <pca9685.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char ** argv){

    char mode = ' ';
    double percent = 0.5;
    int ms = 0;
    int pin = 0;
    if(argc >= 2){
        pin = atoi(argv[1]);
        printf("DIDNT SPECIFY PIN (0-15)\n");
    }
    if(argc >= 3){
        mode = argv[2][0];
        printf("DIDNT SPECIFY MODE (t/p)\n");
    }
    if(argc == 4){
        if(mode == 't'){
            ms = atoi(argv[3]);
        }else if(mode == 'p'){
            percent = atof(argv[3]);
        }
    }

    printf("\"servo\" program:\n");
    printf("rotating servo at pin \"%d\"\n", pin);
    if(mode == 't'){
        printf("mode \"time\": setting on time to %d ms.\n", ms);
    }else if(mode == 'p'){
        printf("mode \"percent\": setting to %f%% rotation.\n", ((int) percent*1000) / 10.0);
    }


    pca9685::init();
    pca9685::set_frequency(50);
    printf("PRESCALE register is: %d\n", pca9685::query_reg(PRESCALE) & 0xFF);
    pca9685::wake_up();
    usleep(500);

    printf("Mode 1 reg: %d\n", pca9685::query_reg(MODE_1) & 0xFF);
    // pca9685::set_pwm_off(15, 205);
    // pca9685::set_pwm_on(15, 0);
    if(mode == 't'){
        pca9685::set_pwm_ms(15, ms);
    }else if(mode == 'p'){
        pca9685::set_pwm_percent(15, percent);
    }
    
    usleep(500);
    printf("OFF registers are: %3d %3d\n", pca9685::query_reg(PWM15_OFF_H) & 0xFF, pca9685::query_reg(PWM15_OFF_L) & 0xFF);
    printf("ON registers are: %3d %3d\n", pca9685::query_reg(PWM15_ON_H) & 0xFF, pca9685::query_reg(PWM15_ON_L) & 0xFF);

    usleep(5000000);

    pca9685::destroy();
}