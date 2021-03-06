EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP32-footprints-Shem-Lib
LIBS:switches
LIBS:silabs
LIBS:mcp73831
LIBS:leds
LIBS:ws2812b
LIBS:usb_otg
LIBS:mma8452q
LIBS:apds-9960
LIBS:BA33DD0WHFP
LIBS:ESP32_Clock-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L APDS-9960 U33
U 1 1 5AABE8C9
P 4200 2200
F 0 "U33" H 3950 2400 60  0000 C CNN
F 1 "APDS-9960" H 4450 2400 60  0000 C CNN
F 2 "ADPS-9960:ADPS-9960" H 4200 2200 60  0001 C CNN
F 3 "" H 4200 2200 60  0001 C CNN
	1    4200 2200
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x05 J9
U 1 1 5AACE850
P 10300 2200
F 0 "J9" H 10300 2500 50  0000 C CNN
F 1 "Gesture" H 10300 1900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 10300 2200 50  0001 C CNN
F 3 "" H 10300 2200 50  0001 C CNN
	1    10300 2200
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 5AACE8B3
P 9900 1650
F 0 "R12" V 9980 1650 50  0000 C CNN
F 1 "4k7" V 9900 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9830 1650 50  0001 C CNN
F 3 "" H 9900 1650 50  0001 C CNN
	1    9900 1650
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 5AACE8DD
P 9700 1650
F 0 "R11" V 9780 1650 50  0000 C CNN
F 1 "4k7" V 9700 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9630 1650 50  0001 C CNN
F 3 "" H 9700 1650 50  0001 C CNN
	1    9700 1650
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR041
U 1 1 5AACEA17
P 9900 1300
F 0 "#PWR041" H 9900 1150 50  0001 C CNN
F 1 "+3V3" H 9900 1440 50  0000 C CNN
F 2 "" H 9900 1300 50  0001 C CNN
F 3 "" H 9900 1300 50  0001 C CNN
	1    9900 1300
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR042
U 1 1 5AACEAB3
P 8600 2000
F 0 "#PWR042" H 8600 1850 50  0001 C CNN
F 1 "+3V3" H 8600 2140 50  0000 C CNN
F 2 "" H 8600 2000 50  0001 C CNN
F 3 "" H 8600 2000 50  0001 C CNN
	1    8600 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR043
U 1 1 5AACEAE7
P 8600 2100
F 0 "#PWR043" H 8600 1850 50  0001 C CNN
F 1 "GND" H 8600 1950 50  0000 C CNN
F 2 "" H 8600 2100 50  0001 C CNN
F 3 "" H 8600 2100 50  0001 C CNN
	1    8600 2100
	1    0    0    -1  
$EndComp
Text HLabel 9350 2200 0    60   Input ~ 0
INT0
Text HLabel 9350 2300 0    60   Input ~ 0
SDA0
Text HLabel 9350 2400 0    60   Input ~ 0
SCL0
Wire Wire Line
	8600 2000 10100 2000
Wire Wire Line
	8600 2100 10100 2100
Wire Wire Line
	9350 2200 10100 2200
Wire Wire Line
	9350 2300 10100 2300
Wire Wire Line
	9350 2400 10100 2400
Wire Wire Line
	9700 1800 9700 2300
Connection ~ 9700 2300
Wire Wire Line
	9900 1800 9900 2400
Connection ~ 9900 2400
Wire Wire Line
	9900 1500 9900 1300
Wire Wire Line
	9700 1500 9700 1400
Wire Wire Line
	9500 1400 9900 1400
Connection ~ 9900 1400
Text HLabel 3300 2600 0    60   Input ~ 0
SDA0
Text HLabel 3300 2700 0    60   Input ~ 0
INT0
Text HLabel 3300 2800 0    60   Input ~ 0
SCL0
Wire Wire Line
	3700 2300 3600 2300
Wire Wire Line
	3600 2300 3600 2400
Wire Wire Line
	3600 2400 3700 2400
$Comp
L R R10
U 1 1 5AAD15B5
P 9500 1650
F 0 "R10" V 9580 1650 50  0000 C CNN
F 1 "10k" V 9500 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9430 1650 50  0001 C CNN
F 3 "" H 9500 1650 50  0001 C CNN
	1    9500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 1800 9500 2200
Connection ~ 9500 2200
Wire Wire Line
	9500 1500 9500 1400
