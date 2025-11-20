# Custom Memory Allocator

Implementation of malloc/free in C from scratch with automatic coalescing and error detection

### Memory Layout Design

```
[Header][Payload Data][Header][Payload Data] ...
3 bytes + Variable Size, 3 bytes + Variable Size

Header Format:
[Status][Size High][Size Low]
all one byte.

Status Values:
- 'r': Reserved (allocated)
- 'f': Free (available)
-  0 : Uninitialized
```
## Build & Testing

### Prerequisites
```bash
# Required: GCC with C99 support
gcc --version  # Verify GCC installation
```

### Compilation
```bash
make           # Build allocator with comprehensive test suite
```

### Test Execution
```bash
# Run specific test cases
./memgrind 1   # Invalid free()
./memgrind 2   # Offset pointer free()  
./memgrind 3   # Double-free detection
./memgrind 4   # Rapidly cycling malloc/free of one byte
./memgrind 5   # Bulk allocation
./memgrind 6   # Random allocation/deallocation
./memgrind 7   # Stress test
./memgrind 8   # Stress test
./memgrind 9   # Coalescing verification
./memgrind 10  # Memory reuse
```

### Debug Information
Will appear as a console output, pointing to the file and specific line that caused the error

```c
// Error output example
ERROR! Trying to free something already freed.
File: test.c, line: 42
```

## Getting Started

1. **Clone and build**:
   ```bash
   git clone <repository>
   cd custom-allocator
   make
   ```
   you can use make clean if you want.

2. **Run basic functionality test**:
   ```bash
   ./memgrind 4
   ```

3. **Integrate into your project**:
   ```c
   #include "mymalloc.h"
   
   int main() {
       void *ptr = malloc(100);  // Uses custom allocator
       free(ptr);               // Uses custom deallocator
       return 0;
   }
   ```