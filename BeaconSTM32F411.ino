
HardwareSerial Serial3(PA12, PA11); // USART6

#include <SPI.h>
#include "STM32TimerInterrupt.h"

#include "DDSvariables.h"
#include "FREQUENCYvariables.h"
#include "STM32variables.h"

#define SERIAL            Serial3 // PA11, PA12 USART6 COM13
#define STM32             Serial1 // PA9, PA10  USART1

#define SERIALspeed       57600    // Serial 3
#define STM32speed        57600    // Serial 1

#define STM32input        PA8     // input for when the Atmega is ready
#define STM32output       PB15    // output for when the STM32 is ready

#define PPSpin            PA15    // GPS timetick
#define LEDpin            PC13    // Onboard led

#define CS1               PA4     // DDS1
#define CS2               PA2     // DDS2
#define UPD1              PA3     // DDS1
#define UPD2              PA1     // DDS2

#define CLOCK             PA5     // CLK
#define SPIout            PA7     // MOSI
#define SPIin             PA6     // MISO


#define TIMER2_INTERVAL_MS        1000000 // 1.000.000 = 1 second // 1.000 = 1ms // 100 = 0,1ms
#define TIMER3_INTERVAL_MS        1000       // 10 = 0,01ms (100Khz / 4 = 25Khz taktfrequence)
#define TIMER4_INTERVAL_MS        1000     // 1.000.000 = 1 second // 1.000 = 1ms // 100 = 0,1ms


#define SecondsStart              TIM2->CR1 = 1 // Start 32-bit TIM2
#define SecondsStop               TIM2->CR1 = 0 // Stop  32-bit TIM2
#define SPIsequenceStart          TIM3->CR1 = 1 // Start 16-bit TIM3
#define SPIsequenceStop           TIM3->CR1 = 0 // Stop  16-bit TIM3
#define SymbolDurationStart       TIM4->CR1 = 1 // Start 16-bit TIM4
#define SymbolDurationStop        TIM4->CR1 = 0 // Stop  16-bit TIM4

STM32Timer ITimer2(TIM2); // Initialize TIM2 // 32bit
STM32Timer ITimer3(TIM3); // Initialize TIM3 // 16bit
STM32Timer ITimer4(TIM4); // Initialize TIM4 // 16bit

void setup()
{
     SERIAL.begin(SERIALspeed); // Initialize Serial control
     STM32.begin(STM32speed);   // Initialize Serial to Atmega

     pinMode(STM32input,   INPUT);
     pinMode(STM32output, OUTPUT);
     pinMode(PPSpin,       INPUT);
     pinMode(LEDpin,      OUTPUT);
     pinMode(CS1,         OUTPUT);
     pinMode(CS2,         OUTPUT);
     pinMode(UPD1,        OUTPUT);
     pinMode(UPD2,        OUTPUT);
     pinMode(CLOCK,       OUTPUT);
     pinMode(SPIout,      OUTPUT);
     digitalWrite(LEDpin, LOW);



     if (ITimer2.attachInterruptInterval(TIMER2_INTERVAL_MS, TimerHandler2)) // Taktfrequence is 1s
     {
     }

     if (ITimer3.attachInterruptInterval(TIMER3_INTERVAL_MS, TimerHandler3)) // Taktfrequence is fast
     {
     }

     if (ITimer4.attachInterruptInterval(TIMER4_INTERVAL_MS, TimerHandler4)) // Ticker needed is 0,1ms
     {
     }

     SPI.begin();
     SPI.beginTransaction(SPISettings(18000000, MSBFIRST, SPI_MODE0));
     // 16Mhz =290uS 18Mhz =287uS 24Mhz = 266uS // Zonder Clock_Config 450uS
     Create_register();

     SecondsStop;         // Stop TIM2
     SPIsequenceStop;     // Stop TIM3
     SymbolDurationStop;  // Stop TIM4                
}

void  TimerHandler2() // Ticker is 1s
{
      SecondTimer++;
}

