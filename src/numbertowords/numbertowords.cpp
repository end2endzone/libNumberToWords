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

#include "numbertowords/numbertowords.h"
#include <cstdio>

namespace NumberToWords
{

  ITextGenerator::ITextGenerator()
  {
  }

  ITextGenerator::~ITextGenerator()
  {
  }

  FrenchTextGenerator::FrenchTextGenerator()
  {
  }

  FrenchTextGenerator::~FrenchTextGenerator()
  {
  }

  std::string FrenchTextGenerator::getNumberName(const int64_t & i)
  {
    return std::string();
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
      "soixante dix",
      "quatre vingt",
      "quatre vingt dix"
    };
    if (i >= 1 && i <= 9)
      return teens[i];
    return "";
  }

}; //namespace NumberToWords
