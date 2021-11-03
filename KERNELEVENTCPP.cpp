/*
 * KernelEv.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: OS1
 */
#include"KernelEv.h"
#include"SCHEDULE.H"
#ifndef KERNELEV_CPP_
#define KERNELEV_CPP_
// zabranjuje prekide
#define lock asm cli

// dozvoljava prekide
#define unlock asm sti
#ifndef BCC_BLOCK_IGNORE
	KernelEv* KernelEv::KernelEvLista[256]={0};
#endif

KernelEv::KernelEv(IVTNo ivtNo){
	broj=ivtNo;
	pozivalac=PCB::running;
	if (ivtNo >= 0 )
		if(ivtNo < 256)
			KernelEvLista[broj]=this;
	treba=0;
	blokirana=0;
}

void KernelEv::wait(){
	//lock
	if(PCB::running==pozivalac){
		if(treba!=0) {treba=0;return;}
		blokiraj();
	}
	//unlock
}
void KernelEv::signal(){
	if(blokirana!=0) deblokiraj();
	else treba=1;

	//lock
	//deblokiraj(); //jel to to??
	//unlock
}
void KernelEv::blokiraj(){
	lock
	PCB::running->blocked=1;
	//samo zablokiram i sacuvam u blokirana
	blokirana=PCB::running;
	unlock
	//promena konteksta jer smo zablokirali
	dispatch();
}
void KernelEv::deblokiraj(){
	lock
	//PCB::running=blokirana;
	blokirana->blocked=0;
	//PCB::running->blocked=0;
	//ipak ne treba da diram running
	Scheduler::put(blokirana);
	blokirana=0;
	unlock
}
KernelEv::~KernelEv(){
	if (blokirana != 0) {
			deblokiraj();

			blokirana = 0;
			pozivalac = 0;
		}
		if (broj >= 0)
			if(  broj< 256)
				KernelEv::KernelEvLista[broj] = 0;
}
#endif /* KERNELEV_CPP_ */
