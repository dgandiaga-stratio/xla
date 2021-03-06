#pragma once

#include <vector>

#include "tensorflow/compiler/xla/client/xla_builder.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace torch_xla {

xla::XlaOp PadToSize(xla::XlaOp input, xla::XlaOp pad_value,
                     tensorflow::gtl::ArraySlice<const xla::int64> size);

std::vector<xla::XlaOp> CreateKthValue(xla::XlaOp input, xla::int64 k,
                                       xla::int64 dim, bool keepdim);

std::vector<xla::XlaOp> CreateTopK(xla::XlaOp input, xla::int64 k,
                                   xla::int64 dim, bool largest, bool sorted);

xla::XlaOp CreateMatMul(xla::XlaOp lhs, xla::XlaOp rhs);

xla::XlaOp BuildBernoulli(xla::XlaOp probability, const xla::Shape& shape);

xla::XlaOp BuildDropout(xla::XlaOp input, float probability);

xla::XlaOp BuildRandperm(xla::int64 n, xla::PrimitiveType element_type,
                         xla::XlaBuilder* builder);

std::vector<xla::XlaOp> CreateBroadcastTensors(
    tensorflow::gtl::ArraySlice<const xla::XlaOp> operands);

// Similar to tf.gather_nd, used to implement advanced indexing.
xla::XlaOp CreateIndex(xla::XlaOp input, xla::XlaOp indices,
                       xla::int64 start_dim);

// Similar to tf.scatter_nd, used to implement advanced indexing updates.
xla::XlaOp CreateIndexUpdate(
    xla::XlaOp buffer, xla::XlaOp indices, xla::int64 start_dim,
    xla::XlaOp updates,
    const std::function<xla::XlaOp(xla::XlaOp, xla::XlaOp)>& combiner);

xla::XlaOp CreateIndexAdd(xla::XlaOp buffer, xla::int64 dim, xla::XlaOp index,
                          xla::XlaOp value);

xla::XlaOp CreateIndexCopy(xla::XlaOp buffer, xla::int64 dim, xla::XlaOp index,
                           xla::XlaOp value);

xla::XlaOp CreateIndexFill(xla::XlaOp buffer, xla::int64 dim, xla::XlaOp index,
                           xla::XlaOp values);

using XlaOpCombiner = std::function<xla::XlaOp(xla::XlaOp, xla::XlaOp)>;

XlaOpCombiner NumericAddCombiner();

// Used to lower scatter and scatter_add.
xla::XlaOp CreateScatter(xla::XlaOp input, xla::XlaOp index, xla::XlaOp source,
                         xla::int64 dim, const XlaOpCombiner& combiner);

xla::XlaOp CreatePut(xla::XlaOp input, xla::XlaOp index, xla::XlaOp source,
                     bool accumulate);

std::vector<xla::XlaOp> BuildNonZero(xla::XlaOp input);

std::vector<xla::XlaOp> BuildMaskedSelect(xla::XlaOp input, xla::XlaOp mask);

}  // namespace torch_xla