void  TimerHandler3() // Ticker is as fast as possible
{
      switch (z)
      {
      case 1:
             CS1on();

             SPI.transfer(Band1[freq1][0]);
             SPI.transfer(Band1[freq1][1]);
             SPI.transfer(Band1[freq1][2]);
             SPI.transfer(Band1[freq1][3]);
             SPI.transfer(Band1[freq1][4]);
             SPI.transfer(Band1[freq1][5]);
             SPI.transfer(Band1[freq1][6]);
             SPI.transfer(Band1[freq1][7]);

             UPD1pulse();
             CS1off();
             z = 2;
      break;
      
      case 2:
             CS2on();
             
             SPI.transfer(Band2[freq2][0]);
             SPI.transfer(Band2[freq2][1]);
             SPI.transfer(Band2[freq2][2]);
             SPI.transfer(Band2[freq2][3]);
             SPI.transfer(Band2[freq2][4]);
             SPI.transfer(Band2[freq2][5]);
             SPI.transfer(Band2[freq2][6]);
             SPI.transfer(Band2[freq2][7]);

             UPD2pulse();
             CS2off();
             z = 3;
      break;

      case 3:
             CS1on();
    
             SPI.transfer(Band3[freq3][0]);
             SPI.transfer(Band3[freq3][1]);
             SPI.transfer(Band3[freq3][2]);
             SPI.transfer(Band3[freq3][3]);
             SPI.transfer(Band3[freq3][4]);
             SPI.transfer(Band3[freq3][5]);
             SPI.transfer(Band3[freq3][6]);
             SPI.transfer(Band3[freq3][7]);

             UPD1pulse();
             CS1off();
             z = 4;
      break;

      case 4:
             CS2on();

             SPI.transfer(Band4[freq4][0]);
             SPI.transfer(Band4[freq4][1]);
             SPI.transfer(Band4[freq4][2]);
             SPI.transfer(Band4[freq4][3]);
             SPI.transfer(Band4[freq4][4]);
             SPI.transfer(Band4[freq4][5]);
             SPI.transfer(Band4[freq4][6]);
             SPI.transfer(Band4[freq4][7]);

             UPD2pulse();
             CS2off();
             z = 1;
      break;

    default:

    break;
    }
}

void  TimerHandler4() // Ticker is 0,1ms
{     // Interrupt Counter need also to be set 0
      Band1ModeTimerCounter++;
      Band2ModeTimerCounter++;
      Band3ModeTimerCounter++;
      Band4ModeTimerCounter++;

      if (Band1ModeTimerCounter > Symbol_Duration_Band1)
      {
         Position_Array_Band1++;

         if (Position_Array_Band1 > End_Array_Band1)
         {
            Position_Array_Band1 = 0x00;
            ModeBand1counter++;
 
            if (ModeBand1counter > ModeCounterBand1)
            {
            // Do a pause till SecondTimer is ended
            }
         }
         
         Band1ModeTimerCounter = 0;
      }

      if (Band2ModeTimerCounter > Symbol_Duration_Band2)
      {
         Position_Array_Band2++;

         if (Position_Array_Band2 > End_Array_Band2)
         {
            Position_Array_Band2 = 0x00;
            ModeBand2counter++;
 
            if (ModeBand2counter > ModeCounterBand2)
            {
            // Do a pause till SecondTimer is ended
            }
         }
         
         Band2ModeTimerCounter = 0;
      }

      if (Band3ModeTimerCounter > Symbol_Duration_Band3)
      {
         Position_Array_Band3++;

         if (Position_Array_Band3 > End_Array_Band3)
         {
            Position_Array_Band3 = 0x00;
            ModeBand3counter++;
 
            if (ModeBand3counter > ModeCounterBand3)
            {
            // Do a pause till SecondTimer is ended
            }
         }
         
         Band3ModeTimerCounter = 0;
      }

      if (Band4ModeTimerCounter > Symbol_Duration_Band4)
      {
         Position_Array_Band4++;

         if (Position_Array_Band4 > End_Array_Band4)
         {
            Position_Array_Band4 = 0x00;
            ModeBand4counter++;
 
            if (ModeBand4counter > ModeCounterBand4)
            {
            // Do a pause till SecondTimer is ended
            }
         }
         
         Band4ModeTimerCounter = 0;
      }
}

