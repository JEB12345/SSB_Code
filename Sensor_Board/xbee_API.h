/* 
 * File:   xbee_API.h
 * Author: jonathan
 *
 * Created on October 1, 2013, 8:14 PM
 */

#ifndef XBEE_API_H
#define	XBEE_API_H

#include "sensor_state.h"
//#include "sensor_pindefs.h"
//#include "sensor_rf.h"
#include <stdint.h>

/****************************
 * API Frame Names and Values
 ****************************/
// Definitions of the various API frame types
#define XBEE_API_FRAME_TX64			0x00
#define XBEE_API_FRAME_REMOTE_CMD_REQ		0x07
#define XBEE_API_FRAME_ATCMD			0x08
#define XBEE_API_FRAME_ATCMD_QUEUED		0x09
#define XBEE_API_FRAME_TX_IPV4			0x20
#define XBEE_API_FRAME_RX64_INDICATOR		0x80
#define XBEE_API_FRAME_REMOTE_CMD_RESP		0x87
#define XBEE_API_FRAME_ATCMD_RESP		0x88
#define XBEE_API_FRAME_TX_STATUS		0x89
#define XBEE_API_FRAME_MODEM_STATUS		0x8A
#define XBEE_API_FRAME_IO_DATA_SAMPLE_RX	0x8F
#define XBEE_API_FRAME_RX_IPV4			0xB0

// Modem Status Values that could be passed to the
// status callback function
#define XBEE_MODEM_STATUS_RESET			0x00
#define XBEE_MODEM_STATUS_WATCHDOG_RESET	0x01
#define XBEE_MODEM_STATUS_JOINED		0x02
#define XBEE_MODEM_STATUS_NO_LONGER_JOINED	0x03
#define XBEE_MODEM_STATUS_IP_CONFIG_ERROR	0x04
#define XBEE_MODEM_STATUS_S_OR_J_WITHOUT_CON	0x82
#define XBEE_MODEM_STATUS_AP_NOT_FOUND		0x83
#define XBEE_MODEM_STATUS_PSK_NOT_CONFIGURED	0x84
#define XBEE_MODEM_STATUS_SSID_NOT_FOUND	0x87
#define XBEE_MODEM_STATUS_FAILED_WITH_SECURITY	0x88
#define XBEE_MODEM_STATUS_INVALID_CHANNEL	0x8A
#define XBEE_MODEM_STATUS_FAILED_TO_JOIN	0x8E

// Definitions of AT commands for addressing
#define XBEE_AT_ADDR_DEST_ADDR			"DL"
#define XBEE_AT_ADDR_IPADDR			"MY"
#define XBEE_AT_ADDR_NETMASK			"MK"
#define XBEE_AT_ADDR_GATEWAY			"GW"
#define XBEE_AT_ADDR_SERNO_HIGH			"SH"
#define XBEE_AT_ADDR_SERNO_LOW			"SL"
#define XBEE_AT_ADDR_NODEID			"NI"
#define XBEE_AT_ADDR_DEST_PORT			"DE"
#define XBEE_AT_ADDR_SERIAL_COM_SERVICE_PORT	"C0"
#define XBEE_AT_ADDR_DEV_TYPE_ID		"DD"
#define XBEE_AT_ADDR_MAX_RF_PAYLOAD_BYTES	"NP"

// Definitions of AT commands for Network parameters
#define XBEE_AT_NET_SSID			"ID"
#define XBEE_AT_NET_TYPE			"AH"
#define XBEE_AT_NET_IPPROTO			"IP"
#define XBEE_AT_NET_ADDRMODE			"MA"
#define XBEE_AT_NET_TCP_TIMEOUT			"TM"

// Options associated with network commands
#define XBEE_NET_TYPE_IBSS_JOINER		0x00
#define XBEE_NET_TYPE_IBSS_CREATOR		0x01
#define XBEE_NET_TYPE_IBSS_INFRASTRUCTURE	0x02

