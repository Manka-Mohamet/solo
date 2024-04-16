# solo

solo is a toy programming language, and is not meant for use of real programming - it only meant for education and learning purpose.

solo is dynamicly typed scripting language,
That uses somali keywords.
this project started when i was learning compiler and language design.


## Some Background

solo is written in `c`, and it compiles to custom `bytecode`,
and immediately interprets that bytecode 
in the `vm` to produce the result.
this method is easy and fast compared to traversing ASTs.



For the record there are different way of compiling code.

The first one is by compiling to `Machine Code`: `0s and 1s`

The second one is by compiling to `bytecode`: custom `1 byte` instructions.

The Third one is by compiling to `Abstract Sytax Tree (ASTs)`

And The Last one is by compiling to another language and it's called `Transcript`.



## Virtual Machine(VM)

Definition of `virtual machine` is a program that emulates 
and acts as `cpu` to trick other programs that he is the actual cpu.

There are different ways to implement a virtual machine,
but i used stack based virtual machine 



# Installation

If you want to run solo in you local machine.

First clone the repository

```sh
git clone https://github.com/Manka-Mohamet/solo.git
```

### build

When the repository is cloned or downloaded in local device, 

Then if you are using linux, windows  and macOs  you can run this command to automate and build binary files that is needed.

goto the `build/` directory and run `make` to automate and create the binary file that is needed. 

```sh
cd solo/build/
make
```

In the `bin/`  directory, it will generate binary file named `solo`. 

then you will need to add this bin folder to the path enviroment variable to access this binary everywhere.

##### In Linux & MacOs


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

> if you confussed of how to add enviromental variables you can google: `` how to add enviromental variable in Windows/Linux/MacOs``.
>
> you can also watch a youtube vedios to understand it.



# Getting Start

solo langauge you can run in two ways 


## Using REPL

You can run solo using cli terminal, 
to open the repl.

type this command to the terminal.

```sh
solo
```

This opens the solo repl in the terminal where you can execute solo code line by line like this.

```sh
>>> daabac "Hello, World";
Hello, World

>>> daabac 42 * 2 + 6;
90
```

## Using File

create file named `main.solo` the solo script file must always have `.solo` extension.

open your editor then write this script to the `main.solo`.

```py
def test(){
   daabac "Hello, world!";

}

test();

```

and then  you can run the script file using this command.

```sh
solo main.solo
```

and last it prints `Hello, world` to the terminal.



## Docs

you can read the documentation in the (docs)[].
the documentation is a tutorial that teachs programming fundamentals.

> remember this is intended for the beginers, if you know the concepts mentioned you can skipped it.




# Thanks 

I want to thank many people who helped me learn compiler and language design knowing or not knowing.

One of them is Language Engineer ``Robert Nystrom`` Who is one of the  engineers who is working at google to designed and created dart language, he also created many languages on his own.


One of The fun languages that  ``Robert Nystrom`` created is [wren](https://wren.io/).

His blog posts, papers and books he talked about different parsing techniques for generating ASTs and bytecode.


Thanks again for providing Free Educational Resources.
