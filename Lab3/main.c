#include <stdio.h>
#include <stdlib.h>
#define TLB_SIZE 16
#define PAGE_SIZE 256

int TLB_hits = 0;
int TLB_counter = 0;
float operations = 0.0;
int page_table_faults = 0;

FILE *address_file;
FILE *backing_store;

typedef struct
{
    int page_number;
    int frame_number;

} tlb;

int page_table[PAGE_SIZE];
tlb TLB[TLB_SIZE];

// search for page number in TLB and return frame number, -1 if not found
int searchTLB(int page_number)
{
    for (int i = 0; i < TLB_SIZE; i++)
    {
        if (TLB[i].page_number == page_number)
            return TLB[i].frame_number;
    }
    return -1;
}

// add page number and frame number to TLB and increment TLB counter and reset if TLB is full
void addToTLB(int page_number, int frame_number)
{
    TLB[TLB_counter].page_number = page_number;
    TLB[TLB_counter].frame_number = frame_number;
    TLB_counter = (TLB_counter + 1) % TLB_SIZE;
}

int main(int argc, char *argv[])
{
    int logical_address;
    int frame_counter = 0;
    char value;

    address_file = fopen("addresses.txt", "r");
    backing_store = fopen("BACKING_STORE.bin", "rb");

    // check if files are open
    if (address_file == NULL || backing_store == NULL)
    {
        printf("Error opening files");
    }

    // initialize page table and TLB
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        page_table[i] = -1;
    }

    for (int i = 0; i < TLB_SIZE; i++)
    {
        TLB[i].page_number = -1;
        TLB[i].frame_number = -1;
    }

    // read addresses from file
    while (fscanf(address_file, "%d,", &logical_address) > 0)
    {
        operations++;

        // gets the page number from the address
        int page = (logical_address >> 8) & 0xff;

        // gets the offset from the address
        int offset = logical_address & 0xff;

        // search for frame in TLB
        int frame = searchTLB(page);

        if (frame == -1)
        {
            if (page_table[page] == -1)
            {
                frame = frame_counter++ << 8;
                page_table[page] = frame;
            }
            else
            {
                frame = page_table[page];
                page_table_faults++;
            }

            // add to TLB
            addToTLB(page, frame);
        }
        else
        {
            TLB_hits++;
        }

        // seek to frame in backing store and read value and sets offset using SEEK_SET
        fseek(backing_store, logical_address, SEEK_SET);
        fread(&value, sizeof(char), 1, backing_store);

        // get the physical address by using the frame and virtual address
        int physical_address = logical_address & 0xff | frame;

        printf("Virtual address: %d Physical address: %d Value: %d\n", logical_address, physical_address, value);
    }

    printf("TLB hit rate: %f%%\n", (TLB_hits / operations) * 100);
    printf("Page fault rate %f%%\n", (page_table_faults / operations) * 100);

    return 0;
}
