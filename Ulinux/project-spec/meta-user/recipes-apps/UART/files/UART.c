#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>


#define UART_CHANNEL_BASE_ADDR 0x42c00000
#define CHANNEL_0_BASE_ADDR    0x42c00000
#define CHANNEL_1_BASE_ADDR    0x42c00004
#define CHANNEL_2_BASE_ADDR    0x42c00008
#define CHANNEL_3_BASE_ADDR    0x42c0000c



// Memory mapped keyhole register to pwm decoder
uint8_t RX;
uint8_t TX;

// Channel registers
uint8_t *channel_registers;

int main()
{
	int mem_fd = open("/dev/mem", O_RDWR|O_SYNC|O_CLOEXEC);
	if (mem_fd == -1) 
	{
		printf("Unable to open /dev/mem");
	}

	// The PIO hardware cores are setup as read only (Not a problem fro RCInput).
	channel_registers = (uint16_t *) mmap(NULL, 0x40, PROT_READ, MAP_SHARED, mem_fd, UART_CHANNEL_BASE_ADDR);

	close(mem_fd);

	RX = channel_registers[0];
	TX = channel_registers[16];

	channel_registers[16] = 'x';
	
}
