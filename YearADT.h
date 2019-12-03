#ifndef _yearADT_h
#define _yearADT_h
	
	#include <stddef.h>
    
    typedef struct yearCDT * yearADT;

    void addYear (yearADT yearSet, unsigned int year, size_t male, size_t female);

    void toBeginYear (yearADT yearSet);

    yearADT * nextYear (yearADT yearSet);

    int hasNextYear (yearADT yearSet);

    int getMale (yearADT * currentYear);

    int getFemale(yearADT * currentYear);

    int getTotal (yearADT * currentYear);


#endif
