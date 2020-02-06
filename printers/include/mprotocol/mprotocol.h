#ifndef MACSA_MPROTOCOL_DEFINITIONS_H
#define MACSA_MPROTOCOL_DEFINITIONS_H

#include "printer/printer.h"
#include <string>

namespace  Macsa {
	namespace  MProtocol {

#define M_PROTOCOL_PORT	9991

#define ATTRIBUTE_VALUE		"Value"
#define ATTRIBUTE_ID		"id"
#define ATTRIBUTE_FILEPATH	"FilePath"
#define ATTRIBUTE_NAME		"Name"
#define ATTRIBUTE_CODE		"Code"
#define ATTRIBUTE_KEY		"Key"

#define MWIND				"WIND"
#define MWIND_ID_ATTR		ATTRIBUTE_ID

#define MERROR				"ERROR"

#define MLIVE				"LIVE"
#define MLIVE_DT_ATTR			"DateTime"
#define MLIVE_STATUS_ATTR		"StatusChanged"
#define MLIVE_CONFIG_ATTR		"ConfigChanged"
#define MLIVE_FILES_ATTR		"FilesChanged"
#define MLIVE_FONTS_ATTR		"FontsChanged"
#define MLIVE_USER_VALUES_ATTR	"UVChanged"
#define MLIVE_ERROR_ATTR		"HaveError"
#define MLIVE_ERRORS_LOG_ATTR	"ErrLogChanged"

#define MSTATUS					"STATUS"
#define MIOSTATUS				"IOSTATUS"
#define MERRORS_GET				"GETERRORS"

#define MSTATUS_DT				"DATETIME"
#define MSTATUS_VERSION			"VERSIONS"
#define MSTATUS_VERSION_CTRL	"CONTROLLER"
#define MSTATUS_VERSION_FPGA	"FPGA"
#define MSTATUS_VERSION_API		"API"

#define MCONFIG_GET				"GETCONFIGURATION"
#define MCONFIG_SET				"SETCONFIGURATION"
#define MCONFIG_GENERAL				"GENERAL"
#define MCONFIG_GENERAL_DT				MSTATUS_DT
#define MCONFIG_GENERAL_LOG				"LOG"
#define MCONFIG_GENERAL_LOG_LEVEL_ATTR 		"traceLevel"
#define MCONFIG_GENERAL_LOG_ENABLED_ATTR 	"traceLogs"
#define MCONFIG_GENERAL_LOG_COMMS 			"traceComDetails"

#define MCONFIG_CONNECTIONS			"CONNECTIONS"
#define MCONFIG_CONN_NETWORK			"NETWORK"
#define MCONFIG_CONN_NETWORK_ADAPTER		"ADAPTER"
#define MCONFIG_CONN_NETWORK_IP					"IP_ADDRESS"
#define MCONFIG_CONN_NETWORK_SUBNET				"SUBNET_MASK"
#define MCONFIG_CONN_NETWORK_GATEWAY			"GATEWAY"
#define MCONFIG_CONN_NETWORK_DHCP				"DHCP"
#define MCONFIG_CONN_NETWORK_HOSTNAME			"HOSTNAME"
#define MCONFIG_CONN_NETWORK_TCPPORT			"TCP_PORT"
#define MCONFIG_CONN_BLUETOOTH			"BLUETOOTH"
#define MCONFIG_CONN_BLUETOOTH_DEVNAME		"DEVICE_NAME"
#define MCONFIG_CONN_BLUETOOTH_VISIBILITY	"VISIBILITY"
#define MCONFIG_CONN_BLUETOOTH_PASSWORD		"PASSWORD"

#define MPRINTER_BOARDS_LIST	"BOARDS"
#define MPRINTER_BOARD			"BOARD"
#define MPRINTER_BOARD_ENABLED_ATTR	"Enabled"
#define MPRINTER_BOARD_PRINT_ATTR	"Printing"
#define MPRINTER_BOARD_TYPE			"TYPE"
#define MPRINTER_BOARD_ENABLED		"ENABLED"
#define MPRINTER_BOARD_BLOCKED		"BLOCK"
#define MPRINTER_BOARD_PRINTING		"PRINTING"
#define MPRINTER_BOARD_AUTOSTART	"AUTOSTART"
#define MPRINTER_BOARD_LOW_LEVEL	"LOWLEVEL_OUTPUT"
#define MPRINTER_BOARD_CURRENT_MSG	"CURRENT_MESSAGE"

#define MPRINTER_BOARD_PRINT_SPEED		"PRINT_SPEED"
#define MPRINTER_BOARD_PRINTS_REMAIN	"NUM_PRINTS_REMAIN"

#define MPRINTER_BOARD_BCD_MODE		"BCD_MODE"
#define MPRINTER_BOARD_BCD_STATUS   "BCD_STATUS"
#define MPRINTER_BOARD_BCD_TABLE	"BCD_ASSIGNMENT"
#define MPRINTER_BOARD_BCD_CODE		"BCD"

#define MPRINTER_BOARD_SHOT_MODE				"SHOT_MODE"
#define MPRINTER_BOARD_SHOT_MODE_MODE_ATTR			"Mode"
#define MPRINTER_BOARD_SHOT_MODE_DELAY_ATTR			"Delays"
#define MPRINTER_BOARD_SHOT_MODE_REPEAT_ATTR		"Repeat"
#define MPRINTER_BOARD_SHOT_DELAY				"DELAY"
#define MPRINTER_BOARD_SHOT_DELAY_UNITS_ATTR		"Units"

#define MPRINTER_BOARD_ENCODER					"ENCODER"
#define MPRINTER_BOARD_ENCODER_MODE_ATTR			"CurrentMode"
#define MPRINTER_BOARD_ENCODER_FIXED			"FIXED_SPEED"
#define MPRINTER_BOARD_ENCODER_EXTERNAL			"EXTERNAL_ENCODER"
#define MPRINTER_BOARD_ENCODER_EXT_RESOL_ATTR		"Resolution"
#define MPRINTER_BOARD_ENCODER_EXT_DIAM_ATTR		"Diameter"

#define MPRINTER_BOARD_PRINT_DIR		"PRINT_DIRECTION"
#define MPRINTER_BOARD_PRINT_INVERTED	"INVERTED"
#define MPRINTER_BOARD_NOZZLES_COL		"NOZZLES_COLUMN"
#define MPRINTER_BOARD_PHOTOCELL		"PRODUCT_PHOTOCELL"

#define MPRINTER_BOARD_CARTRIDGE				"CARTIGE"	//TODO change to CARTRIDGE
#define MPRINTER_BOARD_CARTRIDGE_AUTOCONFIG_ATTR   "AutoConfig"
#define MPRINTER_BOARD_CARTRIDGE_VOLTAGE_ATTR	   "Voltage"
#define MPRINTER_BOARD_CARTRIDGE_PULSE_WARM_ATTR   "PulseWarming"
#define MPRINTER_BOARD_CARTRIDGE_WARM_TEMP_ATTR    "PulseWarmingTemp"
#define MPRINTER_BOARD_CARTRIDGE_COL_DIST_ATTR     "ColumnDistance"
#define MPRINTER_BOARD_CARTRIDGE_PULSE_WIDTH_ATTR  "PulseWidth"
#define MPRINTER_BOARD_CARTRIDGE_ADJ_CAPACITY_ATTR "AdjustedCapacity"

#define MPRINTER_BOARD_COUNTERS_LIST "COUNTERS"
#define MPRINTER_BOARD_COUNTER			"COUNTER"
#define MPRINTER_BOARD_COUNT_TOTAL		"total"
#define MPRINTER_BOARD_COUNT_USER		"user"

#define MPRINTER_BOARD_ERRORS_LIST		"ERRORS"
#define MPRINTER_BOARD_ERROR 			"ERROR"
#define MPRINTER_BOARD_ERR_TSTAMP_ATTR		"When"
#define MPRINTER_BOARD_ERR_TYPE_ATTR		"Type"
#define MPRINTER_BOARD_ERR_PRIO_ATTR		"Priority"
#define MPRINTER_BOARD_ERR_CODE_ATTR		"ErrorCode"

#define MPRINTER_BOARD_INPUTS_LIST		"INPUTS"
#define MPRINTER_BOARD_INPUT 			"INPUT"
#define MPRINTER_BOARD_OUTPUTS_LIST		"OUTPUTS"
#define MPRINTER_BOARD_OUTPUT 			"OUTPUT"
#define MPRINTER_BOARD_IO_DESCRIPT_ATTR		"Descriptor"
#define MPRINTER_BOARD_IO_CONFIG_ATTR		"Config"
#define MPRINTER_BOARD_IO_INVERTED_ATTR		"Inverted"
#define MPRINTER_BOARD_IO_FILTER_ATTR		"Filter"
#define MPRINTER_BOARD_IO_TYPE_ATTR			"Type"
#define MPRINTER_BOARD_IO_TIME_ATTR			"Time"
#define MPRINTER_BOARD_IO_INI_VAL_ATTR		"InitialValue"

#define MPRINTER_BOARD_PROPERTIES_LIST	"PROPERTIES"
#define MPRINTER_BOARD_PROPERTY			"PROPERTY"

#define MPRINTER_DATECODES_LIST			"DATECODES"
#define MPRINTER_DATECODE				"DATECODE"
#define MPRINTER_DATECODE_FORMAT_ATTR		"Format"
#define MPRINTER_DATECODE_CODE			"CODE"
#define MPRINTER_DATECODE_INTERVAL_ATTR		"IntervalStart"


#define FONTS_FILTER	".ttf"
#define NISX_FILTER		".nisx"
#define IMG_FILTER		".png,.jpg,.jpeg,.bmp"
#define NO_FILTER		"*.*"
#define ALL_FILES		".nisx,.ttf,.png,.jpg,.jpeg,.bmp"

#define MFILES_GET_LIST				"GETFILESLIST"
#define MFILES_GET_LIST_TYPE_ATTR		"type"
#define MFILES_DEVICE_UNIT			"UNIT"
#define MFILES_FILE_PATH			"FILE"
#define MFILES_FILE_PATH_ATTR			"Path"
#define MFILES_COPY					"COPYFILE"
#define MFILES_SOURCE_PATH_ATTR			"SourceFilePath"
#define MFILES_TARGET_PATH_ATTR			"TargetFilePath"
#define MFILES_MOVE					"MOVEFILE"
#define MFILES_DELETE				"DELETEFILE"
#define MFILES_GET					"GETFILE"
#define MFILES_SET					"SETFILE"
#define MFILES_FILE_RAW_ATTR			"Raw"
#define MFILES_FILE_CONTENT			"CONTENT"

#define MMESSAGE_USER_FIELD_GET			"GETMESSAGEVALUES"
#define MMESSAGE_USER_FIELD_SET			"SETMESSAGEVALUES"
#define MMESSAGE_DATA_SOURCE_GET		"GETMESSAGEDATASOURCE"
#define MMESSAGE_DATA_SOURCE_SET		"SETMESSAGEDATASOURCE"

#define MMESSAGE_DATA_SOURCE_FIELD_TYPE_ATTR "FieldType"
#define DATA_SOURCE_ALL_FIELDS					""
#define DATA_SOURCE_USER_FIELDS					"user"
#define DATA_SOURCE_DATETIME_FIELDS				"date"
#define DATA_SOURCE_COUNTER_FIELDS				"counter"
#define MMESSAGE_USER_FIELD_ELEMENT		"UI_FIELD"
#define MMESSAGE_DATETIME_FIELD_ELEMENT	"DATETIME"
#define MMESSAGE_DATETIME_FORMAT_ATTR		"Format"
#define MMESSAGE_DATETIME_DOFFSET_ATTR		"DayOffset"
#define MMESSAGE_DATETIME_MOFFSET_ATTR		"MonthOffset"
#define MMESSAGE_DATETIME_YOFFSET_ATTR		"YearsOffset"
#define MMESSAGE_DATETIME_SOD_ATTR			"SoD"
#define MMESSAGE_COUNTER_FIELD_ELEMENT	"COUNTER"
#define MMESSAGE_COUNTER_ZERO_ATTR			"LeadingZeros"
#define MMESSAGE_COUNTER_MIN_ATTR			"Min"
#define MMESSAGE_COUNTER_MAX_ATTR			"Max"
#define MMESSAGE_COUNTER_STEP_ATTR			"Step"
#define MMESSAGE_COUNTER_REPEAT_ATTR		"Repeat"




#define MUPDATE					"UPDATE"
#define MUPDATE_PROGRESS_ATTR	"Progress"
#define MUPDATE_STATUS			"STATUS"
#define MUPDATE_HMI_VERSIONS	"HMI_VERSIONS"
#define MUPDATE_HMI_BIN				"HMI"
#define MUPDATE_HMI_BIN_VERSION_ATTR	"Version"
#define MUPDATE_HMI_BIN_MD5SUM_ATTR		"MD5"

#define OPEN_CDATA	"<![CDATA["
#define CLOSE_CDATA	"]]>"

// /////////////////////////////////////////////////////////////////// //		//MOVE TO PRINTER DEFINITIONS
#define key_prop_status_general_printer_vendor				"PRINTER.VENDOR"
#define key_prop_status_general_printer_sn					"PRINTER.SERIAL_NUM"

#define key_prop_status_general_print_speed					"GENERAL.CURRENT_PRINT_SPEED"
#define key_prop_status_general_print_remain				"GENERAL.NUM_PRINTS_REMAIN"
#define key_prop_status_general_prod_rate					"GENERAL.PROD_RATE"
#define key_prop_status_general_header_type					"GENERAL.HeaderType"

#define key_prop_status_cartridge_connected					"HP.SmartCardSessionOpened"
#define key_prop_status_cartridge_trademark					"HP.ManufactureId"
#define key_prop_status_cartridge_part_number				"HP.PartNumber"
#define key_prop_status_cartridge_id						"HP.CartridgeId"
#define key_prop_status_cartridge_chip_tag					"HP.SmartCardChipTag"
#define key_prop_status_cartridge_firing_frequency			"HP.FiringFrequency"
#define key_prop_status_cartridge_firing_voltage			"HP.FiringVoltage"
#define key_prop_status_cartridge_pulse_width				"HP.PulseWidth"
#define key_prop_status_cartridge_pulse_warming				"HP.PulseWarming"
#define key_prop_status_cartridge_max_temperature			"HP.MaxTemperature"
#define key_prop_status_cartridge_turn_on_energy			"HP.TurnOnEnergy"
#define key_prop_status_cartridge_drop_volume				"HP.DropVolume"
#define key_prop_status_cartridge_tank_volume				"HP.TankVolume"
#define key_prop_status_cartridge_ink_level_gauge			"HP.InkLevelGauge"
#define key_prop_status_cartridge_total_usage_gauge			"HP.TotalUsageGauge"
#define key_prop_status_cartridge_altered_supply			"HP.AlteredSupply"
#define key_prop_status_cartridge_altered_supply_notif_lvl	"HP.AlteredSupplyNotificationLevel"
#define key_prop_status_cartridge_out_of_ink				"HP.OutOfInk"
#define key_prop_status_cartridge_first_platform_id			"HP.FirstPlatformId"
//	#define key_prop_status_cartridge_manufacture_date			"HP.ManufactureDate" //Same as fill date
#define key_prop_status_cartridge_fill_date					"HP.FillDate"
#define key_prop_status_cartridge_first_install_date		"HP.FirstInstall"
#define key_prop_status_cartridge_last_use_date				"HP.LastDayOfUse"
#define key_prop_status_cartridge_shelf_days				"HP.ShelfDays"
#define key_prop_status_cartridge_shelf_weeks				"HP.ShelfWeeks"
#define key_prop_status_cartridge_expiration_date			"HP.ExpirationDate"
#define key_prop_status_cartridge_expiration_flag			"HP.ExpiredInk"

#define key_counter_system_total "SYSTEM.TOTAL"
#define key_counter_system_user  "SYSTEM.USER"
#define key_counter_system_bcd	 "BCD."

	} //namespace Protocol
}//namespace Macsa

#endif
