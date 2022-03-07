/*
 * Pins_Duet3Mini4.h
 *
 *  Created on: 02 Feb 2022
 *      Author: David
 */

#ifndef SRC_DUET3MINI_PINS_DUET3MINI_H_
#define SRC_DUET3MINI_PINS_DUET3MINI_H_

#include <PinDescription.h>

#define DEFAULT_BOARD_TYPE		 BoardType::Duet3Mini4

#define BOARD_SHORT_NAME		"Mini4"
#define BOARD_NAME				"Duet 3 Mini 4"
#define FIRMWARE_NAME			"RepRapFirmware for Duet 3 Mini 4"

#define IAP_FIRMWARE_FILE		"Duet3Firmware_" BOARD_SHORT_NAME ".uf2"
#define IAP_UPDATE_FILE			"Duet3_SDiap32_" BOARD_SHORT_NAME ".bin"
constexpr uint32_t IAP_IMAGE_START = 0x20028000;

#define WIFI_FIRMWARE_FILE		"DuetWiFiServer.bin"

// Features definition
#define HAS_LWIP_NETWORKING		0
#define HAS_WIFI_NETWORKING		1
#define HAS_W5500_NETWORKING	0
#define HAS_SBC_INTERFACE		0

#define HAS_MASS_STORAGE		1
#define HAS_HIGH_SPEED_SD		1
//#define HAS_CPU_TEMP_SENSOR	0					// according to the SAME5x errata doc, the temperature sensors don't work in revision A or D chips (revision D is latest as at 2020-06-28)
#define HAS_CPU_TEMP_SENSOR		1					// enable this as an experiment - it may be better than nothing

#define SUPPORT_TMC22xx			1
#define HAS_STALL_DETECT		1

#define HAS_VOLTAGE_MONITOR		1
#define ENFORCE_MAX_VIN			0
#define HAS_VREF_MONITOR		1

#define SUPPORT_CAN_EXPANSION	0

#define SUPPORT_LED_STRIPS		0
#define SUPPORT_INKJET			0					// set nonzero to support inkjet control
#define SUPPORT_ROLAND			0					// set nonzero to support Roland mill
#define SUPPORT_SCANNER			0					// set zero to disable support for FreeLSS scanners
#define SUPPORT_LASER			1					// support laser cutters and engravers using G1 S parameter
#define SUPPORT_IOBITS			0					// set to support P parameter in G0/G1 commands
#define SUPPORT_DHT_SENSOR		1					// set nonzero to support DHT temperature/humidity sensors (requires RTOS)
#define SUPPORT_WORKPLACE_COORDINATES	1			// set nonzero to support G10 L2 and G53..59
#define SUPPORT_12864_LCD		0					// set nonzero to support 12864 LCD and rotary encoder
#define SUPPORT_ACCELEROMETERS	1
#define SUPPORT_OBJECT_MODEL	1
#define SUPPORT_FTP				0
#define SUPPORT_TELNET			0
#define SUPPORT_ASYNC_MOVES		0
#define ALLOCATE_DEFAULT_PORTS	0
#define TRACK_OBJECT_NAMES		1
#define SUPPORT_PANELDUE_FLASH	0
#define SUPPORT_SPI_SENSORS		0

#define USE_CACHE				1					// set nonzero to enable the cache
#define USE_MPU					0					// set nonzero to enable the memory protection unit

// Disable the kinematics we don't need to save flash memory space
#define SUPPORT_LINEAR_DELTA	0
#define SUPPORT_ROTARY_DELTA	0
#define SUPPORT_POLAR			0
#define SUPPORT_SCARA			0
#define SUPPORT_FIVEBARSCARA	0
#define SUPPORT_HANGPRINTER		0

// The physical capabilities of the machine

#include <Duet3Common.h>

constexpr size_t NumDirectDrivers = 4;				// The maximum number of drives supported by the electronics

constexpr size_t MaxSmartDrivers = NumDirectDrivers;	// The maximum number of smart drivers

constexpr size_t MaxPortsPerHeater = 2;

constexpr size_t MaxBedHeaters = 4;
constexpr size_t MaxChamberHeaters = 4;
constexpr int8_t DefaultE0Heater = 1;				// Index of the default first extruder heater, used only for the legacy status response

constexpr size_t NumThermistorInputs = 2;
constexpr size_t NumTmcDriversSenseChannels = 1;

constexpr size_t MinAxes = 3;						// The minimum and default number of axes
constexpr size_t MaxAxes = 10;						// The maximum number of movement axes in the machine
constexpr size_t MaxDriversPerAxis = 4;				// The maximum number of stepper drivers assigned to one axis