void Create_register()
{

// void Register_adress_config() {

  Register_adress[0]  = {Ser_config};           // 0x0000
  Register_adress[1]  = {Ser_opt2_update};      // 0x0005
  Register_adress[2]  = {Pdown_pdown};          // 0x0010
  Register_adress[3]  = {Pdown_reset1};         // 0x0012
  Register_adress[4]  = {Pdwon_reset2};         // 0x0013
  Register_adress[5]  = {Sysclk_ndivider};      // 0x0020
  Register_adress[6]  = {Sysclk_pllparameters}; // 0x0022
  Register_adress[7]  = {Cal_dac1};             // 0x040B
  Register_adress[8]  = {Cal_dac2};             // 0x040C
  Register_adress[9]  = {Spur_A1};              // 0x0500
  Register_adress[10] = {Spur_A2};              // 0x0501
  Register_adress[11] = {Spur_A3};              // 0x0503
  Register_adress[12] = {Spur_A4};              // 0x0504
  Register_adress[13] = {Spur_B1};              // 0x0505
  Register_adress[14] = {Spur_B2};              // 0x0506
  Register_adress[15] = {Spur_B3};              // 0x0508
  Register_adress[16] = {Spur_B4};              // 0x0509


////////////////////////////////////////////////////////////////////////////////////////

// void Register_serial_config() {

  Register_data[0] |= SDO_active1       << 0; // bit 0
  Register_data[0] |= LSB_first1        << 1; // bit 1
  Register_data[0] |= Soft_reset1       << 2; // bit 2
  Register_data[0] |= Long_instruction1 << 3; // bit 3
  Register_data[0] |= Long_instruction2 << 4; // bit 4
  Register_data[0] |= Soft_reset2       << 5; // bit 5
  Register_data[0] |= LSB_first2        << 6; // bit 6
  Register_data[0] |= SDO_active2       << 7; // bit 7


// void Register_IOupdate() {
  Register_data[1] |= Register_update      << 0; // bit 0

// void Register_powerdown_enable() {

  Register_data[2] |= Powerdown_digital      << 0; // bit 0
  Register_data[2] |= Powerdown_full         << 1; // bit 1
  Register_data[2] |= Not_used_1             << 2; // bit 2
  Register_data[2] |= Not_used_2             << 3; // bit 3
  Register_data[2] |= Powerdown_sysclock_pll << 4; // bit 4
  Register_data[2] |= Enable_output_doubler  << 5; // bit 5
  Register_data[2] |= Enable_CMOS            << 6; // bit 6
  Register_data[2] |= Powerdown_HSTL         << 7; // bit 7


// void Register_DDS_reset() {

  Register_data[3] = Reset_DDS;                // bit 0


// void Register_powerdown_reset() {

  Register_data[4] |= Not_used_3         << 0; // bit 0
  Register_data[4] |= Reset_sdivider     << 1; // bit 1
  Register_data[4] |= Not_used_4         << 2; // bit 2
  Register_data[4] |= Reset_sdivider2    << 3; // bit 3
  Register_data[4] |= Not_used_5         << 4; // bit 4
  Register_data[4] |= Not_used_6         << 5; // bit 5
  Register_data[4] |= Not_used_7         << 6; // bit 6
  Register_data[4] |= Powerdown_fund_DDS << 7; // bit 7


// void Register_n_divider() {

  Register_data[5] |= N_divider0         << 0; // bit 0
  Register_data[5] |= N_divider1         << 1; // bit 1
  Register_data[5] |= N_divider2         << 2; // bit 2
  Register_data[5] |= N_divider3         << 3; // bit 3
  Register_data[5] |= N_divider4         << 4; // bit 4
  Register_data[5] |= Not_used_8         << 5; // bit 5
  Register_data[5] |= Not_used_9         << 6; // bit 6
  Register_data[5] |= Not_used_10        << 7; // bit 7


// void Register_pll_parameters() {

  Register_data[6] |= Charge_pump1       << 0; // bit 0
  Register_data[6] |= Charge_pump2       << 1; // bit 1
  Register_data[6] |= VCO_range          << 2; // bit 2
  Register_data[6] |= Reference_2x       << 3; // bit 3
  Register_data[6] |= Not_used_11        << 4; // bit 4
  Register_data[6] |= Not_used_12        << 5; // bit 5
  Register_data[6] |= Not_used_13        << 6; // bit 6
  Register_data[6] |= VCO_autorange      << 7; // bit 7


// void Register_calibration() {

  Register_data[7] |= DAC_scale_current1;       // byte 0
  Register_data[8] |= DAC_scale_current2;       // byte 1 bit 0


// void Register_spurA() {

  Register_data[9] |= SpurA_harmonic0    << 0; // bit 0
  Register_data[9] |= SpurA_harmonic1    << 1; // bit 1
  Register_data[9] |= SpurA_harmonic2    << 2; // bit 2
  Register_data[9] |= SpurA_harmonic3    << 3; // bit 3
  Register_data[9] |= Not_used_14        << 4; // bit 4
  Register_data[9] |= Not_used_15        << 5; // bit 5
  Register_data[9] |= AmplitudeA_gainx2  << 6; // bit 6
  Register_data[9] |= Enable_HSRA        << 7; // bit 7


// void Register_spurA_magnetude() {

  Register_data[10] |= SpurA_magnetude;          // byte 0


// void Register_spurA_phase() {

  Register_data[11]  |= SpurA_phase;            // byte 0
  Register_data[12] |= SpurA_phase_bit8;        // byte 1 bit 0


// void Register_spurB() {

  Register_data[13] |= SpurB_harmonic0    << 0; // bit 0
  Register_data[13] |= SpurB_harmonic1    << 1; // bit 1
  Register_data[13] |= SpurB_harmonic2    << 2; // bit 2
  Register_data[13] |= SpurB_harmonic3    << 3; // bit 3
  Register_data[13] |= Not_used_16        << 4; // bit 4
  Register_data[13] |= Not_used_17        << 5; // bit 5
  Register_data[13] |= AmplitudeB_gainx2  << 6; // bit 6
  Register_data[13] |= Enable_HRSB        << 7; // bit 7


// void Register_spurB_magnetude() {

  Register_data[14] |= SpurB_magnetude;          // byte 0


// void Register_spurB_phase() {

  Register_data[15] |= SpurB_phase;              // byte 0
  Register_data[16] |= SpurB_phase_bit8;         // byte 1 bit 0
}

