
//http://www.cnitblog.com/luckydmz/archive/2020/01/07/92011.html
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

constexpr int64_t SEC_US = 1000000;
constexpr int64_t MIN_US = SEC_US * 60;
constexpr int64_t HOUR_US = MIN_US * 60;
constexpr int64_t DAY_US = HOUR_US * 24;

constexpr int64_t SEC_MS = 1000;
constexpr int64_t MIN_MS = SEC_MS * 60;
constexpr int64_t HOUR_MS = MIN_MS * 60;
constexpr int64_t DAY_MS = HOUR_MS * 24;

constexpr int64_t SEC_S = 1;
constexpr int64_t MIN_S = SEC_S * 60;
constexpr int64_t HOUR_S = MIN_S * 60;
constexpr int64_t DAY_S = HOUR_S * 24;

int64_t get_gmtime_us();
int64_t get_localtime_us();

int64_t get_gmtime_ms();
int64_t get_localtime_ms();

int64_t get_gmtime_s();
int64_t get_localtime_s();

string gmtime2localstr(int64_t time_us, const string& );
int64_t localstr2gmtime(const std::string& s, const std::string&);
int64_t gmtime_2_time_us(const std::string& s, const std::string&);
  /**
   * Generate a local time
   * and return as std::string
   */
std::string mylocal_time();
  /**
   * Generate a UTC ISO8601-formatted timestamp
   * and return as std::string
   */
std::string gmt_time();

