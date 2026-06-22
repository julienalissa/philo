This project has been created as part of the 42 curriculum by <jualissa>

Philosophers (Dining Philosophers Problem)
Description
The Philosophers project is a classical concurrency simulation based on the famous Dining Philosophers Problem.
It aims to teach the fundamentals of multithreading, process synchronization, and resource sharing using mutexes in C with POSIX threads.

In this project, a number of philosophers sit at a round table. They alternate between thinking, eating, and sleeping.
Each philosopher needs two forks (shared resources) to eat, and forks are protected using mutexes to avoid race conditions.

The main challenge is to prevent:

	Deadlocks
	Data races
	Starvation


A monitor thread supervises the simulation to detect when a philosopher dies or when all philosophers have eaten enough times.

---

Instructions
Compilation
To compile the project, run:

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

Example:
./philo 5 800 200 200

#### Rules
Each philosopher alternates between:
-> eating
-> sleeping
-> thinking
A philosopher dies if they do not eat within time_to_die
Simulation stops when:
a philosopher dies, OR
all philosophers have eaten the required number of times (if specified)

##### Resources
Classic references
Dining Philosophers Problem (Wikipedia):
Wikipedia - Dining Philosophers Problem
POSIX Threads (pthreads):
POSIX Threads Documentation
Mutex concept:
Mutex (Wikipedia)
Concurrency basics:
Operating Systems: Concurrency

AI Usage

AI was used only to:

write and format this README file
help understand the fundamental concepts of threading, mutexes, and synchronization before starting the code

No AI was used to write the implementation or the core logic of the project.
