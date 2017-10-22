#ifndef __DATATYPER_H__
#define __DATATYPER_H__

#include <boost/regex.hpp>
#include <boost/tuple/tuple.hpp>

const boost::regex re_double_length("\\.\\d+");

// Time, double and integer regular expressions

const boost::regex re_time("([01]\\d|2[0123])(:)([0-5]\\d)((?(2)\\2)([0-5]\\d))?");
const boost::regex re_double( "^\\s*-?(0+|[1-9]\\d*)(,\\d{3})*(\\.\\d+)?\\s*$");
const boost::regex re_integer("^\\s*-?(0+|[1-9]\\d*)(,\\d{3})*(\\.0+)?\\s*$");

// Date regular expressions

const std::string re_start ("(?<![ \\w])\\s*");
const std::string re_end ("\\s*(?![\\w\\.])");

const std::string re_sep_dash ("([ -\\./])");
const std::string re_sep_2 ("(\\1)");

const std::string re_yy ("\\d{2}");
const std::string re_yyyy ("(?:19|20)\\d{2}");
const std::string re_mon ("(?:jan(?:uary)?|feb(?:ruary)?|mar(?:ch)?|apr(?:il)?|may|jun(?:e)?|jul(?:y)?|aug(?:ust)?|sep(?:tember)?|oct(?:ober)?|nov(?:ember)?|dec(?:ember)?)");
const std::string re_mm ("(?:0?[1-9]|1[0-2])");
const std::string re_dd ("(?:[0-2]?\\d|3[0-1])");

