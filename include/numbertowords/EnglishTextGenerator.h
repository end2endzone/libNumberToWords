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

#ifndef ENSLIGHTEXTGENERATOR_H
#define ENSLIGHTEXTGENERATOR_H

#ifdef NUMBERTOWORDS_BUILT_AS_SHARED
#include "export.h"
#endif

#ifndef NUMBERTOWORDS_EXPORT
#define NUMBERTOWORDS_EXPORT
#endif

#include "ITextGenerator.h"
namespace NumberToWords
{

  class NUMBERTOWORDS_EXPORT EnglishTextGenerator : public virtual ITextGenerator
  {
  public:
    EnglishTextGenerator();
    virtual ~EnglishTextGenerator();

    virtual std::string getNumberName(const int64_t & i);
    virtual std::string getDigitName(const int64_t & i);

  protected:
    virtual std::string getNumberName(const int64_t & i, int iDepth);

  };

}; //namespace NumberToWords

#endif //ENSLIGHTEXTGENERATOR_H
