// utility.cpp

#include "utility.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// static 
timespan timespan::time_since_start()
{
   static LARGE_INTEGER start{};
   static int64 factor{};
   if (start.QuadPart == 0) {
      QueryPerformanceCounter(&start);
      LARGE_INTEGER frequency{};
      QueryPerformanceFrequency(&frequency);
      factor = frequency.QuadPart / 1000000;
   }

   LARGE_INTEGER current{};
   QueryPerformanceCounter(&current);

   return timespan{ (current.QuadPart - start.QuadPart) / factor };
}

timespan timespan::operator+(const timespan &rhs) const
{
   return { m_duration + rhs.m_duration };
}

timespan timespan::operator-(const timespan &rhs) const
{
   return { m_duration - rhs.m_duration };
}

float timespan::elapsed_seconds() const
{
   return float(m_duration / 1000000.0);
}

int64 timespan::duration() const
{
   return m_duration;
}
