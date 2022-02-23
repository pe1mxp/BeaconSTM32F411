#ifndef DDSvariables_h
#define DDSvariables_h

///////////////////////////////////////////////////////////////////////////////////////

  uint16_t Register_adress[17];                  // 16-bits
  uint8_t  Register_data[17];                    //  8-bits
  uint8_t  Register_amount = 16;                 // numer of used registers -1

///////////////////////////////////////////////////////////////////////////////////////

  uint16_t Register_adress_FTW[6];               // 16-bits
  uint8_t  Register_data_FTW[6];                 //  8-bits
  uint8_t  Register_amount_FTW = 5;              // number of used registers -1


///////////////////////////////////////////////////////////////////////////////////////

  uint16_t Read_write                  = 0x0000; // 0x0000 = write            bit 15
                                                 // 0x8000 = read             bit 15
  uint16_t Transfer_bytes_register     = 0x0000; // 0x0000 = one byte         bit 13/14
                                                 // 0x1000 = two bytes        bit 13/14
                                                 // 0x2000 = three bytes      bit 13/14
                                                 // 0x3000 = streaming mode   bit 13/14
  uint16_t Transfer_bytes_FTW          = 0x3000; // 0x0000 = one byte         bit 13/14
                                                 // 0x1000 = two bytes        bit 13/14
                                                 // 0x2000 = three bytes      bit 13/14
                                                 // 0x3000 = streaming mode   bit 13/14

///////////////////////////////////////////////////////////////////////////////////////

  uint16_t Instruction_header          = 0;

  uint16_t Instruction_header_FTW      = 0;


