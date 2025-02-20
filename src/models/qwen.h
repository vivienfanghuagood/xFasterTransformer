// Copyright (c) 2023 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ============================================================================
#pragma once

#include "common_decoder.h"
#include "mlp_llama.h"
#include "rms_norm.h"
#include "rotary_embedding_qwen.h"
#include "token_embedding.h"

// TODO: Need to check FP16 KV Cache
template <typename WeiT>
class Qwen : public CommonDecoder<Attention<WeiT, QwenRotaryEmbedding, RmsNorm>, LlamaMLP<WeiT>, float> {
public:
    Qwen(const std::string &modelPath);
    ~Qwen();

    void prepareAttnMask(int *ids, int step);
    void embeddingForward(int *ids, float *output, int batchSize, int seqLen);
    void lastLayerNormForward(float *input, float *output, int rows);

private:
    void setEmbeddingWeights(const std::string &modelPath);
    void setFinalLnWeight(const std::string &modelPath);

private:
    TokenEmbedding<float16_t> *embedding;
    RmsNorm finalLN;
};