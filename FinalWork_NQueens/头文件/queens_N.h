#pragma once
#include <iostream>
#include<omp.h>
#include<math.h>
#include<time.h>

__int64 queens_Normal(int n);
__int64 queens_Opti(int n);
__int64 queens_Opti_Parallel(int n);

