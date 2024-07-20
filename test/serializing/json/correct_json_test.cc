#include "caitlyn/__serializing/json.h"
#include "caitlyn/__testing/macro.h"

TEST(JsonTest, CorrectJsonMacroDocument) {
  auto config = cait::json::make_document();

  config["name"] = "John Doe";
  config["age"] = 30;

  config["array"] = cait::json::make_array();
  config["object"] = cait::json::make_object();

  config["is_student"] = false;

  config["address"] = cait::json::make_object();
  config["address"]["street"] = "123 Main St";
  config["address"]["city"] = "Anytown";
  config["address"]["zip"] = "12345";

  config["phone_numbers"] = cait::json::make_array();
  config["phone_numbers"].append("555-1234", "555-5678");

  config["skills"] = cait::json::make_array("C++", "Python", "JSON");

  config["education"] = cait::json::make_object();
  config["education"]["highschool"] = "Anytown High School";
  config["education"]["university"] = cait::json::make_object();
  config["education"]["university"]["name"] = "State University";
  config["education"]["university"]["graduation_year"] = 2020;

  config["projects"] = cait::json::make_array();
  config["projects"].append(cait::json::make_object(),
                            cait::json::make_object());

  config["projects"][0]["title"] = "Project One";
  config["projects"][0]["description"] = "Description of Project One";
  config["projects"][1]["title"] = "Project Two";
  config["projects"][1]["description"] = "Description of Project Two";

  ASSERT_FALSE(config.has_error());
}

TEST(JsonTest, CorrectJsonMacro) {
  const auto config = JSON_STRING(
    {
      "name": "John Doe",
      "age": 30,
      "array": [],
      "object": {},
      "is_student": false,
      "address": {
        "street": "123 Main St",
        "city": "Anytown",
        "zip": "12345"
      },
      "phone_numbers": [
        "555-1234",
        "555-5678" ],
      "skills": [
        "C++",
        "Python",
        "JSON"
      ],
      "education": {
        "highschool": "Anytown High School",
        "university": {
          "name": "State University",
          "graduation_year" : 2020
        }
      },
      "projects": [
        {
          "title": "Project One",
          "description": "Description of Project One"
        },
        {
          "title": "Project Two",
          "description": "Description of Project Two"
        }
      ]
    }
  );
  ASSERT_FALSE(config.has_error());
}
