#include <DigitalInput.h>
#include <HAL/cpp/Semaphore.hpp>
#include <pthread.h>
#include "SkunkEncoder.h"
#include <cstdbool>
#include <cstdint>

static void tInteruptSkunk(uint32_t interruptAssertedMask, void *param) {
	Data * data = (Data *) param;

	data->m_mutex->unlock();
	data->m_SignSource->Get() ? data->counter++ : data->counter--;
	data->m_mutex->lock();
}

SkunkEncoder::SkunkEncoder(int dataPort, int signPort, std::string name) {
	current_position = 0;
	this->name = name;
	//check digitalinput port before using? (e.g. CheckDigitalChannel)
	dataSource = new DigitalInput(dataPort);
	signSource = new DigitalInput(signPort);

	mutex = new priority_mutex();

	data = new Data();
	data->counter = &current_position;
	data->m_DataSource = dataSource;
	data->m_SignSource = signSource;
	data->m_mutex = mutex;

	dataSource->RequestInterrupts(&tInteruptSkunk, data);
}

void SkunkEncoder::post() {
	SmartDashboard::PutNumber("SkunkEncoder" + name, current_position);
}

SkunkEncoder::~SkunkEncoder() {
	delete mutex;
	delete dataSource;
	delete signSource;
	delete data;
}

void SkunkEncoder::Reset() {
	current_position = 0;
}

int SkunkEncoder::GetPosition() {
	return current_position;
}

double SkunkEncoder::PIDGet() {
	return current_position;
}
