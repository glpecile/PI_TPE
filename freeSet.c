static void freeListRec(nodeProv * first);

void 
freeSet(provADT set)
{
    for(int i = 0; i < set->qProv; i++)
    {
        freeYears(set->provVec[i].years);
    }
    free(set->provVec);
    freeListRec(set->firstList);
    free(set);
}

static void 
freeListRec(nodeProv * first)
{
    if(first == NULL)
    {
        return;
    }

    freeListRec(first->tail);
    free(first->code);
    free(first->value);
    free(first);
    return;
}