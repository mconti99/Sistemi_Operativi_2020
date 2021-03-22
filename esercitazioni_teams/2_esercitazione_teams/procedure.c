#include "header.h"

void generatore(int coda_gen, int i){
	msg m;
	for(int i=0;i<10;i++) m.s[i]='a' + (rand() % 26);
                        m.s[10]='\0';
                        for(int i=0;i<2;i++) m.a[i]=rand()%10;
                        m.var=0;
                        m.type=TYPE;
                        msgsnd(coda_gen, &m, sizeof(msg)-sizeof(long), 0);
                        printf("MESSAGGIO 1 GENERATORE %d: stringa: %s; valori interi: [%d] [%d]; valore intero (ovvero somma): %d\n",i, m.s, m.a[0], m.a[1], m.var);
                        for(int i=0;i<9;i++) m.s[i]='a' + (rand() % 26);
                        m.s[10]='\0';
                        for(int i=0;i<2;i++) m.a[i]=rand()%10;
                        msgsnd(coda_gen, &m, sizeof(msg)-sizeof(long), 0);
                        printf("MESSAGGIO 2 GENERATORE %d: stringa: %s; valori interi: [%d] [%d]; valore intero (ovvero somma): %d\n",i, m.s, m.a[0], m.a[1], m.var);

}
void filtro(int coda_gen, int  coda_filtro){
	msg m;
                for(int i=0;i<6;i++){
                        msgrcv(coda_gen, &m, sizeof(msg)-sizeof(long), TYPE, 0);
                        printf("FILTRO  %d: stringa: %s; valori interi: [%d] [%d]; valore intero (ovvero somma): %d\n",i, m.s, m.a[0], m.a[1], m.var);
                        if(strchr(m.s, 'x')==NULL){
                                msgsnd(coda_filtro, &m, sizeof(msg)-sizeof(long), 0);
                        }
                        else{
                                m.type=MSG_ERR;
                                msgsnd(coda_filtro, &m, sizeof(msg)-sizeof(long), 0);
                        }
                }
                printf("---------FILTRO TERMINATO---------\n");
}

void checksum(int coda_filtro, int coda_csum){
	msg m;
                int somma;
                for(int i=0;i<6;i++){
                somma=0;
                msgrcv(coda_filtro, &m, sizeof(msg)-sizeof(long),0,  0);
                if(m.type==MSG_ERR){	
			msgsnd(coda_csum, &m, sizeof(msg)-sizeof(long), 0);
			printf("CHECKSUM ERRATA  %d: stringa: %s; valori interi: [%d] [%d]; valore intero (ovvero somma): %d\n",i, m.s, m.a[0], m.a[1], m.var);
			printf("----CHECKSUM TERMINATO MALE---\n");
			exit(0);
		}
                        else{
                        for(int i=0;i<10;i++) somma += m.s[i];
                        for(int i=0;i<2;i++) somma+= m.a[i];
                        m.var=somma;
                        printf("CHECKSUM  %d: stringa: %s; valori interi: [%d] [%d]; valore intero (ovvero somma): %d\n",i, m.s, m.a[0], m.a[1], m.var);
                        msgsnd(coda_csum, &m, sizeof(msg)-sizeof(long), 0);
                }
                }
                printf("------------CHECKSUM TERMINATO-----------\n");

}

void visualizzatore(int coda_csum){
	msg m;
                for(int i=0;i<6;i++){
                        msgrcv(coda_csum, &m, sizeof(msg)-sizeof(long),0, 0);
                        if(m.type!=MSG_ERR) printf("VISUALIZZATORE %d: stringa: %s; valori interi: [%d] [%d]; valore intero (ovvero somma): %d\n",i, m.s, m.a[0], m.a[1], m.var);
			else {
				printf("------VISULIZZATORE TERMINATO MALE---\n");
				exit(0);
			}
                }

                printf("-------------VISUALIZZATORE TERMINATO--------------\n");
}


