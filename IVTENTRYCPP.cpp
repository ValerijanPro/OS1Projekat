/*
 * ivtentry.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: OS1
 */


#include"ivtentry.h"
#include<dos.h>
#include"KernelEv.h"

// zabranjuje prekide
#define lock asm cli

// dozvoljava prekide
#define unlock asm sti

#ifndef IVTENTRY_CPP_
#define IVTENTRY_CPP_

#ifndef BCC_BLOCK_IGNORE
IVTEntry* IVTEntry::IVT[256]={0};
#endif

IVTEntry::IVTEntry(IVTNo br,pokInterrupt prekid){
	broj=-1;

	//broj=-1;
	//broj=br;
	staraRut=0;
	if(broj>=0)
		if(broj<256){
			if(IVT[broj]==0){


					IVT[br]=this;
					broj=br;
					#ifndef BCC_BLOCK_IGNORE
					lock
					staraRut=getvect(broj);
					setvect(broj,prekid);
					unlock
					#endif
				}
		}

}
IVTEntry* IVTEntry::dohvUlaz(IVTNo br){
	return (br>=0 && br<=255)?IVT[br]:0;
}
void IVTEntry::signal(){
	if(KernelEv::KernelEvLista[broj])
		if(broj>=0)
			if(broj<256)
				KernelEv::KernelEvLista[broj]->signal();
}


void IVTEntry::stara(){
	if(broj==-1) return;
	staraRut();
}
IVTEntry::~IVTEntry(){
	if(broj==-1) return;
	lock
	setvect(broj, staraRut);

	unlock
	IVT[broj] = 0;
}
#endif /* IVTENTRY_CPP_ */
