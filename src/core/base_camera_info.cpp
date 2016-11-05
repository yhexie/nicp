#include "base_camera_info.h"

namespace nicp {

  using namespace std;

  BaseCameraInfo::BaseCameraInfo(const std::string& topic_,
				 const std::string& frame_id,
				 const Eigen::Isometry3f&offset_,
				 float depth_scale_,
				 int id,
				 nicp::IdContext* context):   nicp::Identifiable(id,context){
    _offset = offset_;
    _topic = topic_;
    _frame_id = frame_id;
    _depth_scale = depth_scale_;
  }

  BaseCameraInfo* BaseCameraInfo::scale(float ) { return 0; }

  void BaseCameraInfo::serialize(nicp::ObjectData& data, nicp::IdContext& context){
    Identifiable::serialize(data,context);
    data.setString("topic",_topic);
    data.setFloat("depth_scale",_depth_scale);
    t2v(_offset).toBOSS(data, "offset");
  }

  void BaseCameraInfo::deserialize(nicp::ObjectData& data, nicp::IdContext& context){
    Identifiable::deserialize(data,context);
    _topic = data.getString("topic");
    _depth_scale = data.getFloat("depth_scale");
    Vector6f v;
    v.fromBOSS(data, "offset");
    _offset = v2t(v);
  }

  BOSS_REGISTER_CLASS(BaseCameraInfo);

}


