#include "..\lua53\lua.hpp"
#include<iostream>

using namespace std;

void main() {
	lua_State* l = luaL_newstate();
	
	//lua_pushlstring ʹ��
	lua_pushlstring(l, "abcd",5);
	size_t* length = nullptr;
	
	const char* a = lua_tolstring(l, -1,length);


	//lua_pushstring ʹ��
	lua_pushstring(l, "bcdef");
	const char* b = lua_tostring(l, -1);
	system("pause");
}