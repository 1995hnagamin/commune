vector<string> split(string str, char d) {
  istringstream s(str);
  string in;
  vector<string> val;
  while (getline(s,in,d)) val.push_back(in);
  return val;
}

