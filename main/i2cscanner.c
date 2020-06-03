#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_system.h"



#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ    /*!< I2C master read */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0           /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */
#define NOP() asm volatile ("nop")


static gpio_num_t i2c_gpio_sda = 21; /*!< SDA pin 21 CHANGE FOR YOUR OWN BOARD PINOUT*/
static gpio_num_t i2c_gpio_scl = 22; /*!< SCL pin 22 CHANGE FOR YOUR OWN BOARD PINOUT*/
static uint32_t i2c_frequency = 100000; /*!< defining bus freqency */
static i2c_port_t i2c_port = I2C_NUM_0; /*!< declaring i2c_port as internal i2c_port_t structure to port 0*/


/* setting up a software timer used in the main loop to wait 1 second */ 
unsigned long IRAM_ATTR micros()
{
    return (unsigned long) (esp_timer_get_time());  /*!< get the current time in microsecond since startup */
}
void IRAM_ATTR delayMicroseconds(uint32_t us)  /*< 'us' is the time in microsecond to wait as argument */
{
    uint32_t m = micros(); /*< Get the time at begining of function */
    if(us){               
        uint32_t e = (m + us); /* e = time at entrance of the function + the time requested to wait */ 
        if(m > e){ //overflow if m+us > uint32_t MAX
            while(micros() > e){ 
                NOP();
            }
        }
        while(micros() < e){
            NOP();
        }
    }
}

// let's say esp_timer_get_time loop between 0 to 100 
// let's say that at call of delayMicronseconds, esp_timer_get_time return 90
// and let's say that 'us' is called with 30 value 
// so e = 90+30 = 120 = 20 (overflow >100) 
// m is still 90 it has to go up to 100 to achieve 10 loops before overflow 
// this is why there is a while(micro()> e ) { nop; }  -- 90 > 20 so it will work until micro reach 100
// Once 100 is reached micro() start again at 0 
// then this is the second while(micro() < e) {nop } -- 0 < 20 so it will work until micro reach e ie 20
//
// if at first m is > e, there isn't any overflow and therfore it jumps directly to the second while as normal. 
// using a pen and paper to draw it is helping the understanding. 


static esp_err_t i2c_master_driver_initialize(void)  /*< initialisation of i2c as a master on esp32 */
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = i2c_gpio_sda,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = i2c_gpio_scl,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = i2c_frequency
    };
    return i2c_param_config(i2c_port, &conf);
}



static int do_i2cdetect_cmd(void)  /*< main function which loops over i2c address space to initialise a session, send a byte and look for answer*/ 
{
    i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0); 
    i2c_master_driver_initialize();
    uint8_t address;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            fflush(stdout);
            address = i + j;
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (address << 1) | WRITE_BIT, ACK_CHECK_EN);
            i2c_master_stop(cmd);
            esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_RATE_MS);
            i2c_cmd_link_delete(cmd);
            if (ret == ESP_OK) { /* if device answer correctly print device address */
                printf("%02x ", address); 
            } else if (ret == ESP_ERR_TIMEOUT) { /* if device is detected but doesn't reply in time print UU*/ 
                printf("UU ");
            } else {
                printf("-- "); /* if no device is detected print --*/
            }
        }
        printf("\r\n");
    }

    i2c_driver_delete(i2c_port);
    return 0;
}


void app_main(void)
{ 
i2c_master_driver_initialize();	

while(1){
  do_i2cdetect_cmd(); 
  delayMicroseconds(100000); /* wait 1 second between loops */ 
  } 
} 



