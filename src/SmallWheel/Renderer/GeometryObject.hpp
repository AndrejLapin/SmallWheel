#pragma once

namespace swheel {
    class GeometryObject {
    public:
        // We can have verticies with indecies seperately from
        // the UV compoent and vertex color component, but need second opinon on that

        // Right now we need vertex position, UV, and that's it
        // Maybe Normals later too?

        // So maybe we create it by pushing data and layout to this object and then?
        // So should geometry objects be tied to shaders then?

        // this gets created with a layout
        GeometryObject();
    };
}