void Create_instruction()
{
     Instruction_header = Read_write
                        + Transfer_bytes_register;
}

void Create_register_instruction_word()
{
     for (z = 0; z < Register_amount; z++)
     {
     Register_adress[z] = Instruction_header
                         + Register_adress[z];
     }
}

void Create_instruction_word_FTW()
{
     for (z = 0; z < Register_amount_FTW; z++)
     {
     Register_adress_FTW[z] = Instruction_header
                            + Register_adress_FTW[z];
     }
}

void Write_register_full()
{
     
     for (z = 0; z < Register_amount; z++)
     {
     uint8_t bytes[3] = { Register_adress[z] << 16, Register_adress[z] << 8, Register_data[z] };

     SPI.transfer(bytes[0]); // 4,298uS Gehele instructie
     SPI.transfer(bytes[1]); // 0,425uS voor 8-bits
     SPI.transfer(bytes[2]);
//     SERIAL.write(bytes[0]); // For testing output
//     SERIAL.write(bytes[1]);
//     SERIAL.write(bytes[2]);
  }
}

void Write_register_FTW_full()
{
     for (z = 0; z < Register_amount_FTW; z++)
     {
     uint8_t bytes[3] = { Register_adress_FTW[z] << 16, Register_adress_FTW[z] << 8, Register_data_FTW[z] }; // Total of 8 bytes

     SPI.transfer(bytes[0]);
     SPI.transfer(bytes[1]);
     SPI.transfer(bytes[2]);
//     SERIAL.write(bytes[0]); // For testing output
//     SERIAL.write(bytes[1]);
//     SERIAL.write(bytes[2]);
     }
}

void CS1on()
{
     digitalWrite(CS1, LOW);  
}

void CS1off()
{
     digitalWrite(CS1, HIGH);  
}

