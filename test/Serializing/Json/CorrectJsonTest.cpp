#include "Caitlyn/__Serializing/Json.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(JsonTest, CorrectJsonMacroDocument)
{
    auto config = Caitlyn::Json::MakeDocument();

    config["name"] = "John Doe";
    config["age"] = 30;

    config["array"] = Caitlyn::Json::MakeArray();
    config["object"] = Caitlyn::Json::MakeObject();

    config["is_student"] = false;

    config["address"] = Caitlyn::Json::MakeObject();
    config["address"]["street"] = "123 Main St";
    config["address"]["city"] = "Anytown";
    config["address"]["zip"] = "12345";

    config["phone_numbers"] = Caitlyn::Json::MakeArray();
    config["phone_numbers"].Append("555-1234", "555-5678");

    config["skills"] = Caitlyn::Json::MakeArray("C++", "Python", "JSON");

    config["education"] = Caitlyn::Json::MakeObject();
    config["education"]["highschool"] = "Anytown High School";
    config["education"]["university"] = Caitlyn::Json::MakeObject();
    config["education"]["university"]["name"] = "State University";
    config["education"]["university"]["graduation_year"] = 2020;

    config["projects"] = Caitlyn::Json::MakeArray();
    config["projects"].Append(Caitlyn::Json::MakeObject(), Caitlyn::Json::MakeObject());

    config["projects"][0]["title"] = "Project One";
    config["projects"][0]["description"] = "Description of Project One";
    config["projects"][1]["title"] = "Project Two";
    config["projects"][1]["description"] = "Description of Project Two";

    ASSERT_FALSE(config.HasError());
}

TEST(JsonTest, CorrectJsonMacro)
{
    const auto config = JSON_STRING({
        "name": "John Doe",
        "age": 30,
        "array": [],
        "object": {},
        "is_student": false,
        "address": {"street": "123 Main St", "city": "Anytown", "zip": "12345"},
        "phone_numbers": ["555-1234", "555-5678"],
        "skills": ["C++", "Python", "JSON"],
        "education":
            {"highschool": "Anytown High School", "university": {"name": "State University", "graduation_year": 2020}},
        "projects": [
            {"title": "Project One", "description": "Description of Project One"},
            {"title": "Project Two", "description": "Description of Project Two"}
        ]
    });
    ASSERT_FALSE(config.HasError());
}
