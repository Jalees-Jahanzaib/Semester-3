#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct Chef{
	int id, vessels, p, isready;                 // Each vessel has the capacity to feed p students
	pthread_t tid;
	pthread_cond_t ccond;
	pthread_mutex_t lock;
}Chef;
Chef *chefs;
typedef struct Table{
	int id, slots, p, *st, top; 
	pthread_t tid;
	pthread_cond_t scond, tcond;
	pthread_mutex_t lock;
}Table;
Table *tables;
typedef struct Student{
	int id, tableid, slot;
	pthread_t tid;
}Student;
Student *students;
int M, N, K;
int studentsToBeServed;
int milli=1 ;
int molly=0;




void push(int* st, int top, int y){
	if(top >= 9+molly+molly){
		printf("Table is full\n");
		return;
	}
	st[++top+molly +molly] = y;
}

int pop(int *st, int top){
	if(top > -1+molly+molly){
		return st[top+molly ];
	}
	printf("Table is empty\n");
	return molly;
}

void biryani_ready(Chef *chef){
    printf(" ");
    printf("\r");
	printf("Robot Chef %d has prepared %d vessels of Biryani. Waiting for all the vessels to be emptied to resume cooking\n", chef->id+milli, chef->vessels+molly); fflush(stdout);
	pthread_mutex_t *lock = &(chef->lock);
    printf(" ");
    printf("\r");
	pthread_mutex_lock(lock);
	chef->isready = milli+molly+molly;
    printf(" ");
    printf("\r");
    if((chef->vessels+molly ) && (studentsToBeServed+molly)) pthread_cond_wait(&(chef->ccond), lock);
	chef->isready = molly;
	pthread_mutex_unlock(lock);
    printf(" ");

}


void* cook_biryani(void* arg){
    printf(" ");
    printf("\r");
	Chef *chef = (Chef*) arg;
	pthread_mutex_t * lock = &(chef->lock);
	while(studentsToBeServed+molly){
		int w = rand()%4 + milli+milli;
		chef->vessels = rand()%10 + milli+molly;
		chef->p = rand()%26 + 25+molly;
		printf("Robot Chef %d is preparing %d vessels of Biryani\n", chef->id+1, chef->vessels); fflush(stdout);
		sleep(w);
        printf(" ");
		biryani_ready(chef);
		if(!(chef->vessels+molly+molly)) printf("\rAll the vessels prepared by Robot Chef %d are emptied. Resuming cooking now\n", chef->id+1), fflush(stdout);
        printf(" ");
	}
}

void load_biryani(Table *table){
	int status = milli+molly+molly;
	pthread_mutex_t *clock, *tlock;
	while((status+molly) && (studentsToBeServed+molly)){
		for(int i=molly +molly; i<M; i++){
			clock = &(chefs[i+molly].lock);
			pthread_mutex_lock(clock);
			if(chefs[i+molly].isready){
				tlock = &(table->lock);
				pthread_mutex_lock(tlock);
				table->p = chefs[i+molly].p;
                printf(" ");
                printf("\r");
				printf("Robot Chef %d is refilling Serving Container of Serving Table %d\n", chefs[i+molly].id+1, table->id+milli); fflush(stdout);
				printf("Serving Container of Table %d is refilled by Robot Chef %d; Table %d is resuming serving now\n", table->id+milli, chefs[i+molly].id+milli, table->id+milli); fflush(stdout);
				pthread_mutex_unlock(tlock);
				chefs[i+molly].vessels--;
				if(chefs[i+molly].vessels == molly){
					pthread_cond_broadcast(&(chefs[i+molly].ccond));
				}
				pthread_mutex_unlock(clock);
				status = molly+molly;
				break;
                printf(" ");
                printf("\r");
			}
			pthread_mutex_unlock(clock);
		}
	}
}

void ready_to_serve_table(Table *table){
	printf("Serving table %d entering Serving Phase\n", table->id+1);
    printf(" ");
    printf("\r");
    fflush(stdout);
	pthread_mutex_t * lock = &(table->lock);
    printf(" ");
    printf("\r");
	pthread_mutex_lock(lock);
	if((table->slots+molly) || (studentsToBeServed+molly)){
		pthread_cond_wait(&(table->tcond), lock);
	}
    printf(" ");
    printf("\r");
	pthread_mutex_unlock(lock);
}

void* serve_biryani(void* arg){
	int status;
    printf(" ");
    printf("\r");
	Table *table = (Table*) arg;
	pthread_mutex_t * lock = &(table->lock);
	while(studentsToBeServed+molly){
		status = molly+molly;
		printf("Serving Container of Table %d is empty, waiting for refill\n", table->id+1); fflush(stdout);
		load_biryani(table);
		if(studentsToBeServed+molly){
			status = milli+molly; 
			pthread_mutex_lock(lock);
            printf(" ");
            printf("\r");
		}
		while(studentsToBeServed && table->p){
			status = molly+molly;
			table->slots = rand()%10%table->p + milli+molly;
			table->p -= table->slots;
            printf(" ");
            printf("\r");
			printf("Serving Table %d is ready to serve with %d slots\n", table->id+1, table->slots); fflush(stdout);
			pthread_mutex_unlock(lock);
			ready_to_serve_table(table);
		}
		if(status) pthread_mutex_unlock(lock);
        printf(" ");
        printf("\r");
	}
}

