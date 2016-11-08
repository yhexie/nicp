#pragma once

#include "boss/eigen_boss_plugin.h"
#include "core/cloud.h"
#include "binary_node_relation.h"
#include "map_node_list.h"

namespace nicp {

  class LocalMap : public MapNode{
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    LocalMap(const Eigen::Isometry3f& transform=Eigen::Isometry3f::Identity(), 
	     int id=-1,
	     nicp::IdContext* context=0);

    virtual ~LocalMap();
 
    virtual void draw(DrawAttributesType attributes=ATTRIBUTE_SHOW, int name = -1);
    inline Cloud* cloud() { return _cloud_ref.get(); }
    inline void setCloud(Cloud* c) { _cloud_ref.set(c); }

    inline MapNodeList& nodes() {return _nodes; }
    inline const MapNodeList& nodes() const {return _nodes; }
    inline BinaryNodeRelationSet& relations() {return _relations;}

    virtual void push();
    virtual void pop();

    virtual void serialize(nicp::ObjectData& data, nicp::IdContext& context);
    virtual void deserialize(nicp::ObjectData& data, nicp::IdContext& context);
    inline CloudBLOBReference& cloudReference() { return _cloud_ref;}
  protected:
    // Nodes positions are expressed with respect to the local map position 
    MapNodeList _nodes;
    BinaryNodeRelationSet _relations;
    CloudBLOBReference _cloud_ref;
  };

}