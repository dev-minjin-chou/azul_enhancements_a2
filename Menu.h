class Menu {
 public:
  void static Main();
  void static Credits();
  void static Instructions();

 private:
  void static PrintList(const char* list[], unsigned int len);
  static const int main_len;
  static const char* main_menu[];
  static const char* help_ins[];
};
