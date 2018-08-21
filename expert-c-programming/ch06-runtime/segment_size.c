#include <stdio.h>

/*           Executable and Segment sizes
 *
 *  1. Basic Hello World!
 *      - executable size : 16616 bytes
 *      - segment sizes
 *          - text : 1475
 *          - data : 584
 *          - bss  : 8
 *          - dec  : 2067   (text + data + bss)
 *          - hex  : 813    (text + data + bss in hexa)
 *
 *  2. With an additional global array of 1000 integers
 *      - executable size : 16640 bytes (+24)
 *      - segment sizes
 *          - text : 1475
 *          - data : 584
 *          - bss  : 4032   (+4024)
 *          - dec  : 6091   (+4024)
 *          - hex  : 17cb
 *
 *  3. With an additional *initialized* global array of 1000 integers
 *      - executable size : 20656 bytes (+4016)
 *      - segment sizes
 *          - text : 1475
 *          - data : 4600   (+4016)
 *          - bss  : 8      (-4024)
 *          - dec  : 6083   (-8)
 *          - hex  : 17c3
 *
 *  4. With an initialized array of 1000 integers *inside main*
 *      - executable size : 16616 bytes (+0, same as basic)
 *      - segment sizes
 *          - text : 1523   (+48)
 *          - data : 584
 *          - bss  : 8
 *          - dec  : 2115   (+48)
 *          - hex  : 843    (+0x30)
 *
 *  5. With the debugging flag `-g`
 *      - executable size : 19224 (+2608)
 *      - segment sizes stay the same
 *     With the optimization flag `-O3`
 *      - executable size stay the same
 *      - segment sizes
 *          - text : 1483   (-20)
 *          - data : 584
 *          - bss  : 8
 *          - dec  : 2075   (-20)
 *          - hex  : 81b    (-0x28)
 */


int main(void)
{
	int ar[1000] = {1};
	printf("Hello World!\n");
	return 0;
}
