//
// Created by Paul Walker on 5/11/23.
//

#include "Realtime.h"
#include "sst-elementary-bindings.h"

int main(int argc, char **argv)
{
    return RealtimeMain(argc, argv, [](auto &a){
        sst::elementary::registerSSTElementaryBindings<float>(a);
    });
}