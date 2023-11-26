#include "..\lua53\lua.hpp"
#include<stdio.h>
#include<iostream>

using namespace std;

struct ColorTable
{
	char* name;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} ct[] = {
	{"WHITE",1,1,1},
	{"RED",1,0,0},
	{"NULL",0,0,0},
	
};

//创建一个table 压入 lua环境中去
void setColor(lua_State* l, ColorTable* ct) {
	lua_newtable(l);
	lua_pushnumber(l, ct->red);
	lua_setfield(l, -2, "r");

	lua_pushnumber(l, ct->green);
	lua_setfield(l, -2, "g");

	lua_pushnumber(l, ct->blue);
	lua_setfield(l, -2, "b");

	lua_setglobal(l, ct->name);//弹出talbe，并修改表的名字
}



//加载lua文件
void load(lua_State* l, const char* name, int* w, int* h) {
	if (luaL_loadfile(l, name) || lua_pcall(l, 0, 0, 0)) {
		printf("cannot run lua file : %s\n", lua_tostring(l, -1));
	}
	lua_getglobal(l, "width");
	if (!lua_isnumber(l, -1)) {
		//输出错误信息
	}

	lua_getglobal(l, "height");
	if (!lua_isnumber(l, -1)) {
		//同上
	}

	*w = lua_tonumber(l, -2);
	*h = lua_tonumber(l, -1);

	lua_settop(l, 0);//清空栈
}



void main() {
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	int w = 0;
	int h = 0;
	load(l, "D:\\IDE\\vsproject\\Lua\\Lua与C交互学习\\交互\\test.lua", &w, &h);

	////////////////////////////从Lua文件中获取

	lua_getglobal(l, "bg");//获取 bg {},
	lua_pushstring(l, "r");//压入 key “r”
	lua_gettable(l, -2);//获取 bg[r]
	cout << lua_gettop(l) << endl;
	double red = lua_tonumber(l, -1);
	
	cout << lua_gettop(l) << endl;
	lua_settop(l, 1);
	

	//获取 bg[g]
	lua_pushstring(l, "g");
	lua_gettable(l, -2);
	double green = lua_tonumber(l, -1);


	////获取 bg[b]
	lua_settop(l, 1);
	/*lua_pushstring(l, "b");
	lua_gettable(l, -2);*/

	//可换为
	lua_getfield(l, -1, "b");//由于没有向栈中 压入 key，故table 位于-1
	double blue = lua_tonumber(l, -1);

	////////////////////////////往Lua文件中添加table

	int count = 0;
	while (ct[count].name != NULL) {
		setColor(l, &ct[count++]);
	}

	//此时再从Lua环境获取刚刚添加的 Color
	lua_getglobal(l, "WHITE");
	lua_pushstring(l, "r");//压入 key “r”
	lua_gettable(l, -2);//获取 bg[r]
	cout << lua_tonumber(l, -1) << endl;

	lua_settop(l, 0);//清空栈
	//////////////////////从C中调用Lua中的函数 f(x,y)
	lua_getglobal(l,"f");//拿到函数指针
	lua_pushnumber(l, 1.0);//压入x
	lua_pushnumber(l, 4);//y
	int ret = lua_pcall(l, 2, 2, 0);//2 parameters，1 return value
	if (ret != 0) {
		cout << "函数调用出错！" << endl;
	}
	cout << "现在栈的深度：" << lua_gettop(l) << endl;
	double result1 = lua_tonumber(l, -2); // get first return value
	double result = lua_tonumber(l, -1); // get second return value
	
	cout << "函数f调用结果为："<<result1<<"和"<<result << endl;
	
	
	lua_settop(l, 0); //clear stack again

	lua_getglobal(l,"my_int_to_string");//find gloabl function f and put into the stack
	lua_pushnumber(l, 1234.0);//first parameter
	int ret2 = lua_pcall(l, 1, 1, 0);//2 parameters and 1 return value
	if (ret2 != 0) {
		cout << "function execute failed" << endl;
	}
	cout << "after call my_int_to_string, the number of elements in the stack :   " << lua_gettop(l) << endl;
	size_t ret_string_len = 0;
	const char* ret_string = lua_tolstring(l, -1, &ret_string_len);
	lua_settop(l, 0); //clear stack again
	
	
	system("pause");
}