void i2c_master_init();
void i2c_send_adress(uint8_t adress, uint8_t RW);
void i2c_write(uint8_t adress, uint8_t *write_data, uint8_t size);
void i2c_read(uint8_t adress, uint8_t *read_data, uint8_t size);