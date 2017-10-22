#include "..\lua53\lua.hpp" 
#include<iostream>


using namespace std;

//求一个数的平方
static int square(lua_State* l) {
	

	//double a = lua_tonumber(l, 1);//获取参数
	//也可以用
	double a = luaL_checknumber(l, 1);

	//进行处理，并将结果压入
	lua_pushnumber(l, a*a);
	return 1;//返回值表示，结果的数量，便于和栈中其他的值区分开

	//return 后，栈中函数结果以下的元素会弹出栈，即保证函数调用结果从1开始
}


//分别求两个数的平方
static int twoSquare(lua_State* l) {
	double a = luaL_checknumber(l, 1);
	double b = luaL_checknumber(l, 2);
	lua_pushnumber(l, a*a);
	lua_pushnumber(l, b*b);
	return 2;
}

//C函数 数组
static const  luaL_Reg CFuncs[] = {
	{"square",square},
	{"twoSquare",twoSquare},
	{0,0}, //这样结尾
};


void main() {
	
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	
	//load lua file
	luaL_loadfile(l, "D:\\IDE\\vsproject\\Lua\\Lua与C交互学习\\从Lua调用C函数\\test.lua");

	//注册C函数，传递函数地址到Lua环境
	lua_pushcfunction(l, square);
	lua_setglobal(l, "square");//并将函数名设置为 “square”（全局）

	 //将多个C函数，以一个模块的形式注册到Lua
	lua_pushcfunction(l, twoSquare);
	lua_setglobal(l, "twoSquare");

	luaL_dofile(l, "D:\\IDE\\vsproject\\Lua\\Lua与C交互学习\\从Lua调用C函数\\test.lua");


	
	



	system("pause");
}