#define XBEE_NET_IPPROTO_UDP			0x00
#define XBEE_NET_IPPROTO_TCP			0x01

#define XBEE_NET_ADDRMODE_DHCP			0x00
#define XBEE_NET_ADDRMODE_STATIC		0x01

// Definition of AT commands for Security
#define XBEE_AT_SEC_ENCTYPE			"EE"
#define XBEE_AT_SEC_KEY				"PK"

// Options associated with security commands
#define XBEE_SEC_ENCTYPE_NONE			0x00
#define XBEE_SEC_ENCTYPE_WPA			0x01
#define XBEE_SEC_ENCTYPE_WPA2			0x02
#define XBEE_SEC_ENCTYPE_WEP			0x03

// Definition of AT commands for RF control
#define XBEE_AT_RF_POWER_LEVEL			"PL"
#define XBEE_AT_RF_CHANNEL			"CH"
#define XBEE_AT_RF_BITRATE			"BR"

// Options associated with RF commands
#define XBEE_RF_BITRATE_AUTO			0x00
#define XBEE_RF_BITRATE_1MBPS			0x01
#define XBEE_RF_BITRATE_2MBPS			0x02
#define XBEE_RF_BITRATE_5MBPS			0x03
#define XBEE_RF_BITRATE_11MBPS			0x04
#define XBEE_RF_BITRATE_6MBPS			0x05
#define XBEE_RF_BITRATE_9MBPS			0x06
#define XBEE_RF_BITRATE_12MBPS			0x07
#define XBEE_RF_BITRATE_18MBPS			0x08
#define XBEE_RF_BITRATE_24MBPS			0x09
#define XBEE_RF_BITRATE_36_BMPS			0x0A
#define XBEE_RF_BITRATE_48_MBPS			0x0B
#define XBEE_RF_BITRATE_54_MBPS			0x0C
#define XBEE_RF_BITRATE_MCS0			0x0D
#define XBEE_RF_BITRATE_MCS1			0x0E
#define XBEE_RF_BITRATE_MCS2			0x0F
#define XBEE_RF_BITRATE_MCS3			0x10
#define XBEE_RF_BITRATE_MCS4			0x11
#define XBEE_RF_BITRATE_MCS5			0x12
#define XBEE_RF_BITRATE_MCS6			0x13
#define XBEE_RF_BITRATE_MCS7			0x14

// Definition of AT commands for diagnostics
#define XBEE_AT_DIAG_FIRMWARE_VERSION		"VR"
#define XBEE_AT_DIAG_HARDWARE_VERSION		"HV"
#define XBEE_AT_DIAG_ASSOC_INFO			"AI"
#define XBEE_AT_DIAG_ACTIVE_SCAN		"AS"
#define XBEE_AT_DIAG_TEMPERATURE		"TP"
#define XBEE_AT_DIAG_CONFIG_CODE		"CK"
#define XBEE_AT_DIAG_SUPPLY_VOLTAGE		"%V"
#define XBEE_AT_DIAG_RSSI			"DB"

// Options associated with diagnostic commands
#define XBEE_DIAG_ASSOC_INSV			0x00
#define XBEE_DIAG_ASSOC_INIT_INPROG		0x01
#define XBEE_DIAG_ASSOC_DISCONNECTING		0x13
#define XBEE_DIAG_ASSOC_SSID_NOT_FOUND		0x22
#define XBEE_DIAG_ASSOC_SSID_NOT_CONFIGURED	0x23
#define XBEE_DIAG_ASSOC_JOIN_FAILED		0x27
#define XBEE_DIAG_ASSOC_PENDING_DHCP		0x41
#define XBEE_DIAG_ASSOC_JOINED_IN_SETUP		0x42
#define XBEE_DIAG_ASSOC_SCANNING		0xFF

