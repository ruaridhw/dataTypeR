#' Profile Column Data Types
#'
#' Tests each column in the data frame against
#' a number of regular expression conditions in
#' order to suggest the \strong{most likely}
#' overall data type
#'
#' @param df An R object to be coerced into a data frame
#'
#' @details
#' The regular expression tests employed search for possible
#' dates, times, integers, doubles and null values.
#' All of the various datetime formats are tested and if one
#' is found to match then the exact format code is returned.
#' If none of the above matches are found then the column is
#' assumed to be a character column.
#' @export
#' @useDynLib dataTypeR, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @importFrom magrittr %>%
#' @return
#' data.frame Columns tested for various data types and the percentage
#' likelihood of each data type tested
#'
#' @examples
#'
#' library(nycflights13)
#' dataTypeR(flights)

dataTypeR <- function(df){
  out <- cpp_dataTypeR(df) %>%
    as.data.frame %>%
    t %>%
    as.data.frame(stringsAsFactors = F)
  out[, 1:10] <- sapply(out[, 1:10], function(x) as.numeric(x))
  out[, 1:6] <- out[, 1:6] * 100
  names(out) <- c("Null", "Date", "Time", "Integer", "Double", "Character",
                  "Max Double Len", "Max Char Len", "Date Code",
                  "Perfect Type Match" , "Data Type")
  row.names(out) <- names(df)
  out
}
