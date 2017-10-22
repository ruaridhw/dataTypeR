# dataTypeR

[![Travis build status](https://travis-ci.org/ruaridhw/dataTypeR.svg?branch=master)](https://travis-ci.org/ruaridhw/dataTypeR)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/ruaridhw/dataTypeR?branch=master&svg=true)](https://ci.appveyor.com/project/ruaridhw/dataTypeR)

Check your data types; they're not what you think they are.

## Motivation

When learning and studying data science techniques, many of the datasets
utilised are pre-pepared, cleaned and tidy. Unfortunately, in the real
world this is not the case. In fact, it is incredibly lucky if datasets
from clients' systems are well-formed and as expected.

This package provides a series of functions for profiling messy data,
primarily focussed around honing in on 1-in-a-million cells causing
headaches for type casting and/or DBMS upload.

There are already a number of existing packages that provide similar
functionality in profiling and summarising columns however *dataTypeR*
sets out to differentiate itself on two fronts:

* When dealing with very wide datasets of +1-10million rows in memory,
speed matters
* The in-built R type-checks return unexpected results and are
sometimes counterintuitive

```r
is.integer(1)
#> [1] FALSE
```

This package tries to address these issues by implementing its core
functions in C++ and relying on regular expression pattern matching
to test whether or not a cell *looks* like a particular data-type,
not whether or not it can be coerced into one.

## Installation

Install the development version from GitHub:

```r
# install.packages("devtools")
devtools::install_github("ruaridhw/dataTypeR")
```

## Usage

```r
library(nycflights13)
dataTypeR(flights)
```
