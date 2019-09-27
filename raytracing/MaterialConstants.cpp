#include "material.h"

/* Found these constants at "http://www.barradeau.com/nicoptere/dump/materials.html" */

static const Material BRASS = Material("Brass",
                                       Vec3(0.780392f, 0.568627f, 0.113725f),
                                       Vec3(0.992157f, 0.941176f, 0.807843f),
                                       28,
                                       false);

static const Material PURE_GLASS = Material("Glass",
                                       Vec3(0, 0, 0),
                                       Vec3(0, 0, 0),
                                       1.5,
                                       1,
                                       true);

static const Material CHROME = Material("Chrome",
                                        Vec3(0.4f, 0.4f, 0.4f),
                                        Vec3(0.774597f, 0.774597f, 0.774597f),
                                        77,
                                        false);

static const Material TURQUOISE = Material("Turquoise",
                                           Vec3(0.396f, 0.74151f, 0.69102f),
                                           Vec3(0.297254f, 0.30829f, 0.306678f),
                                           13,
                                           false);

static const Material PEARL = Material("Pearl",
                                       Vec3(1.0f, 0.829f, 0.829f),
                                       Vec3(0.296648f, 0.296648f, 0.296648f),
                                       11,
                                       false);
