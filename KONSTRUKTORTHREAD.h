//lock??
	lock
	myPCB= new PCB(this,stackSize,timeSlice);

	PCB::lista->add(myPCB);
	if(myPCB->id==1 || myPCB->id==2){
		poslednjiSig=0;
		prviSig=0;
		for(int i=0;i<16;i++){
			blokirani[i]=0;
			prviHendler[i]=0;
			poslednjiHendler[i]=0;
		}
		otac=0;
	}
	else{
		poslednjiSig=0;
		prviSig=0;
		otac=PCB::running->thread;
		for(int i=0;i<16;i++){
			prviHendler[i]=0;
			poslednjiHendler[i]=0;
			blokirani[i]=otac->blokirani[i];
			cvorHendler* tren=otac->prviHendler[i];
			while(tren!=0){
				cvorHendler* novi=new cvorHendler(tren->hendler);
				if(prviHendler[i]==0){
					prviHendler[i]=novi;
					poslednjiHendler[i]=novi;
				}//if
				else{
					poslednjiHendler[i]->next=novi;
					poslednjiHendler[i]=poslednjiHendler[i]->next;
				}//else
				tren=tren->next;
			}//while
		}//for
	}//else
	prviHendler[0]= new cvorHendler(&Thread::hendlerZaNulu);
	poslednjiHendler[0]= prviHendler[0];
	//unlock(); ??
	unlock