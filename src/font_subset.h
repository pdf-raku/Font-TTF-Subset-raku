#ifndef __SFNT_SUBSET_H
#define __SFNT_SUBSET_H

#include <stdint.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FONT_FORMATS_H

struct _sfntSubset {
    // 1 - 1 mapping of existing characters and gids
    // charset_len <= gid_len
    FT_ULong *charset;
    FT_UInt *gids;
    // - gids in range 0 ..^ charset_len are mapped to gids
    // - gids in range charset_len ..^ gids_len are additional components
    size_t charset_len;
    size_t gids_len;   // used size
    size_t gids_size;  // allocated size
    char *fail;
};

typedef struct _sfntSubset sfntSubset;
typedef sfntSubset *sfntSubsetPtr;

#define FONT_SUBSET_WARN(msg) fprintf(stderr, __FILE__ ":%d: %s\n", __LINE__, (msg));

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT extern
#endif

DLLEXPORT sfntSubsetPtr sfnt_subset_create(FT_Face, FT_ULong*, size_t);
DLLEXPORT void font_subset_fail(sfntSubsetPtr, const char*);
DLLEXPORT void font_subset_done(sfntSubsetPtr);

#endif /* __SFNT_SUBSET_H */
