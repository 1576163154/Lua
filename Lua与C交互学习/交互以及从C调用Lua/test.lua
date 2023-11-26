 width = 300
 height = 200
 --若设置为 局部变量 这无法通过 C/C++ 环境进行获取


 --颜色例子
 bg = {
 r = 0.30,
 g = 0.10,
 b = 0,
 }

 --配置常用颜色
 BLUE = {r=0,b=0,g=1}

 function f(x,y )
 local a =  (x+y^2)
 local b = (x^2 + y)
	return a,b
end

--convert a number to c style string
--@a number
function my_int_to_string(a)
	return tostring(a)
end
