## Posit-GCC2

This repository contains a posit-enabled GCC C compiler. A compiler option "-mposit" is added in the GCC compiler. If the option is used, the GCC compiler will treat the data types ''float" and "double" as posit format instead of IEEE-754 format. The data type "float" is viewed as posit (32,2). The data type "double" is viewed as posit(64,2). In this modification, the target platform is RISC-V (i.e., rv64imac and lp64). The modified GCC C compiler can help developers to quickly evaluate the effect of posit number without modifying the program. 

- Host machine: x86 Linux.
- Target machine: RISC-V Linux (Banana Pi BPI-F3 RISC-V development board).



### Compilation and Installation

1. ##### Build a cross compiler for RISC-V

   Use the repository at https://github.com/riscv-collab/riscv-gnu-toolchain to build a cross-compiler that supports RISC-V Linux. This toolchain allows the building of glibc, header files, qemu, and more. The 'sysroot' established during this process can be utilized for subsequent builds."

   ```
   $ git clone https://github.com/riscv/riscv-gnu-toolchain
   $ mkdir build_riscv_toolchain
   $ cd build_riscv_toolchain
   
   $ ../riscv-gnu-toolchain/configure --enable-linux --prefix=/home/yourname/riscv       --with-arch=rv64imac --enable-qemu-system --with-abi=lp64
   
   $ make linux
   ```

   

2. ##### Build a posit-enabled cross GCC C compiler

   Use RISC-V cross toolchain built at the step 1 to build a posit-enabled, cross GCC C compiler.
   
   - Build cross binutils
   
     Download the source file from https://ftp.gnu.org/gnu/binutils/ and decompress the file.
   
     ```
     $ tar -Jxvf binutils-2.43.1.tar.xz
     ```
     
     
     
     Configure binutils. Assume that the directory "sysroot" at the step 1 is located at "/home/yourname/riscv/sysroot". Please change the diretory name "/home/yourname/riscv-posit" to the directory that you want to install.
     
     ```
     $ mkdir build_binutils
     $ cd build_binutils
     $ ../binutils-2.43.1/configure --target=riscv64-unknown-linux-gnu  --with-arch=rv64imac --with-abi=lp64 --prefix=/home/yourname/riscv-posit --with-sysroot=/home/yourname/riscv/sysroot --disable-gprofng -v
     ```
     
     
     
     Compile and install the binutils.
     
     ```
     $ make
     $ make install
     ```
     
   
   
   
   - Build cross compiler
     
       Download the source file using Git. You will find a new directory "Posit-GCC2" that contains all the repository data.
       
       ```
       $ git clone https://github.com/CCU-HPCLAB/Posit-GCC2.git
       ```
       
       
       
       Add the binutils executables to the PATH. Assume that bash is the shell being used.
       
       ```
       $ export PATH=/home/yourname/riscv-posit/bin:$PATH
       ```
       
       
       
       Configure the modified GCC. The modified GCC source code is located at "Posit-GCC2/source_code/gcc-13.2.0-Posit/".
       
           $ mkdir build_gcc
           $ cd build_gcc
           $ ../Posit-GCC2/source_code/gcc-13.2.0-Posit/configure                            --prefix=/home/yourname/riscv-posit --target=riscv64-unknown-linux-gnu              --with-sysroot=/home/yourname/riscv/sysroot --with-system-zlib --disable-shared   --enable-tls  --enable-languages=c,c++  --disable-libmudflap  --disable-libssp    --disable-libquadmath  --disable-libsanitizer  --disable-nls  --disable-bootstrap --disable-default-pie  --disable-multilib  --with-abi=lp64  --with-arch=rv64imac  --with-isa-spec=20191213  'CFLAGS_FOR_TARGET=-O2 -mcmodel=medlow'  'CXXFLAGS_FOR_TARGET=-O2 -mcmodel=medlow'

      
      
      Compile and install the modified GCC.
      
       ```
       $ make
       $ make install
       ```



------

### Usage

Originally, GCC interpreted float and double data types using IEEE-754 specification. Add the option "-mposit" to enable GCC to treat float and double data types using the posit format. Additionally, the option will cause GCC to link `libgcc_posit.a` instead of the original `libgcc.a`. 

The files `libgcc_posit.a` and `libgcc.a` are located at the directory "riscv-posit/lib/gcc/riscv64-unknown-linux-gnu/13.2.0".

```
$ /home/yourname/riscv-posit/bin/riscv64-unknown-linux-gnu-gcc -mposit test.c
```

