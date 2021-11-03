 for(Node* temp=PCB::running->cekajuce->prvi;temp!=0;temp=temp->next){
		 	 	 lock
		 		temp->info->blocked=0;
		 		Scheduler::put(temp->info);
		 		PCB::running->cekajuce->removeFirst();
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






PCB::running->finished=1;
	PCB::running->thread->hendlerZaDvojku();
	if (PCB::running->thread->otac!=0) {

		PCB::running->thread->otac->dozvoljenSig1 = 1;
		PCB::running->thread->otac->signal(1);
		PCB::running->thread->otac->dozvoljenSig1 = 0;

	}
	for(int i=0;i<PCB::running->cekajuce->size();i++){
		PCB* t=PCB::running->cekajuce->pop();
		t->blocked=0;
		Scheduler::put(t);
	}


		//dispatch();

		dispatch();







lock
	PCB::running->finished=1;
		PCB::running->thread->hendlerZaDvojku();
		//PCB::running->thread->signal(2);
		if (PCB::running->thread->otac!=0) {

			PCB::running->thread->otac->dozvoljenSig1 = 1;
			PCB::running->thread->otac->signal(1);
			PCB::running->thread->otac->dozvoljenSig1 = 0;

		}

		for(int i=0;i<PCB::running->cekajuce->size();i++){
			PCB* t=PCB::running->cekajuce->pop();
			t->blocked=0;
			//KernelSem::lista.obrisiSpecificnuNitSEM(t);
			Scheduler::put(t);
			//if(Scheduler::get()==0) cout<<"wtf"<<endl;

		}

		//Thread::getThreadById(PCB::running->id);
		//if(Scheduler::get()==0) cout<<"wtf"<<endl;
		//cout<<"broj tredova: "<<endl;
		unlock
			dispatch();