#include "swpch.hpp"
#include "CommonVertexLayouts.hpp"

#include "SmallWheel/Core.hpp"
#include "VertexLayout.hpp"

namespace swheel::commonLayouts {
    const VertexLayout Position::s_layout = VertexLayout({
        {VertexPropertyType::Float3, "pos"}
    });

    VertexPropertyView<propertyUnion::Triple> Position::GetPosition(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Triple>("pos");
    }

    const VertexLayout PositionUV::s_layout = VertexLayout({
        {VertexPropertyType::Float3, "pos"},
        {VertexPropertyType::Float2, "uv"}
    });

    VertexPropertyView<propertyUnion::Triple> PositionUV::GetPosition(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Triple>("pos");
    }
    
    VertexPropertyView<propertyUnion::Pair> PositionUV::GetUV(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Pair>("uv");
    }

    const VertexLayout PositionColor::s_layout = VertexLayout({
        {VertexPropertyType::Float3, "pos"},
        {VertexPropertyType::Float4, "col"}
    });

    VertexPropertyView<propertyUnion::Triple> PositionColor::GetPosition(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Triple>("pos");
    }

    VertexPropertyView<propertyUnion::Quad> PositionColor::GetColor(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Quad>("col");
    }

    const VertexLayout PositionUVColor::s_layout = VertexLayout({
        {VertexPropertyType::Float3, "pos"},
        {VertexPropertyType::Float2, "uv"},
        {VertexPropertyType::Float4, "col"}
    });

    VertexPropertyView<propertyUnion::Triple> PositionUVColor::GetPosition(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Triple>("pos");
    }

    VertexPropertyView<propertyUnion::Pair> PositionUVColor::GetUV(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Pair>("uv");
    }

    VertexPropertyView<propertyUnion::Quad> PositionUVColor::GetColor(MeshData& mesh) {
        SW_ASSERT_LOG(&mesh.GetLayout() == &s_layout, "Wrong mesh layout type!");
        return mesh.GetPropertyView<propertyUnion::Quad>("col");
    }
}
