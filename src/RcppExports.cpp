// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// cpp_dataTypeR
Rcpp::List cpp_dataTypeR(Rcpp::DataFrame df);
RcppExport SEXP _dataTypeR_cpp_dataTypeR(SEXP dfSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_dataTypeR(df));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_dataTypeR_cpp_dataTypeR", (DL_FUNC) &_dataTypeR_cpp_dataTypeR, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_dataTypeR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}