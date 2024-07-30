#include "Caitlyn/__Serializing/Json.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(JsonTest, IoOperator)
{
    const auto oconfig = JSON_STRING({
        "name": {"first": "John", "last": "Doe"},
        "age": 30,
        "address": {"street": "123 Main St", "city": "Anytown", "zip": "12345"},
        "phone_numbers": ["555-1234", "555-5678"]
    });
    ASSERT_FALSE(oconfig.HasError());

    std::ofstream ofile{"operator_test.json"};
    if (ofile.is_open())
    {
        ofile << oconfig;
        ofile.close();
    }
    auto iconfig = Caitlyn::Json::MakeDocument();

    std::ifstream ifile{"operator_test.json"};
    if (ifile.is_open())
    {
        ifile >> iconfig;
        ofile.close();
    }

    ASSERT_FALSE(iconfig.HasError());
    ASSERT_EQ(oconfig.ToString(), iconfig.ToString());
}
