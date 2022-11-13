#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <string.h>

int main()
{
    int MAX_SIZE = 2048;
    int MAX_NUM_MSG = 10;

    char *my_mq = "/mymq";
    char buf[MAX_SIZE];

    mqd_t mqd;
    struct mq_attr attributes;

    // forming the message queue attributes
    attributes.mq_msgsize = MAX_SIZE;
    attributes.mq_maxmsg = MAX_NUM_MSG;

    int pid = fork();
    if (pid == 0)
    {
        FILE *ptr;
        // Opening file in reading mode
        ptr = fopen("toRead.txt", "r");

        // Reads from file and stores in buf
        fgets(buf, MAX_SIZE, ptr);
        printf("In Child, message to send: %s\n", buf);

        // Opens message queue
        mqd = mq_open(my_mq, O_CREAT | O_WRONLY, S_IRWXU, &attributes);

        if (mqd != (mqd_t)-1)
        {
            printf("Message queue opened \n");
        }

        // Sends message to message queue
        if (mq_send(mqd, buf, strlen(buf) + 1, 0) == 0)
        {
            printf("Message sent successfully...\n");
        }
        else
        {
            printf("Message failed to send!!!\n");
        }

        mq_close(mqd);
    }
    else
    {
        // wait for child to finish
        wait(NULL);

        // Opens message queue
        mqd = mq_open(my_mq, O_RDONLY);

        if (mqd != (mqd_t)-1)
        {
            printf("Message queue opened \n");
        }

        // Receives message from message queue
        if (mq_receive(mqd, buf, MAX_SIZE, NULL) != -1)
        {
            printf("Message recieved: %s\n", buf);
        }
        else
        {
            printf("Message failed to recieve!!!\n");
        }

        mq_close(mqd);

        // Unlinking the message queue
        mq_unlink(my_mq);

        // count number of words
        int count = 0;
        for (int i = 0; i < strlen(buf); i++)
        {
            if (buf[i] == ' ')
            {
                count++;
            }
        }
        printf("Number of words: %d\n", count + 1);
    }

    return 0;
}