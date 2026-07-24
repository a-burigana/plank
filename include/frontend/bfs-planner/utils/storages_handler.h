// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef PLANK_STORAGES_HANDLER_H
#define PLANK_STORAGES_HANDLER_H

#include "../../../lib/utils/storage.h"
#include "../../../lib/utils/label_storage.h"
#include "../signatures/signature.h"

using namespace plank;
using namespace utils;

namespace search::utils {
    class storages_handler {
    public:
        using signature_storage     = storage<signature>;
        using signature_set_storage = storage<signature_set>;

        storages_handler() = default;

        auto &get_label_storage() { return m_lab_storage; }
        auto &get_signature_storage() { return m_sig_storage; }
        auto &get_signature_set_storage() { return m_sig_set_storage; }

    private:
        label_storage m_lab_storage;
        signature_storage m_sig_storage;
        signature_set_storage m_sig_set_storage;
    };

    using storages_handler_ptr = std::shared_ptr<storages_handler>;
}

#endif //PLANK_STORAGES_HANDLER_H
