struct Structure v1, v2;
    
    printf("Enter name and value #1: ");
    scanf("%s %d", v1.name, &v1.value);
    
    printf("Enter name and value #2: ");
    scanf("%s %d", v2.name, &v2.value);

    printf("\nResults:\n");
    printf("Entry 1 - Name: %s, Value: %d\n", v1.name, v1.value);
    printf("Entry 2 - Name: %s, Value: %d\n", v2.name, v2.value);

    return 0;