#include <iostream>
#include <time.h>

#include <algorithm>
#include <limits>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
/*
class Solution0
{
 public:
  enum patten_type : int {
    patten_end       = 0,
    patten_single    = 1,  //单字符          | a . | 返回字符 a或.
    patten_multi     = 2,  //重复多字符      | a*  | 返回重复的字符
    patten_multi_any = 3,  //任意多字符      | .*  | 返回-
  };

  pair<int, char> _get_patten(string& p)
  {
    if (p.size() == 0) {
      return {patten_end, '-'};  // empty
    } else if (p.size() == 1) {
      auto p0 = p[0];
      p.erase(0, 1);
      return {patten_single, p0};  // a or .
    } else if (p.size() == 2) {
      auto p0 = p[0];  //必不是* *是后缀 p0可能是字符或.

      if (p[1] == '*') {
        p.erase(0, 2);
        if (p0 != '.') {
          return {patten_multi, p0};
        } else {
          return {patten_multi_any, p0};
        }
      } else {
        p.erase(0, 1);
        return {patten_single, p0};  // a or .
      }
    } else {
      auto p0 = p[0];  //必不是* *是后缀 p0可能是字符或.

      if (p[1] == '*') {
        p.erase(0, 2);
        if (p0 != '.') {
          // a*
          while (p.size() && ((p[0] == '*') || (p[0] == p0))) {
            // merge a*** to a*
            p.erase(0, 1);
          }
          return {patten_multi, p0};
        } else {
          // .*
          while (p.size() >= 2) {
            // merge .***.* to .*
            if (p[0] == '*') {
              p.erase(0, 1);
            } else if (((p[0] == '.') && (p[1] == '*'))) {
              p.erase(0, 2);
            } else {
              break;
            }
          }
          while ((p.size() != 0) && (p[0] == '*')) {
            // merge .*** to .*
            p.erase(0, 1);
          }
          return {patten_multi_any, '-'};
        }
      } else {
        p.erase(0, 1);
        return {patten_single, p0};  // a or .
      }
    }

    return {0, '0'};
  }

  bool isMatch(string s, string p)
  {
    bool find_any = false;
    while (1) {
      auto  _     = _get_patten(p);
      auto& _type = _.first;
      auto& _char = _.second;
      switch (_type) {
        // end
        case patten_end: {
          if (s.size()) {
            return find_any;
          } else {
            return true;
          }
        } break;
        case patten_single: {
          if (_char == '.') {
            _char = s[0];
          }
          if (find_any) {
            // should find _char
            auto find_char = s.find_first_of(_char);
            if (find_char == std::string::npos) {
              return false;
            } else {
              // erase it
              // bug here   .*a        how to deal with xxxxaxxxa
              // erase first_of  or last of ?
              s.erase(0, find_char + 1);
              find_any = false;
            }
          } else {
            if (s.size() && (s[0] == _char)) {
              s.erase(0, 1);
            } else {
              return false;
            }
          }
        } break;
        case patten_multi: {
          if (find_any) {
            // should find _char
            auto find_char = s.find_first_of(_char);
            if (find_char == std::string::npos) {
              ;
            } else {
              // erase it
              // bug here   .*a        how to deal with xxxxaxxxa
              // erase first_of  or last of ?
              s.erase(0, find_char + 1);
              while (s.size() && (s[0] == _char)) {
                s.erase(0, 1);
              }
            }

          } else {
            while (s.size() && (s[0] == _char)) {
              s.erase(0, 1);
            }
          }
        } break;
        case patten_multi_any: {
          find_any = true;
        } break;
      }
    }
    return true;
  }
};
*/
class Solution
{
 public:
  enum patten_type : int {
    patten_end       = 0,
    patten_single    = 1,  //单字符          | a . | 返回字符 a或.
    patten_multi     = 2,  //重复多字符      | a*  | 返回重复的字符
    patten_multi_any = 3,  //任意多字符      | .*  | 返回-
  };

  using problem_t = struct problem {
    string               s;
    string               p;
    bool                 pass;
    std::vector<problem> sons;
    problem(string s, string p) : s(s), p(p), pass(false), sons() {}
  };

