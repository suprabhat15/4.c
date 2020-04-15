#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define pmt pthread_mutex_t
#define pmul pthread_mutex_unlock
#define pml pthread_mutex_lock
#define pmit pthread_mutex_init
#define pc pthread_create
#define pj pthread_join

#define mx_1 mutex_1
#define mx_2 mutex_2
#define mx_3 mutex_3

pmt mx_1,mx_2,mx_3;

void *one_process(){
	pml(&mx_1);
	printf("R1 acquired by 1st process\n");
	sleep(1);
	pmul(&mx_1);

	pml(&mx_2);
	printf("R2 acquired by 1st process\n");
	sleep(1);
	pmul(&mx_2);
  }

  void *two_process()
  {
  	pml(&mx_2);
	printf("R2 acquired by 2nd process\n");
	sleep(1);
	pmul(&mx_2);
	pml(&mx_3);
	printf("R3 acquired by 2nd process\n");
	sleep(1);
	pmul(&mx_3);
  }

  void *three_process()
  {
  	pml(&mx_3);
	printf("R3 acquired by 3rd process\n");
	sleep(1);
	pmul(&mx_3);

	pml(&mx_1);
	printf("R1 acquired by 3rd process\n");
	sleep(1);
	pmul(&mx_1);

  }

  int main(){
  	pthread_t th_1,th_2,th_3;
  	pmit(&mx_1,NULL);
  	pmit(&mx_2,NULL);
  	pmit(&mx_3,NULL);

  	pc(&th_1,NULL,one_process,NULL);
  	pc(&th_2,NULL,two_process,NULL);
  	pc(&th_3,NULL,three_process,NULL);

  	pj(th_1,NULL);
  	pj(th_2,NULL);
  	pj(th_3,NULL);
  }