constexpr size_t MaxExtruders = 8;					// The maximum number of extruders
constexpr size_t MaxAxesPlusExtruders = 12;

constexpr size_t MaxHeatersPerTool = 2;
constexpr size_t MaxExtrudersPerTool = 8;

constexpr unsigned int MaxTriggers = 16;			// Maximum number of triggers

constexpr size_t NumSerialChannels = 1;				// The number of serial IO channels (USB and one auxiliary UART)

#define SERIAL_MAIN_DEVICE (serialUSB)

// SerialUSB
constexpr Pin UsbVBusPin = PortBPin(6);				// Pin used to monitor VBUS on USB port

//#define I2C_IFACE	Wire							// First and only I2C interface
//#define I2C_IRQn	WIRE_ISR_ID

// The numbers of entries in each array must correspond with the values of DRIVES, AXES, or HEATERS. Set values to NoPin to flag unavailability.

// Drivers
constexpr Pin GlobalTmc22xxEnablePin = PortCPin(28);	// The pin that drives ENN of all drivers
PortGroup * const StepPio = &(PORT->Group[2]);		// The PIO that all the step pins are on (port C)

constexpr Pin STEP_PINS[NumDirectDrivers] = { PortCPin(26), PortCPin(25), PortCPin(24), PortCPin(20) };
constexpr Pin DIRECTION_PINS[NumDirectDrivers] = { PortBPin(3), PortAPin(27), PortCPin(27), PortBPin(2) };
constexpr Pin DriverDiagPins[NumDirectDrivers] = { PortAPin(10), PortBPin(8), PortBPin(1), PortCPin(21) };
// CCL inputs that the DIAG inputs use. Bits 0-1 are the CCL LUT number. Bits 8-19 are the value to OR in to the control register for that LUT.
constexpr uint32_t CclDiagInputs[NumDirectDrivers] =
{
	0x01 | CCL_LUTCTRL_INSEL2(0x04),		// CCLIN[5] = 1.2
	0x02 | CCL_LUTCTRL_INSEL2(0x04),		// CCLIN[8]	= 2.2
	0x00 | CCL_LUTCTRL_INSEL2(0x04),		// CCLIN[2] = 0.2
	0x03 | CCL_LUTCTRL_INSEL1(0x04),		// CCLIN[10] = 2.1
};

// UART interface to stepper drivers
constexpr uint8_t TMC22xxSercomNumber = 1;
Sercom * const SERCOM_TMC22xx = SERCOM1;
constexpr IRQn TMC22xx_SERCOM_IRQn = SERCOM1_0_IRQn;
constexpr Pin TMC22xxSercomTxPin = PortAPin(0);
constexpr GpioPinFunction TMC22xxSercomTxPinPeriphMode = GpioPinFunction::D;
constexpr Pin TMC22xxSercomRxPin = PortAPin(1);
constexpr GpioPinFunction TMC22xxSercomRxPinPeriphMode = GpioPinFunction::D;
constexpr uint8_t TMC22xxSercomRxPad = 1;

#define TMC22xx_HAS_ENABLE_PINS			0
#define TMC22xx_HAS_MUX					0
#define TMC22xx_USES_SERCOM				1
#define TMC22xx_VARIABLE_NUM_DRIVERS	0
#define TMC22xx_SINGLE_DRIVER			0
#define TMC22xx_USE_SLAVEADDR			1
#define TMC22xx_DEFAULT_STEALTHCHOP		0

// Define the baud rate used to send/receive data to/from the drivers.
// If we assume a worst case clock frequency of 8MHz then the maximum baud rate is 8MHz/16 = 500kbaud.
// We send data via a 1K series resistor. Even if we assume a 200pF load on the shared UART line, this gives a 200ns time constant, which is much less than the 2us bit time @ 500kbaud.
// To write a register we need to send 12 bytes and receive 8 bytes after a programmable delay. To read a register we send 4 bytes and receive 8 bytes after a programmable delay.
// In testing I found that 500kbaud was not reliable. Minimum baud rate is 9000.
constexpr uint32_t DriversBaudRate = 100000;								// at 100kbaud a transfer may take up to 2ms
constexpr uint32_t TransferTimeout = 6;										// any transfer should complete within 6 ticks @ 1ms/tick. 5 wasn't quite enough.
constexpr uint32_t DefaultStandstillCurrentPercent = 75;
constexpr float DriverSenseResistor = 0.056 + 0.02;							// in ohms