void CS2on()
{
     digitalWrite(CS2, LOW);  
}

void CS2off()
{
     digitalWrite(CS1, HIGH);  
}

void UPD1pulse()
{
     digitalWrite(UPD1, HIGH);
     digitalWrite(UPD1, LOW);
       
}

void UPD2pulse()
{
     digitalWrite(UPD2, HIGH);
     digitalWrite(UPD2, LOW);  
}

void Startup()
{
        Create_register();
        Create_instruction();
        Create_register_instruction_word();
        Create_instruction_word_FTW();
        CS1on();
        Write_register_full();
        Write_register_FTW_full();
        UPD1pulse(); // 1,3uS
        CS1off();
        CS2on();
        Write_register_full();
        Write_register_FTW_full();
        UPD2pulse();
        CS2off();
}

void PrepairVariablesBand1()
{
      Band1ModeTimerCounter = 0;
      Position_Array_Band1 = 0x00;
      ModeCounterBand1 = 0x00;
      
      Start_Array_Band1 = Mode_Start_Array[ModeBand1];
      End_Array_Band1 = Mode_Start_Array[ModeBand1] + Mode_Lenght_Array[ModeBand1];
      Symbol_Duration_Band1 = Mode_Symbol_Duration[ModeBand1];
      ModeCounterBand1 = ModeRepeat [ModeBand1]; // Moet nog geimplemeteerd worden
}

void PrepairVariablesBand2()
{      
      Band2ModeTimerCounter = 0;
      Position_Array_Band2 = 0x00;
      ModeCounterBand2 = 0x00;

      Start_Array_Band2 = Mode_Start_Array[ModeBand2];
      End_Array_Band2 = Mode_Start_Array[ModeBand2] + Mode_Lenght_Array[ModeBand2];
      Symbol_Duration_Band2 = Mode_Symbol_Duration[ModeBand2];
      ModeCounterBand2 = ModeRepeat [ModeBand2];
}

void PrepairVariablesBand3()
{      
      Band3ModeTimerCounter = 0;
      Position_Array_Band3 = 0x00;
      ModeCounterBand3 = 0x00;

      Start_Array_Band3 = Mode_Start_Array[ModeBand3];
      End_Array_Band3 = Mode_Start_Array[ModeBand3] + Mode_Lenght_Array[ModeBand3];
      Symbol_Duration_Band3 = Mode_Symbol_Duration[ModeBand3];
      ModeCounterBand3 = ModeRepeat[ModeBand3];
}

void PrepairVariablesBand4()
{      
      Band4ModeTimerCounter = 0;
      Position_Array_Band4 = 0x00;
      ModeCounterBand4 = 0x00;

      Start_Array_Band4 = Mode_Start_Array[ModeBand4];
      End_Array_Band4 = Mode_Start_Array[ModeBand4] + Mode_Lenght_Array[ModeBand4];
      Symbol_Duration_Band4 = Mode_Symbol_Duration[ModeBand4];
      ModeCounterBand4 = ModeRepeat [ModeBand4];
}

