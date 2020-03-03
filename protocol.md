# Protocol M

## Revision History:
Version | Date | Edited by | Changes
-|-|-|-
1.0.0 | 2017 June 28 | Nico Mesas | First Release.
1.0.1 | 2018 June 05 | Ignasi Serra | Add type file at [Get files list](#get-files-list).
1.1.0 | 2018 July  25 | Ignasi Serra | Adds [shot mode](#status-and-configuration) for multiprinting by trigger.
1.1.0 | 2018 August 28 | Ignasi Serra|Added [Nozzles column](#status-and-configuration).
1.1.0 | 2018 September 03 | Ignasi Serra|Added cartridge block parameter.
1.1.1 | 2018 August 28 | Ignasi Serra|Added [Date Codes](#date-codes).
1.3.0 | 2019 May 15 | Ignasi Serra| Refactored [live](#live) command and added new commands to improve performance ([Get IO Status](#get-io-status), [Get Errors](#get-errors)).
1.3.0 | 2019 June 05 |Ignasi Serra | Added [2 new commands](#get-message-data-source) to modify message datasource fields.
1.3.1 | 2019 July  01 | Alex Dorado | Allow to send files in [RAW mode](#get-file).

### Index of content
1. [Introduction](#introduction)
1. [Commands](#Files-management)
    
    2.1. [Files management](#Files-management)
    
    - [Get files list](#get-files-list)
    - [Copy file](#copy-file)
    - [Move file](#move-file)
    - [Delete file](#delete-file)
    - [Get file](#get-file)
    - [Set file](#set-file)
    - [Get message value](#get-message-value)
    - [Set message value](#set-message-value)
    - [Get message data source](#get-message-data-source)
    - [Set message data source](#set-message-data-source)
    
    2.2. [Status and configuration](#status-and-configuration)
    
    - [Get status](#get-status)
    - [Get IO status](#get-io-status)
    - [Get errors list](#get-errors)
1. [Data types](#data-types)
1. [Error codes](#error-codes)


## Introduction
This repository contains the code and documentation of Macsa Tij communication protocol.

_Main Brains: José Antonio Bou and Marc Soleda_

_Validated By: José Antonio Bou and Marc Soleda_

---

This protocol uses xml as a language to create the payload. Payloads sent and received must be wrapped as follows:
```xml
<WIND id="[Command ID]">
    <COMMAND_NAME>
        {content}
    </COMMAND_NAME>
</WIND>
```



## Data types
>Note BOOL values must be string literals "true" or "false"

Field | Type | Description
-|-|-
Command Id | unsigned int | Unique identifier of a command sent, this identifier links command sent with the response.
Error Code | unsigned int | Integer with the error code. NOTE: Depending the error, the MAIN element maybe returned empty (see [Error codes](#error-codes)) 
Logical file path | string | The logical File path for a physical file (see [Files management](#files-management)) 
Logical Actived Unit Name  | string | Name of actived drive on server. This must be **`//`** or  **`USB//`** (see [Files management](#files-management)) 
File Content | string | Content of file codified in base64 ( by default ) or in RAW using CDATA if bool param 'Raw' is 'true'
Message type | enum | String with the type of file (see [Message types](#message-types)). 
User field name | string | String with the name of the user field
User field value | string | String with the value of the user field.
Date time | date time | Format ddMMyyyy HHmmss ww ...
Firmware controller | string | String that contains the firmware controller version.
Firmware FPGA | string | String that contains the firmware fpga version.
API Version | string | String that contains the API version.
Speed Value | double | Decimal value with one digit precision and the '.' as separator.
Board Id | unsigned int | Unsigned char with the index value
Board Type | string | literal String: _SM190, SM200 ..._ 
Printing Status | bool | True whether the printhead(board) is printing or False otherwise.
Autostart value | bool | Printer puts automatically in running mode when power-on if enabled.
Printhead Enabled | bool | True=Automatic mode. False=Manual mode
Counter Id | string | Name of the counter: _'USER' or 'BCD.XX'._ 
Counter Value | unsigned int | User counter value and counter of each BCD code.
Total Counter | unsigned int | Total Counter of the printhead (board).
Fixed speed | double | Decimal value with one digit precision and '.' . 
Photocell type | enum | Type of photocells (see [Photocell type](#photocell-type)). 
Photocell mode | enum | Sets the photocell mode ([Photocell mode](#photocell-mode)). 
BCD mode value | enum | Defines the BCD Mode ([BCD mode](#bcd-mode)). 
BCD value | unsigned int | Unsigned char with the decimal value.
Printer Error Type | enum | Defines the [Error type](#printer-error-types). 
Printer Error Priority | unsigned int | Ordinal number that defines the severity of the error message.
Printer Error Code | string | Unique alphanumeric code for an error.
Input Id | unsigned int | Unique input identifier.
Input descriptor | string | Description of input type.
Input value | bool | Input status value.
Output Id | unsigned int | Unique output identifier.
Output descriptor | string | Description of output type.
Output value | bool | Output status value.
Property key | string | Anything
Property value | string | Value depending on the key
Adapter id | unsigned int | Unique adapter identification
IP address | string | IP adress X.X.X.X _192.168.1.64 and 192.168.16.210 by default_
Subnet mask | string | Netmask X.X.X.X _255.255.255.0 by default_
Gateway | string | Gateway X.X.X.X _192.168.1.1 by default_
HostName | string | String with the host name **TO REVIEW**
TCP Port | unsigned int | Communications TCP Port _9991 by default_
Bluetooth Device name| string | String with the name of the device _**NOT IMPLEMENTED**_ 
Bluetooth Visibility | bool | To enable visibility of the bluetooth device **TO REVIEW**
Bluetooth Password | string | Password of the bluetooth connection **TO REVIEW**
Encoder Mode | enum | To set current encoder mode (see [Encoder mode](#encoder-mode)) 
Fixed Speed value | double | Decimal value with one digit presition _X.X_ 
External resolution value | unsigned int | Number of encoder pulses
External diameter value | double | Encoder wheel diameter in decimal with one digit precision. _72.5 by default_
BCD Code | string | Unsigned char with the bcd code **TO REVIEW**
Print direction value | enum | To set print direction. XYDebugSetupPrinthead="1" **TO REVIEW** (see [Print direction](#print-direction)) 
Inverted value | bool | **IDK, Enable of print inverted? TO REVIEW**
Delay value | unsigned int | Unsigned int to define the print delay value in **dots**
Delay units | enum | To define delay units **TO REVIEW, exists?** 
Input config value | enum | Input configuration: _state or edge_ (see [Inputs configuration](#inputs-configuration)) 
Input inverted value | bool |To enable input activation by falling edge or negative pulse
Input filter value | unsigned int | To define input filter in miliseconds
Output type | enum | Enum with all types of possible outputs (see [Output types](#output-types)) 
Output time value | unsigned int | Time in miliseconds that an output is active
Initial value | bool | **IDK, To set output state by default? TO REVIEW**
Status changed value | bool | To notify that status changed (see [Live protocol](#live-protocol)) 
Config changed value | bool | To notify that configuration changed (see [Live protocol](#live-protocol)) 
Files changed | bool | To notify that files changed (see [Live protocol](#live-protocol)) 
Have errors | bool | To notify the error state (see [Live protocol](#live-protocol)) 
Nozzle columns | enum | To select which nozzle column is used to print (see [Nozzle columns](#nozzle-columns))

---
### Enumerations:
#### Message types
Value | Name | Description
-|-|-
0 | Message | Message files
1 | Configuration | Configuration files
2 | Application | Executable files (printer software)
3 | Firmware | Binary file (FPGA firmware)

#### Printer error types

Value| Name|Description
-|-|-|
0| Information | Information message. 
1| Warning| Warnings allow printing status but show that something happens. 
2| Error| Errors stop printing status and they don't allow printing. 

#### Encoder Mode
Value | Name | Description
-|-|-
FixedSpeed | Fixed speed | Speed is fixed as configured.
Internal | Internal encoder | Speed is calculated using internal photocells detection.
External | External encoder | Speed is calculated using pulses of a external encoder.

#### Photocell type
Value | Name | Description
-|-|-
FTC1 | Photocell 1 | Internal photocell 1.
FTC2 | Photocell 2 | Internal photocell 2.
FTCEXT | External photocell | External photocell. **TO REVIEW _Description="" XYDebugSetupPrinthead="23  De moment només interna o externa"_**

#### Photocell Mode
Value | Name | Description
-|-|-
Internal | Internal photocells | Internal photocells are used to product detection and trigger
External | External photocell | External photocel is used as trigger signal

#### BCD mode
Value | Name | Description
-|-|-
Mode0 | No BCD | Manual - **No** BCD Mode. User changes the current message manually and input0 starts printer, input1 stops printer, input2 resets actived user counter, input3 resets print direction and input4 inverts print direction. 
Mode1 | One direction | BCD input signals select the current message from the BCD's table and strobe confirms.
Mode2 | Double direction | BCD input signals select the current message from the BCD's table but input3 resets print direction if strobe is configured by **state** and strobe confirms selected message and inverts print direction.

#### Print direction
Value | Name | Description
-|-|-
LR | Left to right | Print direction left to right.
RL | Right to left | Print direction right to left.

#### Delay Units:  **TO REVIEW**
Value | Name | Description
-|-|-
mm | milimeters | Print delay in milimeters.
ms | miliseconds | Print delay in miliseconds.

#### Inputs configuration:
Value | Name | Description
-|-|-
Edge | Edge | Input signal by edge.
State | State | Input signal by state.

#### Output types:
Value | Name | Description
-|-|-
State | State | Output remains in the state set until the state changes.
OnPulse | OnPulse | State changes to ON, waits an specified time and returns to OFF.
OffPulse | OffPulse | State changes to OFF, wains an specified time and returns to ON.
MaxOn | MaxOn | Same than _state_ but output remains in ON a maximum time and returns to OFF.
MaxOff | MaxOff | Same than _state_ but output remains in OFF a maximum time and returns to ON.

#### Date codes:
Value | Name | Description
-|-|-
Shift | Shift | Code depending on each shift _[DC:S]_
Minutes | Minutes | Codes depending on the minute _[DC:m]_
Hours | Hours | Codes depending on the hour of the day _[DC:H]_ 
Week_Days | Days of a week | Codes depending on the week's day _[DC:ddd]_ 
Month_Days | Days of a month | Codes depending on day's number of the month _[DC:dd]_ 
Months | Months | Codes depending on the month _[DC:M]_.
Julian_Days | Julian days | Codes depending on the Julian day _[DC:J]_ 
Weeks_Of_Year | Week number | Codes depending on the week's number of the year _[DC:w]_
Years | Years | Codes depending on the year  _[DC:Y]_ 

#### Nozzle column:
Value | Name | Description
-|-|-
COL_A | Column A | To select column A of the nozzle plate of the printhead.
COL_B |Column B | To select column B of the nozzle plate of the printhead.
COL_BOTH | Both columns | Both columns, A and B, are selected to print when print resolution 600v dpi.

#### Shot mode:
Value | Name | Description
-|-|-
SingleShot | Single shot | One shot per trigger.
MultiShotRelative | Relative multi shot | More than one shot per trigger: first delay and delay between shots.
MultiShotAbsolute |Absolute multi shot | More than one shot per trigger. Every delay is an absolute time since trigger's signal.  **Not implemented yet** 

---
## Files management
The protocol has the capability to send and receive files inside the payload using the following commands. 

In order to reference files through this protocol all files must be defined with two strings *logical drive* (`<UNIT name="//" />`) and *logical path* (`<FILE path="//messages/CQ.nisx" />` or `<FILE Path="USB//messages/CQ.nisx"/>`).

The protocol is **not** the responsible of how drives and files are mapped. The logical path mapping depends on the code implementation.

**idTIJ project implementation**

In idTIJ project the drives contains subfolders in order to allocate and organize all different type of files.

__drive //__

- messages
- fonts
- images

**TIJ project current used drives implementation**

Logical drive|Description|Mount point
-------------|-----------|-------------
//| Internal storage | /home/root
USB//| External storage | /home/root/usb

---
### Get files list
This command request for a list of files with a desired extension. In order to define what kind of files are requested the extension is the **"type"** attribute. This attribute is a comma separated string (`type=".jpg,.png"`).

The idTIJ project currently support the file extensions defined in the table below.

Type of file|Supported extension
------------|-------------------
Messages | .nisx
Fonts| .ttf
Images | .bmp, .jpg, .png

**Request**
```xml
<WIND id="[Command ID]">
    <GETFILESLIST type="[requested type]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <GETFILESLIST type="[requested type]">
        <UNIT Name="[Logical Active Unit Name]"/> <!-- one item for each active drive -->
        <FILE Path="[Logical File Path]"/> <!-- one item for each file-->
    </GETFILESLIST>
</WIND>
```
---
### Copy file

**Request**
```xml
<WIND id="[Command ID]">
    <COPYFILE SourceFilePath="[Logical File Path]" TargetFilePath="[Logical File Path]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <COPYFILE/>
</WIND>
```
---

### Move file

**Request**
```xml
<WIND id="[Command ID]">
    <MOVEFILE SourceFilePath="[Logical File Path]" TargetFilePath="[Logical File Path]"/>
</WIND> 
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <MOVEFILE/>
</WIND>
```
---
### Delete file

**Request**
```xml
<WIND id="[Command ID]">
    <DELETEFILE FilePath="[Logical File Path]"/>
</WIND> 
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <DELETEFILE/>
</WIND> 
```
---
### Get file
Normally, content file is getting coded in base64 but also it allows to get content file without coding, in raw.
It depends on the bool param _Raw_. If Raw is true, it gets the content file in raw within **CDATA** section at the response.

**Request**
```xml
<WIND id="[Command ID]">
    <GETFILE FilePath="[Logical File Path]" Raw="[Bool]">
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <GETFILE FilePath="[Logical File Path]">
        <CONTENT>[File Content]</CONTENT>
    </GETFILE>
</WIND> 
```
---
### Set file
Normally, content file is setting coded in base64 but also it allows to set content file without coding, in raw.
It depends on the bool param **_Raw_**. If Raw is true, it needs to set the content file in raw within **CDATA** section at the Request.
**Request**

```xml
<WIND id="[Command ID]">
    <SETFILE FilePath="[Logical File Path]" Type="[Message Type]" Raw="[bool]">
        <CONTENT>[File Content]</CONTENT>
    </SETFILE>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <SETFILE FilePath="[Logical File Path]"/>
</WIND>
```
---
### Get Message value

**Request**
```xml
<WIND id="[Command ID]">
    <GETMESSAGEVALUES FilePath="[Logical File Path]"/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <GETMESSAGEVALUES FilePath="[Logical File Path]">
        <UI_FIELD Name="[User Field Name]" Value="[User Field Value]"/>
    </GETMESSAGEVALUES>
</WIND>
```
---
### Set Message value

**Request**
```xml
<WIND id="[Command ID]">
    <SETMESSAGEVALUES FilePath="[Logical File Path]">
        <UI_FIELD Name="[User Field Name]" Value="[User Field Value]"/>
    </SETMESSAGEVALUES>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <SETMESSAGEVALUES/>
</WIND>
```
---
### Get message data source

This command allows the client to get all fields with variable _datasource_ of a requested message.

In the response, the client can find a list of different tags depending on _datasource_ type:

FieldType | Description
-|-
"" | All types
"user"|User fields 
"date"|Date & time fields
"counter"|Counters fields

**Request**
```xml
<WIND id="[Command ID]">
    <GETMESSAGEDATASOURCE FilePath="[Logical File Path]" FieldType="" />
</WIND>
```
**Response**

```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <GETMESSAGEDATASOURCE FilePath="[Logical File Path]" FieldType="">
        <DATETIME Name="[User Field Name]" Format="[date and time format]" DayOffset="[Offset Days]" MonthOffset="[Offset Months]" YearsOffset="[Offset Years]" SoD="[Hour - Start of day]"/>
        <COUNTER  Name="[User Field Name]" LeadingZeros="Leading zeros" Min="[Minimum value]" Max="[Maximum value]" Repeat="[Repeat counter]" Step="[Counter step]"/>
        <UI_FIELD Name="[User Field Name]" Value="[User Field Value]"/>
    </GETMESSAGEDATASOURCE>
</WIND>
```
---
### Set message data source
Like the previous command, this command acts over the message variable fields but this allows the client to modify part or all the fields with variable _datasource_.

**Request**

```xml
<WIND id="[Command ID]">
    <SETMESSAGEDATASOURCE FilePath="[Logical File Path]" FieldType="">
        <DATETIME Name="[User Field Name]" Format="[date and time format]" DayOffset="[Offset Days]" MonthOffset="[Offset Months]" YearsOffset="[Offset Years]" SoD="[Hour - Start of day]"/>
        <COUNTER  Name="[User Field Name]" LeadingZeros="Leading zeros" Min="[Minimum value]" Max="[Maximum value]" Repeat="[Repeat counter]" Step="[Counter step]"/>
        <UI_FIELD Name="[User Field Name]" Value="[User Field Value]"/>
    </SETMESSAGEDATASOURCE>
</WIND>
```
**Response**

```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <SETMESSAGEDATASOURCE />
</WIND>
```
---

## Status and configuration

### Get Status
Get Status command return all available status parameters and information:

- Date and Time
- Software versions.
- Printers (Boards).
    - Printer status (Board).
        - Board type _(SM200 by default)_.
        - Printing status.
        - Printing enabled.
        - Current message.
        - BCD mode and status.
        - Counters.
        - Errors.
        - IO status.
        - Properties map.

**Request**
```xml
<WIND id="[Command ID]">
    <STATUS/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <STATUS>
        <DATETIME>[Date Time]</DATETIME>
        <VERSIONS>
            <CONTROLLER>[Firmware controller]</CONTROLLER>
            <FPGA>[Firmware FPGA]</FPGA>
            <API>[API Version]</API>
        </VERSIONS>
        <BOARDS>
            <BOARD id="[Board Id]">
                <TYPE>[Board Type]</TYPE>
                <PRINTING>[Printing Status]</PRINTING>
                <ENABLED>[Printhead Enabled]</ENABLED>
                <CURRENT_MESSAGE FilePath="[Logical File Path]"/>
                <BCD_MODE>[BcdMode value]</BCD_MODE>
                <BCD_STATUS>[BCD Value]</BCD_STATUS>
                <COUNTERS>
                    <COUNTER id="[Counter Id]" Value="[Counter Value]"/>
                <COUNTERS/>
                <ERRORS>
                    <ERROR Type="[Printer Error Type]" Priority="[Printer Error Priority]" ErrorCode="[Printer Error Code]"/>
                </ERRORS>
                <INPUTS>
                    <INPUT id="[Input Id]" Descriptor="[Input Descriptor]" Value="[Input Value]"/>
                </INPUTS>
                <OUTPUTS>
                    <OUTPUT id="[Output Id]" Descriptor="[Output Descriptor]" Value="[Output Value]"/>
                <OUTPUTS>
                <PROPERTIES>
                    <PROPERTY Key="[Property Key]" Value="[Property Values]"/>
                </PROPERTIES>
            </BOARD>
        </BOARDS>
    </STATUS>
</WIND>
```
---
### Get IO Status
Specific command to get only *Inputs* and *Outputs* status.
**Request**
```xml
<WIND id="[Command ID]">
    <IOSTATUS/>
</WIND>
```
**Response**
```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <IOSTATUS>
        <BOARDS>
            <BOARD id="[Board Id]">
                <ERROR Type="[Printer Error Type]" Priority="[Printer Error Priority]" ErrorCode="[Printer Error Code]"/>
            </BOARD>
        </BOARDS>
    </IOSTATUS>
</WIND>
```
---
### Get Errors
Specific command to get *errors* list.  See [error codes](#error-codes) for further information.
**Request**

```xml
<WIND id="[Command ID]">
    <GETERRORS/>
</WIND>
```
**Response**

```xml
<WIND id="[Command ID]">
    <ERROR Code="[Error Code]"/>
    <GETERRORS>
        <BOARDS>
            <BOARD id="[Board Id]">
                <INPUTS>
                    <INPUT id="[Input Id]" Descriptor="[Input Descriptor]" Value="[Input Value]"/>
                </INPUTS>
                <OUTPUTS>
                    <OUTPUT id="[Output Id]" Descriptor="[Output Descriptor]" Value="[Output Value]"/>
                <OUTPUTS>
            </BOARD>
        </BOARDS>
    </GETERRORS>
</WIND>
```
---

## Error codes

The response frames always contain and error code. The currently implemented errors in **idTij** Project are defined below:

1. [[01 - 11] File operation errors](#files-errors)
1. [[12 - 23] Params related errors](#params-related-errors)
1. [[24 - 26] Generic errors](#generic-errors)
1. [[27 - 37] NeoTIJ related errors](#neotij-related-errors)

### Files errors
Value | Error code | Description
------|------------|------------
01 | FileNotFound | The specified file doesn't exist
02 | FileAlreadyExist | In move or copy operations, if the file already exist... 
03 | FileCopyFail | Copy file operation error 
04 | FileDeleteFail | Delete file operation error 
05 | FileMoveFail | Move operation error 
06 | FileMoveIncomplete | Move operation has copied the source to target, but not delete the source 
07 | FileReadCanNot | Can't read the file 
08 | FileWriteCanNot | Can't write the file 
09 | FileWriteIncomplete | The write on the file is not complete 
10 | FileUserDataNotFound | The name of a user-name-value is not found 
11 | FileInUse | The file is currenty in use 

### Params related errors
Value | Error code | Description
------|------------|------------
12 | ParamBoardIdNotFound | The Board Id specified by the command was not found 
13 | ParamCounterIdNotFound | The Counter Id specified by the command was not found 
14 | ParamCounterValueRejected | The device has rejected the counter modification
15 | ParamOutputIdNotFound | The output id specified by the command was not found
16 | ParamCantSetMsgInBcdMode | Is not posible set a manual current message if the board is in Bcd mode
17 | ParamBoardIsEnabled	| The command requires a enabled board 
18 | ParamBoardIsNotEnabled | The command requires a disabled board 
19 | ParamCannotChangeAdapter | The server can not change the adapter settings
20 | ParamInvalidIpAddress | Invalid IP                                                   
21 | ParamInvalidMaskAddress | Invalid Netmask 
22 | ParamInvalidGatewayAddress | Invalid Gateway 
23 | ParamInvalidPropCount | The client can not change the number of properties

### Generic errors
Value | Error code | Description
------|------------|------------
24 | GenUnexpectedTag | generic xml error
25 | GenNotImplemented | informs that operation is not implemented on the server
26 | GenLockTimeout | Lock data fail

### NeoTIJ related issues
| Value | Issue Type | Display Priority | Error code                      | Description                                                  |
| ----- | ---------- | ---------------- | ------------------------------- | ------------------------------------------------------------ |
| 27    | Error      | 1                | PcaNotdetected                  | "PCA.NOTDETECTED"		    "No connection with PCA"        |
| 28    | Error      | 2                | PhOvertemp                      | "PH.OVERTEMP"			    "Printhead over temperature"    |
| 29    | Error      | 20               | GenOverspeed                    | "GEN.OVERSPEED"			"Overspeed"                       |
| 30    | Error      | 30               | MsgFormaterror                  | "MSG.FORMATERROR"		    "NISX format error"             |
| 31    | Error      | 31               | MsgNoexist                      | "MSG.NOEXIST"			    "Message doesn't exist"         |
| 32    | Error      | 5                | PhNocartridge                   | "PH.NOCARTRIDGE"			"No cartridge loaded"            |
| 33    | Error      | 4                | SmcInvalid                      | "SMC.INVALID"			    "No valid smartcard on cartridge. Unreadable" |
| 34    | Error      | 3                | PhGenfault                      | "PH.GENFAULT"			    "Cartridge fault - not valid"   |
| 35    | Error      | 11               | SmcCartridgeEmpty               | "SMC.CARTRIDGE_EMPTY"	    "Cartridge empty"               |
| 36    | Warning    | 1                | SmcCartridgeOutofdate           | "SMC.CARTRIDGE_OUTOFDATE"  "Cartridge out of expiration date" |
| 37    | Warning    | 2                | SmcCartridgeNearend             | "SMC.CARTRIDGE_NEAREND"	"Cartridge near empty"            |
| 38    | Error      | 6                | SmcInvalidCartridgeManufacturer | "SMC.UNRECOGNIZED_DATA"	"Data on cartridge not valid"     |
| 39    | Info       | 1                | PhInitializingCartridge         | "PH.INITIALIZING_CARTRIDGE"  "Initializing cartridge"        |
| 40    | Error      | 7                | SmcHostNotDetected              | "SMC.HOST_SMARTCARD" "Internal host smartcard not response"  |