constexpr float DriverVRef = 180.0;											// in mV
constexpr float DriverFullScaleCurrent = DriverVRef/DriverSenseResistor;	// in mA
constexpr float DriverCsMultiplier = 32.0/DriverFullScaleCurrent;
constexpr float MaximumMotorCurrent = 2000.0;
constexpr float MaximumStandstillCurrent = 1500.0;

// Thermistors
constexpr Pin TEMP_SENSE_PINS[NumThermistorInputs] = { PortCPin(0), PortCPin(1) }; 	// Thermistor pin numbers
constexpr Pin VssaSensePin = PortBPin(4);
constexpr Pin VrefSensePin = PortBPin(5);

constexpr float DefaultThermistorSeriesR = 2200.0;							// Thermistor series resistor value in ohms
constexpr float MinVrefLoadR = (DefaultThermistorSeriesR / NumThermistorInputs) * 4700.0/((DefaultThermistorSeriesR / NumThermistorInputs) + 4700.0);
																			// there are 3 temperature sensing channels and a 4K7 load resistor
constexpr float VrefSeriesR = 27.0;

// Analogue pin numbers
constexpr Pin PowerMonitorVinDetectPin = PortCPin(3);						// Vin monitor
constexpr float PowerMonitorVoltageRange = 11.0 * 3.3;						// We use an 11:1 voltage divider

#ifdef DEBUG
constexpr Pin DiagPin = NoPin;												// Diag/status LED pin is shared with SWD
constexpr Pin ActLedPin = NoPin;											// Activity LED pin is shared with SWCLK
#else
constexpr Pin DiagPin = PortAPin(31);										// Diag/status LED pin
constexpr Pin ActLedPin = NoPin;											// Activity LED pin (not present)
#endif

constexpr bool DiagOnPolarity = false;
constexpr bool ActOnPolarity = false;

// SD cards
constexpr size_t NumSdCards = 2;
constexpr Pin SdCardDetectPins[NumSdCards] = { PortBPin(16), PortBPin(0) };

constexpr Pin SdWriteProtectPins[NumSdCards] = { NoPin, NoPin };
constexpr Pin SdSpiCSPins[NumSdCards - 1] = { PortCPin(14) };
constexpr Pin SdMciPins[] = { PortAPin(20), PortAPin(21), PortBPin(18), PortBPin(19), PortBPin(20), PortBPin(21) };
constexpr GpioPinFunction SdMciPinsFunction = GpioPinFunction::I;
Sdhc * const SdDevice = SDHC0;
constexpr IRQn_Type SdhcIRQn = SDHC0_IRQn;
constexpr uint32_t ExpectedSdCardSpeed = 15000000;

// LCD interface
// TBC

// Shared SPI definitions
constexpr uint8_t SharedSpiSercomNumber = 7;
constexpr Pin SharedSpiMosiPin = PortCPin(12);
constexpr Pin SharedSpiMisoPin = PortCPin(15);
constexpr Pin SharedSpiSclkPin = PortCPin(13);
constexpr GpioPinFunction SharedSpiPinFunction = GpioPinFunction::C;

// No external serial interfaces

// WiFi pins
constexpr unsigned int WiFiUartSercomNumber = 3;
constexpr uint8_t WiFiUartRxPad = 1;
constexpr Pin WiFiUartSercomPins[] = { PortAPin(16), PortAPin(17) };
constexpr GpioPinFunction WiFiUartSercomPinsMode = GpioPinFunction::D;
constexpr IRQn WiFiUartSercomIRQn = SERCOM3_0_IRQn;			// this is the first of 4 interrupt numbers
#define SERIAL_WIFI_ISR0	SERCOM3_0_Handler
#define SERIAL_WIFI_ISR1	SERCOM3_1_Handler
#define SERIAL_WIFI_ISR2	SERCOM3_2_Handler
#define SERIAL_WIFI_ISR3	SERCOM3_3_Handler

constexpr unsigned int WiFiSpiSercomNumber = 4;
Sercom * const WiFiSpiSercom = SERCOM4;
constexpr Pin EspMosiPin = PortAPin(15);
constexpr Pin EspMisoPin = PortAPin(13);
constexpr Pin EspSclkPin = PortAPin(12);
constexpr Pin EspSSPin = PortAPin(14);
constexpr Pin WiFiSpiSercomPins[] = { EspSclkPin, EspMisoPin, EspSSPin, EspMosiPin };
constexpr GpioPinFunction WiFiSpiSercomPinsMode = GpioPinFunction::D;
constexpr IRQn WiFiSpiSercomIRQn = SERCOM4_3_IRQn;			// this is the SS Low interrupt, the only one we use
#define ESP_SPI_HANDLER		SERCOM4_3_Handler

