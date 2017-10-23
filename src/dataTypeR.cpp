#include <vector>
#include <iterator>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <cstdlib>

#include <Rcpp.h>
#include <dataTypeR.h>

#define num_tests 9

int cpp_samplesize(int n){
  Rcpp::NumericVector x_numer;
  Rcpp::NumericVector x_denom;
  Rcpp::NumericVector p(1, 0.99);
  Rcpp::NumericVector x;

  double error = 0.01;
  double prop  = 0.5;
  x_numer   = Rcpp::qchisq(p, 1) * n * prop * (1 - prop);
  x_denom = (error * error * (n-1)) + (Rcpp::qchisq(p, 1) * prop * (1 - prop));
  x = ceil(x_numer / x_denom);
  std::vector<int> x_int = Rcpp::as<std::vector<int> >(x);
  return x_int[0];
}

template<class bidiiter>
bidiiter random_unique(bidiiter begin, bidiiter end, size_t num_random){
  size_t left = std::distance(begin, end);
  while(num_random--){
    bidiiter r = begin;
    std::advance(r, rand()%left);
    std::swap(*begin, *r);
    ++begin;
    --left;
  }
  return begin;
}

Rcpp::IntegerVector cpp_selectsample(int pop_size, int sample_size){
  std::vector<int> a(pop_size);
  Rcpp::IntegerVector b(sample_size);
  for(int i=0; i<pop_size; ++i){
    a[i] = i;
  }
  random_unique(a.begin(), a.end(), sample_size);
  for(int i=0; i<sample_size; ++i){
    b[i] = a[i];
  }
  return b;
}

std::vector<std::string> subsetCharVec(std::vector<std::string>& x, Rcpp::IntegerVector& index){
  int n = index.size();
  std::vector<std::string> out(n);
  for(int i=0; i<n; i++){
    out[i] = x.at(index[i]);
  }
  return out;
}

int regex_all_dates(std::vector<std::string>& cpp_data, int n){
  // Input:  pointer to std::vector<std::string>
  //         1000 values selected randomly from cpp_data
  // Output: regular expression corresponding to the date_type[j]
  //         with the greatest proportion of matches

  Rcpp::NumericVector date_tests(NUM_DATES);
  double count_succeed;

  for(unsigned int j=0; j<NUM_DATES; j++){
    count_succeed = 0;
    for(int i=0; i<n; i++){
      count_succeed += boost::regex_match(cpp_data[i], RE_DATE_TYPES[j]);
    }
    date_tests[j] = count_succeed;
  }

  int best_index = 0;
  best_index = Rcpp::which_max(date_tests);

  return (date_tests[best_index] == 0) ? 999 : best_index;

  // Loop through NumericalMatrix setting (i,j) equal to TRUE
  // if a match is found in cpp_data[i] for date_type[j]

  // ColSums

  // which.max to find j

  // Lookup j in date_type

  // Return regular expression corresponding to j

  // return "null";
}


Rcpp::CharacterVector determine_data_type(Rcpp::NumericVector out) {
  Rcpp::CharacterVector res(2);
  std::string data_type = "null";
  std::string perfect_match = "0";
  double max_type_prop = out[0];

  if(out[1] > max_type_prop){
    data_type = "date " + boost::lexical_cast<std::string>(out[8]);
    max_type_prop = out[1];
  } if(out[2] > max_type_prop){
    data_type = "time";
    max_type_prop = out[2];
  } if(out[3] > max_type_prop){
    data_type = "integer";
    max_type_prop = out[3];
  } if(out[4] > max_type_prop){
    data_type = "decimal(18," + boost::lexical_cast<std::string>(out[6]) + ")";
    max_type_prop = out[4];
  } if(out[5] > max_type_prop){
    data_type = "varchar(" + boost::lexical_cast<std::string>(out[7]) + ")";
    max_type_prop = out[5];
  }

  if(max_type_prop == 1.0){
    perfect_match = "1";
  }

  res[0] = perfect_match;
  res[1] = data_type;

  return res;
}