void loop()
{
     if (StartupDone == 0) // Run once or calibrate
     {
        Startup();
        WaitForInstruction = 1;
        StartupDone = 1;
     }

     SERIAL.println("W4INST  ");
     digitalWrite(STM32output, HIGH); // AtmegaCanSendData 
     
     do
     {

           if (STM32.available()>0)
           {
               STM32.readBytes(STM32ReadBuffer, buffsize);
            
               AtmegaHasNoData = digitalRead(STM32input); // ATMEGAouput

               if (AtmegaHasNoData == LOW)
               {
                  digitalWrite(STM32output, LOW); // AtmegaCanSendData

                  STM32ReadState   = 1;
                  WaitForInstruction = 0;
                  AtmegaHasNoData = 0;
               }  
           }
     } while (WaitForInstruction == 1); // Activatie voor inkomende data

     while (STM32ReadState == 1) // Here all the serial decoding and programming
     {
           if (STM32ReadBuffer[0] = 0x02) // Take the 3rd byte
           {
              ModeBand1 = STM32ReadBuffer[2]; // Example 0x02 (PI4)
              ModeBand2 = STM32ReadBuffer[3];
              ModeBand3 = STM32ReadBuffer[4];
              ModeBand4 = STM32ReadBuffer[5];
           }

           WaitFor1PPS = 1;
           STM32ReadState = 0;    
     }

     // First a bit calculation to prepare
     // This is in streaming mode eventually can end with register 0x005 for software I/O update
     // Here the actual sending of: 2 bytes instruction byte + adress byte (fixed)
     //                             6 bytes FTW value
     //                             This is a total of 8 bytes = 48 bits
     //
     // Write only an streaming mode = 0x0000 + 0x3000 = 0x3000
     // With MSB first adres is counting lower. So start adress = 0x01AB (otherwise 0x01A6)
     // The instruction word will be 0x31AB
     //
     // Array structure is : mode = band[z], tone[y], frequency[x]    


      Repeat                = 1;

      SecondTimer           = 0;
      MaximumTime           = 55;
             SERIAL.print(MaximumTime);
      PrepairVariablesBand1(); // LET OP: ATMEGA geeft CW
      PrepairVariablesBand2();
      PrepairVariablesBand3();
      PrepairVariablesBand4();
      
//////// CW           WSPR         QRSS         PI4
      if((ModeBand1 || ModeBand2 || ModeBand3 || ModeBand4) == WSPR) // 2 minutes
      {
        if (ModeBand1 != WSPR && QRSS)
        {
           ModeCounterBand1 = ModeCounterBand1 * 2;
        }

        if (ModeBand2 != WSPR && QRSS)
        {
           ModeCounterBand2 = ModeCounterBand2 * 2;
        }

        if (ModeBand3 != WSPR && QRSS)
        {
           ModeCounterBand3 = ModeCounterBand3 * 2;
        }        

        if (ModeBand4 != WSPR && QRSS)
        {
           ModeCounterBand4 = ModeCounterBand4 * 2;
        }

        MaximumTime = 119;
      }
//////// CW           WSPR         QRSS         PI4
      if((ModeBand1 || ModeBand2 || ModeBand3 || ModeBand4) == QRSS) // 10 minutes
      {
        if (ModeBand1 != WSPR && QRSS)
        {
           ModeCounterBand1 = ModeCounterBand1 * 5;
        }
        
        if (ModeBand2 != WSPR && QRSS)
        {
           ModeCounterBand2 = ModeCounterBand2 * 5;
        }

        if (ModeBand3 != WSPR && QRSS)
        {
           ModeCounterBand3 = ModeCounterBand3 * 5;
        }        

        if (ModeBand4 != WSPR && QRSS)
        {
           ModeCounterBand4 = ModeCounterBand4 * 5;
        }

        MaximumTime = 599;
      }
     
      SERIAL.print(STM32ReadBuffer[6]); SERIAL.print(":"); SERIAL.println(STM32ReadBuffer[7]);

     while (WaitFor1PPS == 1)
     {
           PPSdetect = digitalRead(PPSpin);

           if (PPSdetect == 0) // Input is inverted
           {
              PPSdetect = 0;
              z = 1;
              WaitFor1PPS = 0;
            }
     }

            SecondsStart;
            SPIsequenceStart;
            SymbolDurationStart;
            
      do
      {
             freq1 = Band1Mode[ModeBand1][Position_Array_Band1] + Frequency_Start_Array[ModeBand1];
             freq2 = Band2Mode[ModeBand2][Position_Array_Band2] + Frequency_Start_Array[ModeBand2];
             freq3 = Band3Mode[ModeBand3][Position_Array_Band3] + Frequency_Start_Array[ModeBand3];
             freq4 = Band4Mode[ModeBand4][Position_Array_Band4] + Frequency_Start_Array[ModeBand4];
 
             SERIAL.print(MaximumTime);
             SERIAL.println(SecondTimer); //Met deze erbij werkt hij wel

       }while (SecondTimer < MaximumTime); //  ModeBand1counter moet nog geimplemteerd worden
      
      SecondsStop;
      SPIsequenceStop;
      SymbolDurationStop;
      z = 0;
      WaitForInstruction = 1;
}
// end of loop
