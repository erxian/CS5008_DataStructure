# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans:
	pushq %rbp			# push a rbp register to your stack 
	movq  %rsp, %rbp		# assign the head of the stack to rbp register

					# (2) What is going on here
					# Ans:
	movq $1, %rax			# assign the system call number $1 to rax register  
	movq $1, %rdi			# set the first paramter 1 to rdi
	leaq .hello.str,%rsi		# set the second parmater - the address of"Hello World!\n" to rsi


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans: 
	syscall				# Which syscall is being run?
					# Ans: sys_write

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans: use printf

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans: exit(0)
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans: the size of "Hello World!\n"
