//estructura a usar
typedef struct node
{
    int code; //Codigo de identificacion de la Provincia
    char * value; //Nombre de la Provincia
    stuct node * tail;
} node;

typedef struct provCDT
{
    size_t qProv; //Cantidad de Provincias
    tProvVec * provVec; //vector a ser pasado en listToArray
    node * firstList; //Lista en donde se cargan las provincias desordenadas
} provCDT;

typedef struct tYear //estructura para el año
{
    unsigned int year;
    size_t male;    //Cantidad de hombres
    size_t female;  //Cantidad de mujeres

} tYear;

typedef struct tProvVec
{
    int code;  //Codigo de identificacion de la Provincia
    char * value; //Nombre de la provincia
    tYear * years; //Vector donde se almacena la cantidad de nacimientos por años
} tProvVec;
