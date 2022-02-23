#ifndef STM32variables_h
#define STM32variables_h




    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////                                                                                    ////
    //// Initializing variables non DDS                                                     ////
    ////                                                                                    ////
    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

      uint8_t TEST   = 0;
      uint8_t CONFIG = 0;
      uint8_t SEQUENCE = 0;
      uint8_t BAND   = 0;
      uint8_t MODE   = 0;

      uint8_t test =0;
      uint8_t config = 0;
      uint8_t sequence = 0;
      uint8_t Band = 0;
      uint8_t Mode = 0;
      uint8_t toon = 0;

      uint16_t Instruction_word_FTW;

      uint8_t x = 0;
      uint8_t y = 0;
      uint8_t z = 1;

      uint8_t buffsize   = 8;
      uint8_t STM32ReadState   = LOW;
      uint8_t STM32WriteState  = LOW;
      uint8_t STM32ReadBuffer[] = {0,0,0,0,0,0,0,0}; //    [buffsize];
      uint8_t STM32WriteBuffer[] = {0,0,0,0,0,0,0,0}; //    [buffsize];


      uint8_t StartupDone = 0;
      uint8_t WaitForInstruction = 0;
      uint8_t AtmegaHasNoData = 0;
      uint8_t WaitFor1PPS = 0;
      uint8_t PPSdetect = 0;
      uint8_t BeaconStart = 0;
volatile uint16_t SecondTimer = 0;

#endif
