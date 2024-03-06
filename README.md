## sola

sola is dynamicly typed scripting language,
That uses somali keywords.

sola is short for somali language and it is project
i started when i was learning compiler and language design.


## Some Background

sola is written in `c`, and it compiles to custom `bytecode`,
and immediately executes or runs that bytecode 
in the `vm` to produce the result.



## Virtual Machine VM

definition of `virtual machine` is a program that emulates 
and acts as `cpu` to trick the programs that it's the actual cpu.

there are different ways to implement a virtual machine,
but i used stack based virtual machine 



# Installation On Linux And Windows

if you want to run in you local machine.

first clone the repository
```sh
mkdir sola/
cd sola
git clone https://github.com/Betricks/sola.git
```


### Linux

when the repository is cloned or downloaded in local device, then if you are using linux 
you can run this command to automate the compilation process.
```sh
make
```
it will generate bin directory,
the you will need to add this bin folder to the path enviroment variable
to access this binary everywhere
```sh
export PATH=$PATH:bin/
```

### Windows 

when you clonne the repository you will need to install `c compiler`,
The most famous c compiler is `gcc` i recomend you to use this one.
But you can you use your favorite compiler.

run this to generate the sola binary file
```sh
cd sola
gcc -Wall -Wextra -Werror -o sola -std=c11 src/*
```

create this folder
```sh
mkdir bin/
mv sola bin/
```
move the binary file to the bin/ directory
then add the path of this bin/ directory add in the enviromental viriables,
so that you can run the language where ever you want.


# Getting Start

sola langauge you can run in two ways 


### Using REPL

you can run sola using cli terminal, 
to open the repl type this command to the terminal.
```sh
sola
```
this opens the repl in the terminal where you can execute code line by line.


### Using File

you can write the sola code in file that has extension `.sol`
and the you can run the file using this command
```sh
sola  main.sol
sola test.sol
```

### Thanks 

i want to thank many people who helped me learn compiler and language design
one of them is ``Robert Nystrom`` who is one of the google engineers who 
designed and created `dart` language, he also created many languages on his own, one of them is [wren](https://wren.io/)
his blog post and book he talked about different parsing techniques.

Thanks again for providing free educational resources.


# End

you can learn the sytex of language in doc directory.

also if you want to contribute and have fun adding feature to this
project you are welcome contact-> [abdulrahman](abdulrahman.muhammad.omar.201@gmail.com).

in the end i am student at hormuud university foculty of computer science and information technology.
