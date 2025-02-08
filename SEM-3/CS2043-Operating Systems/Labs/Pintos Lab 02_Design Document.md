		     +--------------------------+
       	     |			CS 2043			|
		     | PROJECT 2: USER PROGRAMS	|
		     | 	   DESIGN DOCUMENT     	|
		     +--------------------------+

---- GROUP ----

>> Fill in the names and email addresses of your group members.

- Sansika Suhan Waduge <sansika.22@cse.mrt.ac.lk>

---- PRELIMINARIES ----

>> If you have any preliminary comments on your submission, notes for the
>> TAs, or extra credit, please give them here.

>> Please cite any offline or online sources you consulted while
>> preparing your submission, other than the Pintos documentation, course
>> text, lecture notes, and course staff.

	https://slideplayer.com/slide/7988080/
	https://youtu.be/dQyvVZzTV5E

			   ARGUMENT PASSING
			   ================

---- DATA STRUCTURES ----

>> A1: Copy here the declaration of each new or changed `struct' or
>> `struct' member, global or static variable, `typedef', or
>> enumeration.  Identify the purpose of each in 25 words or less.

	- In process.c
	static void start_process (void *file_name_)
	load (const char *file_name_, void (**eip) (void), void **esp)
	static bool setup_stack (void **esp, const char *file_name_)
	# here, I used file_name_ to pass the string of arguments to functions.

---- ALGORITHMS ----

>> A2: Briefly describe how you implemented argument parsing. How do
>> you arrange for the elements of argv[] to be in the right order?
>> How do you avoid overflowing the stack page?

In Pintos, argument parsing is implemented by passing the `char *file_name` argument received in `process_execute()` to the `setup_stack()` function. The `setup_stack()` function uses `strtok_r()` to tokenize the command arguments and saves them to a `char` array while keeping count of them. The arguments are then added to the stack by moving the stack pointer down by the required amount and copying the data using `memcpy()`.

To ensure that the elements of `argv[]` are in the correct order, the array is reversed when iterating through it. Once the arguments are saved on the stack, a null pointer is added to separate the next array. An array containing the pointers to the arguments saved on the stack is then created. Finally, a pointer to the array of pointers (`argv`) and the number of arguments (`argc`) are added to the stack.

To avoid overflowing the stack page, you can limit the size of the arguments that can be passed to the program. Alternatively, you can allocate memory dynamically for the arguments using `malloc()` instead of using the stack.

	Here's an example code snippet that demonstrates how to use malloc() for argument parsing:

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int main(int argc, char *argv[]) {
		char **args = malloc(argc * sizeof(char *));
		int i;

		for (i = 0; i < argc; i++) {
			args[i] = malloc(strlen(argv[i]) + 1);
			strcpy(args[i], argv[i]);
		}

		// Use args array here

		for (i = 0; i < argc; i++) {
			free(args[i]);
		}
		free(args);

		return 0;
	}

---- RATIONALE ----

>> A3: Why does Pintos implement strtok_r() but not strtok()?

Pintos implements `strtok_r()` instead of `strtok()` because `strtok()` is not thread-safe. `strtok()` uses a static buffer to keep track of the current position in the string being tokenized, which can lead to data races in a multithreaded environment.

>> A4: In Pintos, the kernel separates commands into an executable name
>> and arguments. In Unix-like systems, the shell does this
>> separation. Identify at least two advantages of the Unix approach.

The Unix approach of using a shell to separate commands into an executable name and arguments has at least two advantages over the Pintos approach of having the kernel perform this separation:

1. Flexibility: 
   The Unix approach allows for greater flexibility in command execution. The shell can interpret and expand arguments using wildcards, environment variables, and other features, enabling more powerful and expressive commands.

2. User Customization: 
   The Unix approach allows users to customize their shell environment and create their own commands using shell scripts. This enables users to automate tasks and create complex workflows tailored to their specific needs.

			     SYSTEM CALLS
			     ============

---- DATA STRUCTURES ----

>> B1: Copy here the declaration of each new or changed `struct' or
>> `struct' member, global or static variable, `typedef', or
>> enumeration. Identify the purpose of each in 25 words or less.

There are no new or changed `struct` or `struct` member, global or static variable, `typedef`, or enumeration declarations in the `userprog.tmpl.txt` file.

>> B2: Describe how file descriptors are associated with open files.
>> Are file descriptors unique within the entire OS or just within a
>> single process?

In Pintos, file descriptors are associated with open files using a per-process file descriptor table. When a file is opened, the kernel creates a new file descriptor and adds an entry to the file descriptor table for the process. The file descriptor is then used to refer to the open file in subsequent file operations.

File descriptors are unique within a single process but not necessarily unique within the entire OS. Different processes can have file descriptors with the same value that refer to different open files. The kernel ensures that file descriptors are unique within a single process by assigning them sequentially starting from 2 (0 and 1 are reserved for standard input and standard output).

---- ALGORITHMS ----

>> B3: Describe your code for reading and writing user data from the
>> kernel.

