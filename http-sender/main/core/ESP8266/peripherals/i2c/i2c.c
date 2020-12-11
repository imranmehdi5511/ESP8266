#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i2c.h"

#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#define I2C_MASTER_NUM  0       /*!< I2C port number for master dev */

#define I2C_MASTER_SCL_IO 5              			/*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 4               			/*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ 100000        			/*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                 /*!< I2C master doesn't need buffer */

void init_i2c()
{
	int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = 1;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = 1;
    conf.clk_stretch_tick = 300; // 300 ticks, Clock stretch is about 210us, you can make changes according to the actual situation.
    ESP_ERROR_CHECK(i2c_driver_install(i2c_master_port, conf.mode));
    ESP_ERROR_CHECK(i2c_param_config(i2c_master_port, &conf));
}

