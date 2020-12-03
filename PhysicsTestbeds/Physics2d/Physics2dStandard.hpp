#pragma once

#include "Physics2dCoreStandard.hpp"

namespace Zero
{

//-------------------------------------------------------------------Physics2dLibrary
class ZeroNoImportExport Physics2dLibrary : public Zilch::StaticLibrary
{
public:
  ZilchDeclareStaticLibraryInternals(Physics2dLibrary, "ZeroEngine");

  static void Initialize();
  static void Shutdown();
};

}//namespace Zero
