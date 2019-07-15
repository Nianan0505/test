# GeRoNa框架配置

GeRoNa：Generic Robot Navigation是一个开源的导航算法框架，可在建图定位的基础上导航，该框架的配置流程如下：

## 打开仿真环境

在工作空间内下载cirkit_unit03:

`cd <catkin_ws>/src`

`git clone git@gitee.com:csc105_slam_group/cirkit_unit03_pkgs.git `

`git clone git@gitee.com:csc105_slam_group/cirkit_unit03_apps.git`

`git clone git@gitee.com:csc105_slam_group/cirkit_uint03_deps.git`

需要下载pkgs/apps/deps三个文件，

`cd <catkin_ws>`

`catkin_make`

`source devel/setup.bash`

`roslaunch cirkit_unit03_autorun autorun_gazebo_playpen.launch `

这时打开了gazebo和rviz

![image][https://github.com/Nianan0505/test/blob/master/img/01.png]

![image][https://github.com/Nianan0505/test/blob/master/img/02.png]

## 开启定位

在工作空间内下载location：

`cd <catkin_ws>/src`

`git clone git@gitee.com:csc105_slam_group/location.git`

编译之前需要切换分支，默认是master，需要切换到gazebo_cirkit

`git checkout gazebo_cirkit`

可以单独编译location

`cd <catkin_ws>`

`catkin_make -DCATKIN_WHITELIST_PACKAGES="location"`

会出现缺少包的问题，查看CMakeLists发现还需要装lidar_correction  ndt_omp receive_xsens  lidar_correction 需要什么从码云上下载即可，例如

`git clone git@gitee.com:csc105_slam_group/receive_xsens.git`

下载后需要建立map文件夹，可以从码云上location的附件中下载

下载地址https://gitee.com/csc105_slam_group/location/attach_files

每个地图包含三个文件：用于定位的\*\*\*.pcd 和 用于导航的配置文件\*\*\*.yaml 和 静态地图 ***.pgm， yaml文件如下，可通过修改image的名字换不同的静态地图。

> image: gazebo_cirkit1.pgm
> resolution: 0.050000
> origin: [-54.850001, -59.749998, -0.0]
> negate: 0
> occupied_thresh: 0.65
> free_thresh: 0.196

然后运行

`source devel/setup.bash`

`roslaunch location locationV2.launch`

在rviz中用2D Pose Estimate给一个初始位置

## 开启导航

GeRoNa依赖cslibs_path_planning和cslibs_utils两个包，需要下载编译：

`cd <catkin_ws>/src`

`git clone git@gitee.com:csc105_slam_group/GeRoNa.git`

`git clone git@gitee.com:csc105_slam_group/cslibs_path_planning.git`

`git clone git@gitee.com:csc105_slam_group/cslibs_utils.git`

`catkin_make`

这一步可能会提醒缺少库，例如ALGLIB，安装即可

`sudo apt-get install libalglib-dev`

`sudo apt-get install ros-kinetic-xxx`

需要source

`source devel/setup.bash`

然后运行`roslaunch navigation_launch navigation_cirkit.launch `

在rviz给一个初始位置，打开PointCloud2的/velodyne_points话题，看定位有没有偏移

然后打开一个新的窗口，当打开新窗口后要source

`source devel/setup.bash`

`roslaunch path_follower follower_cirkit.launch`

用2D Nav Goal给一个目标点，就开始规划路线啦

要注意当开启新的path_follower后都要重新给目标点。

关于navigation_cirkit.launch，开启了high level和path_control的launch，可以把path_planner和path_follower的都加进去，gerona具体内容可以参考：https://github.com/cogsys-tuebingen/gerona/wiki
