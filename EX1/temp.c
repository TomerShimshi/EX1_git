while (pch != NULL)
{

	if (i > 2)
	{
		printf("Error input too big");
	}
	else if (i == 0)
	{
		//MyMessege->FileName = pch;
		FileName = pch;

	}
	else if (i == 1)
	{
		//MyMessege->offset = (int)pch;
		offset = (int)pch;
	}
	else
	{
		//MyMessege->KeyFileName = pch;
		KeyFileName = pch;
	}
	printf("%s\n", pch);
	pch = strtok(NULL, " ,.-");
	i++;
}