///////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////
  ////                                             ////
  //// Standard configuration of the DDS           ////
  ////                                             ////
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////

  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////
  //                                                 //
  // Register adresses                               //
  //                                                 //
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////

  /////////////////////////////////////////////////////
  //                                                 //
  // Serial port configuration & identification      //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Ser_config            = 0x0000;  // 0
    uint16_t Ser_opt2_update       = 0x0005;  // 1

  /////////////////////////////////////////////////////
  //                                                 //
  // Power down & reset                              //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Pdown_pdown           = 0x0010;  // 2
    uint16_t Pdown_reset1          = 0x0012;  // 3
    uint16_t Pdwon_reset2          = 0x0013;  // 4

  /////////////////////////////////////////////////////
  //                                                 //
  // System clock                                    //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Sysclk_ndivider       = 0x0020;  // 5
    uint16_t Sysclk_pllparameters  = 0x0022;  // 6

  /////////////////////////////////////////////////////
  //                                                 //
  // Frequency tuning word                           //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Ftw_reg[6]            = {0x01A6,
                                      0x01A7,
                                      0x01A8,
                                      0x01A9,
                                      0x01AA,
                                      0x01AB};

  /////////////////////////////////////////////////////
  //                                                 //
  // Phase tuning word                               //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Phase_reg[2]          =  {0x01AC,
                                      0x01AD};

  /////////////////////////////////////////////////////
  //                                                 //
  // Calibration                                     //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Cal_dac1              = 0x040B;  // 7
    uint16_t Cal_dac2              = 0x040C;  // 8

  /////////////////////////////////////////////////////
  //                                                 //
  // Harmonic spur reduction                         //
  //                                                 //
  /////////////////////////////////////////////////////

    uint16_t Spur_A1               = 0x0500;  // 9
    uint16_t Spur_A2               = 0x0501;  // 10
    uint16_t Spur_A3               = 0x0503;  // 11
    uint16_t Spur_A4               = 0x0504;  // 12
    uint16_t Spur_B1               = 0x0505;  // 13
    uint16_t Spur_B2               = 0x0506;  // 14
    uint16_t Spur_B3               = 0x0508;  // 15
    uint16_t Spur_B4               = 0x0509;  // 16

  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////
  //                                                 //
  // Register data                                   //
  //                                                 //
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////

  /////////////////////////////////////////////////////
  //                                                 //
  // Serial port configuration                       //
  // Register 0x0000 default 0x18 [0]                //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SDO_active1            = 0;       // bit 0
    uint8_t LSB_first1             = 0;       // bit 1
    uint8_t Soft_reset1            = 0;       // bit 2
    uint8_t Long_instruction1      = 1;       // bit 3
    uint8_t Long_instruction2      = 1;       // bit 4
    uint8_t Soft_reset2            = 0;       // bit 5
    uint8_t LSB_first2             = 0;       // bit 6
    uint8_t SDO_active2            = 0;       // bit 7

  /////////////////////////////////////////////////////
  //                                                 //
  // Register update                                 //
  // Register 0x0005 default 0x00 [1]                //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t Register_update        = 0;       // bit 0

  /////////////////////////////////////////////////////
  //                                                 //
  // Power-down & enable                             //
  // Register 0x0010 default 0xC0 or 0xD0 [2]        //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t Powerdown_digital      = 0;       // bit 0
    uint8_t Powerdown_full         = 0;       // bit 1
    uint8_t Not_used_1             = 0;       // bit 2
    uint8_t Not_used_2             = 0;       // bit 3
    uint8_t Powerdown_sysclock_pll = 0;       // bit 4*
    uint8_t Enable_output_doubler  = 0;       // bit 5*
    uint8_t Enable_CMOS            = 0;       // bit 6*
    uint8_t Powerdown_HSTL         = 1;       // bit 7

  /////////////////////////////////////////////////////
  //                                                 //
  // Register 0x0012 default 0x00 [3]                //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t Reset_DDS              = 0;       // bit 0

  /////////////////////////////////////////////////////
  //                                                 //
  // Power-down & reset                              //
  // Register 0x0013 default 0x00 [4]                //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t Not_used_3             = 0;       // bit 0
    uint8_t Reset_sdivider         = 0;       // bit 1
    uint8_t Not_used_4             = 0;       // bit 2
    uint8_t Reset_sdivider2        = 0;       // bit 3
    uint8_t Not_used_5             = 0;       // bit 4
    uint8_t Not_used_6             = 0;       // bit 5
    uint8_t Not_used_7             = 0;       // bit 6
    uint8_t Powerdown_fund_DDS     = 0;       // bit 7

  ///////////////////////////////////////////////////// 1Ghz input = 1x multiplier for 1Ghz clock
  //                                                 // 10Mhz input = 50x multiplier for 500Mhz clock
  // System clock N-divider                          //
  // Register 0x0020 default 0x12 [5]                //
  // 25Mhz = 20                                      //
  ///////////////////////////////////////////////////// Make double data for different LO's

    uint8_t N_divider0             = 0;       // bit 0*
    uint8_t N_divider1             = 0;       // bit 1*
    uint8_t N_divider2             = 1;       // bit 2*
    uint8_t N_divider3             = 0;       // bit 3*
    uint8_t N_divider4             = 1;       // bit 4*
    uint8_t Not_used_8             = 0;       // bit 5
    uint8_t Not_used_9             = 0;       // bit 6
    uint8_t Not_used_10            = 0;       // bit 7

  ///////////////////////////////////////////////////// Make double data for different LO's
  //                                                 //
  // PLL parameters                                  //
  // Register 0x0022 default 0x04 [6]                //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t Charge_pump1           = 0;       // bit 0*
    uint8_t Charge_pump2           = 0;       // bit 1*
    uint8_t VCO_range              = 1;       // bit 2
    uint8_t Reference_2x           = 0;       // bit 3*
    uint8_t Not_used_11            = 0;       // bit 4
    uint8_t Not_used_12            = 0;       // bit 5
    uint8_t Not_used_13            = 0;       // bit 6
    uint8_t VCO_autorange          = 0;       // bit 7

  /////////////////////////////////////////////////////
  //                                                 //
  // Frequency tuning word                           //
  // Register 0x01A6 - 0x01AB FTW [0] - [5]          //
  // Testfrequency 100Mhz <> 0x19999999999A          //
  //                                                 //
  ///////////////////////////////////////////////////// Make double data for different LO's

    uint8_t FTW_data_reg[6]        = {0x9A,   // byte 0
                                      0x99,   // byte 1
                                      0x99,   // byte 2
                                      0x99,   // byte 3
                                      0x99,   // byte 4
                                      0x19};  // byte 5

  /////////////////////////////////////////////////////
  //                                                 //
  // Phase tuning word                               //
  // Register 0x01AC - 0x01AD phase [0] [1]          //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t Phase_data_reg1        = 0x00;       // byte 0
    uint8_t Phase_data_reg2        = 0x00;       // byte 1

  /////////////////////////////////////////////////////
  //                                                 //
  // DAC full scale current default 0xFF01           //
  // Register 0x040B - 0x040C [7] [8]                //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t DAC_scale_current1     = 0x00FF;  // byte 0
    uint8_t DAC_scale_current2     = 0x0001;  // byte 1

  /////////////////////////////////////////////////////
  //                                                 //
  // Harmonic spur reduction                         //
  // Register 0x0500 - 0x0509                        //
  // Spur A default 0x00 [9]                         //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SpurA_harmonic0        = 0;       // bit 0
    uint8_t SpurA_harmonic1        = 0;       // bit 1
    uint8_t SpurA_harmonic2        = 0;       // bit 2
    uint8_t SpurA_harmonic3        = 0;       // bit 3
    uint8_t Not_used_14            = 0;       // bit 4
    uint8_t Not_used_15            = 0;       // bit 5
    uint8_t AmplitudeA_gainx2      = 0;       // bit 6
    uint8_t Enable_HSRA            = 0;       // bit 7

  /////////////////////////////////////////////////////
  //                                                 //
  // Spur A magnetude default 0x00 [10]              //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SpurA_magnetude        = 0;       // byte 0

  /////////////////////////////////////////////////////
  //                                                 //
  // Spur A phase default 0x00 [11] [12]             //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SpurA_phase            = 0;       // byte 0
    uint8_t SpurA_phase_bit8       = 0;       // byte 1

  /////////////////////////////////////////////////////
  //                                                 //
  // Spur B default 0x00 [13]                        //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SpurB_harmonic0        = 0;       // bit 0
    uint8_t SpurB_harmonic1        = 0;       // bit 1
    uint8_t SpurB_harmonic2        = 0;       // bit 2
    uint8_t SpurB_harmonic3        = 0;       // bit 3
    uint8_t Not_used_16            = 0;       // bit 4
    uint8_t Not_used_17            = 0;       // bit 5
    uint8_t AmplitudeB_gainx2      = 0;       // bit 6
    uint8_t Enable_HRSB            = 0;       // bit 7

  /////////////////////////////////////////////////////
  //                                                 //
  // Spur B magnetude default 0x00 [14]              //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SpurB_magnetude        = 0;       // byte 0

  /////////////////////////////////////////////////////
  //                                                 //
  // Spur B phase default 0x00 [15] [16]             //
  //                                                 //
  /////////////////////////////////////////////////////

    uint8_t SpurB_phase            = 0;       // byte 0
    uint8_t SpurB_phase_bit8       = 0;       // byte 1

#endif
