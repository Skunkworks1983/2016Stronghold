#include "SkunkEncoder.h"
#include "pthread.h"
#include <Synchronized.h>

struct Data {
	ReentrantSemaphore semaphore;
	DigitalInput * dataSource;
	DigitalInput * signSource;
};


static void tInteruptSkunk(uint32_t interruptAssertedMask, void *param) {
	Data * data = (Data *) param;
	data->semaphore.take();
	data->signSource->Get() ? current_position++ : current_position--;

}

SkunkEncoder::SkunkEncoder(int dataPort, int signPort) {
	current_position = 0;
	dataSource = new DigitalInput(dataPort);
	signSource = new DigitalInput(signPort);
	dataSource->m_channel;
	Data * data = new Data();
	pthread_t thread;


	dataSource->RequestInterrupts(&tInteruptSkunk, data);
}

void SkunkEncoder::update(){
	while(true){
		dataSource->WaitForInterrupt(-1, true);
		signSource->Get() ? current_position++ : current_position--;
	}
}


SkunkEncoder::~SkunkEncoder() {

}

int SkunkEncoder::GetPosition() {
	return current_position;
}