// std::string re_date_000  mon dd yy hh:miAM (or PM);
// std::string re_date_100  mon dd yyyy hh:miAM (or PM);
std::string date_001 = re_mm   + "[\\/]" + re_dd  + "[\\/]"  + re_yy;   // mm/dd/yy;
std::string date_101 = re_mm   + "[\\/]" + re_dd  + "[\\/]"  + re_yyyy; // mm/dd/yyyy;
std::string date_002 = re_yy   + "[\\.]" + re_mm  + "[\\.]"  + re_dd;   // yy.mm.dd;
std::string date_102 = re_yyyy + "[\\.]" + re_mm  + "[\\.]"  + re_dd;   // yyyy.mm.dd;
std::string date_003 = re_dd   + "[\\/]" + re_mm  + "[\\/]"  + re_yy;   // dd/mm/yy;
std::string date_103 = re_dd   + "[\\/]" + re_mm  + "[\\/]"  + re_yyyy; // dd/mm/yyyy;
std::string date_004 = re_dd   + "[\\.]" + re_mm  + "[\\.]"  + re_yy;   // dd.mm.yy;
std::string date_104 = re_dd   + "[\\.]" + re_mm  + "[\\.]"  + re_yyyy; // dd.mm.yyyy;
std::string date_005 = re_dd   + "[-]"   + re_mm  + "[-]"    + re_yy;   // dd-mm-yy;
std::string date_105 = re_dd   + "[-]"   + re_mm  + "[-]"    + re_yyyy; // dd-mm-yyyy;
std::string date_006 = re_dd   + "[ ]"   + re_mon + "[ ]"    + re_yy;   // dd mon yy;
std::string date_106 = re_dd   + "[ ]"   + re_mon + "[ ]"    + re_yyyy; // dd mon yyyy;
std::string date_007 = re_mon  + "[ ]"   + re_dd  + "(?:, )" + re_yy;   // Mon dd, yy;
std::string date_107 = re_mon  + "[ ]"   + re_dd  + "(?:, )" + re_yyyy; // Mon dd, yyyy;
// std::string date_008  hh:mi:ss;
// std::string date_009  mon dd yy hh:mi:ss:mmmAM (or PM);
// std::string date_109  mon dd yyyy hh:mi:ss:mmmAM (or PM);
std::string date_010 = re_mm   + "[-]"   + re_dd  + "[-]"    + re_yy;   // mm-dd-yy;
std::string date_110 = re_mm   + "[-]"   + re_dd  + "[-]"    + re_yyyy; // mm-dd-yyyy;
std::string date_011 = re_yy   + "[\\/]" + re_mm  + "[\\/]"  + re_dd;   // yy/mm/dd;
std::string date_111 = re_yyyy + "[\\/]" + re_mm  + "[\\/]"  + re_dd;   // yyyy/mm/dd;
std::string date_012 = re_yy   + ""      + re_mm  + ""       + re_dd;   // yymmdd;
std::string date_112 = re_yyyy + ""      + re_mm  + ""       + re_dd;   // yyyymmdd;
// std::string date_013  dd mon yy hh:mi:ss:mmm(24h);
// std::string date_113  dd mon yyyy hh:mi:ss:mmm(24h);
// std::string date_014  hh:mi:ss:mmm(24h);
// std::string date_020  yy-mm-dd hh:mi:ss(24h);
// std::string date_120  yyyy-mm-dd hh:mi:ss(24h);
// std::string date_021  yy-mm-dd hh:mi:ss.mmm(24h);
// std::string date_121  yyyy-mm-dd hh:mi:ss.mmm(24h);
// std::string date_126  yyyy-mm-ddThh:mi:ss.mmm (no spaces);
// std::string date_127  yyyy-mm-ddThh:mi:ss.mmmZ (no spaces);
std::string date_030 = re_yy   + "[ ]"    + re_mon;  // yy mon;
std::string date_130 = re_yyyy + "[ ]"    + re_mon;  // yyyy mon;
std::string date_031 = re_yy   + "[ ]"    + re_mm;   // yy mm;
std::string date_131 = re_yyyy + "[ ]"    + re_mm;   // yyyy mm;
std::string date_032 = re_yy   + ""       + re_mm;   // yymm;
std::string date_132 = re_yyyy + ""       + re_mm;   // yyyymm;
std::string date_033 = re_yy   + "[-]"    + re_mm  + "[-]"  + re_dd;   // yy-mm-dd;
std::string date_133 = re_yyyy + "[-]"    + re_mm  + "[-]"  + re_dd;   // yyyy-mm-dd;
std::string date_051 = re_mm   + "[\\/]"  + re_yy;   // mm/yy;
std::string date_151 = re_mm   + "[\\/]"  + re_yyyy; // mm/yyyy;
std::string date_052 = re_yy   + "[\\.]"  + re_mm;   // yy.mm;
std::string date_152 = re_yyyy + "[\\.]"  + re_mm;   // yyyy.mm;
std::string date_053 = re_mm   + "[\\/]"  + re_yy;   // mm/yy;
std::string date_153 = re_mm   + "[\\/]"  + re_yyyy; // mm/yyyy;
std::string date_054 = re_mm   + "[\\.]"  + re_yy;   // mm.yy;
std::string date_154 = re_mm   + "[\\.]"  + re_yyyy; // mm.yyyy;
std::string date_055 = re_mm   + "[-]"    + re_yy;   // mm-yy;
std::string date_155 = re_mm   + "[-]"    + re_yyyy; // mm-yyyy;
std::string date_056 = re_mon  + "[ ]"    + re_yy;   // mon yy;
std::string date_156 = re_mon  + "[ ]"    + re_yyyy; // mon yyyy;
std::string date_057 = re_mon  + "(?:, )" + re_yy;   // mon, yy;
std::string date_157 = re_mon  + "(?:, )" + re_yyyy; // mon, yyyy;
std::string date_061 = re_yy   + "[\\/]"  + re_mm;   // yy/mm;
std::string date_161 = re_yyyy + "[\\/]"  + re_mm;   // yyyy/mm;
std::string date_062 = re_yy   + ""       + re_mm;   // yymm;
std::string date_162 = re_yyyy + ""       + re_mm;   // yyyymm;

