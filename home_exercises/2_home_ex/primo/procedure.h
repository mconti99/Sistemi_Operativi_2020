#define MUTEX_VETT 0
#define MUTEX_VAR 1

#define DIM_BUFFER 80

#define NUM_PRODUTTORI 50

#define BUFFER_VUOTO 0
#define BUFFER_PIENO 1
#define BUFFER_INUSO 2

#define FTOK_PATH_M "./"
#define FTOK_PATH_M1 "./"
#define FTOK_CHAR_M 'a'
#define FTOK_CHAR_M1 'b'

typedef struct {
    unsigned int id_cliente;
    unsigned int stato; 
} posto;



void produttore(posto*,int*, int);

