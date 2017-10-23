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
library(dataTypeR)
dataTypeR(flights)
#>                Null Date Time   Integer Double Character Max_Double_Len
#> year              0   NA   NA 100.00000     NA         0             NA
#> month             0    0   NA 100.00000     NA         0             NA
#> day               0    0   NA 100.00000     NA         0             NA
#> dep_time          0   NA   NA 100.00000     NA         0             NA
#> sched_dep_time    0   NA   NA 100.00000     NA         0             NA
#> dep_delay         0   NA   NA  97.54882    100         0              0
#> arr_time          0   NA   NA 100.00000     NA         0             NA
#> sched_arr_time    0   NA   NA 100.00000     NA         0             NA
#> arr_delay         0   NA   NA  97.19992    100         0              0
#> carrier           0    0    0   0.00000      0       100              0
#> flight            0   NA   NA 100.00000     NA         0             NA
#> tailnum           0    0    0   0.00000      0       100              0
#> origin            0    0    0   0.00000      0       100              0
#> dest              0    0    0   0.00000      0       100              0
#> air_time          0   NA   NA  97.19992    100         0              0
#> distance          0   NA   NA 100.00000    100         0              0
#> hour              0    0   NA 100.00000    100         0              0
#> minute            0    0   NA 100.00000    100         0              0
#> time_hour         0    0   NA   0.00000    100         0              0
#>
#>                Max_Char_Len Date_Code Perfect_Type_Match     Data Type
#> year                     NA        NA                  1       integer
#> month                    NA        NA                  1       integer
#> day                      NA        NA                  1       integer
#> dep_time                 NA        NA                  1       integer
#> sched_dep_time           NA        NA                  1       integer
#> dep_delay                NA        NA                  1 decimal(18,0)
#> arr_time                 NA        NA                  1       integer
#> sched_arr_time           NA        NA                  1       integer
#> arr_delay                NA        NA                  1 decimal(18,0)
#> carrier                   2        NA                  1    varchar(2)
#> flight                   NA        NA                  1       integer
#> tailnum                   6        NA                  1    varchar(6)
#> origin                    3        NA                  1    varchar(3)
#> dest                      3        NA                  1    varchar(3)
#> air_time                 NA        NA                  1 decimal(18,0)
#> distance                 NA        NA                  1       integer
#> hour                     NA        NA                  1       integer
#> minute                   NA        NA                  1       integer
#> time_hour                NA        NA                  1 decimal(18,0)
```
