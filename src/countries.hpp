#ifndef STATES_H
#define STATES_H

const unsigned RECORD_LENGTH = 80;

enum { dummy, country, capital, flag };

class Record {
   public:
      std::string getCountry();
      std::string getCapital();
      std::string getFlag();
      std::string getTableRow();
   private:
      char buf[RECORD_LENGTH];
      std::string getfield(int);
};

Record* binarysearch(const std::string&);

#endif
