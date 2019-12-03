void alphaSort(provADT set)
{
    int dim = set->qProv;
    tProvVec aux;

    for(int i = 0; i < dim; i++)
    {
        for(int j = i + 1; j < dim; j++)
        {
            if(strcmp(set->provVec[i].value, set->provVec[j].value) > 0)
            {
                aux = set->provVec[i];
                set->provVec[i] = set->provVec[j];
                set->provVec[j] = aux;
            }
        }
    }
}