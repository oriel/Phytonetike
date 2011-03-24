#################################################
# This file is machine-generated - Do NOT edit! #
#################################################

CC = avr-gcc $(CPP_FLAGS)
LD = avr-gcc $(LD_FLAGS)
AR = avr-ar $(AR_FLAGS)
OBJCP = avr-objcopy
SIZE = avr-size -A --mcu=$(MCU)
AVRDUDE = /opt/arduino-0017/hardware/tools/avrdude

LIBRARIES = default.a
OBJECTS = src/main.o
INCLUDES = -I"/usr/lib/avr/include/avr" -I"./include" -I"src" -I"lib/default"
DEFINES = -DF_CPU=$(F_CPU)L -DARDUINO=18

CPP_FLAGS = -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) $(DEFINES) $(INCLUDES)
LD_FLAGS = -Os -Wl,--gc-sections -mmcu=$(MCU)
AR_FLAGS = rcs

USB=0
PORT = /dev/ttyUSB$(USB)
MCU = atmega328p
F_CPU = 16000000
FORMAT = ihex
UPLOAD_RATE = 57600
MAX_SIZE = 30720

OUTPUT = Phytonetike

all: $(LIBRARIES) $(OUTPUT).hex

default.a: lib/default/wiring_digital.o lib/default/Print.o lib/default/WMath.o lib/default/main.o lib/default/wiring_analog.o lib/default/WInterrupts.o lib/default/wiring_shift.o lib/default/wiring.o lib/default/wiring_pulse.o lib/default/pins_arduino.o lib/default/Tone.o lib/default/HardwareSerial.o
	$(AR) default.a lib/default/wiring_digital.o
	$(AR) default.a lib/default/Print.o
	$(AR) default.a lib/default/WMath.o
	$(AR) default.a lib/default/main.o
	$(AR) default.a lib/default/wiring_analog.o
	$(AR) default.a lib/default/WInterrupts.o
	$(AR) default.a lib/default/wiring_shift.o
	$(AR) default.a lib/default/wiring.o
	$(AR) default.a lib/default/wiring_pulse.o
	$(AR) default.a lib/default/pins_arduino.o
	$(AR) default.a lib/default/Tone.o
	$(AR) default.a lib/default/HardwareSerial.o

lib/default/wiring_digital.o: lib/default/wiring_digital.c
	$(CC) -c lib/default/wiring_digital.c -o lib/default/wiring_digital.o

lib/default/Print.o: lib/default/Print.cpp
	$(CC) -c lib/default/Print.cpp -o lib/default/Print.o

lib/default/WMath.o: lib/default/WMath.cpp
	$(CC) -c lib/default/WMath.cpp -o lib/default/WMath.o

lib/default/main.o: lib/default/main.cpp
	$(CC) -c lib/default/main.cpp -o lib/default/main.o

lib/default/wiring_analog.o: lib/default/wiring_analog.c
	$(CC) -c lib/default/wiring_analog.c -o lib/default/wiring_analog.o

lib/default/WInterrupts.o: lib/default/WInterrupts.c
	$(CC) -c lib/default/WInterrupts.c -o lib/default/WInterrupts.o

lib/default/wiring_shift.o: lib/default/wiring_shift.c
	$(CC) -c lib/default/wiring_shift.c -o lib/default/wiring_shift.o

lib/default/wiring.o: lib/default/wiring.c
	$(CC) -c lib/default/wiring.c -o lib/default/wiring.o

lib/default/wiring_pulse.o: lib/default/wiring_pulse.c
	$(CC) -c lib/default/wiring_pulse.c -o lib/default/wiring_pulse.o

lib/default/pins_arduino.o: lib/default/pins_arduino.c
	$(CC) -c lib/default/pins_arduino.c -o lib/default/pins_arduino.o

lib/default/Tone.o: lib/default/Tone.cpp
	$(CC) -c lib/default/Tone.cpp -o lib/default/Tone.o

lib/default/HardwareSerial.o: lib/default/HardwareSerial.cpp
	$(CC) -c lib/default/HardwareSerial.cpp -o lib/default/HardwareSerial.o

src/main.o: src/main.cpp
	$(CC) -c src/main.cpp -o src/main.o

$(OUTPUT).elf: $(OBJECTS) $(LIBRARIES)
	$(LD) $(OBJECTS) $(LIBRARIES) -lm -o $(OUTPUT).elf

$(OUTPUT).hex: $(OUTPUT).elf
	$(OBJCP) -O ihex -R .eeprom $(OUTPUT).elf $(OUTPUT).hex
	$(SIZE) $(OUTPUT).hex | scripts/size.rb $(MAX_SIZE) "$(OUTPUT).hex"
  
.PHONY: upload clean

upload: all
	stty -F $(PORT) hupcl
	$(AVRDUDE) -C/opt/arduino-0017/hardware/tools/avrdude.conf -p$(MCU) -cstk500v1 -P$(PORT) -b$(UPLOAD_RATE) -D -Uflash:w:$(OUTPUT).hex:i 

clean:
	@rm -f $(LIBRARIES) $(OUTPUT).elf $(OUTPUT).hex $(shell find . -follow -name "*.o")
  
Makefile: scripts/make.rb $(shell find src -follow -not -type f -newer Makefile)
	@scripts/make.rb
