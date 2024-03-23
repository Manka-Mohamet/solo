# solo

solo is dynamicly typed scripting language,
That uses somali keywords.
this project started when i was learning compiler and language design.


## Some Background

solo is written in `c`, and it compiles to custom `bytecode`,
and immediately executes or runs that bytecode 
in the `vm` to produce the result.



## Virtual Machine(VM)

Definition of `virtual machine` is a program that emulates 
and acts as `cpu` to trick other programs that he is the actual cpu.

There are different ways to implement a virtual machine,
but i used stack based virtual machine 



# Installation

If you want to run solo in you local machine.

First clone the repository

```sh
mkdir sola/
cd solo
git clone https://github.com/Betricks/sola.git
```


### build

When the repository is cloned or downloaded in local device, 

Then if you are using linux, windows  and macOs  you can run this command to automate and build binary files that is needed.

```sh
make
```

It will generate `bin/`  directory,
then you will need to add this bin folder to the path enviroment variable to access this binary everywhere.

##### in linux

```sh
export PATH=$PATH:bin/
```
##### in windows

1. click the Start menu.

1. click Properties, In the System Properties dialog box, 

1. click the Advanced tab.

1. click Environment Variables.
In the top list, scroll down to the PATH variable, select it, 

1. and click New and enter PATH for the Variable Name.

1. click OK to close each dialog box.

### Executing on your own

if you want to excute the c files on your own. 

there are many c compiler you can use the build the binary file.

the two most used c compilers are `llvm` and `gcc`.

You will need to install `c compiler`,
My favourite c compiler is `gcc` i recomend you to use this one.
But you can you use what compiler that you like.

Run this to generate the solo binary file

```sh
cd solo
gcc -O3  -Wall -Wextra -Werror -ggdb -o solo  src/*
```

create this folder

```sh
mkdir bin/
mv solo bin/
```

Move the binary file to the `bin/` directory
then add the path of this `bin/` directory add in the enviromental viriables, so that you can run the language where ever you want.


# Getting Start

solo langauge you can run in two ways 


## Using REPL

You can run solo using cli terminal, 
to open the repl.

type this command to the terminal.

```sh
solo
```

This opens the solo repl in the terminal where you can execute solo code line by line.

## Solo Script

create file named `main.solo` the solo script file must always have `.solo` extension.

open your fav editor then write this script to the `main.solo`.

```py
def test(){
   daabac "Hello, world!";

}

test();

```

## Using File

and then  you can run the script file using this command.

```sh
solo main.solo
```

and last it prints `Hello,  world` to the terminal.



## Docs

you can read the documentation in the (docs)[].
the documentation is a tutorial that teachs the fundamental programming langauges, remember this is intended for the beginers, if you know the concepts mentioned you can skipped it.




# Thanks 

I want to thank many people who helped me learn compiler and language design knowing or not knowing.

One of them is Language Engineer ``Robert Nystrom`` Who is one of the  engineers who is working at google to designed and created dart language, he also created many languages on his own, 

One of The fun languages that  ``Robert Nystrom`` created is [wren](https://wren.io/).

His blog posts, papers and books he talked about different parsing techniques for generating ASTs and bytecode.

Thanks again for providing Free Educational Resources.



# End

Also if you want to contribute and have fun adding features to this
project you are welcome  contact [A/Man](https://wa.link/0gaepx)
and read [contribute guide](./CONTRIBUTING.md).
