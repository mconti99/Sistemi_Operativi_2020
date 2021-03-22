#include "buffer.h"

#include <unistd.h>
#include <stdio.h>

void produzione(int sem_id, buffer *buf1, buffer *buf2, int valore)
{

    /* TBD: Inizio produzione */
	Wait_Sem(sem_id, SPAZIO_DISP);

    if (buf1->stato == LIBERO)
    {
        /* TBD: Inizio produzione */
	buf1->stato=INUSO;
        printf("[%d] In produzione su buf1...\n", getpid());

        sleep(1);

        buf1->valore = valore;
	buf1->stato=OCCUPATO;
        /* TBD: Fine produzione */

        printf("[%d] Prodotto il valore %d su buf1\n", getpid(), valore);
    }
    else
    {

        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno uno spazio disponibile, e 
         * quello spazio non è in "buf1", per cui "buf2"
         * è necessariamente libero.
         */

        /* TBD: Inizio produzione */
	buf2->stato=INUSO;
        printf("[%d] In produzione su buf2...\n", getpid());

        sleep(1);

        buf2->valore = valore;

        /* TBD: Fine produzione */
	buf2->stato=OCCUPATO;
        printf("[%d] Prodotto il valore %d su buf2\n", getpid(), valore);

    }
	Signal_Sem(sem_id, MESSAGGIO_DISP);
    /* TBD: Fine produzione */
}

int consumazione(int sem_id, buffer *buf1, buffer *buf2)
{

    int valore;
	Wait_Sem(sem_id, MESSAGGIO_DISP);
    /* TBD: Inizio consumazione */


    if (buf1->stato == OCCUPATO)
    {
        /* TBD: Inizio consumazione */
	buf1->stato=INUSO;
        printf("[%d] In consumazione su buf1...\n", getpid());

        sleep(2);

        valore = buf1->valore;
	buf1->stato=OCCUPATO;
        /* TBD: Fine consumazione */

        printf("[%d] Consumato il valore %d su buf1\n", getpid(), valore);

    }
    else
    {
        /* se il programma è arrivato a questo punto, vi
         * deve essere almeno un messaggio disponibile, e 
         * quel messaggio non è in "buf1", per cui "buf2"
         * è necessariamente occupato.
         */

        /* TBD: Inizio consumazione */
	buf2->stato=INUSO;
        printf("[%d] In consumazione su buf2...\n", getpid());

        sleep(2);

        valore = buf2->valore;
	buf2->stato=OCCUPATO;
        /* TBD: Fine consumazione */

        printf("[%d] Consumato il valore %d su buf2\n", getpid(), valore);

    }
	Signal_Sem(sem_id, SPAZIO_DISP);
    /* TBD: Fine consumazione */

    return valore;
}
