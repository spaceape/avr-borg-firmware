
objects=\
	mmio.o uart.o debug.o channel.o device.o core.o

depends=$(objects:.o=.d)

all: borg-$(SYSTEM)-firmware-$(VERSION).bin

%.o: %.cpp makefile
	$(CC) $(SYSFLAGS) -MMD -MP $(CCFLAGS) $(INCLUDES) $(DEFS) -c $< -o $@

-include $(depends)

borg-$(SYSTEM)-firmware-$(VERSION).bin: $(objects)
	$(CC) $(SYSFLAGS) $(LDFLAGS) $(objects) $(system_objects) -o $@
	avr-size -A $@

clean:
	rm -fv $(depends)
	rm -fv $(objects)
	rm -fv borg-$(SYSTEM)-firmware-$(VERSION).bin

.PHONY: all clean
