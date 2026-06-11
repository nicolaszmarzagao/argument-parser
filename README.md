# argument-parser

A small command-line argument parser written in C.

This project is mostly for **personal use and education**. The goal is to build a minimal CLI parser from scratch to better understand how argument parsing, validation, and simple library design work in C.

The name `argument-parser` is temporary and may change later.

## Goal

The main goal is to create a small but usable parser that can:

* create a parser configuration
* register flags
* parse `argc` and `argv`
* store parsed flag values
* validate common user input errors
* retrieve values from parsed flags

## TODO List

* Create parser config

  * [x] name
  * [x] version
  * [x] description

* Register flags

  * [x] flag name
  * [x] type
  * [x] required/optional

* [x] Parse `argc` / `argv`

* [x] Store parsed flag values

* Validate errors #2

  * [ ] unknown flag
  * [ ] missing value
  * [ ] invalid type
  * [ ] missing required flag

* [X] Retrieve values #1

* [ ] Return error codes

* [ ] Print basic error/help message

## Planned Features

The first version will stay intentionally small. More advanced CLI features may be added later, such as:

* short flags
* default values
* automatic help output
* positional arguments
* `--flag=value` syntax
* subcommands
