#pragma once

#include "Mesh.hpp"
#include "VertexLayout.hpp"

// Here code is being mixed with data, maybe not good

namespace swheel::commonLayouts {
    class Position {
    public:
        static VertexPropertyView<propertyUnion::Triple> GetPosition(Mesh& mesh);
        static const VertexLayout& Layout() { return s_layout; }

    private:
        Position();
    
    private:
        static const VertexLayout s_layout;
    };

    class PositionUV {
    public:
        static VertexPropertyView<propertyUnion::Triple> GetPosition(Mesh& mesh);
        static VertexPropertyView<propertyUnion::Pair>   GetUV(Mesh& mesh);
        static const VertexLayout& Layout() { return s_layout; }

    private:
        PositionUV();
    
    private:
        static const VertexLayout s_layout;
    };

    class PositionColor {
    public:
        static VertexPropertyView<propertyUnion::Triple> GetPosition(Mesh& mesh);
        static VertexPropertyView<propertyUnion::Quad>   GetColor(Mesh& mesh);
        static const VertexLayout& Layout() { return s_layout; }

    private:
        PositionColor();
    
    private:
        static const VertexLayout s_layout;
    };

    class PositionUVColor {
    public:
        static VertexPropertyView<propertyUnion::Triple> GetPosition(Mesh& mesh);
        static VertexPropertyView<propertyUnion::Pair>   GetUV(Mesh& mesh);
        static VertexPropertyView<propertyUnion::Quad>   GetColor(Mesh& mesh);
        static const VertexLayout& Layout() { return s_layout; }

    private:
        PositionUVColor();
    
    private:
        static const VertexLayout s_layout;
    };
}
