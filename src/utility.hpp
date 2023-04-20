// utility.hpp

#pragma once

using int64 = signed long long;

struct timespan {
   static constexpr timespan from_seconds(double seconds) { return timespan{ int64(seconds * 1000000.0) }; }

   static timespan time_since_start();

   constexpr timespan() = default;
   constexpr timespan(int64 duration) : m_duration(duration) {}
   constexpr timespan(const timespan &rhs) : m_duration(rhs.m_duration) {}

   timespan operator+(const timespan &rhs) const;
   timespan operator-(const timespan &rhs) const;

   float elapsed_seconds() const;
   int64 duration() const;

   int64 m_duration{ 0 };
};
