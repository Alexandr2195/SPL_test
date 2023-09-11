void RemoveDups(char* str)
{
    if (!str)
        return;

    char            PrevChar(str[0]);
    unsigned int    newInd(0);

    for (unsigned int i(0); str[i]; i++)
    {
        if (PrevChar != str[i])
            newInd++;

        str[newInd] = str[i];

        PrevChar = str[i];
    }

    str[newInd + 1] = 0;

    return;
}