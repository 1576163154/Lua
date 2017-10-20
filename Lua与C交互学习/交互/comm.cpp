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
	load(l, "test.lua", &w, &h);

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
	system("pause");
}