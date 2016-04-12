s_lib
===========

个人开发过程中一些跨平台通用库与DEMO的合集，有兴趣希望大家可以将自己的代码片段传上来一起完善这个库。
这个库讲究是简单易用，不追求效率，方便开发过程中插入进行代码测试，日志打印等功能。


第三方相关库说明
------

引用boost_1_58_0

文件夹说明
------

src: 		一些个人常用库
examples:	库的使用例子，以及一些其他平时使用的DEMO，编译部分DEMO可能需要引入其他第三方库，请根据实际情况自己配置。

使用方法
------

直接复制src中所需要的文件添加到工程中即可使用。

封装库说明
------

file_operation.hpp		文件读写，创建等操作，demo见example_file_op
simpleini				INI格式文件读写操作，demo见example_simple_ini
string_operation.hpp	字符串格式转换，分割等操作，demo见example_string_op

demo说明
------

example_file_op			file_operation.hpp使用demo
example_simple_ini		simpleini使用demo
example_string_op		string_operation.hpp使用demo
example_glog			glog使用demo
