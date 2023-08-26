#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
using std::size_t;

constexpr auto runs = 500'000;
double ref_time;
std::ostringstream results;

void cout() {
   std::string test_name{ "cout" };

   const auto start = std::chrono::steady_clock::now();
   for (size_t i = 0; i < runs; ++i) {
      std::cout << "Hallo World! ";
   }
   std::cout << std::endl;
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   ref_time = elpsed_seconds.count();
   auto percent = elpsed_seconds.count() * 100 / ref_time;
   auto speed_factor = ref_time / elpsed_seconds.count();

   results
      << '\n'
      << std::setfill(' ')
      << std::setw(15) << test_name
      << std::setw(15) << elpsed_seconds.count()
      << std::setw(15) << trunc(percent * 100) / 100
      << std::setw(15) << trunc(speed_factor * 10) / 10;
}

void ostream() {
   std::string test_name{ "ostream" };
   std::ostringstream ostream;

   const auto start = std::chrono::steady_clock::now();
   for (size_t i = 0; i < runs; ++i) {
      ostream << "Hello World! ";
   }
   std::cout << ostream.str() << std::endl;
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   auto percent = elpsed_seconds.count() * 100 / ref_time;
   auto speed_factor = ref_time / elpsed_seconds.count();

   results
      << '\n'
      << std::setfill(' ')
      << std::setw(15) << test_name
      << std::setw(15) << elpsed_seconds.count()
      << std::setw(15) << trunc(percent * 100) / 100
      << std::setw(15) << trunc(speed_factor * 10) / 10;
}

int main()
{
   results << '\n'
      << "'cout' was used with " << runs << " runs. 'ostream' uses 'cout' just one time for the same output.\n\n"
      << std::setiosflags(std::ios::left)
      << std::setw(15) << "Function"
      << std::setw(15) << "CPU-Time (s)"
      << std::setw(15) << "Percent"
      << std::setw(15) << "Speed factor" << '\n'
      << std::setw(60) << std::setfill('-') << "";

   // Tests
   cout();
   ostream();

   std::cout << results.str() << '\n' << std::endl;
   system("Pause");
}