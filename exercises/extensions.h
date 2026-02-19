#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#define PACK_FOUR_CHAR(a, b, c, d) \
  a | (b << 8) | (c << 16) | (d << 24)

#define HTML PACK_FOUR_CHAR('h', 't', 'm', 'l')
#define CSS PACK_FOUR_CHAR('c', 's', 's', '\0')
#define JS PACK_FOUR_CHAR('j', 's', '\0', '\0')
#define WASM PACK_FOUR_CHAR('w', 'a', 's', 'm')
#define WEBP PACK_FOUR_CHAR('w', 'e', 'b', 'p')
#define PNG PACK_FOUR_CHAR('p', 'n', 'g', '\0')
#define JPG PACK_FOUR_CHAR('j', 'p', 'g', '\0')
#define GIF PACK_FOUR_CHAR('g', 'i', 'f', '\0')
#define SVG PACK_FOUR_CHAR('s', 'v', 'g', '\0')
#define ICO PACK_FOUR_CHAR('i', 'c', 'o', '\0')

char* extension_to_content_type(const char* ext);

#endif
