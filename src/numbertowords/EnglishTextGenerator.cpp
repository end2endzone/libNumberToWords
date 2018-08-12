/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#include "numbertowords/EnglishTextGenerator.h"

namespace NumberToWords
{
  static const std::string gTeens[] = {
    "one", "two", "three", "four", "five",
    "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
  };
  static const std::string gTens[] = {
    "twenty", "thirty",
    "forty", "fifty",
    "sixty", "seventy", 
    "eighty", "ninety"
  };

  EnglishTextGenerator::EnglishTextGenerator()
  {
  }

  EnglishTextGenerator::~EnglishTextGenerator()
  {
  }

  std::string EnglishTextGenerator::getNumberName(const int64_t & i)
  {
    if ( i == 0 )
      return getDigitName(i); 
    else if ( i < 0 )
      return "minus " + getNumberName(-i); //do not call level fonction to allow "Minus Zero" if user 
    return getNumberName(i, 0);
  }

  std::string EnglishTextGenerator::getNumberName(const int64_t & i, int iDepth)
  {
    if ( i == 0 )
      return "";
    else if ( i <= 19 )
      return gTeens[i-1];
    else if ( i <= 99 )
      return gTens[i / 10 - 2] + "-" + getNumberName(i % 10, iDepth+1);
    else if ( i <= 199 )
    {
      static const int64_t multiplicator = 100;
      return "one hundred " + getNumberName(i % multiplicator, iDepth+1);
    }
    else if ( i <= 999 )
    {
      static const int64_t multiplicator = 100;
      return getNumberName(i / multiplicator, iDepth+1) + " hundred " + getNumberName(i % multiplicator, iDepth+1);
    }
    else if ( i <= 1999 )
    {
      static const int64_t multiplicator = 1000;
      return "one thousand " + getNumberName(i % multiplicator, iDepth+1);
    }
    else if ( i <= 999999 )
    {
      static const int64_t multiplicator = 1000;
      return getNumberName(i / multiplicator, iDepth+1) + " thousand " + getNumberName(i % multiplicator, iDepth+1);
    }
    else if ( i <= 1999999 )
    {
      static const int64_t multiplicator = 1000000;
      return "one million " + getNumberName(i % multiplicator, iDepth+1);
    }
    else if ( i <= 999999999)
    {
      static const int64_t multiplicator = 1000000;
      return getNumberName(i / multiplicator, iDepth+1) + " million " + getNumberName(i % multiplicator, iDepth+1);
    }
    else if ( i <= 1999999999 )
    {
      static const int64_t multiplicator = 1000000000;
      return "one billion " + getNumberName(i % multiplicator, iDepth+1);
    }
    else
    {
      static const int64_t multiplicator = 1000000000;
      return getNumberName(i / multiplicator, iDepth+1) + " billion " + getNumberName(i % multiplicator, iDepth+1);
    }
  }

  std::string EnglishTextGenerator::getDigitName(const int64_t & i)
  {
    static const std::string digits[] = {
      "zero",  
      "one",
      "two",
      "three",
      "four",
      "five",
      "six",
      "seven",
      "eight",
      "nine"  
    };
    if (i >= 0 && i <= 9)
      return digits[i];
    return "";
  }

}; //namespace NumberToWords
