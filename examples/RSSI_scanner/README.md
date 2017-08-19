## Test results

### bk2423

Setting RX_SEN seems to not affect detection levels as advertised in AN0007, in both datarate ranges.
The lowest measured power levels are close to the theoretical receiver sensitivity (around -82/-88dBm) in the table with "RX_SEN=0".
It seems to only lower most of the measured power levels (probably increases sensitivity, or rssi offsets).

BEKEN recommended BANK1_REG4 values are most probably changing rssi offsets or increasing sensitivity by a large factor (1-2 steps). 

### bk2425

bk2425 have fixed treshold level (according to rfm73->rfm75 migration manual) at:

|250 kbps|1 mbps|2 mbps|
|:--:|:--:|:--:|
|-84 dBm|-80 dBm|-64dBm|