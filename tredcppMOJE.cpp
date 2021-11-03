
void Thread::signal(SignalId signal){
	//samo dodaje novi signal u listu signala
	if((!dozvoljenSig1 && signal==1)  || signal>15||(signal==2)  || prviHendler[signal]==0) return;
	cvorSignal* novi=new cvorSignal(signal);
	//lock
	lock
	if(prviSig==0){
		prviSig=novi;
		poslednjiSig=novi;
	}
	else{
		poslednjiSig->next=novi;
		poslednjiSig=poslednjiSig->next;
	}
	//unlock
	unlock
}
void Thread::registerHandler(SignalId signal, SignalHandler handler){
	if(signal<0 || signal>15) return;
	cvorHendler* novi=new cvorHendler(handler);
	//lock
	lock
	if(prviHendler[signal]==0){
		prviHendler[signal]=novi;
		poslednjiHendler[signal]=novi;
	}
	else{
		poslednjiHendler[signal]->next=novi;
		poslednjiHendler[signal]=poslednjiHendler[signal]->next;
	}
	//unlock
	unlock
}

void Thread::unregisterAllHandlers(SignalId id) {
	if(id<0 || id>15) return;
	cvorHendler* temp=prviHendler[id];
	prviHendler[id]=0;
	poslednjiHendler[id]=0;
	while(temp!=0){
		cvorHendler* tren=temp;
		temp=temp->next;
		delete tren;
	}
}

void Thread::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	if(id<0 || id>15) return;
	cvorHendler* t1;
	cvorHendler* t2;
	cvorHendler* temp=prviHendler[id];
	while(temp!=0){
		if(temp->hendler==hand1){
			t1=temp;
			break;
		}
		temp=temp->next;
	}
	if(temp==0) return;

	 temp=prviHendler[id];
	while(temp!=0){
		if(temp->hendler==hand2){
			t2=temp;
			break;
		}
		temp=temp->next;
	}
	if(temp==0) return;
	//lock
	lock
	t1->hendler=hand2;
	t2->hendler=hand1;
	//unlock
	unlock
}

void Thread::blockSignal(SignalId signal){
	if(signal<0 || signal>15) return;
	blokirani[signal]=1;
}
static void blockSignalGlobally(SignalId signal){
	if(signal<0 || signal>15) return;
	Thread::globalni[signal]=1;
}
void Thread::unblockSignal(SignalId signal){
	if(signal<0 || signal>15) return;
		blokirani[signal]=0;
}
static void unblockSignalGlobally(SignalId signal){
	if(signal<0 || signal>15) return;
	Thread::globalni[signal]=0;
}

void Thread::hendlerZaDvojku(){
	if(blokirani[2]==1 || Thread::globalni[2]==1) return;
	cvorHendler* temp=prviHendler[2];
	while(temp!=0){
		hendlujem=1;
		temp->hendler();
		hendlujem=0;
		temp=temp->next;
	}
}
void Thread::hendlerZaNulu(){
	if( Thread::globalni[0]==1) return;
	 for(Node* temp=PCB::running->cekajuce->prvi;temp!=0;temp=temp->next){
		 	 	 lock
		 		temp->info->blocked=0;
		 		Scheduler::put(temp->info);
		 		//PCB::running->cekajuce->remove();
		 		unlock
	}
	PCB::running->cekajuce->prvi=0;
	PCB::running->cekajuce->poslednji=0;
	if (PCB::running->thread->otac!=0) {

			PCB::running->thread->otac->dozvoljenSig1 = 1;
			PCB::running->thread->otac->signal(1);
			PCB::running->thread->otac->dozvoljenSig1 = 0;

	}
	PCB::running->thread->hendlerZaDvojku();
	PCB::running->finished=1;
}


void Thread::hendlujSignale(){
	cvorSignal* temp=prviSig;

	cvorSignal* pret=0;
	while(temp!=0){
		if(blokirani[temp->sigId]==1 || Thread::globalni[temp->sigId]==1){
			pret=temp;
			temp=temp->next;
		}
		else{
			//ovaj prvi deo izbaci iz liste
			if(pret==0){
				prviSig=prviSig->next;
				if(prviSig==0) poslednjiSig=0;
			}
			else{
				pret->next=temp->next;
			}
			//izbacen iz liste, sad se brise sam CVOR signala
			SignalId s=temp->sigId;
			cvorSignal* stari=temp;
			temp=temp->next;
			delete stari; //obirsan iz liste signala
			cvorHendler* tren=prviHendler[s];
			while(tren!=0){
				tren->hendler();
				tren=tren->next;
			} //pozvani svi hendleri za obrisani signal
		}


	}
}