// const boost::regex re_date_000(date_000);
// const boost::regex re_date_100(date_100);
const boost::regex re_date_001(date_001);
const boost::regex re_date_101(date_101);
const boost::regex re_date_002(date_002);
const boost::regex re_date_102(date_102);
const boost::regex re_date_003(date_003);
const boost::regex re_date_103(date_103);
const boost::regex re_date_004(date_004);
const boost::regex re_date_104(date_104);
const boost::regex re_date_005(date_005);
const boost::regex re_date_105(date_105);
const boost::regex re_date_006(date_006);
const boost::regex re_date_106(date_106);
const boost::regex re_date_007(date_007);
const boost::regex re_date_107(date_107);
// const boost::regex re_date_008(date_008);
// const boost::regex re_date_009(date_009);
// const boost::regex re_date_109(date_109);
const boost::regex re_date_010(date_010);
const boost::regex re_date_110(date_110);
const boost::regex re_date_011(date_011);
const boost::regex re_date_111(date_111);
const boost::regex re_date_012(date_012);
const boost::regex re_date_112(date_112);
// const boost::regex re_date_013(date_013);
// const boost::regex re_date_113(date_113);
// const boost::regex re_date_014(date_014);
// const boost::regex re_date_020(date_020);
// const boost::regex re_date_120(date_120);
// const boost::regex re_date_021(date_021);
// const boost::regex re_date_121(date_121);
// const boost::regex re_date_126(date_126);
// const boost::regex re_date_127(date_127);
const boost::regex re_date_030(date_030);
const boost::regex re_date_130(date_130);
const boost::regex re_date_031(date_031);
const boost::regex re_date_131(date_131);
const boost::regex re_date_032(date_032);
const boost::regex re_date_132(date_132);
const boost::regex re_date_033(date_033);
const boost::regex re_date_133(date_133);
const boost::regex re_date_051(date_051);
const boost::regex re_date_151(date_151);
const boost::regex re_date_052(date_052);
const boost::regex re_date_152(date_152);
const boost::regex re_date_053(date_053);
const boost::regex re_date_153(date_153);
const boost::regex re_date_054(date_054);
const boost::regex re_date_154(date_154);
const boost::regex re_date_055(date_055);
const boost::regex re_date_155(date_155);
const boost::regex re_date_056(date_056);
const boost::regex re_date_156(date_156);
const boost::regex re_date_057(date_057);
const boost::regex re_date_157(date_157);
const boost::regex re_date_061(date_061);
const boost::regex re_date_161(date_161);
const boost::regex re_date_062(date_062);
const boost::regex re_date_162(date_162);

int RE_DATE_CODES [] = {
  // 000,
  // 100,
  001,
  101,
  002,
  102,
  003,
  103,
  004,
  104,
  005,
  105,
  006,
  106,
  007,
  107,
  // 008,
  // 009,
  // 109,
  010,
  110,
  011,
  111,
  012,
  112,
  // 013,
  // 113,
  // 014,
  // 020,
  // 120,
  // 021,
  // 121,
  // 126,
  // 127,
  030,
  130,
  031,
  131,
  032,
  132,
  033,
  133,
  051,
  151,
  052,
  152,
  053,
  153,
  054,
  154,
  055,
  155,
  056,
  156,
  057,
  157,
  061,
  161,
  062,
  162
};

boost::regex RE_DATE_TYPES [] = {
  // re_date_000,
  // re_date_100,
  re_date_001,
  re_date_101,
  re_date_002,
  re_date_102,
  re_date_003,
  re_date_103,
  re_date_004,
  re_date_104,
  re_date_005,
  re_date_105,
  re_date_006,
  re_date_106,
  re_date_007,
  re_date_107,
  // re_date_008,
  // re_date_009,
  // re_date_109,
  re_date_010,
  re_date_110,
  re_date_011,
  re_date_111,
  re_date_012,
  re_date_112,
  // re_date_013,
  // re_date_113,
  // re_date_014,
  // re_date_020,
  // re_date_120,
  // re_date_021,
  // re_date_121,
  // re_date_126,
  // re_date_127,
  re_date_030,
  re_date_130,
  re_date_031,
  re_date_131,
  re_date_032,
  re_date_132,
  re_date_033,
  re_date_133,
  re_date_051,
  re_date_151,
  re_date_052,
  re_date_152,
  re_date_053,
  re_date_153,
  re_date_054,
  re_date_154,
  re_date_055,
  re_date_155,
  re_date_056,
  re_date_156,
  re_date_057,
  re_date_157,
  re_date_061,
  re_date_161,
  re_date_062,
  re_date_162
};

#define NUM_DATES sizeof(RE_DATE_TYPES)/sizeof(*RE_DATE_TYPES)

#endif
