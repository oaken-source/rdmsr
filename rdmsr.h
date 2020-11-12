#ifndef _RDMSR_H
#define _RDMSR_H

/* Find a header file with uint64_t */
#ifdef __KERNEL__
#  include <linux/types.h>
#else
#  include <stdint.h>
#endif

#if __x86_64

/* Execute privileged rdmsr instruction via inline-assembly 

   This instruction reads the "Model Specific Register" on x86.
	Not all register ids are present on all CPUs.
 */
static inline uint64_t __assembly_rdmsr(uint64_t msr_id)
{
	uint32_t low, high;
	asm volatile ("rdmsr"
	              : "=a"(low), "=d"(high)
	              : "c"(msr_id));
	return ((uint64_t) high << 32) | low;
}

/* Interesting things to find in Intel Core-MSRs:

	MSR_SYSCALLTABLE_COMPAT: Where is my syscall table?
		check: $ sudo grep entry_SYSCALL_compat /proc/kallsyms
	
	MSR_MICROCODE_VERSION: Which patchlevel has my CPU microcode?
		(print as hex number, drop lower 8 digits (32 bytes))
		check: $ grep microcode /proc/cpuinfo

	MSR_TIMESTAMP_COUNTER: How many cycles have passed?
		check: Run, wait, run again.

	For more, read: http://sandpile.org/x86/msr.htm (outdated, and model-specific)
*/
#define MSR_MICROCODE_VERSION   0x0000008b 
#define MSR_SYSCALLTABLE_COMPAT 0xC0000083
#define MSR_TIMESTAMP_COUNTER   0x00000010

#else
#  error "I can only run the rdmsr instruction on x86_64 processors"
#endif

#endif /* _RDMSR_H */

