static void listToArray(provADT set);

void finalizeProvAddition(provADT set)
{
    listToArray(set);
}

static void listToArray(provADT set)
{
    int i = 0;
    nodeProv * aux = set->firstList;

    set->provVec = calloc(set->qProv, sizeof(tProvVec));

    while(aux != NULL)
    {
        set->provVec[i].code = aux->code;
        set->provVec[i].value = aux->value;

        aux = aux->tail;
        i++;
    }   
}  