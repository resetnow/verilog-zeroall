## verilog-zeroall

verilog-zeroall is a small library which uses VPI (Verilog Programming Interface) to provide a way to reset all signals in design to zero.

### Why?

Most FPGAs do not reset FFs/registers on power-up and require a dedicated reset path in code. However, there are some that reset all registers to zero on the event of POR. Therefore, the initial state of registers is not `X` but `0`. It is useful to have a system procedure that walks though the design hierarchy and resets all registers to `0`. The alternative is to specify an initial value for each `reg`.

### Usage

Connect the library to your simulator software and call `$zeroall` in your testbench:

```verilog
module tb();
/* ... */
initial
    $zeroall;
endmodule;
```

### Building

`premake` is used to build the library. You need to provide the following environment variables:

* `PLI_INCLUDE_PATH`: path where `vpi_user.h` is located
* `PLI_LIBRARY_PATH`: library path
* `PLI_LIBRARY`: name of the library to link against

Consult the manual of your simulator software to find out specific values.

*Example: building the library for Active-HDL with GNU Make and mingw-32-gcc:*

```
PLI_INCLUDE_PATH='C:\Software\Aldec\PLI\Include' \ 
PLI_LIBRARY_PATH='C:\Software\Aldec\PLI\Lib' \ 
PLI_LIBRARY='aldecpli' \
GCC_PREFIX='i686-pc-mingw32-' \ 
premake5 gmake
make
```

### Application-specific notes

Use `reimp.exe` supplied with Active-HDL (`Aldec/MINGW/bin/reimp.exe`) to generate static library file if you want to build with GNU make and GCC.

### Software support

The library should work with any IEEE 1364-2001 compatible simulator. The following combinations of compilers and simulators were tested:

Compiler  | Simulator
------------- | -------------
mingw32-gcc  | Active-HDL 10.1
VS2013  | Active-HDL 10.1

### Why `vpiBinStrVal` instead of `vpiVectorVal`?

Apparently Modelsim/Questa does not support aval/bval representation of vectors.