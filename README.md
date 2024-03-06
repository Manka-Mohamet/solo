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

Definition of `virtual machine` is a program that emulates 
and acts as `cpu` to trick the programs that it's the actual cpu.

There are different ways to implement a virtual machine,
but i used stack based virtual machine 



# Installation

If you want to run sola in you local machine.

First clone the repository
```sh
mkdir sola/
cd sola
git clone https://github.com/Betricks/sola.git
```


### Linux

When the repository is cloned or downloaded in local device, 

Then if you are using linux 
you can run this command to automate the compilation process.

```sh
make
```

It will generate bin directory,
the you will need to add this bin folder to the path enviroment variable
to access this binary everywhere
```sh
export PATH=$PATH:bin/
```

### Windows 

When you clonne the repository you will need to install `c compiler`,
The most famous c compiler is `gcc` i recomend you to use this one.
But you can you use your favorite compiler.

Run this to generate the sola binary file

```sh
cd sola
gcc -Wall -Wextra -Werror -o sola -std=c11 src/*
```

create this folder
```sh
mkdir bin/
mv sola bin/
```
Move the binary file to the bin/ directory
then add the path of this bin/ directory add in the enviromental viriables,
so that you can run the language where ever you want.


# Getting Start

sola langauge you can run in two ways 


### Using REPL

You can run sola using cli terminal, 
to open the repl type this command to the terminal.

```sh
sola
```
This opens the repl in the terminal where you can execute sola code line by line.


### Using File

You can write the sola code in file that has extension `.sol`
and the you can run the file using this command

```sh
sola  main.sol
sola test.sol
```

### Thanks 

I want to thank many people who helped me learn compiler and language design knowing or not knowing.

one of them is ``Robert Nystrom`` who is one of the google engineers who 
designed and created `dart` language, he also created many languages on his own, 

One of fun languages that he create is [wren](https://wren.io/)

His blog post and book he talked about different parsing techniques for generating ASTs and bytecode.

Thanks again for providing Free Educational Resources.


# End

You can learn the syntex of The language in doc/ directory.

Also if you want to contribute and have fun adding features to this
project you are welcome contact [A/Man](https://wa.link/0gaepx)
and read the [contribute](https://github.com/Betricks/sola/blob/main/CONTRIBUTING.md)

In the End i am student at `Hormuud university` foculty of computer science and information technology.
