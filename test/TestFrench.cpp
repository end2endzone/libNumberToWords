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

#include "TestFrench.h"
#include "numbertowords/FrenchTextGenerator.h"
#include "rapidassist/filesystem.h"
#include <string>

using namespace NumberToWords;

namespace arduino { namespace test
{
  //using namespace testarduino;

  //--------------------------------------------------------------------------------------------------
  void TestFrench::SetUp()
  {
  }
  //--------------------------------------------------------------------------------------------------
  void TestFrench::TearDown()
  {
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestFrench, testBasic)
  {
    FrenchTextGenerator g;

    ASSERT_EQ("trois"                                                    , g.getNumberName(3     ));
    ASSERT_EQ("trente-quatre"                                            , g.getNumberName(34    ));
    ASSERT_EQ("trois cent quarante-cinq"                                 , g.getNumberName(345   ));
    ASSERT_EQ("trois mille quatre cent cinquante-six"                    , g.getNumberName(3456  ));
    ASSERT_EQ("trente-quatre mille cinq cent soixante-sept"              , g.getNumberName(34567 ));
    ASSERT_EQ("trois cent quarante-cinq mille six cent soixante-dix-huit", g.getNumberName(345678));
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestFrench, test70s)
  {
    FrenchTextGenerator g;

    ASSERT_EQ("soixante-neuf",      g.getNumberName(69));
    ASSERT_EQ("soixante-dix",       g.getNumberName(70));
    ASSERT_EQ("soixante et onze",   g.getNumberName(71));
    ASSERT_EQ("soixante-douze",     g.getNumberName(72));
    ASSERT_EQ("soixante-treize",    g.getNumberName(73));
    ASSERT_EQ("soixante-quatorze",  g.getNumberName(74));
    ASSERT_EQ("soixante-quinze",    g.getNumberName(75));
    ASSERT_EQ("soixante-seize",     g.getNumberName(76));
    ASSERT_EQ("soixante-dix-sept",  g.getNumberName(77));
    ASSERT_EQ("soixante-dix-huit",  g.getNumberName(78));
    ASSERT_EQ("soixante-dix-neuf",  g.getNumberName(79));
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestFrench, testAccords)
  {
    FrenchTextGenerator g;

    ASSERT_EQ("quatre-vingts"           , g.getNumberName(80));
    ASSERT_EQ("quatre-vingt-trois"      , g.getNumberName(83));
    ASSERT_EQ("quatre cents"            , g.getNumberName(400));
    ASSERT_EQ("quatre cent vingt et un" , g.getNumberName(421));
    ASSERT_EQ("quatre cents millions"   , g.getNumberName(400000000));
    ASSERT_EQ("deux cent mille"         , g.getNumberName(200000));
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestFrench, testDash) //and "et"
  {
    FrenchTextGenerator g;

    ASSERT_EQ("trente-cinq", g.getNumberName(35));
    ASSERT_EQ("cent trente-cinq", g.getNumberName(135));
    ASSERT_EQ("quatre-vingt-trois", g.getNumberName(83));
    ASSERT_EQ("deux mille huit cent vingt-quatre", g.getNumberName(2824));
    ASSERT_EQ("six cent un", g.getNumberName(601));
    ASSERT_EQ("cent trente et un", g.getNumberName(131));
    ASSERT_EQ("soixante et onze", g.getNumberName(71));
    ASSERT_EQ("quatre-vingt-un", g.getNumberName(81));
    ASSERT_EQ("quatre-vingt-onze", g.getNumberName(91));
  }
  //--------------------------------------------------------------------------------------------------
  TEST(TestFrench, testDigits)
  {
    FrenchTextGenerator g;

    ASSERT_EQ("",       g.getDigitName(-1));
    ASSERT_EQ("zéro",   g.getDigitName(0));
    ASSERT_EQ("un",     g.getDigitName(1));
    ASSERT_EQ("deux",   g.getDigitName(2));
    ASSERT_EQ("trois",  g.getDigitName(3));
    ASSERT_EQ("quatre", g.getDigitName(4));
    ASSERT_EQ("cinq",   g.getDigitName(5));
    ASSERT_EQ("six",    g.getDigitName(6));
    ASSERT_EQ("sept",   g.getDigitName(7));
    ASSERT_EQ("huit",   g.getDigitName(8));
    ASSERT_EQ("neuf",   g.getDigitName(9));
    ASSERT_EQ("",       g.getDigitName(10));
  }
  //--------------------------------------------------------------------------------------------------
  std::string getFrenchTestFilename(int i)
  {
    char buffer[1024];
    sprintf(buffer, "test_files\\french_%06d_to_%06d.txt", i, i+9999);

    std::string path = buffer;
    ra::filesystem::normalizePath(path);

    return path;
  }
  std::vector<std::string> loadFile(const char * iFilePath)
  {
    std::vector<std::string> lines;
    if ( !ra::filesystem::fileExists(iFilePath) )
      return lines;
    
    FILE * f = fopen(iFilePath, "r");
    if (!f)
      return lines;

    static const int BUFFER_SIZE = 10240;
    char buffer[BUFFER_SIZE];
    while( fgets(buffer, BUFFER_SIZE, f) != NULL )
    {
      ra::strings::removeEOL(buffer);

      lines.push_back(buffer);
    }

    return lines;
  }
  TEST(TestFrench, testFull)
  {
    FrenchTextGenerator g;

    bool show_progress = true;

    for(int i=0; i<990000; i+=10000)
    {
      std::string filename = getFrenchTestFilename(i);
      
      //progress
      if (show_progress)
      {
        printf("Processing file: %s\n", filename.c_str());
      }

      //load file
      ASSERT_TRUE( ra::filesystem::fileExists(filename.c_str()) ) << "File not found: " << filename.c_str();
      std::vector<std::string> lines = loadFile(filename.c_str());
      ASSERT_TRUE( lines.size() != 0 );
      
      //for each lines in the file
      int numLines = (int)lines.size();
      for(int j=0; j<numLines; j++)
      {
        //compute expected and actual values
        int64_t value = i+j;
        std::string expectedName = lines[j];
        std::string actualName = g.getNumberName(value);

        //assert
        ASSERT_EQ(expectedName, actualName) << "Failed converting " << ra::strings::toString(value).c_str() << ". Expected '" << expectedName.c_str() << "' but received '" << actualName.c_str() << "'.";

        //progress every 200 lines.
        if (show_progress && j%200 == 0)
        {
          int percent = (j*100)/numLines;
          printf("%d%%... ", percent);
        }
      }

      //progress: end of % progress
      if (show_progress)
      {
        printf("\n");
      }
    }
  }
  //--------------------------------------------------------------------------------------------------
} // End namespace test
} // End namespace arduino
