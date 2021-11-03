/*
 * KernelEv.h
 *
 *  Created on: Jul 7, 2020
 *      Author: OS1
 */

#include"event.h"
#include"PCB.h"

#ifndef KERNELEV_H_
#define KERNELEV_H_


class KernelEv{
public:
	static KernelEv* KernelEvLista[256];
	KernelEv(IVTNo ivtNo);
	 void wait ();
	 void signal ();
	 void blokiraj();
	 void deblokiraj();

	 PCB* blokirana; //PCB koja je blokirana na ovom binarnom semaforu (sacuvamo prilikom blokiranja u ovu varijablu)
	 	 	 	 	 // onda kada se deblokira,
	 	 	 	 	 //running ce da postane ova koja je bila blokirana
	 PCB* pozivalac; //ili holder
	 IVTNo broj;
	 int treba;
	 //flag za macro
	 ~KernelEv ();
};


#endif /* KERNELEV_H_ */
