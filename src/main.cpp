#include <iostream>
#include <fstream>
#include <cgicc/Cgicc.h>
#include "countries.hpp"

int main()
{
   char buf[RECORD_LENGTH];
   const std::string header = "\t\t\t<tr><th>Country</th><th>Capital</th><th>Flag</th></tr>\n";

   std::cout << "Content-type: text/html\n\n";
   std::cout << "<!DOCTYPE html>\n";
   std::cout << "<html>\n";
   std::cout << "\t<head>\n";
   std::cout << "\t\t<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
   std::cout << "\t\t<link rel='stylesheet' media='all' href='/includes/gradienttable.css'>\n";
   std::cout << "\t\t<title>C++ Countries</title>\n";
   std::cout << "\t</head>\n";
   std::cout << "\t<body>\n";
   std::cout << "\t\t<header><p>C++ countries</p></header>\n";
   std::cout << "\t\t<p><a href='/index.html'>Home</a> | <a href='/countries.html'>Back</a></p>\n";

   // print the form
   std::cout << "\t\t<form action = 'countries.cgi' method = 'POST' accept-charset='utf-8'>\n";
   std::cout << "\t\t\t<div>target: <input type='text' name='target' size='50' value=''> "
      "<input type='submit' name='search' value='search'></div>\n";
   std::cout << "\t\t</form>\n";
   std::cout << "\t\t<br>\n";

   try {
      cgicc::Cgicc cgi;
      
      cgicc::form_iterator pt = cgi.getElement("target");
      if(!pt->isEmpty() && pt != cgi.getElements().end()) {

         std::string target = **pt;
         Record* record = binarysearch(target);
         
         if (record != 0) {
            std::cout << "\t\t<table class='gradienttable'>\n";
            std::cout << header;
            std::cout << record->getTableRow();
            std::cout << "\t\t</table>\n";
         } else {
            std::cout << "target not found\n";
         } 
         
      } else {
         std::cout << "\t\t<p>no text entered for search target" << "</p>\n";
      }
   
   } catch (std::exception& e) {
      // handle any errors - omitted for brevity
   }

   std::cout << "\t\t<p><a href='/index.html'>Home</a> | <a href='/countries.html'>Back</a></p>\n";
   std::cout << "\t\t<footer><p>Copyright &#xa9; 2018 Josh Roybal</p></footer>\n";
   std::cout << "\t</body>\n";
   std::cout << "</html>\n";
   return 0;
}