// Definition of AT commands for serial control
#define XBEE_AT_SERIAL_API_ENABLE		"AP"
#define XBEE_AT_SERIAL_INTERFACE_DATA_RATE	"BD"
#define XBEE_AT_SERIAL_SERIAL_PARITY		"NB"
#define XBEE_AT_SERIAL_STOP_BITS		"SB"
#define XBEE_AT_SERIAL_PACKET_TIMEOUT		"RO"
#define XBEE_AT_SERIAL_DIO7_CONFIG		"D7"
#define XBEE_AT_SERIAL_DIO6_CONFIG		"D6"

// Options associated with serial control commands
#define XBEE_SERIAL_API_TRANSPARENT		0x00
#define XBEE_SERIAL_API_ENABLE_NOESC		0x01
#define XBEE_SERIAL_API_ENABLE_ESC		0x02

#define XBEE_SERIAL_DATA_RATE_1200		0x00
#define XBEE_SERIAL_DATA_RATE_2400		0x01
#define XBEE_SERIAL_DATA_RATE_4800		0x02
#define XBEE_SERIAL_DATA_RATE_9600		0x03
#define XBEE_SERIAL_DATA_RATE_19200		0x04
#define XBEE_SERIAL_DATA_RATE_38400		0x05
#define XBEE_SERIAL_DATA_RATE_57600		0x06
#define XBEE_SERIAL_DATA_RATE_115200		0x07
#define XBEE_SERIAL_DATA_RATE_230400		0x08

#define XBEE_SERIAL_PARITY_NONE			0x00
#define XBEE_SERIAL_PARITY_EVENT		0x01
#define XBEE_SERIAL_PARITY_ODD			0x02

#define XBEE_SERIAL_STOPBITS_1			0x00
#define XBEE_SERIAL_STOPBITS_2			0x01

#define XBEE_SERIAL_DIO7_DISABLED		0x00
#define XBEE_SERIAL_DIO7_CTS			0x01
#define XBEE_SERIAL_DIO7_DIGITAL_IN		0x03
#define XBEE_SERIAL_DIO7_DIGITAL_OUT_LOW	0x04
#define XBEE_SERIAL_DIO7_DIGITAL_OUT_HIGH	0x05
#define XBEE_SERIAL_DIO7_RS485_TX_ENABLE_HIGH	0x06
#define XBEE_SERIAL_DIO7_RS485_TX_ENABLE_LOW	0x07

#define XBEE_SERIAL_DIO6_DISABLED		0x00
#define XBEE_SERIAL_DIO6_RTS			0x01
#define XBEE_SERIAL_DIO6_DIGITAL_IN		0x03
#define XBEE_SERIAL_DIO6_DIGITAL_OUT_LOW	0x04
#define XBEE_SERIAL_DIO6_DIGITAL_OUT_HIGH	0x05

// Definition of AT commands for IO control
#define XBEE_AT_IO_FORCE_SAMPLE			"IS"
#define XBEE_AT_IO_SAMPLE_RATE			"IR"
#define XBEE_AT_IO_DIGITAL_CHANGE_DETECTION	"IC"
#define XBEE_AT_IO_SAMPLE_FROM_SLEEP_RATE	"IF"
#define XBEE_AT_IO_DIO10_CONFIG			"P0"
#define XBEE_AT_IO_DIO11_CONFIG			"P1"
#define XBEE_AT_IO_DIO12_CONFIG			"P2"
#define XBEE_AT_IO_DOUT_CONFIG			"P3"
#define XBEE_AT_IO_DIN_CONFIG			"P4"
#define XBEE_AT_IO_AD0_DIO0_CONFIG		"D0"
#define XBEE_AT_IO_AD1_DIO1_CONFIG		"D1"
#define XBEE_AT_IO_AD2_DIO2_CONFIG		"D2"
#define XBEE_AT_IO_AD3_DIO3_CONFIG		"D3"
#define XBEE_AT_IO_DIO4_CONFIG			"D4"
#define XBEE_AT_IO_DIO5_CONFIG			"D5"
#define XBEE_AT_IO_DIO8_CONFIG			"D8"
#define XBEE_AT_IO_DIO9_CONFIG			"D9"
#define XBEE_AT_IO_ASSOC_LED_BLINK_TIME		"LT"
#define XBEE_AT_IO_PULLUP			"PR"
#define XBEE_AT_IO_PULL_DIRECTION		"PD"
#define XBEE_AT_IO_ANALOG_VOLTAGE_REF		"AV"
#define XBEE_AT_IO_PWM0_DUTY_CYCLE		"M0"
#define XBEE_AT_IO_PWM1_DUTY_CYCLE		"M1"

