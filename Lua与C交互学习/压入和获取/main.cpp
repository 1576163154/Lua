#include "..\lua53\lua.hpp"
#include<stdio.h>
#include<assert.h>
#include<iostream>

using namespace std;




void main() {
	lua_State* l = luaL_newstate();
	
	//lua_pushlstring 
	char* abc = "abcd";
	lua_pushlstring(l, abc,strlen(abc)+1);

	size_t length = 0;
	
	const char* a = lua_tolstring(l, -1,&length);
	assert(strlen("abcd") < length);
	assert(a[length] == '\0');

	//不使用长度信息
	lua_pushlstring(l, abc, 5);
	size_t length2;
	const char* c = lua_tolstring(l, -1,0);//将第三个参数 填为NULL 或 0

	//lua_pushstring 
	lua_pushstring(l, "bcdef");
	
	const char* b = lua_tostring(l, -1);


	//其他栈的操作
	cout << lua_gettop(l) << endl;//获取栈中元素个数
	//lua_settop(l, 0);
	//cout << lua_gettop(l) << endl;
	lua_pushvalue(l, -3);
	printf("%s\n", lua_tostring(l, -1));
	lua_remove(l, -1);
	printf("%s\n", lua_tostring(l, -1));

	
	system("pause");
}