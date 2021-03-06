#include <stm32f4_discovery.h>
#include <os.h>

void proc( unsigned &led, uint32_t timePoint )
{
	for (;;)
	{
		ThisTask::sleepUntil(timePoint += SEC/2);
		led++;
	}
}

auto led = Led();
auto grn = GreenLed();

auto t1 = startTask(0, [] { proc(led[0], SEC/8*0); });
auto t2 = startTask(0, [] { proc(led[1], SEC/8*1); });
auto t3 = startTask(0, [] { proc(led[2], SEC/8*2); });
auto t4 = startTask(0, [] { proc(led[3], SEC/8*3); });
auto t5 = startTask(0, [] { proc(grn,    SEC/8*4); });

int main()
{
	ThisTask::stop();
}
