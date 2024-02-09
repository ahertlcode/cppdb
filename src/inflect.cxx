#include "inflect.h"

map<string, string> Inflect::plural = {
    {"(quiz)$", "$1zes"},
    {"^(oxen)$", "$1"},
    {"^(ox)$", "$1en"},
    {"([m|l])ice$", "$1ice"},
    {"([m|l])ouse$", "$1ice"},
    {"(matr|vert|ind)ix|ex$", "$1ices"},
    {"(x|ch|ss|sh)$", "$1es"},
    {"([^aeiouy]|qu)y$", "$1ies"},
    {"(hive)$", "$1s"},
    {"(?:([^f])fe|([lr])f)$", "$1$2ves"},
    {"(shea|lea|loa|thie)f$", "$1ves"},
    {"sis$", "ses"},
    {"([ti])a$", "$1a"},
    {"([ti])um$", "$1a"},
    {"(buffal|tomat|potat|ech|her|vet)o$", "$1oes"},
    {"(bu)s$", "$1ses"},
    {"(alias|status)$", "$1es"},
    {"(octop|vir)i$", "$1i"},
    {"(octop|vir)us$", "$1i"},
    {"(ax|test)is$", "$1es"},
    {"(us)$", "$1es"},
    {"s$", "s"}
};

map<string, string> Inflect::plural_nos = {
    {"$", "s"}
};

map<string, string> Inflect::singular = {
    { "(ss)$", "$1" },
    { "(database)s$", "$1" },
    { "(quiz)zes$", "$1" },
    { "(matr)ices$", "$1ix" },
    { "(vert|ind)ices$", "$1ex" },
    { "^(ox)en$", "$1" },
    { "(alias|status)(es)?$", "$1" },
    { "(octop|vir)i$", "$1us" },
    { "^(a)x[ie]s$", "$1xis" },
    { "(cris|ax|test)es$", "$1is" },
    { "(cris|ax|test)is$", "$1is" },
    { "(shoe|foe)s$", "$1" },
    { "(bus)es$", "$1" },
    { "^(toe)s$", "$1" },
    { "(o)es$", "$1" },
    { "([m|l])ice$", "$1ouse" },
    { "(x|ch|ss|sh)es$", "$1" },
    { "(m)ovies$", "$1ovie" },
    { "(s)eries$", "$1eries" },
    { "([^aeiouy]|qu)ies$", "$1y" },
    { "([lr])ves$", "$1f" },
    { "(tive)s$", "$1" },
    { "(hive)s$", "$1" },
    { "(li|wi|kni)ves$", "$1fe" },
    { "([^f])ves$", "$1fe" },
    { "(shea|loa|lea|thie)ves$", "$1f" },
    { "^(analy)(sis|ses)$", "$1sis" },
    { "((a)naly|(b)a|(d)iagno|(p)arenthe|(p)rogno|(s)ynop|(t)he)(sis|ses)", "$1$2sis" },
    { "([ti])a$", "$1um" },
    { "(n)ews$", "$1ews" },
    { "(h|bl)ouses$", "$1ouse" },
    { "(corpse)s$", "$1" },
    { "(use)s$", "$1" },
    { "s$", "" }
};

unordered_map<string, string> Inflect::irregular = {
    { "zombie", "zombies" },
    { "move", "moves" },
    { "foot", "feet" },
    { "goose", "geese" },
    { "sex", "sexes" },
    { "child", "children" },
    { "man", "men" },
    { "tooth", "teeth" },
    { "person", "people" }
};

unordered_map<string, bool> Inflect::uncountable = {
    { "sheep", true },
    { "fish", true },
    { "deer", true },
    { "series", true },
    { "species", true },
    { "money", true },
    { "rice", true },
    { "information", true },
    { "equipment", true },
    { "jeans", true },
    { "police", true }
};