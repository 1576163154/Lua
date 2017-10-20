#include "..\lua53\lua.hpp"
#include<stdio.h>
#include<iostream>

using namespace std;






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
	load(l, "test.lua", &w, &h);

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
	system("pause");
}