// Options associated with IO commands
#define XBEE_IO_DISABLED			0x00
#define XBEE_IO_ENABLED				0x01
#define XBEE_IO_ANALOG_INPUT			0x02
#define XBEE_IO_DIGITAL_INPUT_MONITORED		0x03
#define XBEE_IO_DIGITAL_INPUT_DEFAULT_LOW	0x04
#define XBEE_IO_DIGITAL_INPUT_DEFAULT_HIGH	0x05
#define XBEE_IO_SPI_MISO			0X01
#define XBEE_IO_SPI_ATTN			0x01
#define XBEE_IO_SPI_CLK				0x01
#define XBEE_IO_SPI_SELECT			0x01
#define XBEE_IO_SPI_MOSI			0x01
#define XBEE_IO_ASSOC_INDICATOR			0x01
#define XBEE_IO_SLEEP_REQ			0x01
#define XBEE_IO_ON_SLEED_INDICATOR		0x01
#define XBEE_IO_AVREF_1_25V			0x00
#define XBEE_IO_AVREF_2_5V			0x01

// Definition of AT commands for AT command options
#define XBEE_AT_CMD_OPT_CMD_MODE_TIMEOUT	"CT"
#define XBEE_AT_CMD_OPT_EXIT_COMMAND_MODE	"CN"
#define XBEE_AT_CMD_OPT_GUARD_TIMES		"GT"
#define XBEE_AT_CMD_OPT_CMD_MODE_CHAR		"CC"

// Definition of AT commands for sleep commands
#define XBEE_AT_SLEEP_MODE			"SM"
#define XBEE_AT_SLEEP_PERIOD			"SP"
#define XBEE_AT_SLEEP_OPTIONS			"SO"
#define XBEE_AT_WAKE_HOST			"WH"
#define XBEE_AT_WAKE_TIME			"ST"

// Options associated with sleep commands
#define XBEE_SLEEP_NO_SLEEP			0x00
#define XBEE_SLEEP_PIN_SLEEP			0x01
#define XBEE_SLEEP_CYCLIC_SLEEP			0x04
#define XBEE_SLEEP_CYCLIC_SLEEP_PIN_WAKE	0x05

// Definition of AT commands for execution
#define XBEE_AT_EXEC_APPLY_CHANGES		"AC"
#define XBEE_AT_EXEC_WRITE			"WR"
#define XBEE_AT_EXEC_RESTORE_DEFAULTS		"RE"
#define XBEE_AT_EXEC_SOFTWARE_RESET		"FR"
#define XBEE_AT_EXEC_NETWORK_RESET		"NR"

// Definition of API header lengths
#define LENGTH_XBEE_START_DELIMITER             1
#define LENGTH_XBEE_API_LENGTH                  2
#define LENGTH_XBEE_API_ID                      1
#define LENGTH_XBEE_FRAMEID                     1
#define LENGTH_XBEE_CHECKSUM                    1

// Definiton of AT header lengths
#define LENGTH_XBEE_API_ATCMD                   2
#define LENGTH_XBEE_AT_FRAME_NOPARAM            LENGTH_XBEE_START_DELIMITER+LENGTH_XBEE_API_LENGTH+LENGTH_XBEE_API_ID+LENGTH_XBEE_FRAMEID+LENGTH_XBEE_API_ATCMD+LENGTH_XBEE_CHECKSUM

