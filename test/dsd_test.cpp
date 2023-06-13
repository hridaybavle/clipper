/**
 * @file sdp_test.cpp
 * @brief Point Cloud CLIPPER SDR tests
 * @author Parker Lusk <plusk@mit.edu>
 * @date 12 June 2023
 */

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <clipper/dsd.h>

TEST(DSD, Solve) {
  std::vector<int> dsd_nodes = { 3, 5, 12, 14, 15 }; // true nodes
  Eigen::MatrixXd M(20, 20);
  M << 1.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.2964, 0.    ,
       0.    , 1.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0138, 0.    , 0.    , 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 1.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0016, 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0747, 0.    ,
       0.    , 0.    , 0.    , 1.    , 0.    , 0.0555, 0.2547, 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0102, 0.    , 0.7715, 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 1.    , 0.0063, 0.    , 0.3846, 0.    , 0.0003, 0.0014, 0.    , 0.    , 0.    , 0.    , 0.0063, 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.0555, 0.0063, 1.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.9927, 0.    , 0.    , 0.9722, 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.2547, 0.    , 0.    , 1.    , 0.    , 0.0023, 0.    , 0.    , 0.8775, 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.3846, 0.    , 0.    , 1.    , 0.0001, 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0023, 0.0001, 1.    , 0.7914, 0.    , 0.    , 0.    , 0.0617, 0.    , 0.    , 0.9938, 0.    , 0.    , 0.0007,
       0.    , 0.    , 0.    , 0.    , 0.0003, 0.    , 0.    , 0.    , 0.7914, 1.    , 0.    , 0.    , 0.0001, 0.0091, 0.    , 0.2503, 0.0222, 0.0549, 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.0014, 0.    , 0.    , 0.    , 0.    , 0.    , 1.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0008,
       0.    , 0.    , 0.0016, 0.    , 0.    , 0.    , 0.8775, 0.    , 0.    , 0.    , 0.    , 1.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.7007, 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.    , 0.9927, 0.    , 0.    , 0.    , 0.0001, 0.    , 0.    , 1.    , 0.    , 0.9978, 0.    , 0.    , 0.    , 0.    , 0.    ,
       0.    , 0.0138, 0.    , 0.0102, 0.    , 0.    , 0.    , 0.    , 0.0617, 0.0091, 0.    , 0.    , 0.    , 1.    , 0.    , 0.    , 0.    , 0.0003, 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.9978, 0.    , 1.    , 0.0012, 0.    , 0.    , 0.    , 0.0074,
       0.    , 0.    , 0.    , 0.7715, 0.0063, 0.9722, 0.    , 0.    , 0.    , 0.2503, 0.    , 0.    , 0.    , 0.    , 0.0012, 1.    , 0.0026, 0.0217, 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.9938, 0.0222, 0.    , 0.    , 0.    , 0.    , 0.    , 0.0026, 1.    , 0.    , 0.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0549, 0.    , 0.    , 0.    , 0.0003, 0.    , 0.0217, 0.    , 1.    , 0.0007, 0.    ,
       0.2964, 0.    , 0.0747, 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.7007, 0.    , 0.    , 0.    , 0.    , 0.    , 0.0007, 1.    , 0.    ,
       0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.    , 0.0007, 0.    , 0.0008, 0.    , 0.    , 0.    , 0.0074, 0.    , 0.    , 0.    , 0.    , 1.    ;

  std::vector<int> nodes = clipper::dsd::solve(M);

  ASSERT_EQ(nodes.size(), dsd_nodes.size());
  for (size_t i=0; i<nodes.size(); ++i) {
    EXPECT_EQ(nodes[i], dsd_nodes[i]);
  }
}
