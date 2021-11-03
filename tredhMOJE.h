
	 void hendlujSignale();
	 static void hendlerZaNulu();
	 void hendlerZaDvojku();
//private:
public:
	PCB* myPCB;
public:




		struct cvorSignal {
			cvorSignal(SignalId id) { sigId = id; next = 0; }
			SignalId sigId;
			cvorSignal* next;

		};
		cvorSignal *poslednjiSig;
		cvorSignal *prviSig;


		struct cvorHendler {
			SignalHandler hendler;
			cvorHendler* next;
			cvorHendler(SignalHandler s) { hendler = s; next = 0; }
		};
		cvorHendler *prviHendler[16]; //16 prvih hendlera (za svaki signal)
		cvorHendler *poslednjiHendler[16];  //16 poslednjih hendlera(za svaki signal)

		int dozvoljenSig1;
		Thread* otac;

		static int globalni[16];
		int blokirani[16];