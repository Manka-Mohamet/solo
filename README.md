# sola

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
gcc -O3  -Wall -Wextra -Werror -o sola -std=c11 src/*
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


## Using REPL

You can run sola using cli terminal, 
to open the repl type this command to the terminal.

```sh
sola
```
This opens the repl in the terminal where you can execute sola code line by line.

## Sola Script Example

create file named `main.sola` the sola script file must always have `.sola` extension.
open your fav editor then write this script to the `main.sola`

```py
def test_sola(){
   celi "Hello, world!";

}


daabac test_sola();

```

## Using File


and then  you can run the script file using this command.

```sh
sola  main.sola
```

and last it prints `Hello, world` to the terminal.



## Docs

the can read the documentation in the (docs)[].
the documentation is a tutorial that teachs the fundamental programming langauges, remember this is intended for the beginers and the slow leaner.




# Thanks 

I want to thank many people who helped me learn compiler and language design knowing or not knowing.

One of them is Language Engineer ``Robert Nystrom`` Who is one of the  engineers who is working at google to designed and created `dart` language, he also created many languages on his own, 

One of The fun languages that  ``Robert Nystrom`` created is [wren](https://wren.io/).

His blog posts, papers and books he talked about different parsing techniques for generating ASTs and bytecode.

Thanks again for providing Free Educational Resources.



# End

Also if you want to contribute and have fun adding features to this
project you are welcome contact [A/Man](https://wa.link/0gaepx)
and read [contribute guide](./CONTRIBUTING.md).
