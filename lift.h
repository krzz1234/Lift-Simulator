#ifndef LIFT_H_
#define LIFT_H_

// ------------------------------
// Random Number Generator
// ------------------------------
// Return a random number from 0..i-1 (inclusive)
#define rnd(i) (rand()%(i))
int rand_seed = 123456;
#define randomise() srand(rand_seed);rand_seed=rand();

// ------------------------------
// Move cursor to (x,y)
// ------------------------------
void gotoxy(int x,int y) {
	printf("%c[%d;%df",0x1B,y+1,x+1);fflush(stdout);
}

// ------------------------------
// Windows Specific Code
// ------------------------------
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#define semaphore HANDLE

// Wait for a semaphore
void semaphore_wait(semaphore *s) {
	// Sem wait
	WaitForSingleObject(*s, MAXLONG);
}

// Signal a semaphore
void semaphore_signal(semaphore *s) {
	// Sem post
	ReleaseSemaphore(*s, 1, NULL);
}

// Create a semaphore initialised to value
void semaphore_create(semaphore *s, int value) {
	// Initialise Semaphore
	(*s) = CreateSemaphore(NULL, (long)value, MAXLONG, NULL);
}

// Create a Thread
void create_thread(void* (*func)(void*), void *args) {
	// Create Thread - Windows API
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, args, 0, NULL);
}

// Constants for printing
const char *tl = "\xc9";
const char *tr = "\xbb";
const char *bl = "\xc8";
const char *br = "\xbc";
const char *vl = "\xba";
const char *hl = "\xcd";
const char *td = "\xcb";
const char *tu = "\xca";
const char *lc = "\xb3";
const char *lf = "\xdb";
const char *pr = "\xfe";
const char *clear_screen = "cls";

#endif
// ------------------------------

// ------------------------------
// Linux Specific Code
// ------------------------------
#ifdef __linux__
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#define semaphore sem_t

typedef unsigned char bool;
#define true 1
#define false 0 

// Wait for a semaphore
void semaphore_wait(semaphore *s) {
	// Sem wait
	sem_wait(s);
}

// Signal a semaphore
void semaphore_signal(semaphore *s) {
	// Sem post
	sem_post(s);
}

// Create a semaphore initialised to value
void semaphore_create(semaphore *s, int value) {
	// Initialise Semaphore
	sem_init(s, 0, value);
}
#endif
// ------------------------------

// ------------------------------
// macOS Specific Code
// ------------------------------
#ifdef __APPLE__

#include <pthread.h>
#include <unistd.h>
#include <dispatch/dispatch.h>
#define semaphore dispatch_semaphore_t

// Wait for a semaphore
void semaphore_wait(semaphore *s) {
	// Dispatch wait
	dispatch_semaphore_wait(*s, DISPATCH_TIME_FOREVER);
}

// Signal a semaphore
void semaphore_signal(semaphore *s) {
	// Dispatch signal
	dispatch_semaphore_signal(*s);
}

// Create a semaphore initialised to value
void semaphore_create(semaphore *s, int value) {
	// Dispatch create semaphore
	(*s) = dispatch_semaphore_create(value);
}
#endif
// ------------------------------

// ------------------------------
// UNIX Specific Code
// ------------------------------
#if defined(__APPLE__) || defined(__linux__)

// Create a thread (pthreads)
void create_thread(void *(*func)(void*), void *args) {
	// Create Thread - POSIX API
	pthread_t thread;
	pthread_create(&thread, NULL, func, args);
}

// Constants for printing
const char *tl = "\u250f";
const char *tr = "\u2513";
const char *bl = "\u2517";
const char *br = "\u251b";
const char *vl = "\u2503";
const char *hl = "\u2501";
const char *td = "\u2533";
const char *tu = "\u253b";
const char *lc = "\u2502";
const char *lf = "\u2588";
const char *pr = "\u2596";
const char *clear_screen = "clear";

// Sleep (in milliseconds)
void Sleep(unsigned long long milliseconds) {
	// Sleep for nanoseconds
	struct timespec req = {0};
	req.tv_sec = milliseconds / 1000ULL;
	req.tv_nsec = (milliseconds - (req.tv_sec*1000ULL)) * 1000000ULL;
	nanosleep(&req, (struct timespec *)NULL);
}
#endif

#endif // LIFT_H_