#include <fstream>
// #include <string>
#include <cstring>
#include "countries.hpp"

// Record class public method definitions
std::string Record::getCountry()
{
   return getfield(country);
}

std::string Record::getCapital()
{
   return getfield(capital);
}

std::string Record::getFlag()
{
   return "/countries/" + getfield(flag);
}

std::string Record::getTableRow()
{
   return "\t\t\t<tr><td>" + getCountry() + "</td><td>" + getCapital() 
      + "</td><td><img src='" + getFlag() + "'></td></tr>\n";
}

// Record class private method definitions
std::string Record::getfield(int n)
{
   unsigned i = 0, j = 0, buflen = strlen(buf);
   std::string field;

   while (i < buflen) {
      while (buf[i] != ',' && i < buflen)
         if (buf[i] != '\"')
            if (j + 1 == n)
               field += buf[i++];
            else
               i++;
         else {
            i++;
            while (buf[i] != '\"') {
               if (j + 1 == n)
                  field += buf[i++];
               else
                  i++;
            }
            i++;
         }
      if (j + 1 == n) return field;
      i++;
      j++;
   }
   field.clear();
   return field;
}

// auxiliary utility function definitions
Record* binarysearch(const std::string& target)
{
   static Record record;
   std::ifstream ifstr;
   ifstr.open("countries.dat", std::ios::in | std::ios::binary);
   ifstr.seekg(0, ifstr.end);
   int n = ifstr.tellg() / sizeof(Record);
   int m, l = 0, r = n - 1;

   while (l <= r) {
      m = (l + r) / 2;
      ifstr.seekg(m * sizeof(Record), ifstr.beg);
      ifstr.read((char *)&record, sizeof(Record));
      std::string field = record.getCountry();
      if (target < field)
         r = m - 1;
      else if (target > field)
         l = m + 1;       
      else {
         ifstr.close();         
         return &record;
      }
   }
   return 0;
}
