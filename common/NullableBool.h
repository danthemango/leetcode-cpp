#include <string>

// a nullable boolean value
enum class NullableBool {
    nbNull,
    nbTrue,
    nbFalse
};

// returns the stringified version of nb
// nbNull -> null
// nbTrue -> true
// nbFalse -> false
std::string nullableBool2string(NullableBool nb);

// tries to parse a nullable boolean value,
// returning true if possible
// filling out_nb with the value
bool tryParseNullableBool(const std::string& input, unsigned int& i, NullableBool& out_nb);