  pair<int, char> _get_patten(string& p)
  {
    if (p.size() == 0) {
      return {patten_end, '-'};  // empty
    } else if (p.size() == 1) {
      auto p0 = p[0];
      p.erase(0, 1);
      return {patten_single, p0};  // a or .
    } else if (p.size() == 2) {
      auto p0 = p[0];  //必不是* *是后缀 p0可能是字符或.

      if (p[1] == '*') {
        p.erase(0, 2);
        if (p0 != '.') {
          return {patten_multi, p0};
        } else {
          return {patten_multi_any, p0};
        }
      } else {
        p.erase(0, 1);
        return {patten_single, p0};  // a or .
      }
    } else {
      auto p0 = p[0];  //必不是* *是后缀 p0可能是字符或.

      if (p[1] == '*') {
        p.erase(0, 2);
        if (p0 != '.') {
          // a*
          // merge a*a* to a*
          while (p.size() >= 2) {
            if (p[0] == '*') {
              p.erase(0, 1);
            } else if (((p[0] == p0) && (p[1] == '*'))) {
              p.erase(0, 2);
            } else {
              break;
            }
          }
          // merge a*** to a*
          while (p.size() && (p[0] == '*')) {
            p.erase(0, 1);
          }
          return {patten_multi, p0};
        } else {
          // .*
          while (p.size() >= 2) {
            // merge .***.* to .*
            if (p[0] == '*') {
              p.erase(0, 1);
            } else if (((p[0] == '.') && (p[1] == '*'))) {
              p.erase(0, 2);
            } else {
              break;
            }
          }
          while ((p.size() != 0) && (p[0] == '*')) {
            // merge .*** to .*
            p.erase(0, 1);
          }
          return {patten_multi_any, '-'};
        }
      } else {
        p.erase(0, 1);
        return {patten_single, p0};  // a or .
      }
    }

    return {0, '0'};
  }

  bool step(problem_t& root)
  {
    string& s     = root.s;
    string& p     = root.p;
    auto    _     = _get_patten(p);
    auto&   _type = _.first;
    auto&   _char = _.second;
    switch (_type) {
      // end
      case patten_end: {
        root.pass = s.empty();
        return s.empty();
      } break;
      case patten_single: {
        if (_char == '.') {
          if (s.size()) {
            s.erase(0, 1);
            return true;
          } else {
            return false;
          }
        }
        if (s.size() && (s[0] == _char)) {
          s.erase(0, 1);
        } else {
          return false;
        }
      } break;
      case patten_multi: {
        if (p.empty()) {
          if (s.find_first_not_of(_char) == string::npos) {
            root.pass = true;
            return true;
          } else {
            root.pass = false;
            return false;
          }
        } else {
          // create sons
          // root doesnot erase any
          string tmp_s = s;
          while (tmp_s.size() && (tmp_s[0] == _char)) {
            tmp_s.erase(0, 1);
            problem_t son(tmp_s, root.p);
            root.sons.emplace_back(son);
          }
        }

      } break;
      case patten_multi_any: {
        if (p.empty()) {
          root.pass = true;
          return true;
        } else {
          string tmp_s = s;
          while (tmp_s.size()) {
            tmp_s.erase(0, 1);
            problem_t son(tmp_s, root.p);
            root.sons.emplace_back(son);
          }
        }
      } break;
    }

    return true;
  }

  bool deal(problem_t& root)
  {
    // 遇到*时 需要增加sons解法
    // 如 a*b*aaa
    // a可以匹配0到任意多个a
    //
    // 如 .* 可以匹配任意多个.
    //
    // 但.*.*.*.* 可能boom 需要使用lazy的方式创建子解法
    while (1) {
      if (step(root)) {
        if (root.pass) {
          return true;
        }
        while (root.sons.size()) {
          auto& son = root.sons.back();
          if (deal(son)) {
            return true;
          } else {
            root.sons.pop_back();
          }
        }
      } else {
        return false;
      }
    }
  }
  bool isMatch(string s, string p)
  {
    problem_t problem(s, p);
    return deal(problem);
  }
};

