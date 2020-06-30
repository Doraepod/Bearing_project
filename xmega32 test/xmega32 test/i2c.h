
//-------------------------------------------------< ���������� ��� ������ � ����� I2C >----------------------------------------------------



#ifndef I2C_H_
#define I2C_H_

#define BYTE unsigned char

#define I2C_DDR		PORTC_DIR	// ���� �� ������� ����������� I2C
#define I2C_PORT	PORTC_OUT	// ���� �� ������� ����������� I2C
#define I2C_PIN		PORTC_IN	// ���� �� ������� ����������� I2C

#define I2C_SCL		1	// ��� SCL
#define I2C_SDA		0	// ��� SDA

#define ACK 0		// ����� �������
#define NACK 1		// ����� �� �������

#define I2C_DELAY()	_delay_us(10);	// ����� ����� �� ����

#define ONE_SCL()	{ I2C_DDR &= ~(1 << I2C_SCL); I2C_PORT |= (1 << I2C_SCL); } // ��������� ������� �� ����� SCL
#define NULL_SCL()	{ I2C_DDR |= (1 << I2C_SCL);  I2C_PORT &= ~(1 << I2C_SCL); } // ��������� ���� �� ����� SCL
#define ONE_SDA()	{ I2C_DDR &= ~(1 << I2C_SDA); I2C_PORT |= (1 << I2C_SDA); } // ��������� ������� �� ����� SDA
#define NULL_SDA()	{ I2C_DDR |= (1 << I2C_SDA);  I2C_PORT &= ~(1 << I2C_SDA); } // ��������� ���� �� ����� SDA
	

// ��������� �������

BYTE i2c_stop(void);			// ������� �����/ ���������� 0 ���� ��� ���������. ���������� 1 ���� ������ �� SDA. ���������� 2 ���� ������ �� SCL. ���� 3, ������ �� ����� ������.
void i2c_start(void);			// ������� ������
void i2c_restart(void);			// ������� ��������
void i2c_init(void);			// ������� ������������� ����
BYTE i2c_send_byte(BYTE data);	// ������� �������� �����. ���������� ACK ������ ��������, NACK ������ �� ��������
BYTE i2c_read_byte(BYTE ask);	// ������� ������ ����. ���� �������� ���������� ACK, ������ ����� ������� ��� ���� ����. ���� �������� NACK, ������ ������ ��������� ����

#endif /* I2C_H_ */