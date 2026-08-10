*his project has been created as part of the 42 curriculum by outaouss*

# Description

The Codexion project is a multi-threaded system simulation designed to explore and solve complex concurrency, resource contention, and real-time scheduling challenges in C. Inspired by classic multi-agent synchronization problems, the simulation models multiple concurrent developers ("coders") working simultaneously while competing for a limited set of shared resources ("dongles") to compile, debug, and refactor their code.

The primary goal of the project is to build a high-performance, race-condition-free, and deadlock-free engine using POSIX threads (pthreads), mutexes, condition variables, and dynamic priority queues. By implementing scheduling algorithms such as Earliest Deadline First (EDF) and First-In, First-Out (FIFO) via custom Min-Heap data structures, the simulation ensures fair resource distribution while strictly enforcing system parameters—such as thread cooldowns, work execution phases, and strict burnout thresholds .

# Instructions

**Compilation & Installation:**
The project uses a standard `Makefile` for compilation. Build the program using the following commands:

- `make`: Compiles all .c source files into object `(.o)` files and links them to create the codexion executable.

- `make clean`: Removes all compiled object `(.o)` files while keeping the executable intact.

- `make fclean`: Performs a complete cleanup by removing all object `(.o)` files and the binary executable itself.

- `make re`: Executes fclean followed by make to perform a full re-compilation from scratch.

**Execution & Usage:**
To launch the simulation, execute the compiled binary with the required positional arguments in the exact following order:

```./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles> <dongle_cooldown> <scheduler_mode>```

Command Arguments Breakdown

- number_of_coders: Total number of concurrent threads to spawn (e.g., 40 or 1300).

- time_to_burnout: Time in milliseconds a coder can go without starting a compilation before burning out.

- time_to_debug: Duration in milliseconds spent in the debugging phase after compiling.

- time_to_refactor: Duration in milliseconds spent in the refactoring phase after debugging.

- number_of_compiles: Minimum number of compilation passes each coder must complete before the simulation ends successfully.

- dongle_cooldown: Cooldown time in milliseconds imposed on a shared dongle after release before it can be re-acquired.

- scheduler_mode: Scheduling algorithm used for queue management (either fifo or edf).

# Resources

- **Youtube** : [ `https://www.youtube.com/watch?v=M9HHWFp84f0` - `https://www.youtube.com/watch?v=oq29KUy29iQ` - `https://www.youtube.com/watch?v=d9s_d28yJq0` ]

- **AI Usage** : I Use The AI To Help Me Find Some Deadlock's And Some Mutexes Order Fix, Also I Used Him For Knowing Something About Thread Like Why We Must Use The Pthread_Join() And Also I Used Him To Explain To Me What The Role of Every Parameter In The Functions Used [ Pthread_Create() - pthread_mutex_lock() - pthread_mutex_ulock ... ] .

# Blocking cases handled

1. **Deadlock Prevention & Coffman’s Conditions**
Deadlock occurs when threads become permanently blocked while waiting for each other to release shared resources. To eliminate deadlocks, our implementation targets and breaks the Circular Wait condition—one of Coffman’s four necessary conditions for deadlock.

- Consistent Resource Ordering: In a circular table setup, if Coder $A$ attempts to lock Dongle 1 then Dongle 2, while neighboring Coder $B$ locks Dongle 2 then Dongle 1, a cyclic lock dependency is created
- The Fix (first / second Hierarchy): Every coder strictly acquires dongles in a consistent global order based on their numerical ID:

```c
if (coder->left < coder->right)
{
    first = coder->left;
    second = coder->right;
}
else
{
    first = coder->right;
    second = coder->left;
}

pthread_mutex_lock(&first->d_mutex);
pthread_mutex_lock(&second->d_mutex);
```

By ensuring every thread always locks the smaller index first (lock(smaller) $\to$ lock(larger)), a circular dependency chain is mathematically impossible.

