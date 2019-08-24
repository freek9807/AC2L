# AC2L ( Another Compiler to Lisp )

C Compiler using Bison that translate to Lisp .

## Getting Started

These instructions will get you a copy of the project and allow you to run on your local machine for development and testing purposes.

### Prerequisites

Following packages are needed ,so, if you run on Ubuntu try :

```
sudo apt-get update
sudo apt-get install flex
sudo apt-get install bison
sudo apt-get install sbcl
```

## Running the tests

The Make command to run the project are :

```
# Compile the Bison code and the generated C code .
# Now you can write C code and it'll be automatically translate in Lisp
make

# Use FILE (in src folder) on input to generate Lisp code .
# If FILE is not set , it will use src/file.txt
make tol FILE=foo

# Use FILE (in src folder) on input to generate Lisp code in OUTPUT (in out folder) .
# If FILE is not set , it will use src/file.txt
# If OUTPUT is not set , it will use out/output.txt
make out FILE=foo OUTPUT=bar
```

## Project Structure


```
    .
    ├── src                   # It contains .c file to generate the AST (ast.c) and translate it to LISP (lisp.c)
    ├── test                  # It contains some .c testing programs
    ├── AC2L.y                # Parser file
    ├── ac2l.lex              # Lexer file
    ├── Makefile
    ├── LICENSE
    └── README.md
```


## Built With

* [GNU Bison](https://www.gnu.org/) - The parser generator used

## Authors

* **Federico Pennino** - *Developer* - [Freek.io](https://freek.io/)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