Connection ~ 9700 1400
$Comp
L R R13
U 1 1 5AAD1932
P 5750 1800
F 0 "R13" V 5830 1800 50  0000 C CNN
F 1 "22R" V 5750 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5680 1800 50  0001 C CNN
F 3 "" H 5750 1800 50  0001 C CNN
	1    5750 1800
	0    1    1    0   
$EndComp
$Comp
L CP1 C39
U 1 1 5AAD1C92
P 6100 1950
F 0 "C39" H 6125 2050 50  0000 L CNN
F 1 "47uF" H 6125 1850 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-A_EIA-3216-18_Hand" H 6100 1950 50  0001 C CNN
F 3 "" H 6100 1950 50  0001 C CNN
	1    6100 1950
	1    0    0    -1  
$EndComp
$Comp
L CP1 C38
U 1 1 5AAD1D24
P 5400 1950
F 0 "C38" H 5425 2050 50  0000 L CNN
F 1 "1uF" H 5425 1850 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-R_EIA-2012-12_Hand" H 5400 1950 50  0001 C CNN
F 3 "" H 5400 1950 50  0001 C CNN
	1    5400 1950
	1    0    0    -1  
$EndComp
$Comp
L CP1 C40
U 1 1 5AAD1D7A
P 6400 1950
F 0 "C40" H 6425 2050 50  0000 L CNN
F 1 "1uF" H 6425 1850 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-R_EIA-2012-12_Hand" H 6400 1950 50  0001 C CNN
F 3 "" H 6400 1950 50  0001 C CNN
	1    6400 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2600 3400 2600
Wire Wire Line
	3400 2600 3400 2100
Wire Wire Line
	3400 2100 3700 2100
Wire Wire Line
	3300 2700 3500 2700
Wire Wire Line
	3500 2700 3500 2200
Wire Wire Line
	3500 2200 3700 2200
Wire Wire Line
	3300 2800 5000 2800
Wire Wire Line
	5000 2800 5000 2200
Wire Wire Line
	5000 2200 4700 2200
Wire Wire Line
	5900 1800 6700 1800
Connection ~ 6100 1800
Wire Wire Line
	5000 1800 5600 1800
Wire Wire Line
	5000 1800 5000 2100
Wire Wire Line
	5000 2100 4700 2100
Connection ~ 5400 1800
Wire Wire Line
	5950 1800 5950 2400
Wire Wire Line
	5950 2400 4700 2400
Connection ~ 5950 1800
Wire Wire Line
	4700 2300 6700 2300
Wire Wire Line
	6400 2300 6400 2100
Wire Wire Line
	6100 2100 6100 2300
Connection ~ 6100 2300
Wire Wire Line
	5400 2100 5400 2300
Connection ~ 5400 2300
$Comp
L +3V3 #PWR044
U 1 1 5AAD236C
P 6700 1800
F 0 "#PWR044" H 6700 1650 50  0001 C CNN
F 1 "+3V3" H 6700 1940 50  0000 C CNN
F 2 "" H 6700 1800 50  0001 C CNN
F 3 "" H 6700 1800 50  0001 C CNN
	1    6700 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR045
U 1 1 5AAD23C4
P 6700 2300
F 0 "#PWR045" H 6700 2050 50  0001 C CNN
F 1 "GND" H 6700 2150 50  0000 C CNN
F 2 "" H 6700 2300 50  0001 C CNN
F 3 "" H 6700 2300 50  0001 C CNN
	1    6700 2300
	1    0    0    -1  
$EndComp
Connection ~ 6400 1800
Connection ~ 6400 2300
$Comp
L PWR_FLAG #FLG046
U 1 1 5AAD2D33
P 5100 1700
F 0 "#FLG046" H 5100 1775 50  0001 C CNN
F 1 "PWR_FLAG" H 5100 1850 50  0000 C CNN
F 2 "" H 5100 1700 50  0001 C CNN
F 3 "" H 5100 1700 50  0001 C CNN
	1    5100 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1700 5100 1800
Connection ~ 5100 1800
$Comp
L Conn_01x04 J10
U 1 1 5AAD32A4
P 10300 3000
F 0 "J10" H 10300 3200 50  0000 C CNN
F 1 "OLED" H 10300 2700 50  0000 C CNN
F 2 "128x32_OLED:128x32_OLED" H 10300 3000 50  0001 C CNN
F 3 "" H 10300 3000 50  0001 C CNN
	1    10300 3000
	1    0    0    -1  
