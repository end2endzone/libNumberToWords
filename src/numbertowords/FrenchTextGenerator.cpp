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

#include "numbertowords/FrenchTextGenerator.h"

namespace NumberToWords
{
  static const std::string gTeens[] = {
    "un", "deux", "trois", "quatre", "cinq",
    "six", "sept", "huit", "neuf", "dix",
    "onze", "douze", "treize", "quatorze",
    "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"
  };
  static const std::string gTens[] = {
    "vingt", "trente",
    "quarante", "cinquante",
    "soixante", "soixante-dix", 
    "quatre-vingt", "quatre-vingt-dix"
  };

  FrenchTextGenerator::FrenchTextGenerator()
  {
  }

  FrenchTextGenerator::~FrenchTextGenerator()
  {
  }

  std::string FrenchTextGenerator::getNumberName(const int64_t & i)
  {
    if ( i == 0 )
      return getDigitName(i); 
    else if ( i < 0 )
      return "moins " + getNumberName(-i);
    return getNumberName(i, 0);
  }

  std::string FrenchTextGenerator::getNumberName(const int64_t & i, int iDepth)
  {
    //multiplicators
    static const int64_t HUNDRED  =        100;
    static const int64_t THOUSAND =       1000;
    static const int64_t MILLION  =    1000000;
    static const int64_t BILLION  = 1000000000;

    if ( i == 0 )
      return "";
    else if ( i <= 19 )
      return gTeens[i-1];
    else if ( i < 20 )
    {
      std::string start = gTens[i / 10 - 2];
      return  + "-" + getNumberName(i % 10, iDepth+1);
    }
    else if ( i <= 99 )
      return gTens[i / 10 - 2] + "-" + getNumberName(i % 10, iDepth+1);
    else if ( i <= 199 )
    {
      return "cent " + getNumberName(i % HUNDRED, iDepth+1);
    }
    else if ( i <= 999 )
    {
      return getNumberName(i / HUNDRED, iDepth+1) + " cent " + getNumberName(i % HUNDRED, iDepth+1);
    }
    else if ( i <= 1999 )
    {
      return "mille " + getNumberName(i % THOUSAND, iDepth+1);
    }
    else if ( i <= 999999 )
    {
      return getNumberName(i / THOUSAND, iDepth+1) + " mille " + getNumberName(i % THOUSAND, iDepth+1);
    }
    else if ( i <= 1999999 )
    {
      return "un million " + getNumberName(i % MILLION, iDepth+1);
    }
    else if ( i <= 999999999)
    {
      return getNumberName(i / MILLION, iDepth+1) + " million " + getNumberName(i % MILLION, iDepth+1);
    }
    else if ( i <= 1999999999 )
    {
      return "un milliard " + getNumberName(i % BILLION, iDepth+1);
    }
    else
    {
      return getNumberName(i / BILLION, iDepth+1) + " milliard " + getNumberName(i % BILLION, iDepth+1);
    }
  }

  std::string FrenchTextGenerator::getDigitName(const int64_t & i)
  {
    static const std::string digits[] = {
      "zéro",  
      "un",    
      "deux",  
      "trois", 
      "quatre",
      "cinq",  
      "six",   
      "sept",  
      "huit",  
      "neuf"   
    };
    if (i >= 0 && i <= 9)
      return digits[i];
    return "";
  }

  std::string FrenchTextGenerator::getTeenName(const int64_t & i)
  {
    static const std::string teens[] = {
      "",
      "dix"
      "vingt",
      "trente",
      "quarantre",
      "cinquante",
      "soixante",
      "soixante-dix",
      "quatre-vingt",
      "quatre-vingt-dix"
    };
    if (i >= 1 && i <= 9)
      return teens[i];
    return "";
  }

}; //namespace NumberToWords