2. **Precise Burnout Detection:**
To maintain real-time evaluation accuracy without adding overhead to active coder routines, burnout monitoring is offloaded to a dedicated monitor_thread.

- Elapsed Time Calculation: The monitor thread continually evaluates each coder’s state by computing the exact elapsed time:$$\text{time\_since} = \text{get\_time}() - \text{coder}->\text{last\_compile\_start}$$
- Threshold Evaluation: If $\text{time\_since} > \text{time\_to\_burnout}$ while the coder is not in an active compile state, the monitor thread sets the global stop_flag, prints the exact burnout timestamp log, and unblocks all waiting threads for clean shutdown.

3. **Log Serialization:**
When hundreds of threads run concurrently, standard console output calls (printf) can interleave outputs across lines, creating garbled terminal logs.

Output Mutex (print_mutex): Every state change output (e.g., has taken a dongle, is compiling, is debugging, burned out) is wrapped inside a dedicated mutex lock


**This guarantees strictly sequential, uninterrupted log output across all concurrent threads.**

# Thread Synchronization Mechanisms

1. POSIX Primitives & Shared Resource Coordination
To coordinate execution across hundreds of concurrent coder threads and the central monitor thread, our implementation uses low-level POSIX synchronization primitives. Each primitive is assigned to protect specific shared system states:

- pthread_mutex_t (Mutual Exclusion Locks):
 1. Dongle Mutexes (d_mutex): Each shared dongle contains a dedicated mutex lock. Coders must hold both neighboring dongle mutexes before proceeding to the compilation phase.
 2. Coder Mutexes (c_mutex): Protects individual coder state variables (such as last_compile_start and compile_count) from concurrent read operations by the monitor thread while worker threads modify them.
 3. Logging Mutex (print_mutex): Wraps all terminal write calls (printf) across all threads to serialize output logs sequentially and prevent interleaved text lines.
 4. Simulation Control Mutexes (start_mutex, stop_mutex): Protect global state variables (simulation_started, stop_flag) during initialization, execution, and cleanup.
 5. pthread_cond_t (Condition Variables):
 - Start Broadcast Condition (start_cond): Used to synchronize the exact start time of all worker threads. When launched, coders enter a waiting state via pthread_cond_wait() until the main thread signals pthread_cond_broadcast(). This ensures all threads begin competing for dongles simultaneously at $t = 0\text{ ms}$.

 2. Prevention of Race Conditions
A data race occurs when two or more threads access the same memory location concurrently, and at least one access is a write.

**Protecting `last_compile_start` Updates**
The `last_compile_start` timestamp is read continuously by the `monitor_thread` to check for burnout, while being updated by the worker thread whenever a compilation begins. To prevent reading partial/corrupted memory values or stale timestamps, updates are encapsulated within the coder's private mutex:

```c
/* Worker Thread: Updating timestamp upon starting compilation */
pthread_mutex_lock(&coder->c_mutex);
coder->last_compile_start = get_time();
pthread_mutex_unlock(&coder->c_mutex);
```

**Safe Global Termination Checking**
To check whether the simulation has ended (due to burnout or quota completion), threads call a thread-safe helper function `check_stop_flag()`:

```c
int	check_stop_flag(t_sim *sim)
{
	int	status;

	pthread_mutex_lock(&sim->stop_mutex);
	status = sim->stop_flag;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (status);
}
```

3. Thread-Safe Communication: Coders $\leftrightarrow$ MonitorCommunication between coder worker threads and the monitor thread relies on shared memory state combined with non-blocking polling and condition notifications.

```
+-------------------------------------------------------+
       |                    Shared Memory                      |
       |  sim->stop_flag  |  coder->last_compile_start / state |
       +-------------------------------------------------------+
                   ^                               ^
  Writes state /   |                               |  Reads state /
  Checks stop flag |                               |  Triggers stop flag
                   v                               v
       +-----------------------+       +-----------------------+
       |   Coder Threads (N)   |       |    Monitor Thread     |
       +-----------------------+       +-----------------------+
```