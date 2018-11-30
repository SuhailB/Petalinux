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


#define GPIO_CHANNEL_BASE_ADDR 0x41210000
#define CHANNEL_0_BASE_ADDR    0x41210000




// Memory mapped keyhole register to pwm decoder
uint8_t LED;
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
	channel_registers = (uint8_t *) mmap(NULL, 0x40, PROT_READ, MAP_SHARED, mem_fd, GPIO_CHANNEL_BASE_ADDR);

	close(mem_fd);

    printf("Light up LEDs ...");
	while(1)
    {
        channel_registers[0] = 0xf5;
    }
	
}
