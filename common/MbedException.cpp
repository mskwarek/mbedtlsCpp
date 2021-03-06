#include<exception>
#include<iostream>
#include<string>

class MbedException : public std::exception
{
 private:
  int returnedValue = 0;
  std::string message = "";

 public:
  MbedException(std::string msg, int val_)
    {
      this->returnedValue = val_;
      this->message = msg;
    }
  void what()
  {
    std::cout<<message<<" "<<std::hex<<returnedValue<<std::endl;
  }
};
