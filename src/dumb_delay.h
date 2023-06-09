#include "GraphNode.h"
#include <array>

template<typename FloatType>
struct BaconNode : elem::GraphNode<FloatType>
{
    using elem::GraphNode<FloatType>::GraphNode;

    void setProperty(std::string const& key, elem::js::Value const& val) override
    {
       if (key == "value") {
          value.store((elem::js::Number) val);
       }
    }

    static constexpr size_t bs{1<<14};
    std::array<FloatType, bs> delayBuffer{};
    int wp{0};
    void process (elem::BlockContext<FloatType> const& ctx) override
    {
       auto** inputData = ctx.inputData;
       auto* outputData = ctx.outputData;
       auto numChannels = ctx.numInputChannels;
       auto numSamples = ctx.numSamples;

       if (numChannels < 1)
          return (void) std::fill_n(outputData, numSamples, FloatType(0));

       // Copy the first input to the output buffer
       for (size_t i = 0; i < numSamples; ++i) {
          outputData[i] = 0.5 * inputData[0][i] + 0.5 * delayBuffer[wp];
          delayBuffer[wp] = inputData[0][i];
          wp = (wp+1)&(bs-1);
       }
    }

    std::atomic<FloatType> value { 0 };

};
 
    // More BP Hack
 //   proxy->runtime.registerNodeType("baconNode",
  //                          [](elem::NodeId const id, double sampleRate, int const blockSize) {
   //                             return std::make_shared<BaconNode>(id, sampleRate, blockSize);
    //                        });
 
// A simple wrapper for calling to createNode
// let baconNode = (...children) => createNode("baconNode", {}, children);
 
