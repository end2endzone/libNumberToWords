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
    "soixante", "soixante" /*-dix*/, 
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
    else if ( i <= 99 )
    {
      int64_t left = i / 10 - 2;
      int64_t right = i % 10;
      std::string left_string = gTens[left];
      std::string right_string = getNumberName(right, iDepth+1);
      if (i >= 70 && i <= 79) //handle 70-79 range
      {
        right_string = getNumberName(i-60, iDepth+1);
      }
      if (right_string.empty())
        return left_string;
      const char * conjonction = "";
      if ( i != 81 && i != 91 && (i%10)==1 ) //nombre se terminant par 1, sauf 81 et 91
        conjonction = " et "; //Pour les nombres se terminant en 1, on ajoute la conjonction `et`
      else
        conjonction = "-"; //Prennent un trait d'union tous les nombres composés inférieurs à 100 ne se terminant pas en 1 sauf 81 et 91.
      left_string.append(conjonction);
      left_string.append(right_string);
      return left_string;
    }
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
