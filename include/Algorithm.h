#pragma once

#include <memory>
#include <string>
#include "Evaluator.h"
#include "Gallery.h"
#include "LayoutState.h"
#include "Show.h"

namespace gallery {

class Algorithm {
public:
    virtual ~Algorithm() = default;
    virtual LayoutState solve(const Gallery& gallery, const Show& show, const Evaluator& evaluator) = 0;
    virtual std::string name() const = 0;
};

std::unique_ptr<Algorithm> createAlgorithm(const std::string& name);

}  // namespace gallery
