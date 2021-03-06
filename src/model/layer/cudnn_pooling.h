/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_MODEL_LAYER_CUDNN_POOLING_H_
#define SRC_MODEL_LAYER_CUDNN_POOLING_H_
#include "singa/singa_config.h"
#ifdef USE_CUDNN
#include <cudnn.h>
#include <string>
#include <utility>
#include <vector>

#include "./pooling.h"
#include "singa/core/common.h"
#include "singa/model/layer.h"
#include "singa/proto/core.pb.h"

namespace singa {
class CudnnPooling : public Pooling {
 public:
  ~CudnnPooling();
  /// \copydoc Layer::layer_type()
  // const std::string layer_type() const override { return "CudnnPooling"; }

  void Setup(const Shape& in_sample, const LayerConf &conf) override;
  const Tensor Forward(int flag, const Tensor &input) override;
  const std::pair<Tensor, vector<Tensor>> Backward(int flag,
                                                   const Tensor &grad) override;
 private:
  /// Init cudnn related data structures.
  void InitCudnn(const Tensor& input);

 private:
  bool has_init_cudnn_ = false;
  cudnnTensorDescriptor_t x_desc_ = nullptr;
  cudnnTensorDescriptor_t y_desc_ = nullptr;
  cudnnPoolingDescriptor_t pool_desc_ = nullptr;
  cudnnNanPropagation_t nan_prop_;
};
}  // namespace singa
#endif  // USE_CUDNN
#endif  // SRC_MODEL_LAYER_CUDNN_POOLING_H_
