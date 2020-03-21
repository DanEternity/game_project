#pragma once

//
// This file contain utility function to help
// parse input conditions and other
//
//

#include "compilerTemplatesFormat.h"

int convertMarkerToLine(CompilerCommandTemplateDataBuffer * buffer, std::wstring marker);

std::wstring convertExtReferences(CompilerCommandTemplateDataBuffer * buffer, std::wstring line);

ComparatorElement parseCondition(std::wstring s);