static void freeYearRec(nodeYear * first);

void freeYears(yearADT years)
{
	if(years != NULL)
	{
		freeYearRec(years->firstYear);
		free(years);		
	}

}

static void
freeYearRec(nodeYear * first)
{
	if(first == NULL)
	{
		return;
	}

	freeYearRec(first->tail);
	free(first);
	return;
}
