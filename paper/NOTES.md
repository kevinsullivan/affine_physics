http://docs.ros.org/melodic/api/geometry_msgs/html/msg/Vector3.html

# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z

http://docs.ros.org/melodic/api/geometry_msgs/html/msg/Vector3Stamped.html

# This represents a Vector3 with reference coordinate frame and timestamp
Header header
Vector3 vector


http://docs.ros.org/melodic/api/std_msgs/html/msg/Header.html

# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

Note: crappy cohesion

http://docs.ros.org/melodic/api/geometry_msgs/html/msg/TransformStamped.html

# This expresses a transform from coordinate frame header.frame_id
# to the coordinate frame child_frame_id
#
# This message is mostly used by the 
# tf package. 
# See its documentation for more information.

Header header
string child_frame_id # the frame id of the child frame
Transform transform

http://docs.ros.org/melodic/api/geometry_msgs/html/msg/Point.html

# This contains the position of a point in free space
float64 x
float64 y
float64 z

Can I write a 20 line ROS program in which a translation transformation is applied to a vector