Rcpp::CharacterVector regex_routine(SEXP input_data,
                                    std::string data_class){
  // Create std copy of Rcpp data type for regex tests
  Rcpp::CharacterVector data(input_data);
  std::vector<std::string> cpp_data = Rcpp::as<std::vector<std::string> >(data);
  int n = cpp_data.size();

  // Test if data is entirely NA
  Rcpp::LogicalVector test_null = is_na(Rcpp::as<Rcpp::CharacterVector>(data)); // MIGHT FAIL
  double prop_null = (Rcpp::sum(test_null) / n);

  // If so, return without proceeding further
  Rcpp::NumericVector out(num_tests, NA_REAL);
  Rcpp::CharacterVector res(num_tests + 2, NA_STRING);
  if(prop_null == 100.0){
    res[num_tests] = "null";
    return res;
  }

  // Determine samplesize m
  int m = cpp_samplesize(n);

  // Declare indices and cpp_data_small
  Rcpp::IntegerVector indices(m);
  std::vector<std::string> cpp_data_small(m);

  // Subset cpp_data to cpp_data_small of size m
  indices = cpp_selectsample(n, m);
  cpp_data_small = subsetCharVec(cpp_data, indices);

  // Declare output proportions
  double small_prop_double    = NA_REAL;
  double small_prop_int       = NA_REAL;
  double small_prop_date_best = NA_REAL;
  double small_prop_time      = NA_REAL;

  // Declare calculation flags
  bool docalc_date_best     = 0;
  bool docalc_time          = 0;
  bool docalc_int           = 0;
  bool docalc_double        = 0;
  bool docalc_double_length = 0;
  bool docalc_char_length   = 0;

  if(data_class == "numeric"){
    // Set prop_double = 100%
    // for each cell:
    // // Search for integer
    // // Search for date_int
    // // Accumulate max_double_length
    // return

    small_prop_double = 1.0;

    docalc_int = 1;
    // docalc_date_int = 1;
    docalc_double_length = 1.0;
  }

  else if(data_class == "integer"){
    // Set prop_int = 100%
    // for each cell:
    // // Search for date_int
    // return

    small_prop_int = 1;

    // docalc_date_int = 1;
  }


  else {
    // for each cell:
    // // Search for double
    // // Search for int
    // // Search for date_best
    // // Search for time
    // // Accumulate max_double_length
    // // Accumulate max_char_length
    // return

    docalc_date_best     = 1;
    docalc_time          = 1;
    docalc_int           = 1;
    docalc_double        = 1;
    docalc_double_length = 1;
    docalc_char_length   = 1;
    // docalc_date_int = 0;
  }

  // START DATE TESTS

  // Declare indices and cpp_data_small
  int num_test_dates = 500;
  num_test_dates = std::min(n, num_test_dates);
  Rcpp::IntegerVector indices_dates(num_test_dates);
  std::vector<std::string> cpp_data_dates(num_test_dates);

  // Subset cpp_data to cpp_data_small of size m
  indices_dates = cpp_selectsample(n, num_test_dates);
  cpp_data_dates = subsetCharVec(cpp_data, indices_dates);

  int best_date_index = 0;
  int date_code;
  boost::regex re_date_best;
  best_date_index = regex_all_dates(cpp_data_dates, cpp_data_dates.size());
  if(best_date_index == 999){
    docalc_date_best = 0;
    small_prop_date_best = 0.0;
    date_code = -1;
  } else {
    re_date_best = RE_DATE_TYPES[best_date_index];
    date_code = RE_DATE_CODES[best_date_index];
  }

  // END DATE TESTS

  // Match cpp_data_small

  double count_test_date_best = 0;
  double count_test_time = 0;
  double count_test_double = 0;
  double count_test_int = 0;

  for(int i=0; i<m; i++){
    count_test_date_best += (docalc_date_best ? boost::regex_match(cpp_data_small[i], re_date_best) : 0);
    count_test_time      += (docalc_time      ? boost::regex_match(cpp_data_small[i], re_time) : 0);
    count_test_int       += (docalc_int       ? boost::regex_match(cpp_data_small[i], re_integer) : 0);
    count_test_double    += (docalc_double    ? boost::regex_match(cpp_data_small[i], re_double) : 0);
  }

  // Significance testing of small_test vectors and
  // select relevant tests to run on entire vector

  double signif_match = 0.5;

  small_prop_date_best = (docalc_date_best ? (count_test_date_best / m) : small_prop_date_best);
  small_prop_time      = (docalc_time      ? (count_test_time / m)      : small_prop_time);
  small_prop_int       = (docalc_int       ? (count_test_int / m)       : small_prop_int);
  small_prop_double    = (docalc_double    ? (count_test_double / m)    : small_prop_double);

  docalc_date_best = (docalc_date_best ? (small_prop_date_best > signif_match) : 0);
  docalc_time      = (docalc_time      ? (small_prop_time      > signif_match) : 0);
  docalc_int       = (docalc_int       ? (small_prop_int       > signif_match) : 0);
  docalc_double    = (docalc_double    ? (small_prop_double    > signif_match) : 0);

  count_test_date_best = 0;
  count_test_time = 0;
  count_test_double = 0;
  count_test_int = 0;
  int double_length = 0;
  int char_length = 0;
  int max_double_length = 0;
  int max_char_length = 0;
  boost::match_results<std::string::const_iterator> what;

  for(int i=0; i<n; i++){
    if(docalc_date_best) {count_test_date_best += boost::regex_match(cpp_data[i], re_date_best);}
    if(docalc_time)      {count_test_time      += boost::regex_match(cpp_data[i], re_time);}
    if(docalc_int)       {count_test_int       += boost::regex_match(cpp_data[i], re_integer);}
    if(docalc_double)    {count_test_double    += boost::regex_match(cpp_data[i], re_double);}

    // Extremely slow implementation
    // double_length[i]   = length_of_match(cpp_data[i], "\\.\\d+") - 1;
    if(docalc_double_length) {
      double_length = (regex_search(cpp_data[i], what, re_double_length)) ? what.length() - 1 : 0;
      max_double_length = (double_length > max_double_length) ? double_length : max_double_length;
    }

    if(docalc_char_length){
      char_length = cpp_data[i].length();
      max_char_length = (char_length > max_char_length) ? char_length : max_char_length;
    }
  }

  double prop_date_best = (docalc_date_best ? (count_test_date_best / n) : small_prop_date_best);
  double prop_time      = (docalc_time      ? (count_test_time / n)      : small_prop_time);
  double prop_int       = (docalc_int       ? (count_test_int / n)       : small_prop_int);
  double prop_double    = (docalc_double    ? (count_test_double / n)    : small_prop_double);

  // int max_double_length = max(double_length);
  // int max_char_length   = max(char_length);

  std::vector<double> props(4);
  props[0] = (R_IsNA(prop_date_best) ? 0.0 : prop_date_best);
  props[1] = (R_IsNA(prop_time)      ? 0.0 : prop_time);
  props[2] = (R_IsNA(prop_int)       ? 0.0 : prop_int);
  props[3] = (R_IsNA(prop_double)    ? 0.0 : prop_double);

  double prop_char = (prop_null < 1.0 ? 1.0 - *std::max_element(props.begin(), props.end()) : 0.0);

  out[0] = prop_null;
  out[1] = (docalc_date_best     ? prop_date_best : small_prop_date_best);
  out[2] = (docalc_time          ? prop_time : small_prop_time);
  out[3] = (docalc_int           ? prop_int : small_prop_int);
  out[4] = (docalc_double        ? prop_double : small_prop_double);
  out[5] = prop_char;
  out[6] = (docalc_double_length ? max_double_length : NA_REAL);
  out[7] = (docalc_char_length   ? max_char_length : NA_REAL);
  out[8] = (docalc_date_best     ? date_code : NA_REAL);

  res = out;
  Rcpp::CharacterVector data_type(2);
  data_type = determine_data_type(out);
  res.push_back(data_type[0]);
  res.push_back(data_type[1]);

  return res;
}


