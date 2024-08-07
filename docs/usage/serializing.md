# JSON

The JSON format is crucial for web development, API integration, and any
applications that need efficient data exchange in a structured format.

- `JsonDocument`: Provides comprehensive support for JSON handling.
  Facilitates parsing, generating, and manipulating JSON data structures.
  Enables easy serialization of complex data into JSON format for storage or
  transmission, and deserialization of JSON back into native data structures.
  Offers efficient methods for encoding and decoding JSON, handling nested
  objects and arrays, ensuring compatibility across various platforms and
  systems.

## Usage

- Brackets operator

```c++
#include <Caitlyn/IO>
#include <Caitlyn/Serializing>

using namespace Caitlyn;
using namespace Caitlyn::Json;

int main()
{
    auto config = MakeDocument();
    config["name"] = MakeObject();
    config["name"]["first"] = "John";
    config["name"]["last"] = "Doe";
    config["age"] = 30;
    config["address"] = MakeObject();
    config["address"]["street"] = "123 Main St";
    config["address"]["city"] = "Anytown";
    config["address"]["zip"] = "12345";
    config["phone_numbers"] = MakeArray("555-1234", "555-5678");
    
    OutputStream::WriteLine(config);
    return 0;
}
```

- Native JSON

```c++
#include <Caitlyn/IO>
#include <Caitlyn/Serializing>

using namespace Caitlyn;

int main()
{
    const auto config = JSON_STRING(
        {
            "name": {
                 "first": "John",
                "last": "Doe"
            },
            "age": 30,
            "address": {
                "street": "123 Main St",
                "city": "Anytown",
                "zip": "12345"
            },
            "phone_numbers": [
                "555-1234",
                "555-5678"
            ]
        }
    );
    OutputStream::WriteLine(config);
    return 0;
}
```

- Optimized output

```c++
config.ToString();
```

- Structured output

```c++
// Pass true and optional indent width (2 by default)
config.ToString(true);
config.ToString(true, 4);
```

### Output

```json
{"name":{"first":"John","last":"Doe"},"age":30,"address":{"street":"123 Main St","city":"Anytown","zip":"12345"},"phone_numbers":["555-1234","555-5678"]}
```

```json
{
    "name": {
        "first": "John",
        "last": "Doe"
    },
    "age": 30,
    "address": {
        "street": "123 Main St",
        "city": "Anytown",
        "zip": "12345"
    },
    "phone_numbers": [
        "555-1234",
        "555-5678"
    ]
}
```
