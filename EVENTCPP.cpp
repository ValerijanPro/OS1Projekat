/*
 * event.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: OS1
 */
#include"event.h"
#include"KernelEv.h"
#ifndef EVENT_CPP_
#define EVENT_CPP_

// zabranjuje prekide
#define lock asm cli

// dozvoljava prekide
#define unlock asm sti
typedef unsigned char IVTNo;
class KernelEv;

Event::Event(IVTNo ivtNo) {
	lock
	myImpl = new KernelEv(ivtNo);
	unlock
}

Event::~Event(){
	lock
	if (myImpl!=0)delete myImpl;
	myImpl = 0;
	unlock
}


void Event::signal() {
	if (myImpl!=0) myImpl->signal();
}

void Event::wait () {
	if (myImpl!=0) myImpl->wait();
}

#endif /* EVENT_CPP_ */
