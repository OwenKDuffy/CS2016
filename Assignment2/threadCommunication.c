#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct consumerInput
{
	int index;
	char** readLocation;
	char** writeLocation;
}consumerInput;

void *readMessage(void* P)
{
	struct consumerInput *info = P;
}

void *printMessage(void* msg)
{
	while(1)
	{
		if(msg != NULL)
		{
			printf("%s\n", (char*) msg);
		}
	}
}

int main(int argc, char** argv)
{
	pthread_t threads[3];
	int rc,index;
	char mainToConsumer[16000];
	char consumerToPrinter[16000];

	for (index=0;index<3;index++) {
		struct consumerInput parameters = {.index = index, .readLocation = &mainToConsumer,
			.writeLocation = &consumerToPrinter};
			rc = pthread_create(&threads[index],NULL,readMessage,(void *) &parameters);
			if (rc) {
				printf("ERROR return code from pthread_create(): %d\n",rc);
				exit(-1);
			}
	}
	rc = 0;
	rc = pthread_create(&threads[3],NULL,printMessage,(void *) &consumerToPrinter);
	if (rc) {
		printf("ERROR return code from pthread_create(): %d\n",rc);
		exit(-1);
	}

	// wait for threads to exit
	for(index=0;index<4;index++) {
		pthread_join( threads[index], NULL);
	}
	return 0;

}
