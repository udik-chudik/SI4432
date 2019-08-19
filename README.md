# SI4432 driver
## Description
This driver was written for module, based on **SI4432** IC, which is RF transciever. Corrently only STM32\`s HAL is supported as a communication layer, but another IO-layers can be developed easily due to modular design. For example, all you need to port this lib to Arduino - implement custom `SI44_Read`, `SI44_Write` and `SI44_IO_Init` functions. If you do that, please send me a pull request!
Supported only transmit with Packet Handler active. Length of payload automatically added to packet.
## How to work with this lib
Example bellow for STM32 CubeMX preconfigured project.
1. Clone this repo into you `Drivers/` directory:
   ```bash
   $ cd Drivers/
   $ git clone https://github.com/udik-chudik/SI4432.git
   ```
2. Add `SI4432.h` on top of your **main.c** file.
3. Initialize communication by adding the folowing lines into you `main` function:
   ```C
    SI44_Init(&hspi2, GPIOB, GPIO_PIN_12);

   ```
Here we assume that module has been connected to appropriate pind, dedicated to `hspi2`, and NSS (slave select pin, with low active) connected to `PIN12` of `SPIOB`.

4. Now lets configure out:
   ```C
   /* General config */
   si44_config conf;
   conf.encoding_options = 0;
   conf.modulation_source = SI44_MODULATION_SOURCE_FIFO;    //Use FIFO mode
   conf.modulation_type = SI44_MODULATION_TYPE_GFSK;        //Modulation GFSK
   SI44_SetConfig(conf);
   /* Packet handler config */
   si44_ph_config ph_conf;
   ph_conf.path = SI44_PH_PATH_TX_ONLY;
   ph_conf.preambule_length = 8;                //Preambule length in nibbles (8 * 4 -> 32 bits)
   ph_conf.sync = SI44_PH_SYNC_2;               //Use 2 bytes (3 and 4) length sync-word
   ph_conf.header = SI44_PH_HEADER_OFF;         //Don`t use header
   ph_conf.crc = SI44_PH_CRC_DATA_ONLY;         //Use CRC, computed over data only
   ph_conf.crc_type = SI44_PH_CRC_TYPE_IBM16;   //Use IBM16 as a CRC type
   SI44_SetPHConfig(ph_conf);
   ```
5. Set up frequency, frequency deviation, data rate and TX power:
   ```C
   SI44_SetFrequency(433.95);               //Set up 433.95 MHz
   SI44_SetDataRate(2400);                  //Set up data rate as 2400 bit/sec
   SI44_SetFrequencyDeviation(2400);        //Set deviation to 2400 Hz (BH=1 for baud=2400
   SI44_SetTXPower(SI44_TX_POWER_11dBm);    //Set TX power to 11dBm (12.5 mW)
   ```

6. Now we are ready to send a message!
   ```C
   uint8_t message[] = "Hello world!\n";
   SI44_SendPacket(message, sizeof(message));
   ```

   With configuration above, resulting transmittes structure will be:

   [`10101010...`][`2d d4`][`0c`][`Hello world!\n`][`crc`]