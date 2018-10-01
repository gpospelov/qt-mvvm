# Specifications for json SessionItem format


## List of values - same as QJsonValue

+ QJsonValue::Null
+ QJsonValue::Bool
+ QJsonValue::Double
+ QJsonValue::String
+ QJsonValue::Array
+ QJsonValue::Object
+ QJsonValue::Undefined

+ double
+ int
+ string

## Json objects

```

# Parameter

"ItemData" : [
    {
        "type" : "double",
        "role" : 0,
        "value" : 0.01
    },
    {
        "type" : "string",
        "role" : 0,
        "value" : "Cylinder"
    },
    {
        "type" : "ComboProperty",
        "role" : 1,
        "current_index" : 0,
        "values" : ["Aniso Pyramid", "Box", "Cone", "Cone6", "Cuboctahedron", "Cylinder"]
    }
]



```