$EndComp
Text HLabel 9350 2900 0    60   Input ~ 0
SDA0
Text HLabel 9350 3000 0    60   Input ~ 0
SCL0
$Comp
L GND #PWR047
U 1 1 5AAD33E7
P 8600 3200
F 0 "#PWR047" H 8600 2950 50  0001 C CNN
F 1 "GND" H 8600 3050 50  0000 C CNN
F 2 "" H 8600 3200 50  0001 C CNN
F 3 "" H 8600 3200 50  0001 C CNN
	1    8600 3200
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR048
U 1 1 5AAD3443
P 8600 3100
F 0 "#PWR048" H 8600 2950 50  0001 C CNN
F 1 "+3V3" H 8600 3240 50  0000 C CNN
F 2 "" H 8600 3100 50  0001 C CNN
F 3 "" H 8600 3100 50  0001 C CNN
	1    8600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2900 10100 2900
Wire Wire Line
	9350 3000 10100 3000
Wire Wire Line
	8600 3100 10100 3100
Wire Wire Line
	8600 3200 10100 3200
Text HLabel 9350 4700 0    60   Input ~ 0
SCL1
Text HLabel 9350 4800 0    60   Input ~ 0
SDA1
Text HLabel 9350 5000 0    60   Input ~ 0
INT1
Text HLabel 9350 5100 0    60   Input ~ 0
INT2
$Comp
L GND #PWR049
U 1 1 5B0D8F98
P 8600 4650
F 0 "#PWR049" H 8600 4400 50  0001 C CNN
F 1 "GND" H 8600 4500 50  0000 C CNN
F 2 "" H 8600 4650 50  0001 C CNN
F 3 "" H 8600 4650 50  0001 C CNN
	1    8600 4650
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR050
U 1 1 5B0D8FC2
P 8600 4500
F 0 "#PWR050" H 8600 4350 50  0001 C CNN
F 1 "+3V3" H 8600 4640 50  0000 C CNN
F 2 "" H 8600 4500 50  0001 C CNN
F 3 "" H 8600 4500 50  0001 C CNN
	1    8600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4500 10100 4500
Wire Wire Line
	8600 4650 8600 4600
Wire Wire Line
	8600 4600 10100 4600
Wire Wire Line
	9350 4700 10100 4700
Wire Wire Line
	9350 4800 10100 4800
Wire Wire Line
	9350 5000 10100 5000
$Comp
L R R14
U 1 1 5B0D9185
P 9500 4150
F 0 "R14" V 9580 4150 50  0000 C CNN
F 1 "4k7" V 9500 4150 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9430 4150 50  0001 C CNN
F 3 "" H 9500 4150 50  0001 C CNN
	1    9500 4150
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 5B0D91C4
P 9700 4150
F 0 "R15" V 9780 4150 50  0000 C CNN
F 1 "4k7" V 9700 4150 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9630 4150 50  0001 C CNN
F 3 "" H 9700 4150 50  0001 C CNN
	1    9700 4150
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR051
U 1 1 5B0D91F4
P 9700 3800
F 0 "#PWR051" H 9700 3650 50  0001 C CNN
F 1 "+3V3" H 9700 3940 50  0000 C CNN
F 2 "" H 9700 3800 50  0001 C CNN
F 3 "" H 9700 3800 50  0001 C CNN
	1    9700 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4300 9500 4700
Connection ~ 9500 4700
Wire Wire Line
	9700 4300 9700 4800
Connection ~ 9700 4800
Wire Wire Line
	9700 3800 9700 4000
Wire Wire Line
	9500 4000 9500 3900
Wire Wire Line
	9500 3900 9700 3900
Connection ~ 9700 3900
$Comp
L Conn_01x08 J11
U 1 1 5B0ED26B
P 10300 4700
F 0 "J11" H 10300 5100 50  0000 C CNN
F 1 "MMA8542Q Accelerometer" H 10300 4200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 10300 4700 50  0001 C CNN
F 3 "" H 10300 4700 50  0001 C CNN
	1    10300 4700
	1    0    0    -1  
$EndComp
NoConn ~ 10100 4400
NoConn ~ 10100 4900
Wire Wire Line
	9350 5100 10100 5100
$EndSCHEMATC
