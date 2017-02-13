#ifndef SPI_H_
#define SPI_H_

void spi_init(void);

uint8_t spi_xfer(uint8_t dat);
uint8_t rfm7x_xfer_spi(uint8_t dat); // internally used alias for spi function (to not force name for generic spi transfer function)

//universal spi functions (no CSN/SS handling)
void spi_reg_write(uint8_t reg, uint8_t dat);
uint8_t spi_reg_read(uint8_t reg);

void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len);
void spi_buff_write(uint8_t *buff, uint8_t len);

void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len);
void spi_buff_read(uint8_t *buff, uint8_t len);

#endif /* SPI_H_ */