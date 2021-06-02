#include <bits/stdc++.h>
using namespace std;
map<string, int> mapInt;
map<string, double> mapDb;

void killTheSpace(const string& line, int& cur) {
  while (cur < line.size() && line[cur] == ' ') cur++;
}
string getVar(const string& line, int& cur) {
  killTheSpace(line, cur);
  string ret = "";
  if (!isalpha(line[cur])) return ret;
  for (int i = 0; cur + i < line.size(); i++) {
    if (isalnum(line[cur + i]))
      ret += line[cur + i];
    else
      break;
  }
  return ret;
}
void moveVar(const string& line, int& cur) {
  killTheSpace(line, cur);
  for (; cur < line.size(); cur++)
    if (!isalnum(line[cur])) break;
}
bool parseInit(const string& line, int& cur) {
  string x = getVar(line, cur);
  if (x == "int" || x == "double") {
    moveVar(line, cur);
    int type = x == "int" ? 0 : 1;
    while (true) {
      while (cur < line.size() && (line[cur] == ' ' || line[cur] == ',')) cur++;
      x = getVar(line, cur);
      if (x == "") break;
      moveVar(line, cur);
      if (type == 0)
        mapInt[x] = 0;
      else
        mapDb[x] = 0.0;
    }
    return true;
  }
  return false;
}

const double eps = 1e-8;
int dcmp(double x) {
  if (fabs(x) < eps)
    return 0;
  else
    return x < 0 ? -1 : 1;
}
const int INF = 0x3f3f3f3f;

struct Value {
  double dval;
  int ival;
  int type;    // 0, 1, INF
  string var;  // "-1,  "
};

void Error() {
  cout << "divided by ZERO" << endl;
  exit(0);
}
Value parseExp(const string& line, int& cur);

Value parseVar(const string& line, int& cur) {
  killTheSpace(line, cur);
  if (isdigit(line[cur])) {
    int db = 0, i;
    for (i = 0; i + cur < line.size(); i++) {
      if (line[i + cur] == '.') {
        db = 1;
        continue;
      }
      if (!isdigit(line[i + cur])) break;
    }
    if (db == 0) {
      int val = stoi(line.substr(cur, i));
      cur += i;
      return {0.0, val, db, "-1"};
    } else {
      double val = stod(line.substr(cur, i));
      cur += i;
      return {val, 0, db, "-1"};
    }
  } else {
    string x = getVar(line, cur);
    if (mapInt.find(x) != mapInt.end()) {
      moveVar(line, cur);
      return {0.0, mapInt[x], 0, x};
    }
    if (mapDb.find(x) != mapDb.end()) {
      moveVar(line, cur);
      return {mapDb[x], 0, 1, x};
    }
  }
  *(int*)0 = 1;
}

Value parseBracket(const string& line, int& cur) {
  killTheSpace(line, cur);
  if (line[cur] == '(') {
    cur++;
    auto x = parseExp(line, cur);
    killTheSpace(line, cur);
    cur++;
    return x;
  }
  return parseVar(line, cur);
}

Value parseSign(const string& line, int& cur) {
  killTheSpace(line, cur);
  char op = line[cur];
  if (op == '+') {
    cur++;
    return parseSign(line, cur);
  }
  if (op == '-') {
    cur++;
    auto ret = parseSign(line, cur);
    ret.ival *= -1;
    ret.dval *= -1;
    return ret;
  }
  return parseBracket(line, cur);
}
Value parseMul(const string& line, int& cur) {
  auto ret = parseSign(line, cur);
  killTheSpace(line, cur);
  char op = line[cur];
  if (op == '*' || op == '/') {
    cur++;
    auto x = parseMul(line, cur);
    if (op == '*') {
      if (ret.type == 0) {
        if (x.type == 0) {
          ret.ival *= x.ival;
        } else {
          ret.dval = ret.ival * x.dval;
        }
      } else {
        if (x.type == 0) {
          ret.dval *= x.ival;
        } else {
          ret.dval *= x.dval;
        }
      }
    } else {
      if (x.type == 0) {
        if (x.ival == 0) Error();
        if (ret.type == 0) {
          ret.ival /= x.ival;
        } else {
          ret.dval /= x.ival;
        }
      } else {
        if (x.dval == 0) Error();
        if (ret.type == 0) {
          ret.dval = ret.ival / x.dval;
        } else {
          ret.dval /= x.dval;
        }
      }
    }
    ret.type = max(ret.type, x.type);
  }
  return ret;
}
Value parseAdd(const string& line, int& cur) {
  auto ret = parseMul(line, cur);
  while (true) {
    killTheSpace(line, cur);
    char op = line[cur];
    if (op != '+' && op != '-') break;
    cur++;
    auto x = parseMul(line, cur);
    if (ret.type == 0) {
      if (x.type == 0) {
        if (op == '+')
          ret.ival += x.ival;
        else
          ret.ival -= x.ival;
      } else {
        if (op == '+')
          ret.dval = ret.ival + x.dval;
        else
          ret.dval = ret.ival - x.dval;
      }
    } else {
      if (x.type == 0) {
        if (op == '+')
          ret.dval = ret.dval + x.ival;
        else
          ret.dval = ret.dval - x.ival;
      } else {
        if (op == '+')
          ret.dval = ret.dval + x.dval;
        else
          ret.dval = ret.dval - x.dval;
      }
    }
    ret.type = max(ret.type, x.type);
  }
  return ret;
}
Value parseExp(const string& line, int& cur) {
  auto ret = parseAdd(line, cur);
  killTheSpace(line, cur);
  if (line[cur] == '=') {
    cur++;
    auto x = parseExp(line, cur);
    if (ret.type == 0) {
      if (x.type == 0) {
        ret.ival = x.ival;
      } else {
        ret.ival = (int)x.dval;
      }
      mapInt[ret.var] = ret.ival;
    } else {
      if (x.type == 0) {
        ret.dval = x.ival;
      } else {
        ret.dval = x.dval;
      }
      mapDb[ret.var] = ret.dval;
    }
  }
  return ret;
}

bool print(const string& line, int& cur) {
  string x = getVar(line, cur);
  if (x == "print") {
    moveVar(line, cur);
    killTheSpace(line, cur);
    cur++;
    auto res = parseVar(line, cur);
    if (res.type == 0) {
      cout << res.ival << endl;
    } else {
      cout << fixed << setprecision(6) << res.dval << endl;
    }
    return true;
  }
  return false;
}
void caozuo(const string& line, int& cur) {
  killTheSpace(line, cur);
  if (parseInit(line, cur)) return;
  if (print(line, cur)) return;
  parseExp(line, cur);
}

int main() {
  int n;
  cin >> n;
  string line;
  getline(cin, line);
  while (n--) {
    getline(cin, line);
    int cur = 0;
    caozuo(line, cur);
  }
}
/*
100
int a,b;
double c,d;
*/