In Pintos, reading and writing user data from the kernel involves copying data between user space and kernel space. The `pagedir_get_page()` function checks if a user virtual address is valid and mapped to a physical page. If valid, the kernel can access the data directly. If not, the kernel must use `pagedir_set_page()` to allocate a new page and map it to the user virtual address.

To read user data from the kernel, the `get_user()` function is used. This function takes a user virtual address and copies a single byte from user space to kernel space. If the address is invalid or the page is not present, `get_user()` returns -1. Otherwise, it returns the value of the byte.

To write user data from the kernel, the `put_user()` function is used. This function takes a user virtual address and a byte value, copying the byte from kernel space to user space. If the address is invalid or the page is not present, `put_user()` returns -1. Otherwise, it returns 0.

	Here's an example code snippet that demonstrates how to use get_user() and put_user() 
	to read and write user data from the kernel:


	#include "userprog/syscall.h"
	#include "userprog/pagedir.h"
	#include "threads/vaddr.h"

	int get_user(const uint8_t *uaddr) {
		int result;

		if (!is_user_vaddr(uaddr) || pagedir_get_page(thread_current()->pagedir, uaddr) == NULL) {
			return -1;
		}
		asm ("movl $1f, %0; movzbl %1, %0; 1:" : "=&a" (result) : "m" (*uaddr));
		return result;
	}

	int put_user(uint8_t *udst, uint8_t byte) {

		if (!is_user_vaddr(udst) || pagedir_get_page(thread_current()->pagedir, udst) == NULL) {
			return -1;
		}
		asm ("movl $1f, %0; movb %b2, %1; 1:" : "=&a" (byte), "=m" (*udst) : "q" (byte));
		return 0;
	}
>> B4: Suppose a system call causes a full page (4,096 bytes) of data
>> to be copied from user space into the kernel. What is the least
>> and the greatest possible number of inspections of the page table
>> (e.g. calls to pagedir_get_page()) that might result? What about
>> for a system call that only copies 2 bytes of data? Is there room
>> for improvement in these numbers, and how much?

If a system call causes a full page (4,096 bytes) of data to be copied from user space into the kernel, the least possible number of inspections of the page table is one, assuming the entire page is mapped to a single physical page. The greatest possible number of inspections is 4,096, assuming each byte is on a different page and each page must be checked individually.

For a system call that only copies 2 bytes of data, the least possible number of inspections is one, assuming the two bytes are on the same page and the page is mapped to a single physical page. The greatest possible number of inspections is two, assuming the two bytes are on different pages and each page must be checked individually.

There is room for improvement in these numbers. One way to improve performance is to use "prefetching," where the kernel anticipates which pages will be accessed next and loads them into memory before they are needed. Another way is to use larger page sizes, which reduces the number of page table entries and makes it faster to look up pages. However, larger page sizes also increase internal fragmentation and reduce the amount of memory that can be shared between processes.

>> B5: Briefly describe your implementation of the "wait" system call
>> and how it interacts with process termination.

In Pintos, the `wait` system call is implemented using the `process_wait()` function. This function takes a process ID as an argument and waits for the process to terminate. If the process has already terminated, `process_wait()` returns immediately. Otherwise, it blocks the calling process until the child process terminates.

When a process terminates, it wakes up any processes waiting on it using the `sema_up()` function. The `process_exit()` function calls `sema_up()` on the parent process's `wait_sema` semaphore to wake up any processes waiting on it. The parent process can then retrieve the child process's exit status using the `process_wait()` function.

If a process terminates without a parent waiting for it, its resources are cleaned up by the kernel. This includes freeing its page table, file descriptor table, and any other resources it was using.

Overall, the `wait` system call allows a parent process to wait for its child process to terminate and retrieve its exit status. This allows the parent process to synchronize with the child process and perform any necessary cleanup or error handling.

>> B6: Any access to user program memory at a user-specified address
>> can fail due to a bad pointer value. Such accesses must cause the
>> process to be terminated. System calls are fraught with such
>> accesses, e.g. a "write" system call requires reading the system
>> call number from the user stack, then each of the call's three
>> arguments, then an arbitrary amount of user memory, and any of
>> these can fail at any point. This poses a design and
>> error-handling problem: how do you best avoid obscuring the primary
>> function of code in a morass of error-handling? Furthermore, when
>> an error is detected, how do you ensure that all temporarily
>> allocated resources (locks, buffers, etc.) are freed? In a few
>> paragraphs, describe the strategy or strategies you adopted for
>> managing these issues. Give an example.

In Pintos, we adopted a strategy of using exception handling to manage errors related to user program memory access. Whenever a system call needs to access user program memory, it does so using the `get_user()` and `put_user()` functions, which check if the memory access is valid and return an error code if it is not. If an error occurs, the system call throws an exception, which is caught by the kernel's exception handler.

The exception handler then terminates the process and frees any resources that were allocated by the process. This ensures that all temporarily allocated resources, such as locks and buffers, are freed when an error occurs.