constexpr Pin EspResetPin = PortBPin(14);
constexpr Pin EspEnablePin = PortCPin(11);
constexpr Pin EspDataReadyPin = PortAPin(18);
constexpr Pin SamTfrReadyPin = PortAPin(19);
constexpr Pin SamCsPin = PortAPin(14);

// Function to look up a pin name and pass back the corresponding index into the pin table
bool LookupPinName(const char *pn, LogicalPin& lpin, bool& hardwareInverted) noexcept;

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been concerted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DueX.

constexpr PinDescription PinTable[] =
{
	//	TC					TCC					ADC					SERCOM in			SERCOM out	  Exint Capability				PinNames
	// Port A
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA00 TMC UART TxD
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA01 TMC UART RxD
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx, PinCapability::none,	"ate.lcd.flashwp"	},	// PA02 LCD flash WP
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx, PinCapability::none,	nullptr			},	// PA03 RTP pen
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA04 LCD MISO
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA05 LCD SCLK
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA06 LCD CS
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA07 LCD MOSI
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA08 Buzzer A
	{ TcOutput::tc0_1,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA09 Buzzer B
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d0.diag"	},	// PA10 driver 0 diag
	{ TcOutput::tc1_1,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"out4"			},	// PA11 OUT4
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA12 WiFi SCLK (SERCOM4.1)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA13 WiFi MISO (SERCOM4.0)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA14 WiFi SS (SERCOM4.2)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA15 WiFi MOSI (SERCOM4.3)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA16 WiFi RxD (SERCOM3.1)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA17 WiFi TxD (SERCOM3.0)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		2,	PinCapability::none,	nullptr			},	// PA18 WiFi ESP_DATA_RDY
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA19 WiFi SAM_TRANSFER_RDY
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA20 SDHC CMD
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA21 SDHC CLK
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA22 unused
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA23 unused
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA24 USB
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA25 USB
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA26 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d1.dir"	},	// PA27 driver 1 dir
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA28 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA29 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA30 swclk
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PA31 swdio/STATUS LED

	// Port B
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.spi.cd"	},	// PB00 external CD CD
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"ate.d2.diag"	},	// PB01 driver 2 diag
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"ate.d3.dir"	},	// PB02 driver 3 dir
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d0.dir"	},	// PB03 driver 0 dir
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_6,	SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB04 VssaMon
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_7,	SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB05 VrefMon
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_8,	SercomIo::none,		SercomIo::none,		6,	PinCapability::none,	"ate.vbus"		},	// PB06 Vbus
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_9,	SercomIo::none,		SercomIo::none,		7,	PinCapability::ainr,	"io0.in"		},	// PB07 IO0_IN
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d1.diag"	},	// PB08 driver 1 diag
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_1,	SercomIo::none,		SercomIo::none,		9,	PinCapability::none,	"io2.in"		},	// PB09 IO2_IN
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		10,	PinCapability::none,	"io1.in"		},	// PB10 IO1_IN
	{ TcOutput::tc5_1,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"out3"			},	// PB11 OUT3
	{ TcOutput::none,	TccOutput::tcc3_0F,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"ate.lcd.backlight"	},	// PB12 LCD backlight control
	{ TcOutput::tc4_1,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"out2"			},	// PB13 OUT2
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	nullptr			},	// PB14 WiFi ESP reset
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::read,	"ate.lcd.fontcs"	},	// PB15 LCD font CS
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.cd"		},	// PB16 SD CD
	{ TcOutput::tc6_1,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"out0"			},	// PB17 OUT0
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB18 SD DAT0
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB19 SD DAT1
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none	,	Nx,	PinCapability::none,	nullptr			},	// PB20 SD DAT2
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB21 SD DAT3
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB22 crystal XIN1
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB23 crystal XOUT1
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB24 unused (spare UART Sercom2)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB25 unused (spare UART Sercom2)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB26 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB27 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB28 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PB29 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::sercom5d,	SercomIo::none,		14,	PinCapability::read,	"io3.in"		},	// PB30 IO3_IN
	{ TcOutput::none,	TccOutput::tcc0_7G,	AdcInput::none,		SercomIo::none,		SercomIo::sercom5d,	Nx,	PinCapability::wpwm,	"io3.out"		},	// PB31 IO3_OUT

	// Port C
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_10,	SercomIo::none,		SercomIo::none,		Nx,	PinCapability::ain,		"temp0"			},	// PC00 thermistor0
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_11,	SercomIo::none,		SercomIo::none,		Nx,	PinCapability::ain,		"temp1"			},	// PC01 thermistor1
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_4,	SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.lcd.flashcs"	},	// PC02 LCD flash CS
	{ TcOutput::none,	TccOutput::none,	AdcInput::adc1_5,	SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.vin"		},	// PC03 VIN monitor
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC04 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.lcd.dc"	},	// PC05 LCD DC
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.lcd.rst"	},	// PC06 LCD_RST
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.lcd.flashhold"	},	// PC07 LCD flash hold
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC08 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC09 not on chip
	{ TcOutput::none,	TccOutput::tcc1_4G,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::wpwm,	"out1"			},	// PC10 OUT1
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		11,	PinCapability::none,	nullptr			},	// PC11 WiFi ESP enable
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC12 SPI MOSI
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC13 SPI SCK
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC14 SPI CS0 (external SD card)
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC15 SPI_MISO
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC16 LCD RTP MOSI
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC17 LCD RTP SCK
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC18 LCD RTP CS
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC19 LCD RTP MISO
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d3.step"	},	// PC20 driver 3 step
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d3.diag"	},	// PC21 driver 3 diag
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC22 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC23 not on chip
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d2.step"	},	// PC24 driver 2 step
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d1.step"	},	// PC25 driver 1 step
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d0.step"	},	// PC26 driver 0 step
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	"ate.d2.dir"	},	// PC27 driver 2 dir
	{ TcOutput::none,	TccOutput::none,	AdcInput::none,		SercomIo::none,		SercomIo::none,		Nx,	PinCapability::none,	nullptr			},	// PC28 driver ENN
};

