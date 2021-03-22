//#include


int leggi(struct LettScritt *ls){
	int valore;
	enter_monitor(&(ls->m));
	//while con la signal&continue
	if(ls->numero_scrittori>0){//se c'è almeno uno scrittore, mi devo fermare
		   // Nel caso signal_and_wait, lo scrittore segnala e va in attesa, e quindi può segnalare
        // solo un lettore invece di tutti come per la soluzione signal_and_continue.
		wait_condition(&(ls->m), VARCOND_LETTORI);
	}


	//lo scrittore potrà segnalare un solo lettore
	//il primo lettore (riavviato dallo scrittore) riavvia il secondo, il secondo il terzo,..
	ls->numero_lettori++;//questa funzione è un lettore
	signal_condition(&(ls->m), VARCOND_LETTORI); 
	//questa signal_condition non la devo fare più con la signal&continue
	leave_monitor(&(ls->m));
	
	//LETTURA
	
	valore=ls->buffer;

	enter_monitor(&(ls->m));
	ls->numero_lettori--;//ho finito di leggere
	/*
	 * NOTA: l'ultimo lettore ad abbandonare la risorsa
	 * riattiva uno degli scrittori in attesa
	 */
	if(ls->numero_lettori==0){//se sono l'ultimo lettore, sveglio gli scrittori
		signal_condition(&(ls->m), VARCOND_SCRITTORI);
	}

	leave_monitor(&(ls->m));
	return valore;
}

void scrivi(struct LettScritt *ls, int valore){
	enter_monitor(&(ls->m));
	//WHILE CON SIGNAL &CONTINUE
	if(ls->numero_lettori>0 || ls->numero_scrittori>0){
		wait_condition(&(ls->m), VARCOND_SCRITTORI);
	}
	ls->numero_scrittori++;

	leave_monitor(&(ls->m));
	//scrivo
	

	ls->buffer=valore;

	enter_monitor(&(ls->m));
	//starvation di entrambi: devo segnalare prima gli altri scrittori, poi se non ce ne sono allora segnalo i lettori (1 solo lettore perchè il monitor è signal&wait)
	ls->numero_scrittori--; //me ne sto andando

	if(queue_condition(&(ls->m), VARCOND_SCRITTORI)>0){//ci sono altri scrittori in attesa
		signal_condition(&(ls->m), VARCOND_SCRITTORI);
	}else{
		signal_condition(&(ls->m), VARCOND_LETTORI);
		//signal_all(&(ls->m), VARCOND_LETTORI); SIGNAL&CONTINUE
	}
	leave_monitor(&(ls->m));

}
