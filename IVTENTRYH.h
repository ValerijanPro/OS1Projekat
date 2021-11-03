/*
 * ivtentry.h
 *
 *  Created on: Jul 7, 2020
 *      Author: OS1
 */
#include"event.h"
#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt(*pokInterrupt)(...);

#define PREPAREENTRY(b,treba)\
		void interrupt prekidna##b(...);\
		IVTEntry ulaz##b =IVTEntry(b,prekidna##b);\
		void interrupt prekidna##b(...){\
			ulaz##b.signal();\
			if(treba!=0)\
			ulaz##b.stara();\
		}


class IVTEntry{
public:
	static IVTEntry* dohvUlaz(IVTNo br);
	static IVTEntry* IVT[256];
	IVTEntry(IVTNo br,pokInterrupt prekid);



	void stara();
	void signal();

	~IVTEntry();
private:
	IVTNo broj;
	pokInterrupt staraRut;
};



#endif /* IVTENTRY_H_ */