// [[Rcpp::export]]
Rcpp::List cpp_dataTypeR(Rcpp::DataFrame df) {

  // create the dataframe
  Rcpp::List out_df;

  int num_cols = df.length();

  for(int i=0; i<num_cols; i++){
    SEXP col = df[i];
    std::string colname = "V" + boost::lexical_cast<std::string>(i+1);
    if (Rcpp::is<Rcpp::CharacterVector>(col)) {
      out_df.push_back(regex_routine(col, "character"), colname);
      // cppTest_impl<STRSXP>(col, "character");
    } else if (Rcpp::is<Rcpp::IntegerVector>(col)) {
      out_df.push_back(regex_routine(col, "integer"), colname); // cppTest_impl<INTSXP>(col, "integer");
    } else if (Rcpp::is<Rcpp::NumericVector>(col)) {
      out_df.push_back(regex_routine(col, "numeric"), colname); // cppTest_impl<REALSXP>(col, "numeric");
    } else if (Rcpp::is<Rcpp::LogicalVector>(col)) {
      out_df.push_back(regex_routine(col, "logical"), colname); // cppTest_impl<LGLSXP>(col, "logical");
    } else {
      Rcpp::stop("Unsupported Type");
      // exception for class == POSIXct, POSIXt
    }
  }

  // out_df.attr("class") = "data.frame";
  // Rcpp::DataFrame df_final = Rcpp::DataFrame::create(out_df);
  return out_df;
}