// Definition of IPv4 API header lengths
#define LENGTH_XBEE_IPv4_DESTINATION_ADDRESS    4
#define LENGTH_XBEE_IPv4_DESTINATION_PORT       2
#define LENGTH_XBEE_IPv4_SOURCE_PORT            2
#define LENGTH_XBEE_IPv4_PROTOCOL               1
#define LENGTH_XBEE_IPv4_OPTIONS                1
#define LENGTH_XBEE_IPv4_FRAME_NODATA           LENGTH_XBEE_IPv4_DESTINATION_ADDRESS+LENGTH_XBEE_IPv4_DESTINATION_PORT+LENGTH_XBEE_IPv4_SOURCE_PORT+LENGTH_XBEE_IPv4_PROTOCOL+LENGTH_XBEE_IPv4_OPTIONS+LENGTH_XBEE_CHECKSUM

// This packet is used for the sample reception callback to provide sample data
typedef struct {
	uint8_t source_addr[4];
	uint16_t digital_mask;
	uint8_t analog_mask;
	uint16_t digital_samples;
	uint16_t analog_samples;
} s_sample;

#define XBEE_CHECKSUM_VALUE 0xFF

/***********
 * Functions
 ***********/

/**
 * @brief confirm_checksum checks if message was received correctly.
 *
 * Checks the integrity of the message. If the checksum does not equal 0xFF, the
 * fuction will return RET_ERROR.
 *
 * @param data A pointer to the wifi_data being checked
 */
//return_value_t confirm_checksum(wifi_data* data);



// Send AT command with data of various possible forms
// atxx = Two digit string (i.e. "XY" would indicate ATXY command)
// Set queued = true to delay execution until applied (per spec)
// But note that queued AT commands are executed without confirmation
// so errors will not be reported
bool xbee_at_cmd_raw(const char *atxx, uint8_t *buffer, int len, bool queued);
bool xbee_at_cmd_str(const char *atxx, const char *buffer, bool queued );
bool xbee_at_cmd_byte(const char *atxx, uint8_t byte, bool queued );
bool xbee_at_cmd_short(const char *atxx, uint16_t twobyte, bool queued );
bool xbee_at_cmd_noparm(const char *atxx, bool queued );

// Query an AT parameter
// Provide a buffer (parmval) and it's length (maxlen)
// Will return parmlen indicating the number of bytes read back into the buffer
bool xbee_at_query(const char *atxx, uint8_t *parmval, int *parmlen, int maxlen);


// The following functions define callbacks for asynchronous data delivery
// To stop delivery (and discard data) of any given type
// set the associated callback to it's default (NULL)

// Register a callback to receive incoming IP data
// Callback should be of following form:
//	void my_callback(uint8_t *data, int len, s_rxinfo *info)
void xbee_register_ip_data_callback(void (*func)(uint8_t *, int, s_rxinfo *));

// Register callback for modem status indications
// Callback should be of following form:
//	void my_callback(uint8_t status)
void xbee_register_status_callback(void (*func)(uint8_t));

// Transmit data to an endpoint
// ip should be the binary form (uint8_t[4]) IP address
// addr should be transmission options indicating port assignments and such. May be null when useAppService is true
// data and len provide the data to be transmitted
// Leave confirm=true to block for confirmation of delivery (TCP)
// Set useAppService to true to use the compatability mode (64bit) app service to transmit the data to the 0xBEE port
bool xbee_transmit(const uint8_t *ip, s_txoptions *addr, uint8_t *data, int len, bool confirm, bool useAppService );

//PRIVATE
// This is the actual method that does all AT processing
bool xbee_at_cmd(const char *atxx, const uint8_t *parmval, int parmlen, void *returndata, int *returnlen, bool queued);

// Transmit an API frame of specified type, length and data
void xbee_tx_frame(uint8_t type, unsigned int len, uint8_t *data);

        
        
#endif	/* XBEE_API_H */