class Solution3
{
 public:
  bool isMatch(string s, string p)
  {
    if (p.empty()) {
      return s.empty();
    }
    //提前排除这种非法输入 简化后续代码
    if (p[0] == '*') {
      return false;
    }
    int ns = s.size();
    int np = p.size();
    //    由于判断p[j] == s[i]、p[j-1]p[j]等当前问题附近的情况,
    //    即可减小原问题,因此存在最优子结构,因此可以写出动态规划方程：
    //    记dp[i][j]表示前i个源字符与前j个模式串字符是否匹配（含当前i,j这两个字符）
    /*
    dp[i][j]就等于：

    如果p[j] == '.'或者p[j] == s[i]：当前匹配成功,等于true && dp[i-1][j-1]

    如果p[j] == '*'：需要进一步分情况讨论,假设p[j]前面p[j-1]存在

      如果p[j-1] == '.'或者p[j-1] == s[i],则p[j-1]p[j] .* a*
        这两个模式串可以使用1到无数次,匹配成功,等于true && dp[i-1][j]

      如果p[j-1] == '.'和p[j-1] == s[i]都不成立, .* a*
        但可以使用p[j-1]p[j]这两个模式串0次,
          匹配成功,等于true && dp[i-1][j-2]
            如：   aa    匹配 aa
                   aab 不匹配 aac
                但 aab   匹配 aac*

    除了以上情况,均匹配不成功,等于false && dp[i-1][j-1]
    */
    vector<vector<bool>> dp(ns + 1, vector<bool>(np + 1, false));
    /*
       初始解
       动态规划方程根据分析很好写,但是很重要的一点是初始解怎么写
       初始解一般是对第一个变量等于0的情况,
       含义即源字符串为空的时候怎么与模式串P进行匹配

       首先想到两个都是空的时候,是匹配的,为true
     */
    dp[0][0] = true;
    /*
       如果模式串不为空(dp[0][j]),也要分情况讨论：
       如果p[j] != '*',一定是不匹配的 (因为初始解串为空)
          dp[0][j] = false && dp[0][j-1] = false
       如果p[j] == '*',那么就存在p[j-1]p[j]这两个模式串使用0次, 也可以匹配,
          dp[0][j] = true && dp[0][j-2] = dp[0][j-2]
     */
    //考虑*消除一个p字符的情况  初始s="" p=".*" ".*a*" ".*a*a*" 等
    for (int j = 1; j <= np; j++) {
      if ((p[j - 1] == '*') && (j - 2 >= 0)) {
        dp[0][j] = true && dp[0][j - 2];
      }
    }

    // 一般解
    // 记dp[i][j]表示前i个源字符与前j个模式串字符是否匹配（含当前i,j这两个字符）
    for (int i = 1; i <= ns; i++) {
      auto& si = s[i - 1];  //当前s
      for (int j = 1; j <= np; j++) {
        auto& pj = p[j - 1];  //当前p

        // 如果当前 p == s 或者p == '.' 当前匹配成功
        // dp[i][j]值与"ps都少1字符(dp[i-1][j-1])"的匹配结果相同
        if (pj == si || pj == '.')
          dp[i][j] = dp[i - 1][j - 1];

        // 如果当前 p == '*' 进一步考虑
        if (pj == '*') {
          // 这里需要确保前一个p存在
          // 但pj_1一定存在  *为后缀 函数入口已排除第一个字符为*的情况
          // 故而不用判断pj_1的下标是否越界
          auto& pj_1 = p[j - 2];  //前一个p
          //
          // 如果 "上一个p == (当前s || '.') " 当前能够匹配成功，
          //          aa  aa   (x1)
          //          aaa aa*  (x2) 上一个p 等于当前s
          // 等价于   aaa aaa  (x3)
          //
          //          ab  aa   (x1)
          //          aba aa*  (x2) 上一个p 等于当前s
          // 等价于   aba aaa  (x3)
          //
          //          当前位置匹配成功，结果应取决于x1 (x2=true&&x1)
          //      其结果与"ps都少1字符(dp[i-1][j-1])"的匹配结果相同 (x2=x1)
          //
          bool get_two_sth = (pj_1 == si || pj_1 == '.') && dp[i - 1][j];
          // 用*消掉一个p 直接 x1==x2
          //          aaa ab*  (x1)
          // 等价于   aaa a    (x2)
          //
          // 当前*匹配到0次
          // 结果与"ps都少1字符(dp[i-1][j-1])"的匹配结果相同
          bool eat_a_p = dp[i][j - 2];
          dp[i][j]     = eat_a_p || get_two_sth;
        }
      }
    }

    return dp[ns][np];
  }
};

int main(int argc, char const* argv[])
{
  Solution3                         sol;
  std::vector<pair<string, string>> v;
  v.emplace_back("a", ".*..a*");                             // false
  v.emplace_back("acaabbaccbbacaabbbb", "a*.*b*.*a*aa*a*");  // false
  v.emplace_back("bbba", ".*b");                             // false
  v.emplace_back("aaa", "a*a");                              // true
  v.emplace_back("mississippi", "mis*is*ip*.");              // true
  v.emplace_back("aa", "aa");                                // true
  v.emplace_back("aa", "a*");                                // true
  v.emplace_back("aa", "a");                                 // false
  v.emplace_back("ab", ".*");                                // true
  v.emplace_back("aab", "c*a*b");                            // true
  v.emplace_back("aab", "ca*b");                             // false
  v.emplace_back("mississippi", "mis*is*p*.");               // false
  v.emplace_back("aaa", "ab*a*c*a");  // true// func0 can't fix it
  int cnt = 0;
  for (auto&& i : v) {
    // build
    const bool show_time = 0;
    // run
    clock_t _start   = clock();
    auto    result   = sol.isMatch(i.first, i.second);
    clock_t _stop    = clock();
    double  _time    = double(_stop - _start);
    double  _time_s  = (_time / CLOCKS_PER_SEC);
    double _time_ms = _time_s*1000.0;
    double _time_ns = _time_ms*1000.0;
    cout << "problem" << cnt++ << ": ";
    if(show_time)
      cout<< _time_s <<" s \n\t\t\t";
    else
      cout<< "\n\t";
    cout << result;
    cout << endl;

    // delete
  }

  return 0;
}

// Automaton