constexpr unsigned int NumNamedPins = ARRAY_SIZE(PinTable);
static_assert(NumNamedPins == 32+32+29);

// DMA channel assignments. Channels 0-3 have individual interrupt vectors, channels 4-31 share an interrupt vector.
// When static arbitration within a priority level is selected, lower channel number have higher priority.
// So we use the low channel numbers for the highest priority sources.
constexpr DmaChannel DmacChanWiFiTx = 0;
constexpr DmaChannel DmacChanWiFiRx = 1;
constexpr DmaChannel DmacChanTmcTx = 2;
constexpr DmaChannel DmacChanTmcRx = 3;
constexpr DmaChannel DmacChanLcdTx = 4;

constexpr unsigned int NumDmaChannelsUsed = 5;

// The DMAC has priority levels 0-3 but on revision A chips it is unsafe to use multiple levels
// Fortunately, all our SAME54P20Achips seem to be revision D
constexpr DmaPriority DmacPrioTmcTx = 0;
constexpr DmaPriority DmacPrioTmcRx = 1;				// the baud rate is 100kbps so this is not very critical
constexpr DmaPriority DmacPrioWiFi = 2;					// high speed SPI in slave mode
constexpr DmaPriority DmacPrioSbc = 2;					// high speed SPI in slave mode

// Timer allocation
// TC2 and TC3 are used for step pulse generation and software timers
TcCount32 * const StepTc = &(TC2->COUNT32);
constexpr IRQn StepTcIRQn = TC2_IRQn;
constexpr unsigned int StepTcNumber = 2;
#define STEP_TC_HANDLER		TC2_Handler

// SAME5x event channel allocation, max 32 channels. Only the first 12 provide a synchronous or resynchronised path and can generate interrupts.
constexpr EventNumber CclLut0Event = 0;					// this uses up 4 channels
constexpr EventNumber NextFreeEvent = CclLut0Event + 4;

// Step pulse generation
namespace StepPins
{
	// *** These next three functions must use the same bit assignments in the drivers bitmap ***
	// Each stepper driver must be assigned one bit in a 32-bit word, in such a way that multiple drivers can be stepped efficiently
	// and more or less simultaneously by doing parallel writes to several bits in one or more output ports.
	// All our step pins are on port C, so the bitmap is just the map of step bits in port C.

	// Calculate the step bit for a driver. This doesn't need to be fast. It must return 0 if the driver is remote.
	static inline uint32_t CalcDriverBitmap(size_t driver) noexcept
	{
		return (driver < NumDirectDrivers)
				? 1u << (STEP_PINS[driver] & 0x1Fu)
				: 0;
	}

	// Set the specified step pins high. This needs to be fast.
	static inline __attribute__((always_inline)) void StepDriversHigh(uint32_t driverMap) noexcept
	{
		StepPio->OUTSET.reg = driverMap;				// all step pins are on port C
	}

	// Set the specified step pins low. This needs to be fast.
	static inline void __attribute__((always_inline)) StepDriversLow(uint32_t driverMap) noexcept
	{
		StepPio->OUTCLR.reg = driverMap;				// all step pins are on port C
	}
}

#endif /* SRC_DUET3MINI_PINS_DUET3MINI_H_ */
