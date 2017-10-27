#include<iostream>
#include"..\lua53\lua.hpp"

using namespace std;

int l_map(lua_State* l) {
	int i;
	
	luaL_checktype(l, 1, LUA_TTABLE);//��һ������������һ��table
	luaL_checktype(l, 2, LUA_TFUNCTION);// ��           ����

	int n = lua_rawlen(l, 1);

	for (i = 1; i <= n; i++) {
		lua_pushvalue(l, 2);
		lua_rawgeti(l, 1, i);
		lua_call(l, 1, 1);
		lua_rawseti(l, 1, i);
	}

	return 0; //�޽��
}

static int l_split(lua_State* l) {
	const char* s = luaL_checkstring(l, 1);
	const char* sep = luaL_checkstring(l, 2);
	const char* e;
	int i = 1;


	lua_newtable(l);//����һ��table�ŵ�ջ��

	while((e == strchr(s, *sep)) != NULL) {
		lua_pushlstring(l, s, e - s);
		lua_rawseti(l, -2, i++);
		s = e + 1;
	}

	lua_pushstring(l, s);
	lua_rawseti(l, -2, i);

	return 1;


}

void main() {
	lua_State* l =  luaL_newstate();
	luaL_openlibs(l);

	//load lua file
	luaL_loadfile(l, "D:\\GitHub\\Lua\\Lua��C����ѧϰ\\��дC�����ļ���\\test.lua");

	lua_pushcfunction(l, l_map);
	lua_setglobal(l, "mapSquare");

	luaL_dofile(l, "D:\\GitHub\\Lua\\Lua��C����ѧϰ\\��дC�����ļ���\\test.lua");

	system("pause");
}