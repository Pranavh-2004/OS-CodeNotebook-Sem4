// Write a program to simulate optimal page replacement algorithm.
// Assume 3 frames and a series of page access.
// Compute the number of page faults.

#include <stdio.h>
#include <stdbool.h>

#define FRAME_COUNT 3

// Function to check if page is present in frames
bool isPagePresent(int page, int frames[], int frameCount)
{
    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == page)
            return true;
    }
    return false;
}

// Function to find optimal page to replace
int findOptimalReplacement(int pages[], int frames[], int frameCount, int currentIndex, int pageCount)
{
    int farthest = -1, replaceIndex = -1;

    for (int i = 0; i < frameCount; i++)
    {
        int j;
        for (j = currentIndex + 1; j < pageCount; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        if (j == pageCount) // If a page is never used again
            return i;
    }

    if (replaceIndex == -1)
    {
        return 0;
    }
    else
    {
        return replaceIndex;
    }
}

// Function to print current frames
void printFrames(int frames[], int frameCount)
{
    printf("Current frames: ");
    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frames[i]);
    }
    printf("\n");
}

// Function to implement Optimal Page Replacement Algorithm
int optimalPageReplacement(int pages[], int pageCount)
{
    int frames[FRAME_COUNT];
    for (int i = 0; i < FRAME_COUNT; i++)
        frames[i] = -1;

    int pageFaults = 0;

    printf("\n");
    printf("Page Replacement Simulation (Optimal)\n");
    printf("-------------------------------------\n");

    for (int i = 0; i < pageCount; i++)
    {
        int currentPage = pages[i];
        printf("\nPage request: %d\n", currentPage);

        if (!isPagePresent(currentPage, frames, FRAME_COUNT))
        { // Page fault
            pageFaults++;
            printf("Page fault occurred! ");

            // Use empty frame if available
            int freeIndex = -1;
            for (int j = 0; j < FRAME_COUNT; j++)
            {
                if (frames[j] == -1)
                {
                    freeIndex = j;
                    break;
                }
            }

            if (freeIndex != -1)
                frames[freeIndex] = currentPage;
            else
            {
                int replaceIndex = findOptimalReplacement(pages, frames, FRAME_COUNT, i, pageCount);
                frames[replaceIndex] = currentPage;
            }

            printFrames(frames, FRAME_COUNT);
        }
        else
        {
            printf("Page already in memory. ");
            printFrames(frames, FRAME_COUNT);
        }
    }

    printf("\nTotal number of page faults: %d\n", pageFaults);
    return pageFaults;
}

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    int faults = optimalPageReplacement(pages, pageCount);
    return 0;
}