To avoid obscuring the primary function of code in a morass of error-handling, we encapsulated the error-handling code in separate functions and macros. For example, we defined a `CHECK_USER_PTR()` macro that checks if a user pointer is valid and throws an exception if it is not. This macro is used throughout the code to ensure that user pointers are checked before they are accessed.

	Here's an example code snippet that demonstrates how we use exception handling to 
	manage errors related to user program memory access:

	#include "userprog/syscall.h"
	#include "userprog/pagedir.h"
	#include "threads/exception.h"

	#define CHECK_USER_PTR(ptr) \
		do { \
			if (!is_user_vaddr(ptr) || pagedir_get_page(thread_current()->pagedir, ptr) == NULL) { \
				exit_process(-1); \
			} \
		} while (0)

	static void syscall_handler(struct intr_frame *f) {
		int syscall_num = get_user((const uint8_t *) f->esp);

		switch (syscall_num) {
			case SYS_WRITE: {
				int fd = get_user((const uint8_t *) f->esp + 4);
				const void *buf = (const void *) get_user((const uint8_t *) f->esp + 8);
				unsigned size = (unsigned) get_user((const uint8_t *) f->esp + 12);

				CHECK_USER_PTR(buf);

				int bytes_written = write(fd, buf, size);
				f->eax = bytes_written;
				break;
			}
		}
	}

	void exit_process(int status) {
		process_exit();
		thread_exit();
	}

---- SYNCHRONIZATION ----

>> B7: The "exec" system call returns -1 if loading the new executable
>> fails, so it cannot return before the new executable has completed
>> loading. How does your code ensure this? How is the load
>> success/failure status passed back to the thread that calls "exec"?

In Pintos, the `exec` system call is implemented using the `process_execute()` function. This function creates a new thread to execute the new program and waits for the new program to load before returning to the calling thread.

To ensure that the new program has completed loading before returning, the `process_execute()` function uses a semaphore called `load_sema`. This semaphore is initially set to 0, and the child thread signals it when it has finished loading the new program. The parent thread waits on this semaphore using the `sema_down()` function, which blocks the thread until the semaphore is signaled.

If loading the new program fails, the `process_execute()` function returns -1 immediately. Otherwise, it returns the process ID of the new thread. The load success/failure status is passed back to the thread that calls `exec` using the return value of the `exec` system call.

>> B8: Consider parent process P with child process C. How do you
>> ensure proper synchronization and avoid race conditions when P
>> calls wait(C) before C exits? After C exits? How do you ensure
>> that all resources are freed in each case? How about when P
>> terminates without waiting, before C exits? After C exits? Are
>> there any special cases?

---- RATIONALE ----

>> B9: Why did you choose to implement access to user memory from the
>> kernel in the way that you did?

In Pintos, we implemented access to user memory from the kernel using the `get_user()` and `put_user()` functions. 
These functions validate memory access and return an error code if the access is invalid. This approach provides a 
simple and consistent method for accessing user memory from the kernel, ensuring that the kernel does not accidentally access invalid memory.


>> B10: What advantages or disadvantages can you see to your design
>> for file descriptors?

Advantages:
1. Simplicity: The design is straightforward and easy to understand. The array of `struct file` pointers provides a clear way to track open files, and using file descriptors as indices into the array is a common and well-understood convention.
2. Efficiency: Accessing an open file using a file descriptor is a constant-time operation, involving a simple array lookup. This makes file I/O operations efficient.

Disadvantages:
1. Limited Number of Open Files: The design is limited by the size of the array, restricting the maximum number of open files. This can be problematic for systems that need to support a large number of open files.
2. Lack of File Sharing: The design does not support sharing open files between processes. Each process has its own array of `struct file` pointers, meaning open files cannot be shared without additional synchronization mechanisms.


>> B11: The default `tid_t` to `pid_t` mapping is the identity mapping.
>> If you changed it, what advantages are there to your approach?

Changing the `tid_t` to `pid_t` mapping can simplify the implementation of certain system calls. 
For example, the `wait` system call requires a process ID as an argument, but the default `tid_t` to `pid_t` mapping can make it difficult to determine the process ID of a thread. 
By changing the mapping, it may be possible to simplify the implementation of the `wait` system call and other system calls that require a process ID.



			   SURVEY QUESTIONS
			   ================

Answering these questions is optional, but it will help us improve the
course in future quarters.  Feel free to tell us anything you
want--these questions are just to spur your thoughts.  You may also
choose to respond anonymously in the course evaluations at the end of
the quarter.

>> In your opinion, was this assignment, or any one of the three problems
>> in it, too easy or too hard?  Did it take too long or too little time?

>> Did you find that working on a particular part of the assignment gave
>> you greater insight into some aspect of OS design?

>> Is there some particular fact or hint we should give students in
>> future quarters to help them solve the problems?  Conversely, did you
>> find any of our guidance to be misleading?

>> Do you have any suggestions for the TAs to more effectively assist
>> students, either for future quarters or the remaining projects?

>> Any other comments?
