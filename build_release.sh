#!/usr/bin/env sh
mkdir -p release
cd release
cmake -DCPT_WITH_OMP=0 -DDAE_WITH_MPI=0 -DCMAKE_BUILD_TYPE=Release  ..
make
cd ..
