#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Test with 82,170,43,140,24,16,190. will need to replace 1000 with 7 and 4999 with 199(range 0-200)
int FCFS(int cyllinder[], int head)
{
    int sum = abs(cyllinder[0] - head); // move from head to first in qeueu
    for (int i = 1; i < 1000; i++)
    {

        int diff = cyllinder[i] - cyllinder[i - 1]; // keep moving to next element in qeueu
        sum = sum + abs(diff);
        // printf("%d", diff);
        // printf("%c", '\n');
    }
    return sum;
}

int minDistance(int arr[], int head, bool visited[])
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i])
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        return 0;
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + minDistance(arr, arr[minIndex], visited); // recursively visit all elements
    return sum;
}

int SSTF(int cyllinder[], int head)
{
    bool visited[1000];
    for (int i = 0; i < 1000; i++)
    {
        visited[i] = false; // initialize visited array to false
    }
    int sum = minDistance(cyllinder, head, visited); // minDistance function recursively sums up travel
    return sum;
}

int moveLeftScan(int arr[], int head, bool visited[])
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i] || arr[i] > head)
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        return 0;
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + moveLeftScan(arr, arr[minIndex], visited); // recursively visit all elements
    return sum;
}

int moveRightScan(int arr[], int head, bool visited[])
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i] || arr[i] < head)
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        sum = abs(4999 - head) + moveLeftScan(arr, 4999, visited);
        return sum;
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + moveRightScan(arr, arr[minIndex], visited); // recursively visit all elements
    return sum;
}

int SCAN(int cyllinder[], int head)
{
    bool visited[1000];
    for (int i = 0; i < 1000; i++)
    {
        visited[i] = false; // initialize visited array to false
    }
    int sum = moveRightScan(cyllinder, head, visited); // minDistance function recursively sums up travel
    return sum;
}

int moveRightCScan(int arr[], int head, bool visited[], int initial)
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i] || arr[i] < head)
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        if (head > initial)
        {
            for (int i = 0; i < 1000; i++)
            {
                if (arr[i] < minValue)
                {
                    minValue = arr[i];
                }
            }
            sum = abs(4999 - head) + abs(4999) + moveRightCScan(arr, 0, visited, initial);
            return sum;
        }
        else
        {
            return 0;
        }
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + moveRightCScan(arr, arr[minIndex], visited, initial); // recursively visit all elements
    return sum;
}

int CSCAN(int cyllinder[], int head)
{
    bool visited[1000];
    for (int i = 0; i < 1000; i++)
    {
        visited[i] = false; // initialize visited array to false
    }
    int sum = moveRightCScan(cyllinder, head, visited, head); // minDistance function recursively sums up travel
    return sum;
}

int moveLeftLook(int arr[], int head, bool visited[])
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i] || arr[i] > head)
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        return 0;
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + moveLeftLook(arr, arr[minIndex], visited); // recursively visit all elements
    return sum;
}

int moveRightLook(int arr[], int head, bool visited[])
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i] || arr[i] < head)
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        return moveLeftLook(arr, head, visited);
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + moveRightLook(arr, arr[minIndex], visited); // recursively visit all elements
    return sum;
}

int Look(int cyllinder[], int head)
{
    bool visited[1000];
    for (int i = 0; i < 1000; i++)
    {
        visited[i] = false; // initialize visited array to false
    }
    int sum = moveRightLook(cyllinder, head, visited); // minDistance function recursively sums up travel
    return sum;
}

int moveRightCLook(int arr[], int head, bool visited[], int initial)
{
    int sum;
    int minIndex = 0;         // store index for min value from head
    int minValue = INT32_MAX; // compare with int max initially
    for (int i = 0; i < 1000; i++)
    {
        if (visited[i] || arr[i] < head)
        {
            continue; // skip the elements which are marked visited
        }
        if (abs(arr[i] - head) < minValue)
        {
            minValue = abs(arr[i] - head); // set new minimum if distance less than old min
            minIndex = i;                  // set new min index
        }
    }
    if (minValue == INT32_MAX) // base case if no min val found
    {
        if (head > initial)
        {
            for (int i = 0; i < 1000; i++)
            {
                if (arr[i] < minValue)
                {
                    minValue = arr[i];
                }
            }
            sum = abs(head - minValue) + moveRightCLook(arr, minValue, visited, initial);
            return sum;
        }
        else
        {
            return 0;
        }
    }
    visited[minIndex] = true; // mark min val node visited
    // printf("%d", arr[minIndex]);
    // printf("%c", '\n');
    sum = minValue + moveRightCLook(arr, arr[minIndex], visited, initial); // recursively visit all elements
    return sum;
}

int CLook(int cyllinder[], int head)
{
    bool visited[1000];
    for (int i = 0; i < 1000; i++)
    {
        visited[i] = false; // initialize visited array to false
    }
    int sum = moveRightCLook(cyllinder, head, visited, head); // minDistance function recursively sums up travel
    return sum;
}

int main(int argc, char *argv[])
{
    char *a = argv[1];
    int initial = atoi(a);
    int arr[5000];
    for (int i = 0; i < 5000; i++)
    {
        arr[i] = i;
    }
    for (int i = 0; i < 5000; i++)
    { // shuffle array
        int temp = arr[i];
        int randomIndex = arc4random() % 5000;
        arr[i] = arr[randomIndex];
        arr[randomIndex] = temp;
    }
    int cyllinders[1000];
    for (int i = 0; i < 1000; i++)
    {
        cyllinders[i] = arr[i];
    }
    int sum1 = FCFS(cyllinders, initial);
    printf("FCFS : %d", sum1);
    printf("%c", '\n');
    int sum2 = SSTF(cyllinders, initial);
    printf("SSTF : %d", sum2);
    printf("%c", '\n');
    int sum3 = SCAN(cyllinders, initial); // right
    printf("SCAN : %d", sum3);
    printf("%c", '\n');
    int sum4 = CSCAN(cyllinders, initial); // right
    printf("CSCAN : %d", sum4);
    printf("%c", '\n');
    int sum5 = Look(cyllinders, initial); // right
    printf("Look : %d", sum5);
    printf("%c", '\n');
    int sum6 = CLook(cyllinders, initial); // right
    printf("CLook : %d", sum6);
    return 0;
}
