# Corewar

## Introduction

The Corewar Epitech project is about champion fighting simulation.
Pseudo-assembly programs are run in a virtual machine, and the goal is to call last the special instruction `live`.

## Installation

TODO

## Usage

A champion program is a pseudo-assembly program, with the following syntax:

```asm
# This is a comment
    .name "<champion name>"
    .comment "<champion description>"

label: # This is a label
    live r1 # This is an instruction
    ld %42, r2 # Load the direct value 42 into the register r2
    ld 42, r3 # Load the indirect value at address 42 into the register r3
    zjmp %:label # Jump to the label
```

You can then compile your champion program with the `asm` program:

```sh
asm/asm champion.s
ls -l champion.cor
```

You can then use it with the `corewar` program:

```sh
corewar/corewar champion.cor champion.cor champion2.cor
```
