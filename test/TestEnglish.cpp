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

#include "TestEnglish.h"
#include "numbertowords/EnglishTextGenerator.h"
#include <string>

using namespace NumberToWords;

namespace arduino { namespace test
{
  //using namespace testarduino;

  //--------------------------------------------------------------------------------------------------
  void TestEnglish::SetUp()
  {
  }
  //--------------------------------------------------------------------------------------------------
  void TestEnglish::TearDown()
  {
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestEnglish, testBasic)
  {
    EnglishTextGenerator g;

    ASSERT_EQ("three"                                                      , g.getNumberName(3     ));
    ASSERT_EQ("thirty-four"                                                , g.getNumberName(34)   );
    ASSERT_EQ("three hundred forty-five"                                   , g.getNumberName(345   ));
    ASSERT_EQ("three thousand four hundred fifty-six"                      , g.getNumberName(3456  ));
    ASSERT_EQ("thirty-four thousand five hundred sixty-seven"              , g.getNumberName(34567 ));
    ASSERT_EQ("three hundred forty-five thousand six hundred seventy-eight", g.getNumberName(345678));
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestEnglish, testDigits)
  {
    EnglishTextGenerator g;

    ASSERT_EQ("",       g.getDigitName(-1));
    ASSERT_EQ("zero",   g.getDigitName(0));
    ASSERT_EQ("one",    g.getDigitName(1));
    ASSERT_EQ("two",    g.getDigitName(2));
    ASSERT_EQ("three",  g.getDigitName(3));
    ASSERT_EQ("four",   g.getDigitName(4));
    ASSERT_EQ("five",   g.getDigitName(5));
    ASSERT_EQ("six",    g.getDigitName(6));
    ASSERT_EQ("seven",  g.getDigitName(7));
    ASSERT_EQ("eight", g.getDigitName(8));
    ASSERT_EQ("nine",   g.getDigitName(9));
    ASSERT_EQ("",       g.getDigitName(10));
  }
  //--------------------------------------------------------------------------------------------------
} // End namespace test
} // End namespace arduino
