# Userspace executable + kernel module names
USERSPACE_TARGET = user_rdmsr
KERNELSPACE_TARGET = kernel_rdmsr

# Use existing Makefile (from linux kernel) to build our own module
obj-m += $(KERNELSPACE_TARGET).o
KERNEL_MAKE=make -C /lib/modules/$(shell uname -r)/build M=$(PWD)

all: $(USERSPACE_TARGET) kernel

# Make sure we don't miss changes to rdmsr.h
$(USERSPACE_TARGET): $(USERSPACE_TARGET).o
$(USERSPACE_TARGET).o: $(USERSPACE_TARGET).c rdmsr.h

kernel:
	$(KERNEL_MAKE) modules

clean:
	$(RM) $(USERSPACE_TARGET).o $(USERSPACE_TARGET)
	$(KERNEL_MAKE) clean

.PHONY: all kernel clean
