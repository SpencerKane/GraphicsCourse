#include "material.h"

/* Found these constants at "http://www.barradeau.com/nicoptere/dump/materials.html" */

static const Material BRASS = Material("Brass",
                                       0.4f,
                                       0.87f,
                                       28,
                                       false,
                                       Vec3(181.0f/255.0f, 166.0f/255.0f, 66.0f/255.0f));

static const Material PURE_GLASS = Material("Glass",
                                       1.0f,
                                       1.0f,
                                       1.5,
                                       1,
                                       true,
                                       Vec3(255.0f/255.0f, 255.0f/255.0f, 255/255.0f));

static const Material AIR = Material("Air",
                                     1.0f,
                                     1.0f,
                                     1,
                                     1,
                                     true,
                                     Vec3(255/255.0f, 255/255.0f, 255/255.0f));

static const Material CHROME = Material("Chrome",
                                        0.4f,
                                        0.774597f,
                                        77,
                                        false,
                                        Vec3(219.0f/255.0f, 228.0f/255.0f, 235.0f/255.0f));

static const Material TURQUOISE = Material("Turquoise",
                                           0.6f,
                                           0.33f,
                                           13,
                                           false,
                                           Vec3(64.0f/255.0f, 224.0f/255.0f, 208.0f/255.0f));

static const Material PEARL = Material("Pearl",
                                       0.87f,
                                       0.296648f,
                                       11,
                                       false,
                                       Vec3(234.0f/255.0f, 224.0f/255.0f, 200.0f/255.0f));
