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
      return "Minus " + getNumberName(-i); //do not call level fonction to allow "Minus Zero" if user 
    return getNumberName(i, 0);
  }

  std::string EnglishTextGenerator::getNumberName(const int64_t & i, int iLevel)
  {
    static const std::string teens[] = {
      "One", "Two", "Three", "Four", "Five",
      "Six", "Seven", "Eight", "Nine", "Ten",
      "Eleven", "Twelve", "Thirteen", "Fourteen",
      "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    static const std::string tens[] = {
      "Twenty", "Thirty",
      "Forty", "Fifty",
      "Sixty", "Seventy", 
      "Eighty", "Ninety"
    };

    if ( i == 0 )
      return "";
    else if ( i <= 19 )
      return teens[i-1] + " ";
    else if ( i <= 99 )
      return tens[i / 10 - 2] + " " + getNumberName(i % 10);
    else if ( i <= 199 )
      return "One Hundred " + getNumberName(i % 100);
    else if ( i <= 999 )
      return getNumberName(i / 100) + "Hundreds " + getNumberName(i % 100);
    else if ( i <= 1999 )
      return "One Thousand " + getNumberName(i % 1000);
    else if ( i <= 999999 )
      return getNumberName(i / 1000) + "Thousands " + getNumberName(i % 1000);
    else if ( i <= 1999999 )
      return "One Million " + getNumberName(i % 1000000);
    else if ( i <= 999999999)
      return getNumberName(i / 1000000) + "Millions " + getNumberName(i % 1000000);
    else if ( i <= 1999999999 )
      return "One Billion " + getNumberName(i % 1000000000);
    else 
      return getNumberName(i / 1000000000) + "Billions " + getNumberName(i % 1000000000);
  }

  std::string EnglishTextGenerator::getDigitName(const int64_t & i)
  {
    static const std::string digits[] = {
      "Zero",  
      "One",
      "Two",
      "Three",
      "Four",
      "Five",
      "Six",
      "Seven",
      "Eight",
      "Nine"  
    };
    if (i >= 0 && i <= 9)
      return digits[i];
    return "";
  }

}; //namespace NumberToWords
