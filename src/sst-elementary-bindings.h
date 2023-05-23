#include "Runtime.h"

#include "dumb_delay.h"

namespace sst::elementary
{
template <typename FloatType> void registerSSTElementaryBindings(elem::Runtime<FloatType> &runtime)
{
    runtime.registerNodeType("baconNode",
                             [](elem::NodeId const id, double sampleRate, int const blockSize) {
                                 return std::make_shared<BaconNode<FloatType>>(id, sampleRate, blockSize);
                             });
}
} // namespace sst::elementary
