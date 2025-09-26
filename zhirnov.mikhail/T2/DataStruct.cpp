#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "DataStruct.h"

namespace nspace
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data;
    if (in >> data && data != dest.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  // Улучшенный парсер для DataStruct
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    DataStruct input;
    std::string key;

    // Читаем открывающую скобку
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

    // Парсим три ключа
    for (int i = 0; i < 3; ++i)
    {
      in >> key;

      if (key == "key1")
      {
        std::string value;
        in >> value;

        // Парсим разные форматы чисел для key1
        if (value.back() == 'd' || value.back() == 'D')
        {
          value.pop_back(); // Убираем 'd'
          std::istringstream iss(value);
          if (!(iss >> input.key1)) in.setstate(std::ios::failbit);
        }
        else if (value.find("ll") != std::string::npos ||
          value.find("ull") != std::string::npos ||
          value.find("0x") == 0 ||
          value.find("0b") == 0 ||
          value.find("0") == 0 && value.length() > 1)
        {
          // Для целых чисел преобразуем в double
          try {
            size_t pos;
            input.key1 = std::stod(value, &pos);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else if (value.length() == 3 && value[0] == '\'' && value[2] == '\'')
        {
          // Символы: 'a' -> ASCII код
          input.key1 = static_cast<double>(value[1]);
        }
        else
        {
          // Простое double число
          std::istringstream iss(value);
          if (!(iss >> input.key1)) in.setstate(std::ios::failbit);
        }

        in >> DelimiterIO{ ':' };
      }
      else if (key == "key2")
      {
        std::string value;
        in >> value;

        // Парсим разные форматы для key2 (unsigned long long)
        if (value.find("0x") == 0 || value.find("0X") == 0)
        {
          // Hex формат
          std::istringstream iss(value.substr(2));
          iss >> std::hex;
          if (!(iss >> input.key2)) in.setstate(std::ios::failbit);
        }
        else if (value.find("0b") == 0 || value.find("0B") == 0)
        {
          // Binary формат (упрощенно)
          try {
            input.key2 = std::stoull(value.substr(2), nullptr, 2);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else if (value.find("ll") != std::string::npos ||
          value.find("ull") != std::string::npos)
        {
          // Убираем суффиксы
          if (value.find("ull") != std::string::npos)
            value = value.substr(0, value.length() - 3);
          else if (value.find("ll") != std::string::npos)
            value = value.substr(0, value.length() - 2);

          try {
            input.key2 = std::stoull(value);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else if (value.length() == 3 && value[0] == '\'' && value[2] == '\'')
        {
          // Символы
          input.key2 = static_cast<unsigned long long>(value[1]);
        }
        else if (value.length() > 1 && value[0] == '0')
        {
          // Octal или другие системы
          try {
            input.key2 = std::stoull(value, nullptr, 0);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else
        {
          // Простое число
          try {
            input.key2 = std::stoull(value);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }

        in >> DelimiterIO{ ':' };
      }
      else if (key == "key3")
      {
        in >> StringIO{ input.key3 } >> DelimiterIO{ ':' };
      }
      else
      {
        in.setstate(std::ios::failbit);
        break;
      }
    }

    // Читаем закрывающую скобку
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "DataStruct.h"

namespace nspace
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data;
    if (in >> data && data != dest.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  // Улучшенный парсер для DataStruct
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    DataStruct input;
    std::string key;

    // Читаем открывающую скобку
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

    // Парсим три ключа
    for (int i = 0; i < 3; ++i)
    {
      in >> key;

      if (key == "key1")
      {
        std::string value;
        in >> value;

        // Парсим разные форматы чисел для key1
        if (value.back() == 'd' || value.back() == 'D')
        {
          value.pop_back(); // Убираем 'd'
          std::istringstream iss(value);
          if (!(iss >> input.key1)) in.setstate(std::ios::failbit);
        }
        else if (value.find("ll") != std::string::npos ||
          value.find("ull") != std::string::npos ||
          value.find("0x") == 0 ||
          value.find("0b") == 0 ||
          value.find("0") == 0 && value.length() > 1)
        {
          // Для целых чисел преобразуем в double
          try {
            size_t pos;
            input.key1 = std::stod(value, &pos);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else if (value.length() == 3 && value[0] == '\'' && value[2] == '\'')
        {
          // Символы: 'a' -> ASCII код
          input.key1 = static_cast<double>(value[1]);
        }
        else
        {
          // Простое double число
          std::istringstream iss(value);
          if (!(iss >> input.key1)) in.setstate(std::ios::failbit);
        }

        in >> DelimiterIO{ ':' };
      }
      else if (key == "key2")
      {
        std::string value;
        in >> value;

        // Парсим разные форматы для key2 (unsigned long long)
        if (value.find("0x") == 0 || value.find("0X") == 0)
        {
          // Hex формат
          std::istringstream iss(value.substr(2));
          iss >> std::hex;
          if (!(iss >> input.key2)) in.setstate(std::ios::failbit);
        }
        else if (value.find("0b") == 0 || value.find("0B") == 0)
        {
          // Binary формат (упрощенно)
          try {
            input.key2 = std::stoull(value.substr(2), nullptr, 2);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else if (value.find("ll") != std::string::npos ||
          value.find("ull") != std::string::npos)
        {
          // Убираем суффиксы
          if (value.find("ull") != std::string::npos)
            value = value.substr(0, value.length() - 3);
          else if (value.find("ll") != std::string::npos)
            value = value.substr(0, value.length() - 2);

          try {
            input.key2 = std::stoull(value);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else if (value.length() == 3 && value[0] == '\'' && value[2] == '\'')
        {
          // Символы
          input.key2 = static_cast<unsigned long long>(value[1]);
        }
        else if (value.length() > 1 && value[0] == '0')
        {
          // Octal или другие системы
          try {
            input.key2 = std::stoull(value, nullptr, 0);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }
        else
        {
          // Простое число
          try {
            input.key2 = std::stoull(value);
          }
          catch (...) {
            in.setstate(std::ios::failbit);
          }
        }

        in >> DelimiterIO{ ':' };
      }
      else if (key == "key3")
      {
        in >> StringIO{ input.key3 } >> DelimiterIO{ ':' };
      }
      else
      {
        in.setstate(std::ios::failbit);
        break;
      }
    }

    // Читаем закрывающую скобку
    in >> DelimiterIO{ ')' };

    if (in)
    {
      dest = input;
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    iofmtguard fmtguard(out);

    out << "(:";
    out << "key1 " << dest.key1 << "d:";
    out << "key2 " << dest.key2 << "ull:"; // Изменено на универсальный формат
    out << "key3 \"" << dest.key3 << "\":";
    out << ")";

    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {
  }

  iofmtguard::~iofmtguard()
  {
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

  bool compareDataStruct(const DataStruct& a, const DataStruct& b)
  {
    if (a.key1 != b.key1)
    {
      return a.key1 < b.key1;
    }
    if (a.key2 != b.key2)
    {
      return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
  }
}
