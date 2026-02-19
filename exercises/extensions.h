#ifndef EXTENSIONS_H

#define PACK_FOUR_CHAR(a, b, c, d) \
  a | (b << 8) | (c << 16) | (d << 24)

const int HTML = PACK_FOUR_CHAR('h', 't', 'm', 'l');
const int CSS = PACK_FOUR_CHAR('c', 's', 's', '\0');
const int JS = PACK_FOUR_CHAR('j', 's', '\0', '\0');
const int PNG = PACK_FOUR_CHAR('p', 'n', 'g', '\0');
const int JPG = PACK_FOUR_CHAR('j', 'p', 'g', '\0');
const int GIF = PACK_FOUR_CHAR('g', 'i', 'f', '\0');
const int SVG = PACK_FOUR_CHAR('s', 'v', 'g', '\0');
const int ICO = PACK_FOUR_CHAR('i', 'c', 'o', '\0');

char* extension_to_content_type(const char* ext);

#endif
