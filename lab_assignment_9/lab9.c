#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next; // Pointer to the next record in the chain
};

// Fill out this structure
struct HashType
{
    struct RecordType* hashArray[100];
    int hashSize;
};

// Compute the hash function
int hash(int x)
{
    return x % 100; // Using a simple modulus operation for simplicity
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL; // Initialize the next pointer to NULL
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
    int i;

    for (i = 0; i < hashSz; ++i)
    {
        // if index is occupied with any records, print all
        struct RecordType* current = pHashArray->hashArray[i];
        if (current != NULL)
        {
            printf("index %d -> ", i);
            while (current != NULL)
            {
                printf("%d %c %d -> ", current->id, current->name, current->order);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    struct HashType hashTable;
    hashTable.hashSize = 100;

    // Initialize hash array to NULL
    for (int i = 0; i < 100; ++i)
    {
        hashTable.hashArray[i] = NULL;
    }

    // Insert records into the hash with chaining
    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id);
        struct RecordType* newRecord = (struct RecordType*)malloc(sizeof(struct RecordType));
        if (newRecord == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        *newRecord = pRecords[i];
        newRecord->next = NULL;

        if (hashTable.hashArray[index] == NULL)
        {
            hashTable.hashArray[index] = newRecord;
        }
        else
        {
            struct RecordType* current = hashTable.hashArray[index];
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newRecord;
        }
    }

    // Display records in the hash with chaining
    displayRecordsInHash(&hashTable, 100);

    // Free allocated memory for pRecords and the hash table
    for (int i = 0; i < 100; ++i)
    {
        struct RecordType* current = hashTable.hashArray[i];
        while (current != NULL)
        {
            struct RecordType* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(pRecords);

    return 0;
}
