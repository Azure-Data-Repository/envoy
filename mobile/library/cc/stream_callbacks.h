#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "absl/types/optional.h"
#include "library/cc/envoy_error.h"
#include "library/cc/response_headers.h"
#include "library/cc/response_trailers.h"
#include "library/cc/stream.h"
#include "library/common/types/c_types.h"

namespace Envoy {
namespace Platform {

class Stream;
using StreamSharedPtr = std::shared_ptr<Stream>;

using OnHeadersCallback = std::function<void(ResponseHeadersSharedPtr headers, bool end_stream,
                                             envoy_stream_intel intel)>;
using OnDataCallback = std::function<void(envoy_data data, bool end_stream)>;
using OnTrailersCallback =
    std::function<void(ResponseTrailersSharedPtr trailers, envoy_stream_intel intel)>;
using OnErrorCallback = std::function<void(EnvoyErrorSharedPtr error, envoy_stream_intel intel,
                                           envoy_final_stream_intel final_intel)>;
using OnCompleteCallback =
    std::function<void(envoy_stream_intel intel, envoy_final_stream_intel final_intel)>;
using OnCancelCallback =
    std::function<void(envoy_stream_intel intel, envoy_final_stream_intel final_intel)>;
using OnSendWindowAvailableCallback = std::function<void(envoy_stream_intel intel)>;

// See library/common/types/c_types.h for what these callbacks should do.
struct StreamCallbacks : public std::enable_shared_from_this<StreamCallbacks> {
  absl::optional<OnHeadersCallback> on_headers;
  absl::optional<OnDataCallback> on_data;
  absl::optional<OnTrailersCallback> on_trailers;
  absl::optional<OnErrorCallback> on_error;
  absl::optional<OnCompleteCallback> on_complete;
  absl::optional<OnCancelCallback> on_cancel;
  absl::optional<OnSendWindowAvailableCallback> on_send_window_available;

  envoy_http_callbacks asEnvoyHttpCallbacks();
};

using StreamCallbacksSharedPtr = std::shared_ptr<StreamCallbacks>;

} // namespace Platform
} // namespace Envoy
