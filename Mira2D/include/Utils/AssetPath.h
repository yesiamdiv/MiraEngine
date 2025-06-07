#pragma once

#ifndef ASSET_PATH
#define ASSET_PATH ""
#endif

// Define the macro for getting asset paths if not already defined
#ifndef GET_ASSET_PATH
#define GET_ASSET_PATH(file) ASSET_PATH "/" file
#endif