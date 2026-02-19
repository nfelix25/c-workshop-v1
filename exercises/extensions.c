#include "extensions.h"

char* extension_to_content_type (const char* ext) {
  switch (*(int *)ext) {
    case HTML:
      return "text/html";
    case CSS:
      return "text/css";
    case JS:
      return "application/javascript";
    case PNG:
      return "image/png";
    case JPG:
      return "image/jpeg";
    case GIF:
      return "image/gif";
    case SVG:
      return "image/svg+xml";
    case ICO:
      return "image/x-icon";
    default:
      return "application/octet-stream";
  }
}
