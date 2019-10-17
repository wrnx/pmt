
#include "algorithms.h"

#include <string.h>
#include "algorithms/aho_corasick.h"
#include "algorithms/boyer_moore.h"
#include "algorithms/ukkonen.h"
#include "algorithms/wu_manber.h"

static const struct algorithm algorithms[] = {
        {"ac",  "Aho-Corasick (1975)",                 0, 1, &aho_corasick_search},
        {"bm",  "Boyer-Moore (1977)",                  0, 0, &boyer_moore_search},
        {"uk",  "Ukkonen (1985)",                      1, 0, &ukkonen_search},
        {"wm",  "Wu-Manber (1992)",                    1, 0, &wu_manber_search},
        {NULL,  NULL,                                  0, 0, NULL}
};

const struct algorithm *get_algorithms(void) {
    return algorithms;
}

const struct algorithm *get_algorithm(const char *const algorithm_id) {
    int i = 0;
    const struct algorithm *algorithm;

    for (i = 0; (algorithm = &algorithms[i])->id != NULL; ++i)
        if (strcmp(algorithm_id, algorithm->id) == 0)
            return algorithm;

    return NULL;
}

const struct algorithm *choose_algorithm(const struct search_context *const ctx) {
    return get_algorithm(ctx->edit_distance > 0 ? "wm" : (ctx->num_patterns > 1 ? "ac" : "bm"));
}