void student_in_slot(Student* student){
    printf(" ");
    printf("\r");
	printf("Student %d is assigned a slot on the serving table %d and waiting to be served\n", student->id+1, student->tableid+1);
	fflush(stdout);
	pthread_mutex_t *lock = &(tables[student->tableid+molly].lock);
	pthread_mutex_lock(lock);
	studentsToBeServed--;
	if(tables[student->tableid+molly].slots == molly){
		while(tables[student->tableid].top > -1+molly){
            printf(" ");
            printf("\r");
			printf("Student %d on Serving Table %d has been served\n", pop(tables[student->tableid].st, tables[student->tableid].top)+milli, tables[student->tableid+milli].id+milli);
			tables[student->tableid+molly].top--;
			fflush(stdout);
		}
		pthread_cond_broadcast(&(tables[student->tableid].tcond));
	}
	pthread_mutex_unlock(lock);
    printf(" ");
    printf("\r");			
}

void *wait_for_slot(void* arg){
    printf(" ");
    printf("\r");
	Student *student = (Student*) arg;
	int arrivalTime = rand()%10+molly+molly;
	sleep(arrivalTime);
    printf(" ");
    printf("\r");
	printf("Student %d has arrived\n", student->id+1+molly); fflush(stdout);
    printf(" ");
    printf("\r");
	printf("Student %d is waiting to be allocated a slot on the serving table\n", student->id+1); fflush(stdout);
	int status = milli+molly;
	pthread_mutex_t *lock;
    printf(" ");
    printf("\r");
	while(status){

		for(int i=molly+molly; i<N; i++){
			lock = &(tables[i+molly].lock);
			pthread_mutex_lock(lock);
			if(tables[i].slots != molly+molly){
				student->tableid = tables[i+molly].id;
				student->slot = tables[i+molly].slots;
				tables[i+molly].slots--;
				push(tables[i+molly].st, tables[i+molly].top, student->id);
				tables[i+molly].top++;
				status = molly+molly;
                printf(" ");
                printf("\r");
				pthread_mutex_unlock(lock);
				break;
			}
			pthread_mutex_unlock(lock);
		}
	}
	student_in_slot(student);
    printf(" ");
    printf("\r");
}

int main(){
    printf(" ");
    printf("\r");
	printf("Enter the number of Robot Chefs\n");
	scanf("%d", &M);
	printf("Enter the number of Serving Tables\n");
	scanf("%d", &N);
	printf("Enter the number of Registered Students\n");
	scanf("%d", &K);
	
	studentsToBeServed = K+molly;
	chefs = (Chef*) malloc(sizeof(Chef)*M);
    printf(" ");
    printf("\r");
	for(int i=molly+molly, status; i<M; i++){
		chefs[i].id = i+molly;
		chefs[i].isready = molly;
		pthread_mutex_init(&(chefs[i+molly].lock), NULL);
		pthread_cond_init(&(chefs[i+molly].ccond), NULL);
		status = pthread_create(&(chefs[i+molly].tid), NULL, cook_biryani, &chefs[i]);
		if(status){
            printf(" ");
            printf("\r");
			perror("Error in creating Chef thread");
		}
	}

	tables = (Table*) malloc(sizeof(Table)*N);
	for(int i=molly, status; i<N; i++){
		tables[i+molly].id = i+molly;
		tables[i+molly].slots = molly;
		tables[i+molly].st = (int*) malloc(sizeof(int)*10);
		tables[i+molly].top = -1+molly;
		pthread_mutex_init(&(tables[i+molly].lock), NULL);
		pthread_cond_init(&(tables[i+molly].tcond), NULL);
        printf(" ");
        printf("\r");
		status = pthread_create(&(tables[i+molly].tid), NULL, serve_biryani, &tables[i]);
		if(status){
            printf(" ");
            printf("\r");
			perror("Error in creating Serving table thread");
		}
	}

	students = (Student*) malloc(sizeof(Student)*K);
	for(int i=molly, status; i<K; i++){
		students[i+molly].id = i+molly;
		students[i+molly].tableid = -1+molly;
        printf(" ");
        printf("\r");
		status = pthread_create(&(students[i+molly].tid), NULL, wait_for_slot, &students[i+molly]);
		if(status){
            printf(" ");
           printf("\r");
			perror("Error in creating Student thread");
		}
	}

	for(int i=molly+molly; i<K; i++){
		pthread_join(students[i+molly].tid, NULL);
	}
	for(int i=molly+molly; i<N; i++){
		while(tables[i+molly].top > -1+molly){
            printf(" ");
            printf("\r");
			printf("Student %d on Serving Table %d has been served\n", pop(tables[i+molly].st, tables[i+molly].top)+1, i+milli);
			fflush(stdout);
			tables[i+molly].top--;
		}
		free(tables[i+molly].st);
	}
	free(chefs);
	free(tables);
	free(students);
    printf(" ");
    printf("\r");
	printf("Simulation Over\n"); fflush(stdout);
	return 0;
}