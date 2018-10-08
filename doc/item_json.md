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

## Old Xml Parameter

```
<Parameter ParType="double" ParRole="0" ParValue="5.970000000000e+2"/>
<Parameter ParType="ComboProperty" ParRole="0" ParValue="1" ParExt="Basic;No"/>
<Parameter ParType="ExternalProperty" ParRole="0" Text="example01_Air" Color="#ffb3f2ff" Identifier="{3a9b9a8a-54a3-45f7-ad22-1f6167d6c5c8}"/>
<Parameter ParType="ComboProperty" ParRole="0" ParValue="5" ParExt="Aniso Pyramid;Box;Cone;Cone6;Cuboctahedron;Cylinder;Dodecahedron;Dot;Ellipsoidal Cylinder;Full Sphere;Full Spheroid;Hemi Ellipsoid;Icosahedron;Prism3;Prism6;Pyramid;Ripple1;Ripple2;Tetrahedron;Truncated Cube;Truncated Sphere;Truncated Spheroid"/>
<Parameter ParType="bool" ParRole="0" ParValue="0"/>

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

## Example n.1

+ Original XML

```
<Item ModelType="MultiLayer" Tag="rootTag" DisplayName="MultiLayer">
   <Item ModelType="Property" Tag="xpos" DisplayName="xpos">
       <Parameter ParType="double" ParRole="0" ParValue="1.850000000000e+1"/>
   </Item>
</Item>

```

+ It's json equivalent

```
{
    "modelType" : "MultiLayer",
    "Tag" : "rootTag",
    "displayName" : "MultiLayer"
    "items" : [
        {
        "modelType" : "PropertyItem",
        "Tag" : "xpos",
        "displayName" : "xpos"
        "parameter" : {
            "role" : displayRole,
            "value" : "xpos"
        }
    ]
}
```

+ Extended equivalent

```
{
    "modelType" : "MultiLayer",
    "Tag" : "rootTag",
    "itemData" : [
        {
            "role" : displayRole,
            "value" : "MultiLayer"
        }
    ],
    "children" : [
        {
            "modelType" : "PropertyItem",
            "tag" : "xpos",
            "itemData" : [
                {
                    "role" : displayRole,
                    "variant" : "string",
                    "value" : "xpos"
                },
                {
                    "role" : dataRole,
                    "variant" : {
                        "type" : "string",
                        "value" : "abc",
                    }
                }
            ]
        },
    ]
}

```

+ Many models

```
{
    "models" : [
        {
            "modelType" : "MaterialModel",
            "items" : [
                {

                }
            ]
        }
    ]
}


```

