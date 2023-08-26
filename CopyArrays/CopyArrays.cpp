#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <chrono>
using std::size_t;

constexpr auto n = 100;
constexpr auto runs = 50'000'000;
double ref_time;

void PrintResult(
   std::string test_name,
   std::chrono::duration<double> elpsed_seconds)
{
   auto percent = elpsed_seconds.count() * 100 / ref_time;
   auto speed_factor = ref_time / elpsed_seconds.count();

   std::cout
      << '\n'
      << std::setfill(' ')
      << std::setw(15) << test_name
      << std::setw(15) << elpsed_seconds.count()
      << std::setw(15) << trunc(percent * 100) / 100
      << std::setw(15) << trunc(speed_factor * 10) / 10;
}

void loop() {
   std::string test_name{ "loop copy" };
   int arr1[n]{}, arr2[n]{};

   const auto start = std::chrono::steady_clock::now();
   for (std::size_t i = 0; i < runs; ++i) {
      for (int i = 0; i < n; ++i) {
         arr2[i] = arr1[i];
      }
   }
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   ref_time = elpsed_seconds.count();
   PrintResult(test_name, elpsed_seconds);
}

void copy() {
   std::string test_name{ "copy()" };
   int arr1[n]{}, arr2[n]{};

   const auto start = std::chrono::steady_clock::now();
   for (std::size_t i = 0; i < runs; ++i) {
      std::copy(std::begin(arr1), std::end(arr1), std::begin(arr2));
   }
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   PrintResult(test_name, elpsed_seconds);
}

void copy_n() {
   std::string test_name{ "copy_n()" };
   int arr1[n]{}, arr2[n]{};

   const auto start = std::chrono::steady_clock::now();
   for (std::size_t i = 0; i < runs; ++i) {
      std::copy_n(arr1, n, arr2);
   }
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   PrintResult(test_name, elpsed_seconds);
}

void memcpy() {
   std::string test_name{ "memcpy()" };
   int arr1[n]{}, arr2[n]{};

   const auto start = std::chrono::steady_clock::now();
   for (std::size_t i = 0; i < runs; ++i) {
      std::memcpy(&arr2, &arr1, sizeof(arr1));
   }
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   PrintResult(test_name, elpsed_seconds);
}

void cpp_array() {
   std::string test_name{ "cpp_array (=)" };
   std::array<int, n> arr1{}, arr2;

   const auto start = std::chrono::steady_clock::now();
   for (std::size_t i = 0; i < runs; ++i) {
      arr2 = arr1;
   }
   const auto end = std::chrono::steady_clock::now();

   const std::chrono::duration<double> elpsed_seconds = end - start;
   PrintResult(test_name, elpsed_seconds);
}

int main()
{
   std::cout
      << "Copy arrays with " << runs << " runs.\n\n"
      << "Test is running...\n\n"
      << std::setiosflags(std::ios::left)
      << std::setw(15) << "Function"
      << std::setw(15) << "CPU-Time (s)"
      << std::setw(15) << "Percent"
      << std::setw(15) << "Speed factor" << '\n'
      << std::setw(60) << std::setfill('-') << ""
      << std::flush;

   // Tests
   loop();
   copy();
   copy_n();
   cpp_array();
   memcpy();

   std::cout << '\n' << std::endl;
   system("Pause");
}