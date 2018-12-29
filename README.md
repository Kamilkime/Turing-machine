# Turing-machine
Console Turing machine written in C

## Purpose
The machine was created as a part of **Informatics Basics** laboratories (Warsaw University of Technology, Electrical Faculty, Applied Computer Science, semester I)

## Building
`make clean`

## Usage
`./turing fileName`

## Machine file syntax
```
Symbols

Memory tape
Start index

Machine states
```

**1.** All symbols must be listed first, every symbol in the line will be counted separately

**2.** The memory tape is the next line - every symbol is counted, only previously defined symbols and # (empty memory cell) are allowed

**3.** Start index is the next line - the symbol pointed by the `^` character is the start symbol

**4.** Machine states come last - state syntax is `name C/R;M nextName`

   * **name** - state name
   * **C** - condition, symbol which will trigger the state
   * **R** - result, symbol to which the memory cell will be changed
   * **M** - move, direction of the head move after the state is executed (R for right or L for left)
   * **nextName** - name of the next state
   
**5.** There must be exactly one state named **START**, there must be at least one state in which **nextName** is **STOP**

**6.** All empty lines in the file are ignored

## Example
An example file can be found in `test/testMachine.tur`

You can test the machine using `./turing testMachine.tur`

## License
The analyser is licensed under **MIT License** - https://choosealicense.com/licenses/mit/
