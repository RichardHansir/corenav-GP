#ifndef GP_PREDICTOR_H_
#define GP_PREDICTOR_H_

#include <Eigen/Dense>
#include <Eigen/Geometry>


#include <ros/ros.h>
#include <ros/console.h>
#include "std_msgs/Int64.h"
#include <std_msgs/Bool.h>
#include <core_nav/SetStopping.h>
#include <core_nav/GP_Input.h>
#include <core_nav/GP_Output.h>
#include <std_msgs/Float64.h>


class GpPredictor
{
public:

  GpPredictor(ros::NodeHandle &);

  typedef Eigen::Matrix<double, 3, 1> Vector3;
  typedef Eigen::MatrixXd Matrix;

  void mobility(bool flag);
  void mobilityCallback(const std_msgs::Int64::ConstPtr& msg);
  void GPCallBack(const core_nav::GP_Output::ConstPtr& gp_data_in_);
  bool LoadParameters(const ros::NodeHandle& nh_);
  GpPredictor::Vector3 llh_to_enu(const double latitude, const double longitude, const double height);

  core_nav::GP_Input slip_msg;
  core_nav::GP_Output gp_data_;

  Eigen::Matrix<double, 4, 4> R_IP;
  Eigen::Matrix<double, 4, 4> R_IP_1;
  Eigen::Matrix<double, 4, 4> R_IP_2;
  Eigen::Matrix<double, 15, 4> K_pred;
  Eigen::Matrix<double, 4, 15> H_;
  Eigen::Matrix<double, 15, 15> P_pred;
  Eigen::Matrix<double, 15, 15> STM_;
  Eigen::Matrix<double, 15, 15> Q_;

  GpPredictor::Vector3 savePos, ins_enu_slip, ins_enu_slip3p, ins_enu_slip_3p;
  std_msgs::Float64 stop_cmd_msg_;

  bool new_gp_data_arrived_;
  bool gp_flag = false;
  double gp_arrived_time_;
  double xy_errSlip,odomUptCount, startRecording, stopRecording, saveCountOdom;
  double init_ecef_x,init_ecef_y,init_ecef_z,init_x, init_y, init_z;
  int slip_i=0;
  int i=0;
  
private:
  ros::Subscriber gp_sub_;
  ros::Publisher stop_cmd_pub_;
  ros::ServiceClient clt_setStopping_;
  ros::NodeHandle & nh_;

};
int main(int argc, char **argv);

#endif //GP_PREDICTOR_H_
