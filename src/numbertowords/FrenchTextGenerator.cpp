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
#include "rapidassist/strings.h"

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
      if (i == 80) //20 et 100 s'accordent quand ils sont multipliés par un nombre sans être suivis par un autre nombre.
      {
        left_string.append("s");
        return left_string;
      }
      else if (i >= 70 && i <= 79) //handle 70-79 range
      {
        right_string = getNumberName(i-60, iDepth+1);
      }
      else if (i >= 90 && i <= 99) //handle 90-99 range
      {
        if (i == 90)
          return left_string;
        
        //from 90s to 80s
        left--;
        left_string = gTens[left];

        right_string = getNumberName(i-80, iDepth+1);
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
      int64_t left = i / HUNDRED;
      int64_t right = i % HUNDRED;
      std::string left_string = getNumberName(left, iDepth+1);
      std::string right_string = (right == 0 ? "" : getNumberName(right, iDepth+1));
      if (right == 0) //20 et 100 s'accordent quand ils sont multipliés par un nombre sans être suivis par un autre nombre.
      {
        return left_string + " cents";
      }
      return left_string + " cent " + right_string;
    }
    else if ( i <= 1999 )
    {
      return "mille " + getNumberName(i % THOUSAND, iDepth+1);
    }
    else if ( i <= 999999 )
    {
      int64_t left = i / THOUSAND;
      int64_t right = i % THOUSAND;
      std::string left_string = getNumberName(left, iDepth+1);
      std::string right_string = (right == 0 ? "" : getNumberName(right, iDepth+1));
      
      //remove any plurial form since we are adding "mille"
      ra::strings::strReplace(left_string, "cents", "cent");

      //continue with adding the right side
      left_string.append(" mille"); // Mille est toujours invariable
      if (!right_string.empty())
      {
        return left_string + " " + right_string;
      }
      return left_string;
    }
    else if ( i <= 1999999 )
    {
      return "un million " + getNumberName(i % MILLION, iDepth+1);
    }
    else if ( i <= 999999999)
    {
      int64_t left = i / MILLION;
      int64_t right = i % MILLION;
      std::string left_string = getNumberName(left, iDepth+1);
      std::string right_string = (right == 0 ? "" : getNumberName(right, iDepth+1));
      
      left_string.append(" millions"); // Millier, million et milliard sont des noms et non des adjectifs. Ils ne font pas vraiment partie du nombre et laissent place à l'accord
      if (!right_string.empty())
      {
        return left_string + " " + right_string;
      }
      return left_string;
    }
    else if ( i <= 1999999999 )
    {
      return "un milliard " + getNumberName(i % BILLION, iDepth+1);
    }
    else
    {
      int64_t left = i / BILLION;
      int64_t right = i % BILLION;
      std::string left_string = getNumberName(left, iDepth+1);
      std::string right_string = (right == 0 ? "" : getNumberName(right, iDepth+1));
      
      left_string.append(" milliards"); // Millier, million et milliard sont des noms et non des adjectifs. Ils ne font pas vraiment partie du nombre et laissent place à l'accord
      if (!right_string.empty())
      {
        return left_string + " " + right_string;
      }
      return left_string;
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
