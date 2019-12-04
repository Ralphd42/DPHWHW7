CC = gcc
CFLAGS =  
LDFLAGS =
OBJFILES = picalc.o timing.o
TARGET = part_1_serial.out
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
